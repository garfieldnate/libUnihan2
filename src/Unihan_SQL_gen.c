/** 
 * @file Unihan_SQL_gen.c
 * @brief SQL statement generation function and house keeping functions.
 *
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



/*=================================
 * Select generating functions.
 */
static char *unihan_generate_select_clause(UnihanField givenField,UnihanField queryField,UnihanQueryOption qOption){
    GString *strBuf=g_string_new(NULL);
    UnihanTable fromTable=unihanField_get_table(queryField);
    UnihanTable fieldTable;
    switch(queryField){
	case UNIHAN_FIELD_CODE:
	    fieldTable=unihanField_get_table(givenField);
	    
	    if (qOption & UNIHAN_QUERY_OPTION_SCALAR_STRING){
		g_string_printf(strBuf,"TO_SCALAR_STRING(%s.%s) AS CodePoint",UNIHAN_TABLE_NAMES[fieldTable],UNIHAN_FIELD_NAMES[UNIHAN_FIELD_CODE]);
	    }else{
		g_string_printf(strBuf,"%s.%s",UNIHAN_TABLE_NAMES[fieldTable],UNIHAN_FIELD_NAMES[UNIHAN_FIELD_CODE]);
	    }
	    break;
	case UNIHAN_FIELD_KCOMPATIBILITYVARIANT:
	case UNIHAN_FIELD_KSIMPLIFIEDVARIANT:
	case UNIHAN_FIELD_KTRADITIONALVARIANT:

	case UNIHAN_FIELD_VARIANT_CODE:
	    if (qOption & UNIHAN_QUERY_OPTION_SCALAR_STRING){
		g_string_printf(strBuf,"TO_SCALAR_STRING(%s.%s) AS VariantCodePoint",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
	    }else{
		g_string_printf(strBuf,"%s.%s",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
	    }
	    break;
	case UNIHAN_FIELD_KIRG_HSOURCE:
	case UNIHAN_FIELD_KIRG_USOURCE:
	    g_string_printf(strBuf,"%s.%s",
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_MAPPING]);
	    break;
	case UNIHAN_FIELD_KIRG_GSOURCE:
	case UNIHAN_FIELD_KIRG_JSOURCE:
	case UNIHAN_FIELD_KIRG_KPSOURCE:
	case UNIHAN_FIELD_KIRG_KSOURCE:
	case UNIHAN_FIELD_KIRG_TSOURCE:
	case UNIHAN_FIELD_KIRG_VSOURCE:
	    g_string_printf(strBuf,"IRG_SOURCE_VALUE_CONCAT(%s.%s,%s.%s)",
		    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_MAPPING]);
	    break;
	case UNIHAN_FIELD_KIRGKANGXI:
	case UNIHAN_FIELD_KKANGXI:
	    g_string_printf(strBuf,"KANGXI_VALUE_CONCAT(%s, %s, %s)",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_PAGE],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_CHARNUM],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_VIRTUAL]);
	    break;
	case UNIHAN_FIELD_KHANYUPINLU:
	    g_string_printf(strBuf,"HANYU_PINLU_VALUE_CONCAT(%s, %s)",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN_FREQ]);
	    break;
	case UNIHAN_FIELD_KRSADOBE_JAPAN1_6:
	    g_string_printf(strBuf,"ADOBE_RADICAL_STROKE_VALUE_CONCAT(%s, %s, %s, %s, %s)",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_CV],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT]);
	    break;
	case UNIHAN_FIELD_KRSJAPANESE:
	case UNIHAN_FIELD_KRSKANGXI:
	case UNIHAN_FIELD_KRSKANWA:
	case UNIHAN_FIELD_KRSKOREAN:
	case UNIHAN_FIELD_KRSUNICODE:
	    g_string_printf(strBuf,"RADICAL_STROKE_VALUE_CONCAT(%s, %s)",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT]);
	    break;
	case UNIHAN_FIELD_KSEMANTICVARIANT:
	case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
	    g_string_printf(strBuf,"SEMANTIC_VARIANT_VALUE_CONCAT(%s.%s, %s, %s, %s, %s)",
		    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_FROM_DICT],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_SEMANTIC_T],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_SEMANTIC_B],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_SEMANTIC_Z]);
	    break;
	case UNIHAN_FIELD_KZVARIANT:
	    g_string_printf(strBuf,"Z_VARIANT_VALUE_CONCAT(%s.%s, %s)",
	    	    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ZVARIANT_SOURCE]);
	    break;

	default:
	    g_string_printf(strBuf,"%s.%s",UNIHAN_TABLE_NAMES[fromTable],UNIHAN_FIELD_NAMES[queryField]);
	    break;  
    }    
    return g_string_free(strBuf,FALSE);
}

