/*
 * Copyright © 2008  Red Hat, Inc. All rights reserved.
 * Copyright © 2008  Ding-Yi Chen <dchen at redhat dot com>
 *
 * This file is part of the libUnihan Project.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 */

#include "config.h"
#include <stdio.h>
#include <sqlite3.h>
#include "Unihan.h"
#include "allocate.h"
#include "verboseMsg.h"
#include "file_functions.h"
#include "Unihan_phonetic.h"

#define MAX_BUFFER_SIZE 2000
static sqlite3 *unihanDb=NULL;

#include "Unihan_SQL_funcs.c"
#include "Unihan_SQL_gen.c"
#define UNIHAN_FIELD_ARRAY_MAX_LEN 10
#define UNIHAN_TABLE_ARRAY_MAX_LEN 100

/*=================================
 * Unihan character functions.
 */

gboolean unihanChar_has_property(gunichar code, UnihanField field){
    if (field==UNIHAN_FIELD_CODE){
	return TRUE;
    }
    char buf[20];
    g_snprintf(buf,20,"%d",code);
    char *ret=unihan_find_first_matched(UNIHAN_FIELD_CODE, buf, field, UNIHAN_QUERY_OPTION_DEFAULT);
    if ((ret!=NULL) && strlen(ret)>0){
	return TRUE;
    }
    return FALSE;
}

gboolean unihanChar_is_in_source(gunichar code, UnihanIRG_SourceId source){
    char buf[MAX_BUFFER_SIZE];
    UnihanTable fromTable=unihanField_get_table(UNIHAN_FIELD_IRG_SOURCE_MAPPING);

    g_snprintf(buf,MAX_BUFFER_SIZE,"SELECT %s FROM %s WHERE code='%d' AND %s='%s';",
	    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_MAPPING],
	    UNIHAN_TABLE_NAMES[fromTable],
	    code,UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
	    UNIHAN_IRG_SOURCES[source].name);

    char *errMsg=NULL;
    int ret=unihanSql_count_matches(buf,&errMsg);
    if (ret>0){
	return TRUE;
    }
    if (ret<0){
	verboseMsg_print(VERBOSE_MSG_WARNING, "unihanChar_is_in_source(%d,%d): %s\n",code,source,errMsg);
	sqlite3_free(errMsg);
    }
    return FALSE;
}

UnihanIRG_SourceId unihanChar_is_in_sources(gunichar code, UnihanIRG_SourceId source, ...){
    va_list options;
    UnihanIRG_SourceId src=source;
    va_start(options,source);
    while( src >= 0 ) {
	if (unihanChar_is_in_source(code,src)){
	    return src;
	}
	src = va_arg( options, UnihanIRG_SourceId); 
    }
    va_end(options);
    return UNIHAN_INVALID_SOURCEID;

}

UnihanRange unihanChar_in_range(gunichar code){
    if (code<0x3400){
	return UNIHAN_INVALID_RANGE;
    }else if (code<=0x4DB5){
	return UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS_EXT_A;
    }else if (code<0x4E00){
	return UNIHAN_INVALID_RANGE;
    }else if (code<=0x9FA5){
	return UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS;
    }else if (code<=0x9FBB){
	return UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS_4_1;
    }else if (code<=0x9FC3){
	return UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS_5_1;
    }else if (code<0xF900){
	return UNIHAN_INVALID_RANGE;
    }else if (code<=0xFA2D){
	return UNIHAN_RANGE_CJK_COMPATIBILITY_UNIFIED_IDEOGRAPHS_A;
    }else if (code<0xFA30){
	return UNIHAN_INVALID_RANGE;
    }else if (code<=0xFA6A){
	return UNIHAN_RANGE_CJK_COMPATIBILITY_UNIFIED_IDEOGRAPHS_B;
    }else if (code<0xFA70){
	return UNIHAN_INVALID_RANGE;
    }else if (code<=0xFAD9){
	return UNIHAN_RANGE_CJK_COMPATIBILITY_UNIFIED_IDEOGRAPHS_4_1;
    }else if (code<0x20000){
	return UNIHAN_INVALID_RANGE;
    }else if (code<=0x2A6D6){
	return UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS_EXT_B;
    }else if (code<0x2F800){
	return UNIHAN_INVALID_RANGE;
    }else if (code<=0x2FA1D){
	return UNIHAN_RANGE_CJK_COMPATIBILITY_SUPPLEMENT;
    }
    return UNIHAN_INVALID_RANGE;
}

