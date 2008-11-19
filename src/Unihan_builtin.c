/** 
 * @file Unihan_builtin.c
 * @brief Functions for builtin tables and fields only.
 * 
 * This file contains the functions 
 *  which only deal for builtin tables and fields.
 */

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

#include <glib.h>
#include <sqlite3.h>
#include "Unihan.h"

#include "Unihan_builtin_def.c"
#define MAX_BUFFER_SIZE 2000
#define UNIHAN_FIELD_ARRAY_MAX_LEN 200
#define UNIHAN_TABLE_ARRAY_MAX_LEN 800



/*=========================================================
 * Functions
 */


UnihanTable unihanField_get_builtin_preferred_table(UnihanField field){
    int i;
    for(i=0;FIELD_PREFERRED_TABLES[i].field!=UNIHAN_INVALID_FIELD;i++){
	if (FIELD_PREFERRED_TABLES[i].field==field){
	    return FIELD_PREFERRED_TABLES[i].table;
	}
    }
    return UNIHAN_INVAILD_TABLE;
}

UnihanTable *unihanField_get_builtin_required_tables(UnihanField field){
    int i,counter=0;
    UnihanTable *tables=NEW_ARRAY_INSTANCES(UNIHAN_TABLE_ARRAY_MAX_LEN, UnihanTable);
    for(i=0;PSEUDOFIELD_REQUIRED_TABLES[i].field!=UNIHAN_INVALID_FIELD;i++){
	if (PSEUDOFIELD_REQUIRED_TABLES[i].field==field){
	    tables[counter++]=PSEUDOFIELD_REQUIRED_TABLES[i].refTable;
	}
    }
    if (counter==0){
	/* Maybe a real field */
	tables[counter++]=unihanField_get_builtin_preferred_table(field);
    }
    tables[counter]=UNIHAN_INVALID_TABLE;
    return tables;
}

static int latest_db_result(int result,int newResult){
    if ((result<=0) && (newResult>0)){
	/* newResult overrides result, indicates there is database error */
	result=newResult;
    }else if ((result==0) && (newResult<0)){
	/* newResult overrides result, indicates at least one insert instruction is skipped. */
	result=newResult;
    }else{
	/* no need to change result */
    }
    return result;
}

static int insert_semanticVariant(gunichar code, UnihanField field, const char *composite_value){
    StringList *sList=NULL;

    GArray *gArray=semanticDictRec_parse(composite_value);
    SemanticDictRec *sRec=NULL;
    int i;
    char codeBuf[20], variantBuf[20];
    const char oneStr[]="1", zeroStr[]="0";
    int result=0,newResult=0;
    UnihanTable table=unihanField_get_table(field),
		extraTable=unihanField_get_extra_table(field);


    g_snprintf(codeBuf,20,"%d",code);
    for(i=0;i<gArray->len;i++){
	sList=stringList_new();
	sRec=&g_array_index(gArray,SemanticDictRec,i);

	g_snprintf(variantBuf,20,"%d",sRec->variantCode);
	/* Insert to k*SementicVariantTable */
	stringList_insert(sList,codeBuf);
	stringList_insert(sList,variantBuf);

	newResult=unihan_insert_no_duplicate(table,sList);
	result=latest_db_result(result,newResult);
	stringList_free(sList);

	if (isEmptyString(sRec->fromDict)){
	    continue;
	}

	sList=stringList_new();
	/* Insert to SemanticDictTable */
	stringList_insert(sList,codeBuf);
	stringList_insert(sList,variantBuf);
	stringList_insert(sList,sRec->fromDict);
	stringList_insert(sList,(sRec->T)? oneStr: zeroStr);
	stringList_insert(sList,(sRec->B)? oneStr: zeroStr);
	stringList_insert(sList,(sRec->Z)? oneStr: zeroStr);

	newResult=unihan_insert_no_duplicate(extraTable,sList);
	result=latest_db_result(result,newResult);
	stringList_free(sList);
    }

    g_array_free(gArray,TRUE);
    return result;
}