/*=================================
 * FROM generating functions.
 */
static char *unihan_generate_from_clause(UnihanField givenField,UnihanField queryField){
    GString *strBuf=g_string_new(NULL);
    UnihanTable table,extraTable;
    gboolean first=TRUE;

    if (queryField!=UNIHAN_FIELD_CODE ){
	table=unihanField_get_table(queryField);
	g_string_append(strBuf,UNIHAN_TABLE_NAMES[table]);
	if (unihanField_is_IRG_Source(queryField)){
	    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[table],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[table],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME]);
	}else{
	    switch(queryField){
		case UNIHAN_FIELD_KSEMANTICVARIANT:
		case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		    extraTable=unihanField_get_extra_table(queryField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s ",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]
			    );
		    break;
                case UNIHAN_FIELD_KZVARIANT:
		    extraTable=unihanField_get_extra_table(queryField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
                    break;
		default:
		    break;
	    }
	}
	first=FALSE;
    }
    if (givenField!=UNIHAN_FIELD_CODE ){
	if (!first){
	    g_string_append_c(strBuf,',');
	}

	table=unihanField_get_table(givenField);
	g_string_append(strBuf,UNIHAN_TABLE_NAMES[table]);
	if (unihanField_is_IRG_Source(givenField)){
	    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[table],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[table],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME]);
	}else{
	    switch(givenField){
		case UNIHAN_FIELD_KSEMANTICVARIANT:
		case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		    extraTable=unihanField_get_extra_table(givenField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]
			    );
		    break;
		case UNIHAN_FIELD_KZVARIANT:
		    extraTable=unihanField_get_extra_table(givenField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
		    break;
		default:
		    break;
	    }
	}
    }
    g_string_append_c(strBuf,' ');
    return g_string_free(strBuf,FALSE);
}

/*=================================
 * WHERE generating functions.
 */

static char *unihan_append_radical_stroke_where_clause(GString *strBuf, UnihanField field, const char *value){
    int i=0,len=strlen(value);
    g_string_append_printf(strBuf,"%s='",
	    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX]);

    while (i<len && value[i]!='.'){
	g_string_append_c(strBuf,value[i]);
	if (value[i]=='\''){
	    g_string_append_c(strBuf,value[i]);
	}
	i++;
    }

    if (value[i]=='.'){
	/* additional strokes count   */
	g_string_append_printf(strBuf,"' AND %s='",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	return NULL;
    }
    while (i<len){
	g_string_append_c(strBuf,value[i]);
	if (value[i]=='\''){
	    g_string_append_c(strBuf,value[i]);
	}
	i++;
    }
    g_string_append(strBuf,"' ") ;

    return strBuf->str;
}