gunichar unihanChar_parse(const char *str){
    char codeBuf[15];
    subString(codeBuf,str,2,strlen(str)-2);
    long code=strtol(codeBuf,(char**) NULL,16);
    return (gunichar) code;
}

char *unihanChar_to_scalar_string(gunichar code){
    GString *strBuf=g_string_new("U+");
    g_string_append_printf(strBuf,"%X",code);
    return g_string_free(strBuf,FALSE);
}

/*=================================
 * Sqlite DB file functions.
 */
#ifndef SQLITE_OPEN_READONLY
#define SQLITE_OPEN_READONLY         0x00000001
#endif

#ifndef SQLITE_OPEN_READWRITE
#define SQLITE_OPEN_READWRITE        0x00000002
#endif

#ifndef SQLITE_OPEN_CREATE
#define SQLITE_OPEN_CREATE           0x00000004
#endif


int unihanDb_open(const char *filename, int flags){
    int ret=0;
#ifdef HAVE_SQLITE3_OPEN_V2    
    ret = sqlite3_open_v2(filename, &unihanDb, flags, NULL);
#else
    if (flags & SQLITE_OPEN_READONLY ){
	if (!isReadable(filename)){
	    verboseMsg_print(VERBOSE_MSG_ERROR, "unihanDb_open(%s,%d): File is not readable\n", 
		    filename,flags);
	    return -1;
	}
    }else if (flags & SQLITE_OPEN_CREATE){
	if (!isWritable(filename)){
	    verboseMsg_print(VERBOSE_MSG_ERROR, "unihanDb_open(%s,%d): File is not writable\n", 
		    filename,flags);
	    return -2;
	}
    }else if (flags & SQLITE_OPEN_READWRITE ){
	if (!isReadable(filename)){
	    verboseMsg_print(VERBOSE_MSG_ERROR, "unihanDb_open(%s,%d): File is not readable\n", 
		    filename,flags);
	    return -1;
	}
	if (!isWritable(filename)){
	    verboseMsg_print(VERBOSE_MSG_ERROR, "unihanDb_open(%s,%d): File is not writable\n", 
		    filename,flags);
	    return -2;
	}
    }
    sqlite3_open(filename, &unihanDb);
#endif

    if (ret) {
	verboseMsg_print(VERBOSE_MSG_ERROR, "unihanDb_open(%s,%d): %s\n", 
		filename,flags,sqlite3_errmsg(unihanDb));
	sqlite3_close(unihanDb);
	unihanDb=NULL;
	return ret;
    }

    int i=0;
    for(i=0; DATABASE_FUNCS[i].argc!=0;i++){
	ret = sqlite3_create_function(unihanDb,DATABASE_FUNCS[i].funcName,
		DATABASE_FUNCS[i].argc,SQLITE_UTF8,NULL,
		DATABASE_FUNCS[i].func,DATABASE_FUNCS[i].stepFunc,DATABASE_FUNCS[i].finalizeFunc);
	if (ret) {
	    verboseMsg_print(VERBOSE_MSG_ERROR, "unihanDb_open(%s,%d): Cannot set function %s, Msg:%s\n",
		    filename,flags,DATABASE_FUNCS[i].funcName,sqlite3_errmsg(unihanDb));
	    sqlite3_close(unihanDb);
	    unihanDb=NULL;
	}
    }

    return ret;
}

int unihanDb_open_default(){
    return unihanDb_open(UNIHAN_DEFAULT_DB, SQLITE_OPEN_READONLY);
}

sqlite3 *unihanDb_get(){
    return unihanDb;
}

SQL_Result *unihanDb_get_tableNames(){
    g_assert(unihanDb);
    return sqlite_get_tableNames(unihanDb);
}

int unihanDb_close(){
    return sqlite3_close(unihanDb);
}

/*=================================
 * Field functions
 */
int unihanField_array_index(UnihanField field, const UnihanField* fieldArray){
    int i;
    for(i=0;fieldArray[i]>=0;i++){
	if (field==fieldArray[i]){
	    return i;
	}
    }
    return -1;
}