static int insert_zVariant(gunichar code, UnihanField field, const char *composite_value){
    char **subFieldArray=g_strsplit(composite_value,":",-1);
    g_assert(subFieldArray[0]);
    gunichar variantCode=unihanChar_parse(subFieldArray[0]);
    char codeBuf[20], variantBuf[20];
    StringList *sList=stringList_new();

    int result=0,newResult=0;
    UnihanTable table=unihanField_get_table(field),
		extraTable=unihanField_get_extra_table(field);

    g_snprintf(codeBuf,20,"%d",code);
    g_snprintf(variantBuf,20,"%d",variantCode);

    stringList_insert(sList,codeBuf);
    stringList_insert(sList,variantBuf);
    newResult=unihan_insert_no_duplicate(table, sList);
    result=latest_db_result(result,newResult);

    if (!isEmptyString(subFieldArray[1])){
	stringList_clear(sList);
	stringList_insert(sList,codeBuf);
	stringList_insert(sList,variantBuf);
	stringList_insert(sList,subFieldArray[1]);

	newResult=unihan_insert_no_duplicate(extraTable,sList);
	result=latest_db_result(result,newResult);

    }
    stringList_free(sList);
    g_strfreev(subFieldArray);
    return result;
}

int unihan_insert(UnihanTable table, StringList *valueList){
    int i;
    char *errmsg=NULL;
    if (table<0){
	return -1;
    }
    UnihanField* fields=unihanTable_get_fields(table);
    GString *strBuf=g_string_new("INSERT INTO");
    g_string_append_printf(strBuf," %s VALUES (", UNIHAN_TABLE_NAMES[table]);

    for(i=0;i<valueList->len;i++){
	if (fields[i]<0){
	    g_error("unihan_insert(): too many values!  %d value required, but %d are given!\n",i,valueList->len);
	}
	if (i>0){
	    g_string_append_c(strBuf,',');
	}
	if (unihanField_is_integer(fields[i])){
	    g_string_append_printf(strBuf," %s",stringList_index(valueList,i));
	}else{
	    g_string_append_printf(strBuf," \"%s\"",stringList_index(valueList,i));
	}
    }
    while(fields[i]>=0){
	i++;
    }
    if (i!=valueList->len){
	g_error("unihan_insert(): too few values!  %d value required, but %d are given!\n",i,valueList->len);
    }
    g_string_append(strBuf,");");
    verboseMsg_print(VERBOSE_MSG_INFO1,"%s\n",strBuf->str);
    int ret=unihanSql_exec(strBuf->str,NULL,NULL,&errmsg);
    if (ret) {
	verboseMsg_print(VERBOSE_MSG_ERROR, "unihan_insert(): Cannot insert. :%s\n", errmsg);
    }
    g_string_free(strBuf,TRUE);
    g_free(fields);
    return ret;
}