static char *unihan_append_adobe_japan1_6_where_clause(GString *strBuf ,const char *value){
    int i=0,len=strlen(value);
    if (value[i]=='C'){
	g_string_append_printf(strBuf," %s='C'",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_CV]);
	i++;
    }
    if (value[i]=='V'){
	g_string_append_printf(strBuf," %s='V'",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_CV]);
	i++;
    }
    if (value[i]=='+'){
	/* CID field */
	g_string_append_printf(strBuf," AND %s='",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	g_string_free(strBuf,TRUE);
	return NULL;
    }

    while (i<len && value[i]!='+'){
	g_string_append_c(strBuf,value[i]);
	if (value[i]=='\''){
	    g_string_append_c(strBuf,value[i]);
	}
	i++;
    }
    if (value[i]=='+'){
	/* Radical field  */
	g_string_append_printf(strBuf,"' AND %s='",
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	g_string_free(strBuf,TRUE);
	exit(-1);
	return NULL;
    }

    while (i<len && value[i]!='.'){
	g_string_append_c(strBuf,value[i]);
	if (value[i]=='\''){
	    g_string_append_c(strBuf,value[i]);
	}
	i++;
    }

    if (value[i]=='.'){
	/* Radical strokes count   */
	g_string_append_printf(strBuf,"' AND %s='",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	g_string_free(strBuf,TRUE);
	return NULL;
    }

    while (i<len && value[i]!='.'){
	g_string_append_c(strBuf,value[i]);
	if (value[i]=='\''){
	    g_string_append_c(strBuf,value[i]);
	}
	i++;
    }

    if (value[i]=='.'){
	/* additional strokes count   */
	g_string_append_printf(strBuf,"' AND %s='",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	return NULL;
    }
    while (i<len){
	g_string_append_c(strBuf,value[i]);
	if (value[i]=='\''){
	    g_string_append_c(strBuf,value[i]);
	}
	i++;
    }

    g_string_append_printf(strBuf,"' ");
    return strBuf->str;
}

static void unihan_append_IRG_sources_query_where_clause(GString *strBuf, UnihanIRG_Source source){
    g_string_append_printf(strBuf," AND %s.%s LIKE ",
	    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE],
	    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME]);
    switch(source){
	case UNIHAN_IRG_SOURCE_G:
	    g_string_append(strBuf,"'G%%'");
	    break;
	case UNIHAN_IRG_SOURCE_H:
	    g_string_append(strBuf,"'H'");
	    break;
	case UNIHAN_IRG_SOURCE_J:
	    g_string_append(strBuf,"'J%%'");
	    break;
	case UNIHAN_IRG_SOURCE_KP:
	    g_string_append(strBuf,"'KP_'");
	    break;
	case UNIHAN_IRG_SOURCE_K:
	    g_string_append(strBuf,"'K_'");
	    break;
	case UNIHAN_IRG_SOURCE_T:
	    g_string_append(strBuf,"'T%%'");
	    break;
	case UNIHAN_IRG_SOURCE_U:
	    g_string_append(strBuf,"'U'");
	    break;
	case UNIHAN_IRG_SOURCE_V:
	    g_string_append(strBuf,"'V_'");
	    break;
	default:
	    break;
    }
}

static void unihan_append_kangXi_where_clause(GString *strBuf, UnihanField field,const char* composite_value){
    UnihanTable table=unihanField_get_table(field);
    GArray *gArray=kangXiRec_parse(composite_value);
    int i=0;
    KangXiRec *rec=NULL;
    char *strTmp=NULL;
    g_assert(table>=0);

    if (gArray->len>0){
	rec=&g_array_index(gArray,KangXiRec,i);
	strTmp=sqlite3_mprintf(" %s.%s=%Q AND %s.%s=%Q",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_PAGE],
		rec->page,
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_CHARNUM],
		rec->charNum);
	g_string_append_printf(strBuf,"%s AND %s.%s=%d",
		strTmp,
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_VIRTUAL],
		rec->virtual);
	sqlite3_free(strTmp);
    }
    g_array_free(gArray,TRUE);
}

static void unihan_append_pinyinFreq_where_clause(GString *strBuf, UnihanField field,const char* composite_value){
    UnihanTable table=unihanField_get_table(field);
    GArray *gArray=pinyinFreqRec_parse(composite_value);
    char *strTmp=NULL;
    int i=0;
    PinyinFreqRec *rec=NULL;
    g_assert(table>=0);

    if (gArray->len>0){
	rec=&g_array_index(gArray,PinyinFreqRec,i);
	strTmp=sqlite3_mprintf(" %s.%s=%Q",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN],
		rec->pinyin);
	g_string_append_printf(strBuf,"%s AND %s.%s=%d",
		strTmp,
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN_FREQ],
		rec->freq);
	sqlite3_free(strTmp);
    }
    g_array_free(gArray,TRUE);
}

static void unihan_append_semantic_where_clause(GString *strBuf, UnihanField field, const char* composite_value){
    GArray *gArray=semanticDictRec_parse(composite_value);
    char *strTmp=NULL;
    int i=0;
    SemanticDictRec *rec=NULL;
    UnihanTable table=unihanField_get_table(field);
    g_assert(table>=0);

    if (gArray->len>0){
	rec=&g_array_index(gArray,SemanticDictRec,i);
	g_string_append_printf(strBuf," %s.%s=%d",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
		rec->variantCode);
	if (!isEmptyString(rec->fromDict)){
	        strTmp=sqlite3_mprintf(" AND %s=%Q",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_FROM_DICT],
		    rec->fromDict);
	    g_string_append_printf(strBuf,"%s AND semanticT=%d AND semanticB=%d AND semanticZ=%d",
		    strTmp,rec->T,rec->B,rec->Z);
	    sqlite3_free(strTmp);
	}
    }
    g_array_free(gArray,TRUE);
}