UnihanIRG_Source unihanField_get_IRG_source(UnihanField field){
    return (UnihanIRG_Source) unihanField_array_index(field,UNIHAN_IRG_SOURCE_FIELDS);
}

UnihanTable unihanField_get_table(UnihanField field){
    if (field==UNIHAN_INVALID_FIELD)
	return UNIHAN_INVALID_TABLE;
    if (unihanField_is_IRG_Source(field)){
	return UNIHAN_TABLE_IRG_SOURCE;
    }else{
	switch(field){
	    case UNIHAN_FIELD_CODE:
		return UNIHAN_AMBIGUOUS_TABLE;

	    case UNIHAN_FIELD_KANGXI_PAGE:
	    case UNIHAN_FIELD_KANGXI_CHARNUM:
	    case UNIHAN_FIELD_KANGXI_VIRTUAL:
		return UNIHAN_AMBIGUOUS_TABLE;

	    case UNIHAN_FIELD_PINYIN:
	    case UNIHAN_FIELD_PINYIN_FREQ:
		return UNIHAN_TABLE_KHANYUPINLU;

	    case UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME:
		return UNIHAN_TABLE_IRG_SOURCE;
	    case UNIHAN_FIELD_IRG_SOURCE_MAPPING:
		return UNIHAN_TABLE_IRG_SOURCE_MAPPING;

	    case UNIHAN_FIELD_VARIANT_CODE:
		return UNIHAN_AMBIGUOUS_TABLE;

	    case UNIHAN_FIELD_FROM_DICT:
	    case UNIHAN_FIELD_SEMANTIC_T:
	    case UNIHAN_FIELD_SEMANTIC_B:
	    case UNIHAN_FIELD_SEMANTIC_Z:
		return UNIHAN_AMBIGUOUS_TABLE;

	    case UNIHAN_FIELD_RADICAL_INDEX:
	    case UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT:
		return UNIHAN_AMBIGUOUS_TABLE;

	    case UNIHAN_FIELD_ADOBE_CID_CV:
	    case UNIHAN_FIELD_ADOBE_CID:
	    case UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT:
		return UNIHAN_TABLE_KRSADOBE_JAPAN1_6;

	    case UNIHAN_FIELD_FREQ_RANK:
		return UNIHAN_TABLE_KMANDARIN;
	    case UNIHAN_FIELD_ZVARIANT_SOURCE:
		return UNIHAN_TABLE_KZVARIANT_EXTRA;
	    case UNIHAN_FIELD_ZHUYIN:
		/* Zhuyin is converted from kMandarin */
		return UNIHAN_TABLE_KMANDARIN;
	    default:
		break;
	}
    }
    char buf[100];
    g_snprintf(buf,100,"%sTable",UNIHAN_FIELD_NAMES[field]);
    return unihanTable_parse(buf);
}

UnihanTable *unihanField_get_all_tables(UnihanField field){
    UnihanTable *tables=NEW_ARRAY_INSTANCE(UNIHAN_TABLE_ARRAY_MAX_LEN,UnihanTable);
    int i=0;
    if (field==-1){
	tables[0]=UNIHAN_INVALID_TABLE;
	return tables;
    }
    switch(field){
	case UNIHAN_FIELD_CODE:
	    for(i=0;i<UNIHAN_TABLES_COUNT;i++){
		tables[i]=i;
	    }
	    break;

	case UNIHAN_FIELD_KANGXI_PAGE:
	case UNIHAN_FIELD_KANGXI_CHARNUM:
	case UNIHAN_FIELD_KANGXI_VIRTUAL:
	    tables[i++]=UNIHAN_TABLE_KIRGKANGXI;
	    tables[i++]=UNIHAN_TABLE_KKANGXI;
	    break;

	case UNIHAN_FIELD_VARIANT_CODE:
	    tables[i++]=UNIHAN_TABLE_KCOMPATIBILITYVARIANT;
	    tables[i++]=UNIHAN_TABLE_KSIMPLIFIEDVARIANT;
	    tables[i++]=UNIHAN_TABLE_KTRADITIONALVARIANT;
	    tables[i++]=UNIHAN_TABLE_KSEMANTICVARIANT;
	    tables[i++]=UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT;
	    tables[i++]=UNIHAN_TABLE_KZVARIANT;
	    break;
	case UNIHAN_FIELD_FROM_DICT:
	case UNIHAN_FIELD_SEMANTIC_T:
	case UNIHAN_FIELD_SEMANTIC_B:
	case UNIHAN_FIELD_SEMANTIC_Z:
	    tables[i++]=UNIHAN_TABLE_KSEMANTICVARIANT;
	    tables[i++]=UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT;
	    break;
	case UNIHAN_FIELD_RADICAL_INDEX:
	case UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT:
	    tables[i++]=UNIHAN_TABLE_KRSADOBE_JAPAN1_6;
	    tables[i++]=UNIHAN_TABLE_KRSJAPANESE;	
	    tables[i++]=UNIHAN_TABLE_KRSKANGXI;	
	    tables[i++]=UNIHAN_TABLE_KRSKANWA;	
	    tables[i++]=UNIHAN_TABLE_KRSKOREAN;
	    tables[i++]=UNIHAN_TABLE_KRSUNICODE;
	    break;
	default:
	    tables[i++]=unihanField_get_table(field);
	    break;
    }
    tables[i]=UNIHAN_INVALID_TABLE;
    return tables;
}