int unihan_insert_tagValue_builtin_table(gunichar code, UnihanField field, const char *tagValue){
    char buf[20];
    UnihanTable *tables=unihanField_get_builtin_required_tables(field);
    gchar **values=NULL;
    gchar **fieldArray=NULL;
    gunichar variantCode;
    if (!unihanField_is_singleton(field)){
	values=g_strsplit_set(value," ",-1);
    }else{
	
    }
    



    UnihanTable *tables=unihanField_get_builtin
    StringList *sList=stringList_new();
    char **subFieldArray=NULL;
    gunichar variantCode;
    static gunichar lastCode=0;
    int result=0,newResult=0;
    static int freqRank=1;

    UnihanIRG_SourceRec *rec=NULL;
    if (unihanField_is_IRG_Source(field)){
	rec=unihanIRG_SourceRec_parse(field,value);
    }

    if (rec!=NULL){
	const UnihanIRG_SourceData *srcData=unihanIRG_SourceData_get(rec->sourceId);
	if (srcData==NULL){
	    g_error("Unknown source!");
	}
	g_snprintf(buf,20,"%d",code);

	if (!unihanIRG_Source_has_no_mapping(rec->sourceId)){/
	    stringList_insert(sList,buf);
	    stringList_insert(sList,srcData->name);
	    stringList_insert(sList,rec->sourceMapping);
	    newResult=unihan_insert_no_duplicate(UNIHAN_TABLE_IRG_SOURCE_EXTRA,sList);
	    result=latest_db_result(result,newResult);
	    stringList_clear(sList);
	}
	stringList_insert(sList,buf);
	stringList_insert(sList,srcData->name);
	unihanIRG_SourceRec_free(rec);
    }else if (unihanField_array_index(field,UNIHAN_KVARIANT_FIELDS)>=0){
	switch(field){
	    case UNIHAN_FIELD_kSEMANTICVARIANT:
	    case UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT:
		return insert_semanticVariant(code, field, value);
	    case UNIHAN_FIELD_kZVARIANT:
		return insert_zVariant(code, field, value);
	    default:
		variantCode=unihanChar_parse(value);
		g_snprintf(buf,20,"%d",code);
		stringList_insert(sList,buf);
		g_snprintf(buf,20,"%d",variantCode);
		stringList_insert(sList,buf);
		break;
	}
    }else  if (unihanField_array_index(field,UNIHAN_KRS_FIELDS)>=0){
	switch(field){
	    case UNIHAN_FIELD_kRSADOBE_JAPAN1_6:
		subFieldArray=g_strsplit_set(value,".+",-1);
		g_snprintf(buf,20,"%d",code);

		stringList_insert(sList,buf);
		stringList_insert(sList,subFieldArray[0]);
		stringList_insert(sList,subFieldArray[1]);
		stringList_insert(sList,subFieldArray[2]);
		stringList_insert(sList,subFieldArray[3]);
		stringList_insert(sList,subFieldArray[4]);

		break;
	    default:
		subFieldArray=g_strsplit(value,".",-1);
		g_snprintf(buf,20,"%d",code);
		stringList_insert(sList,buf);
		stringList_insert(sList,subFieldArray[0]);
		stringList_insert(sList,subFieldArray[1]);
		break;
	}
	g_assert(subFieldArray);
	g_free(subFieldArray);
    }else if (field==UNIHAN_FIELD_kMANDARIN){
	if (lastCode!=code){
	    freqRank=1;
	    lastCode=code;
	}
	g_snprintf(buf,20,"%d",code);
	stringList_insert(sList,buf);
	stringList_insert(sList,value);
	g_snprintf(buf,20,"%d",freqRank);
	stringList_insert(sList,buf);
	freqRank++;
    }else if (field==UNIHAN_FIELD_kHANYUPINLU){
	g_snprintf(buf,20,"%d",code);
	stringList_insert(sList,buf);
	GArray *pfArray=pinyinFreqRec_parse(value);
	if (pfArray->len>0){
	    PinyinFreqRec *rec=&g_array_index(pfArray,PinyinFreqRec,0);
	    stringList_insert(sList,rec->pinyin);
	    g_snprintf(buf,20,"%d",rec->freq);
	    stringList_insert(sList,buf);
	}
	g_array_free(pfArray,TRUE);
    }else if (field==UNIHAN_FIELD_kIRGKANGXI || field==UNIHAN_FIELD_kKANGXI){
	g_snprintf(buf,20,"%d",code);
	stringList_insert(sList,buf);
	GArray *kArray=kangXiRec_parse(value);
	if (kArray->len>0){
	    KangXiRec *rec=&g_array_index(kArray,KangXiRec,0);
	    stringList_insert(sList,rec->page);
	    stringList_insert(sList,rec->charNum);
	    g_snprintf(buf,20,"%d",(rec->virtual)? 1:0);
	    stringList_insert(sList,buf);
	}
	g_array_free(kArray,TRUE);

    }else{
	g_snprintf(buf,20,"%d",code);
	stringList_insert(sList,buf);
	stringList_insert(sList,value);
    }
    newResult=unihan_insert_no_duplicate(table,sList);
    result=latest_db_result(result,newResult);
    stringList_free(sList);
    return result;
}

int unihan_insert_no_duplicate(UnihanTable table, StringList *valueList){
    if (unihan_count_matched_record(table,valueList)>0){
	if (table==UNIHAN_TABLE_kSEMANTICVARIANT || table == UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT){
	    verboseMsg_print(VERBOSE_MSG_WARNING,"code %s is already inserted in table %s, no need to insert again.\n",
		    stringList_index(valueList,0),UNIHAN_TABLE_NAMES[table]);
	}else{
	    verboseMsg_print(VERBOSE_MSG_WARNING,"Record duplicate in table %s on code=%s, skip!\n",
		    UNIHAN_TABLE_NAMES[table],stringList_index(valueList,0));
	}
	return -1;
    }
    int ret=unihan_insert(table,valueList);
    if (ret>0){
	return ret;
    }
    return 0;
}