static void unihan_append_zvariant_where_clause(GString *strBuf, UnihanField field, const char* composite_value){
    char **subFieldArray=g_strsplit(composite_value,":",-1);
    char *strTmp=NULL;
    g_assert(subFieldArray[0]);
    gunichar variantCode=unihanChar_parse(subFieldArray[0]);
    g_string_append_printf(strBuf," %s.%s=%d",
	    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_KZVARIANT],
	    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
	    variantCode);
    if (!isEmptyString(subFieldArray[1])){
	strTmp=sqlite3_mprintf(" AND %s=%Q",
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ZVARIANT_SOURCE],
		subFieldArray[1]);
	g_string_append(strBuf,strTmp);
	sqlite3_free(strTmp);
    }
    g_strfreev(subFieldArray);
}

static void unihan_append_where_clause_join_table(GString *strBuf, 
	UnihanField givenField, UnihanField queryField){

    UnihanTable givenTable,queryTable;

    if (givenField==UNIHAN_FIELD_CODE ){
	return;
    }else if (queryField==UNIHAN_FIELD_CODE){
	return;
    }else{
	queryTable=unihanField_get_table(queryField);
	givenTable=unihanField_get_table(givenField);
	g_string_append_printf(strBuf, " AND %s.code=%s.code",
		UNIHAN_TABLE_NAMES[queryTable],
		UNIHAN_TABLE_NAMES[givenTable]);
    }
}

static char *unihan_generate_where_clause(UnihanField givenField, const char *value, 
	UnihanTable fromTable,	UnihanField queryField,  UnihanQueryOption qOption){
    GString *strBuf=g_string_new(NULL);
    UnihanIRG_SourceRec *rec=NULL;
    if (unihanField_is_IRG_Source(givenField)){
	rec=unihanIRG_SourceRec_parse(givenField,value);
    }
    char *relStr=(qOption & UNIHAN_QUERY_OPTION_LIKE)? "LIKE": "=";
    char *strTmp=NULL;

    if (rec!=NULL){
	strTmp=sqlite3_mprintf(" %s.%s=%Q",
		UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		UNIHAN_IRG_SOURCES[rec->sourceId].name);
	if (strTmp){
	    g_string_append(strBuf,strTmp);
	    sqlite3_free(strTmp);
	}
	if (!unihanIRG_Source_has_no_mapping(rec->sourceId)){
	        strTmp=sqlite3_mprintf(" AND %s %s %Q",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_MAPPING],
		    relStr,
		    rec->sourceMapping);
		if (strTmp){
		    g_string_append(strBuf,strTmp);
		    sqlite3_free(strTmp);
		}
	}
	unihanIRG_SourceRec_free(rec);
    }else{
	switch(givenField){
	    case UNIHAN_FIELD_KIRGKANGXI:
	    case UNIHAN_FIELD_KKANGXI:
		unihan_append_kangXi_where_clause(strBuf,givenField,value);
		break;
	    case UNIHAN_FIELD_KHANYUPINLU:
		unihan_append_pinyinFreq_where_clause(strBuf,givenField,value);
		break;
	    case UNIHAN_FIELD_KRSADOBE_JAPAN1_6:
		unihan_append_adobe_japan1_6_where_clause(strBuf,value);
		break;
	    case UNIHAN_FIELD_KRSJAPANESE:
	    case UNIHAN_FIELD_KRSKANGXI:
	    case UNIHAN_FIELD_KRSKANWA:
	    case UNIHAN_FIELD_KRSKOREAN:
	    case UNIHAN_FIELD_KRSUNICODE:
		unihan_append_radical_stroke_where_clause(strBuf, givenField, value);
		break;
	    case UNIHAN_FIELD_KSEMANTICVARIANT:
	    case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		unihan_append_semantic_where_clause(strBuf, givenField, value);
		break;
	    case UNIHAN_FIELD_KCOMPATIBILITYVARIANT:
	    case UNIHAN_FIELD_KSIMPLIFIEDVARIANT:
	    case UNIHAN_FIELD_KTRADITIONALVARIANT:
		strTmp=sqlite3_mprintf("%s.%s=%Q",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			value);
		break;
	    case UNIHAN_FIELD_KZVARIANT:
		unihan_append_zvariant_where_clause(strBuf, givenField, value);
		break;

	    default:
		strTmp=sqlite3_mprintf("%s.%s %s %Q",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[givenField],
			relStr,value);

		break;
	}
	if (strTmp){
	    g_string_append(strBuf,strTmp);
	    sqlite3_free(strTmp);
	}
    }


    unihan_append_where_clause_join_table(strBuf, givenField, queryField);

    /* Below is needed if queryField is pseudo */
    UnihanIRG_Source source=unihanField_get_IRG_source(queryField);
    if (source>=0){
	unihan_append_IRG_sources_query_where_clause(strBuf, source);
    }else{
//        switch(queryField){
//            case UNIHAN_FIELD_KRSJAPANESE:
//            case UNIHAN_FIELD_KRSKANGXI:
//            case UNIHAN_FIELD_KRSKANWA:
//            case UNIHAN_FIELD_KRSKOREAN:
//            case UNIHAN_FIELD_KRSUNICODE:
//                g_string_append(strBuf," AND ");
//                unihan_append_radical_stroke_query_where_clause(strBuf, queryField);
//                break;
//            case UNIHAN_FIELD_KSEMANTICVARIANT:
//            case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
//                g_string_append_printf(strBuf," AND %s.code=%s.code",
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_VARIANT],
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_SEMANTIC_DICT]);
//                g_string_append_printf(strBuf," AND %s.variantCode=%s.variantCode",
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_VARIANT],
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_SEMANTIC_DICT]);
//            case UNIHAN_FIELD_KCOMPATIBILITYVARIANT:
//            case UNIHAN_FIELD_KSIMPLIFIEDVARIANT:
//            case UNIHAN_FIELD_KTRADITIONALVARIANT:
//            case UNIHAN_FIELD_KZVARIANT:
//                g_string_append_printf(strBuf," AND %s.%s=\"%s\"",
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_VARIANT],
//                        UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_TYPE],
//                        UNIHAN_FIELD_NAMES[queryField]);
//                break;
//            default:
//                break;
//        }
    }

    return g_string_free(strBuf,FALSE);
}