UnihanTable unihanField_get_extra_table(UnihanField field){
    if (unihanField_is_IRG_Source(field))
	return UNIHAN_TABLE_IRG_SOURCE_MAPPING;
    switch(field){
	case UNIHAN_FIELD_KSEMANTICVARIANT:
	    return UNIHAN_TABLE_KSEMANTICVARIANT_EXTRA;
	case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
	    return UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT_EXTRA;
	case UNIHAN_FIELD_KZVARIANT:
	    return UNIHAN_TABLE_KZVARIANT_EXTRA;
	default:
	    break;
    }
    return UNIHAN_INVALID_TABLE;
}

gboolean unihanField_is_IRG_Source(UnihanField field){
    if (unihanField_get_IRG_source(field)>=0){
	return TRUE;
    }
    return FALSE;
}

gboolean unihanField_is_indexed(UnihanField field){
    if (unihanField_is_pseudo(field)){
	return FALSE;
    }
    if (field==UNIHAN_FIELD_KDEFINITION)
	return FALSE;
    return TRUE;
}

gboolean unihanField_is_integer(UnihanField field){
    if (unihanField_array_index(field,UNIHAN_INTEGER_FIELDS)>=0){
	return TRUE;
    }
    return FALSE;
}


gboolean unihanField_is_case_no_change(UnihanField field){
    if (unihanField_array_index(field,UNIHAN_CASE_NO_CHANGE_FIELDS)>=0){
	return TRUE;
    }
    return FALSE;
}

gboolean unihanField_is_lowercase(UnihanField field){
    if (unihanField_array_index(field,UNIHAN_LOWERCASE_FIELDS)>=0){
	return TRUE;
    }
    return FALSE;
}


gboolean unihanField_is_mandarin(UnihanField field){
    if (unihanField_array_index(field,UNIHAN_MANDARIN_FIELDS)>=0){
	return TRUE;
    }
    return FALSE;
}

gboolean unihanField_is_pseudo(UnihanField field){
    if (unihanField_is_IRG_Source(field)){
	return TRUE;
    }
    if (unihanField_array_index(field,UNIHAN_KVARIANT_FIELDS)>=0){
	return TRUE;
    }
    if (unihanField_array_index(field,UNIHAN_KRS_FIELDS)>=0){
	return TRUE;
    }
    switch(field){
	case UNIHAN_FIELD_KHANYUPINLU:
	case UNIHAN_FIELD_KIRGKANGXI:
	case UNIHAN_FIELD_KKANGXI:
	    return TRUE;
	case UNIHAN_FIELD_ZHUYIN:
	    return TRUE;
	default:
	    return FALSE;
    }
}

gboolean unihanField_is_ucs4(UnihanField field){
    if (unihanField_array_index(field,UNIHAN_UCS4_FIELDS)>=0){
	return TRUE;
    }
    return FALSE;
}


gboolean unihanField_is_singleton(UnihanField field){
    if (unihanField_array_index(field,UNIHAN_SINGLETON_FIELDS)>=0){
	return TRUE;
    }
    return FALSE;
}


UnihanField unihanField_parse(const char *str){
    int i;
    for(i=0;i<UNIHAN_FIELDS_COUNT;i++){
	if (g_ascii_strcasecmp (str,UNIHAN_FIELD_NAMES[i])==0){
	    return i;
	}
    }
    return UNIHAN_INVALID_FIELD;
}

const char* unihanField_to_string(UnihanField field){
    if (field==-1){
	return "Unknown field";
    }
    return UNIHAN_FIELD_NAMES[field];
}

/*=========================================================================
 * IRG_Source functions
 */

gboolean unihanIRG_Source_has_no_mapping(UnihanIRG_SourceId sourceId){
    int i;
    for (i=0;i<UNIHAN_NOINDEX_IRG_SOURCES_COUNT;i++){
	if (UNIHAN_NOINDEX_IRG_SOURCES[i]==sourceId)
	    return TRUE;
    }
    return FALSE;
}

const UnihanIRG_SourceData *unihanIRG_SourceData_get(UnihanIRG_SourceId sourceId){
    if (sourceId<0){
	return NULL;
    }
    return &UNIHAN_IRG_SOURCES[sourceId];
}


UnihanIRG_SourceId unihanIRG_SourceId_parse(const char *sourceShortName){
    int i;
    for(i=0;i<UNIHAN_SOURCES_COUNT;i++){
	if (g_ascii_strcasecmp (sourceShortName, UNIHAN_IRG_SOURCES[i].name)==0){
	    return i;
	}
    }
    return UNIHAN_INVALID_SOURCEID;
}

UnihanIRG_SourceRec *unihanIRG_SourceRec_parse(UnihanField field,const char *value){
    UnihanIRG_SourceRec *rec=NULL;
    char buf[20];
    char  **valueArray=NULL;
    gboolean invalidValue=FALSE;
    switch(field){
	case UNIHAN_FIELD_KIRG_GSOURCE:
	    valueArray=g_strsplit(value,"-",2);
	    rec=NEW_INSTANCE(UnihanIRG_SourceRec);
	    g_snprintf(buf,20,"G%s",valueArray[0]);
	    rec->sourceId= unihanIRG_SourceId_parse(buf);
	    if (valueArray[1]==NULL){
		invalidValue=TRUE;
		break;
	    }else{
		rec->sourceMapping=g_strdup(valueArray[1]);
	    }
	    break;
	case UNIHAN_FIELD_KIRG_HSOURCE:
	    rec=NEW_INSTANCE(UnihanIRG_SourceRec);
	    rec->sourceId= UNIHAN_SOURCE_H;
	    rec->sourceMapping=g_strdup(value);
	    break;
	case UNIHAN_FIELD_KIRG_JSOURCE:
	    valueArray=g_strsplit(value,"-",2);
	    rec=NEW_INSTANCE(UnihanIRG_SourceRec);
	    g_snprintf(buf,20,"J%s",valueArray[0]);
	    rec->sourceId= unihanIRG_SourceId_parse(buf);
	    if (valueArray[1]==NULL){
		invalidValue=TRUE;
		break;
	    }else{
		rec->sourceMapping=g_strdup(valueArray[1]);
	    }
	    break;
	case UNIHAN_FIELD_KIRG_KPSOURCE:
	    valueArray=g_strsplit(value,"-",2);
	    g_snprintf(buf,20,"%s",valueArray[0]);
	    rec=NEW_INSTANCE(UnihanIRG_SourceRec);
	    rec->sourceId= unihanIRG_SourceId_parse(buf);
	    if (valueArray[1]==NULL){
		invalidValue=TRUE;
		break;
	    }else{
		/* KP sources always has the prefix "KP" */
		rec->sourceMapping=g_strdup(valueArray[1]);
	    }
	    break;
	case UNIHAN_FIELD_KIRG_KSOURCE:
	    valueArray=g_strsplit(value,"-",2);
	    g_snprintf(buf,20,"K%s",valueArray[0]);
	    rec=NEW_INSTANCE(UnihanIRG_SourceRec);
	    rec->sourceId= unihanIRG_SourceId_parse(buf);
	    if (valueArray[1]==NULL){
		invalidValue=TRUE;
		break;
	    }else{
		rec->sourceMapping=g_strdup(valueArray[1]);
	    }
	    break;
	case UNIHAN_FIELD_KIRG_TSOURCE:
	    valueArray=g_strsplit(value,"-",2);
	    g_snprintf(buf,20,"T%s",valueArray[0]);
	    rec=NEW_INSTANCE(UnihanIRG_SourceRec);
	    rec->sourceId= unihanIRG_SourceId_parse(buf);
	    if (valueArray[1]==NULL){
		invalidValue=TRUE;
		break;
	    }else{
		rec->sourceMapping=g_strdup(valueArray[1]);
	    }
	    break;
	case UNIHAN_FIELD_KIRG_USOURCE:
	    rec=NEW_INSTANCE(UnihanIRG_SourceRec);
	    rec->sourceId= UNIHAN_SOURCE_U;
	    rec->sourceMapping=g_strdup(value);
	    break;
	case UNIHAN_FIELD_KIRG_VSOURCE:
	    valueArray=g_strsplit(value,"-",2);
	    g_snprintf(buf,20,"V%s",valueArray[0]);
	    rec=NEW_INSTANCE(UnihanIRG_SourceRec);
	    rec->sourceId= unihanIRG_SourceId_parse(buf);
	    if (valueArray[1]==NULL){
		invalidValue=TRUE;
		break;
	    }else{
		rec->sourceMapping=g_strdup(valueArray[1]);
	    }
	    break;
	default:
	    return NULL;
    }
    if (unihanIRG_Source_has_no_mapping(rec->sourceId)){
	rec->sourceMapping=g_strdup(valueArray[0]);
    }else if (invalidValue){
	g_error("Unihan.c:unihanIRG_SourceRec_parse(): The field %d(%s) require a source index! (Such as 0-XXXX)\n",field,unihanField_to_string(field));
    }
    if (valueArray)
	g_strfreev(valueArray);
    return rec;
}