SQL_Result *unihan_find_all_matched(UnihanField givenField, char *givenValue, 
	UnihanField queryField, UnihanQueryOption qOption){
    char *selectStr=NULL;
    char *fromStr=NULL;
    char *whereStr=NULL;
    int i;
    GString *strBuf=g_string_new(NULL);

    UnihanTable table;
    UnihanTable *tableArray=(givenField!=UNIHAN_FIELD_CODE) ? 
	    unihanField_get_all_tables(givenField): unihanField_get_all_tables(queryField);
    for(i=0;tableArray[i]>=0;i++){
	if (i>0){
	    g_string_append(strBuf," UNION ");
	}
	selectStr=unihan_generate_select_clause(givenField,queryField,qOption);
	fromStr=unihan_generate_from_clause(givenField,queryField);
	whereStr=unihan_generate_where_clause(givenField,givenValue,tableArray[i],queryField,qOption);

	g_string_append_printf(strBuf,"SELECT %s FROM %s WHERE %s",selectStr,fromStr, whereStr);

	/* Group by */
	switch(queryField){
	    case UNIHAN_FIELD_KSEMANTICVARIANT:
	    case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		table=unihanField_get_table(queryField);
		g_string_append_printf(strBuf," GROUP BY %s.%s",
			UNIHAN_TABLE_NAMES[table],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
		break;
	    default:
		break;

	}
    }

    g_string_append(strBuf,";");
    verboseMsg_print(VERBOSE_MSG_INFO1,"%s\n",strBuf->str);
    
    SQL_Result *sResult=unihanSql_get_sql_result(strBuf->str);
    verboseMsg_print(VERBOSE_MSG_INFO4," 2 sResult->colCount=%d \n",sResult->colCount);
    g_free(selectStr);
    g_free(fromStr);
    g_free(whereStr);
    g_string_free(strBuf,TRUE);
    g_free(tableArray);
    return sResult;
}

char* unihan_find_first_matched(UnihanField givenField, char* givenValue, 
	UnihanField queryField, UnihanQueryOption qOption){

    SQL_Result *sResult=unihan_find_all_matched(givenField, givenValue,  queryField, qOption);
    if (sResult->execResult){
	verboseMsg_print(VERBOSE_MSG_ERROR,"Database error: %s\n", sResult->errMsg);
	sql_result_free(sResult, TRUE);
	return NULL;
    }
    char *result=g_strdup(stringList_index(sResult->resultList,0));
    sql_result_free(sResult,TRUE);
    return result;
}


int unihan_count_matched_record(UnihanTable table, StringList *valueList){
    int i;
    if (table<0){
	return -1;
    }
    UnihanField* fields=unihanTable_get_fields(table);
    GString *strBuf=g_string_new("SELECT * FROM");
    g_string_append_printf(strBuf," %s WHERE", UNIHAN_TABLE_NAMES[table]);

    for(i=0;i<valueList->len;i++){
	if (fields[i]<0){
	    g_error("unihan_count_matched_record(): too many values!  %d value required, but %d are given!\n",i,valueList->len);
	}
	if (i>0){
	    g_string_append(strBuf," AND");
	}
	if (unihanField_is_integer(fields[i])){
	    g_string_append_printf(strBuf," %s=%s",UNIHAN_FIELD_NAMES[fields[i]],stringList_index(valueList,i));
	}else{
	    g_string_append_printf(strBuf," %s=\"%s\"",UNIHAN_FIELD_NAMES[fields[i]],stringList_index(valueList,i));
	}
    }
    while(fields[i]>=0){
	i++;
    }
    if (i!=valueList->len){
	g_error("unihan_count_matched_record(): too few values!  %d value required, but %d are given!\n",i,valueList->len);
    }

    g_string_append(strBuf,";");
    verboseMsg_print(VERBOSE_MSG_INFO2,"unihan_count_matched_record(): %s\n",strBuf->str);
    char *errMsg=NULL;
    int ret=unihanSql_count_matches(strBuf->str,&errMsg);
    verboseMsg_print(VERBOSE_MSG_INFO2,"unihan_count_matched_record(): %d records founds\n",ret);
    g_string_free(strBuf,TRUE);
    g_free(fields);
    return ret;
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


int unihan_insert_value(gunichar code, UnihanField field, const char *value){
    char buf[20];
    UnihanTable table=unihanField_get_table(field);
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

	if (!unihanIRG_Source_has_no_mapping(rec->sourceId)){
	    stringList_insert(sList,buf);
	    stringList_insert(sList,srcData->name);
	    stringList_insert(sList,rec->sourceMapping);
	    newResult=unihan_insert_no_duplicate(UNIHAN_TABLE_IRG_SOURCE_MAPPING,sList);
	    result=latest_db_result(result,newResult);
	    stringList_clear(sList);
	}
	stringList_insert(sList,buf);
	stringList_insert(sList,srcData->name);
	unihanIRG_SourceRec_free(rec);
    }else if (unihanField_array_index(field,UNIHAN_KVARIANT_FIELDS)>=0){
	switch(field){
	    case UNIHAN_FIELD_KSEMANTICVARIANT:
	    case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		return insert_semanticVariant(code, field, value);
	    case UNIHAN_FIELD_KZVARIANT:
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
	    case UNIHAN_FIELD_KRSADOBE_JAPAN1_6:
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
    }else if (field==UNIHAN_FIELD_KMANDARIN){
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
    }else if (field==UNIHAN_FIELD_KHANYUPINLU){
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
    }else if (field==UNIHAN_FIELD_KIRGKANGXI || field==UNIHAN_FIELD_KKANGXI){
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
	if (table==UNIHAN_TABLE_KSEMANTICVARIANT || table == UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT){
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

/*=================================
 * SQL wrapper functions.
 */

int unihanSql_exec(char *sqlClause, UnihanCallback callback, 
	void *callbackOption,  char **errMsg_ptr){
    return sqlite3_exec(unihanDb, sqlClause, callback, callbackOption, errMsg_ptr);
}

int unihanSql_count_matches(const char * sqlClause, char **errMsg_ptr){
    int ret=sqlite_count_matches(unihanDb,sqlClause,errMsg_ptr);
    if (ret<0){
	verboseMsg_print(VERBOSE_MSG_ERROR, "Database error: %s\n", *errMsg_ptr);
    }
    return ret;
}

SQL_Result *unihanSql_get_sql_result(const char *sqlClause){
    return sqlite_get_sql_result(unihanDb, sqlClause);
}