void unihanIRG_SourceRec_free(UnihanIRG_SourceRec *rec){
    g_free((char *)rec->sourceMapping);
    g_free(rec);
}



/*=================================
 * Locale functions.
 */

UnihanLocale unihanLocale_parse(char *str){
    int i;
    for(i=0;i<UNIHAN_LOCALES_COUNT;i++){
	if (g_ascii_strcasecmp (str,UNIHAN_LOCALE_NAMES[i])==0){
	    return i;
	}
    }
    return UNIHAN_INVALID_LOCALE;
}

const char* unihanLocale_to_string(UnihanLocale locale){
    return UNIHAN_LOCALE_NAMES[locale];
}

gboolean unihanChar_is_common_in_locale(gunichar code, UnihanLocale locale){
    UnihanIRG_Source source;
    switch(locale){
	case UNIHAN_LOCALE_JA_JP:
	    source=unihanChar_is_in_sources(code, LOCALE_JA_JP_SOURCES_COMMON);
	case UNIHAN_LOCALE_KO_KP:
	    source=unihanChar_is_in_sources(code, LOCALE_KO_KP_SOURCES_COMMON);
	case UNIHAN_LOCALE_KO_KR:
	    source=unihanChar_is_in_sources(code, LOCALE_KO_KR_SOURCES_COMMON);
	case UNIHAN_LOCALE_ZH_CN:
	    source=unihanChar_is_in_sources(code, LOCALE_ZH_CN_SOURCES_COMMON);
	case UNIHAN_LOCALE_ZH_HK:
	    source=unihanChar_is_in_sources(code, LOCALE_ZH_HK_SOURCES_COMMON);
	case UNIHAN_LOCALE_ZH_SG:
	    source=unihanChar_is_in_sources(code, LOCALE_ZH_SG_SOURCES_COMMON);
	case UNIHAN_LOCALE_ZH_TW:
	    source=unihanChar_is_in_sources(code, LOCALE_ZH_TW_SOURCES_COMMON);
	case UNIHAN_LOCALE_VI_VN:
	    source=unihanChar_is_in_sources(code, LOCALE_VI_VN_SOURCES_COMMON);
	default:
	    break;
    }
    if (source>UNIHAN_INVALID_SOURCEID){
	return TRUE;
    }
    return FALSE;

}


/*=================================
 * Unihan Range functions.
 */


const char *unihanRange_to_string(UnihanRange uRange){
    if (uRange<0){
	return "Invalid Unihan range";
    }
    return UNIHAN_RANGE_NAMES[uRange];
}


/*=================================
 * Unihan Table functions.
 */

UnihanTable unihanTable_parse(const char * tableName){
    int i;
    for(i=0;i<UNIHAN_TABLES_COUNT;i++){
	if (g_ascii_strcasecmp(UNIHAN_TABLE_NAMES[i],tableName)==0){
	    return i;
	}
    }
    return UNIHAN_INVALID_TABLE;
}

const char *unihanTable_to_string(UnihanTable table){
    if (table<0){
	return NULL;
    }
    return UNIHAN_TABLE_NAMES[table];
}

UnihanField* unihanTable_get_db_fields(UnihanTable table){
    int execResult;
    char *errMsg=NULL;
    UnihanField *fields=NEW_ARRAY_INSTANCE(UNIHAN_FIELD_ARRAY_MAX_LEN,UnihanField);
    GString *strBuf=g_string_new("SELECT * FROM ");
    g_string_append(strBuf,unihanTable_to_string(table));
    StringList *sList=sqlite_get_fieldNames(unihanDb,strBuf->str,&execResult, &errMsg);
    guint counter=0;
    if (sList){
	for(counter=0;counter< sList->len; counter++){
	    g_assert(counter<UNIHAN_FIELD_ARRAY_MAX_LEN);
	    const char *fieldName=stringList_index(sList,counter);
	    fields[counter]=unihanField_parse(fieldName);
	}
	stringList_free(sList);
    }
    fields[counter]=UNIHAN_INVALID_FIELD;
    return fields;
}

UnihanField* unihanTable_get_fields(UnihanTable table){
    UnihanField *fields=NEW_ARRAY_INSTANCE(UNIHAN_FIELD_ARRAY_MAX_LEN,UnihanField);
    int i=0;
    if (table<0){
	fields[i]=UNIHAN_INVALID_FIELD;
	return fields;
    }
    fields[i++]=UNIHAN_FIELD_CODE;
    const char *tableName=UNIHAN_TABLE_NAMES[table];
    char buf[50];
    switch(table){
	case UNIHAN_TABLE_KCOMPATIBILITYVARIANT:
	case UNIHAN_TABLE_KSIMPLIFIEDVARIANT:
	case UNIHAN_TABLE_KSEMANTICVARIANT:
	case UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT:
	case UNIHAN_TABLE_KTRADITIONALVARIANT:
	case UNIHAN_TABLE_KZVARIANT:
	    fields[i++]=UNIHAN_FIELD_VARIANT_CODE;
	    break;
	case UNIHAN_TABLE_KHANYUPINLU:
	    fields[i++]=UNIHAN_FIELD_PINYIN;
	    fields[i++]=UNIHAN_FIELD_PINYIN_FREQ;
	    break;
	case UNIHAN_TABLE_KIRGKANGXI:
	case UNIHAN_TABLE_KKANGXI:
	    fields[i++]=UNIHAN_FIELD_KANGXI_PAGE;
	    fields[i++]=UNIHAN_FIELD_KANGXI_CHARNUM;
	    fields[i++]=UNIHAN_FIELD_KANGXI_VIRTUAL;
	    break;
	case UNIHAN_TABLE_IRG_SOURCE:
	    fields[i++]=UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME;
	    break;
	case UNIHAN_TABLE_IRG_SOURCE_MAPPING:
	    fields[i++]=UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME;
	    fields[i++]=UNIHAN_FIELD_IRG_SOURCE_MAPPING;
	    break;
	case UNIHAN_TABLE_KRSADOBE_JAPAN1_6:
	    fields[i++]=UNIHAN_FIELD_ADOBE_CID_CV;
	    fields[i++]=UNIHAN_FIELD_ADOBE_CID;
	    fields[i++]=UNIHAN_FIELD_RADICAL_INDEX;
	    fields[i++]=UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT;
	    fields[i++]=UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT;
	    break;
	case UNIHAN_TABLE_KRSJAPANESE:
	case UNIHAN_TABLE_KRSKANGXI:
	case UNIHAN_TABLE_KRSKANWA:
	case UNIHAN_TABLE_KRSKOREAN:
	case UNIHAN_TABLE_KRSUNICODE:
	    fields[i++]=UNIHAN_FIELD_RADICAL_INDEX;
	    fields[i++]=UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT;
	    break;
	case UNIHAN_TABLE_KSEMANTICVARIANT_EXTRA:
	case UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT_EXTRA:
	    fields[i++]=UNIHAN_FIELD_VARIANT_CODE;
	    fields[i++]=UNIHAN_FIELD_FROM_DICT;
	    fields[i++]=UNIHAN_FIELD_SEMANTIC_T;
	    fields[i++]=UNIHAN_FIELD_SEMANTIC_B;
	    fields[i++]=UNIHAN_FIELD_SEMANTIC_Z;
	    break;
	case UNIHAN_TABLE_KZVARIANT_EXTRA:
	    fields[i++]=UNIHAN_FIELD_VARIANT_CODE;
	    fields[i++]=UNIHAN_FIELD_ZVARIANT_SOURCE;
	    break;
	case UNIHAN_TABLE_KMANDARIN:
	    fields[i++]=UNIHAN_FIELD_KMANDARIN;
	    fields[i++]=UNIHAN_FIELD_FREQ_RANK;
	    break;
	default:
	    subString(buf,tableName,0,strlen(tableName)-5);
	    UnihanField field=unihanField_parse(buf);
	    fields[i++]=field;
    }
    fields[i++]=UNIHAN_INVALID_FIELD;
    if (i>UNIHAN_FIELD_ARRAY_MAX_LEN){
	g_error("UnihanField array is too large!\n");
    }
    return fields;
}

UnihanField* unihanTable_get_primary_key_fields(UnihanTable table){
    UnihanField *fields=NEW_ARRAY_INSTANCE(UNIHAN_FIELD_ARRAY_MAX_LEN,UnihanField);
    int i=0;
    if (table<0){
	fields[i]=UNIHAN_INVALID_FIELD;
	return fields;
    }
    fields[i++]=UNIHAN_FIELD_CODE;
    const char *tableName=UNIHAN_TABLE_NAMES[table];
    char buf[50];
    switch(table){
	case UNIHAN_TABLE_IRG_SOURCE:
	    fields[i++]=UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME;
	case UNIHAN_TABLE_IRG_SOURCE_MAPPING:
	    fields[i++]=UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME;
	    break;
	case UNIHAN_TABLE_KCOMPATIBILITYVARIANT:
	case UNIHAN_TABLE_KSIMPLIFIEDVARIANT:
	case UNIHAN_TABLE_KTRADITIONALVARIANT:
	case UNIHAN_TABLE_KSEMANTICVARIANT:
	case UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT:
	case UNIHAN_TABLE_KZVARIANT:
	    fields[i++]=UNIHAN_FIELD_VARIANT_CODE;
	    break;
	case UNIHAN_TABLE_KHANYUPINLU:
	    fields[i++]=UNIHAN_FIELD_PINYIN;
	    break;
	case UNIHAN_TABLE_KIRGKANGXI:
	case UNIHAN_TABLE_KKANGXI:
	    break;
	case UNIHAN_TABLE_KRSADOBE_JAPAN1_6:
	    fields[i++]=UNIHAN_FIELD_ADOBE_CID;
	    fields[i++]=UNIHAN_FIELD_RADICAL_INDEX;
	    fields[i++]=UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT;
	    break;
	case UNIHAN_TABLE_KRSJAPANESE:
	case UNIHAN_TABLE_KRSKANGXI:
	case UNIHAN_TABLE_KRSKANWA:
	case UNIHAN_TABLE_KRSKOREAN:	
        case UNIHAN_TABLE_KRSUNICODE:
	    fields[i++]=UNIHAN_FIELD_RADICAL_INDEX;
	    fields[i++]=UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT;
	    break;
        case UNIHAN_TABLE_KSEMANTICVARIANT_EXTRA:
        case UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT_EXTRA:
	    fields[i++]=UNIHAN_FIELD_VARIANT_CODE;
	    fields[i++]=UNIHAN_FIELD_FROM_DICT;
	    break;
       case UNIHAN_TABLE_KZVARIANT_EXTRA:
	    fields[i++]=UNIHAN_FIELD_VARIANT_CODE;
	    break;

	default:
	    subString(buf,tableName,0,strlen(tableName)-5);
	    UnihanField field=unihanField_parse(buf);
	    if (!unihanField_is_singleton(field)){
		fields[i++]=field;
	    }
	    break;
    }
    fields[i++]=UNIHAN_INVALID_FIELD;
    if (i>UNIHAN_FIELD_ARRAY_MAX_LEN){
	g_error("UnihanField array is too large!\n");
    }
    return fields;
}


