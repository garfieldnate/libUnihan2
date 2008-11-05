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

static void unihan_generate_select_field_clause(GString *strBuf, UnihanField givenField,UnihanField queryField,UnihanQueryOption qOption){
    UnihanTable fromTable=unihanField_get_table(queryField);
    UnihanTable givenTable=unihanField_get_table(givenField);
    gboolean need_right_parenthesis=FALSE;

    if (unihanField_is_lowercase(queryField)){
	g_string_append(strBuf,"TO_LOWERCASE(");
	need_right_parenthesis=TRUE;
    }else if (!unihanField_is_case_no_change(queryField)){
	if (!unihanField_is_mandarin(queryField)){
	    g_string_append(strBuf,"TO_UPPERCASE(");
	    need_right_parenthesis=TRUE;
	}
    }
    switch(queryField){
	case UNIHAN_FIELD_CODE:
	    if (qOption & UNIHAN_QUERY_OPTION_SCALAR_STRING){
		g_string_append_printf(strBuf,"TO_SCALAR_STRING(%s.%s)%c AS code",
			UNIHAN_TABLE_NAMES[givenTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_CODE],
			(need_right_parenthesis)? ')' : ' '
			);
		need_right_parenthesis=FALSE;
	    }else{
		g_string_append_printf(strBuf,"%s.%s",UNIHAN_TABLE_NAMES[givenTable],UNIHAN_FIELD_NAMES[UNIHAN_FIELD_CODE]);
	    }
	    break;
	case UNIHAN_FIELD_kCOMPATIBILITYVARIANT:
	case UNIHAN_FIELD_kSIMPLIFIEDVARIANT:
	case UNIHAN_FIELD_kTRADITIONALVARIANT:

	case UNIHAN_FIELD_VARIANT_CODE:
	    if (qOption & UNIHAN_QUERY_OPTION_SCALAR_STRING){
		g_string_append_printf(strBuf,"TO_SCALAR_STRING(%s.%s)%c AS VariantCodePoint",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			(need_right_parenthesis)? ')' : ' '
			);
		need_right_parenthesis=FALSE;
	    }else{
		g_string_append_printf(strBuf,"%s.%s",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
	    }
	    break;
	case UNIHAN_FIELD_kIRG_HSOURCE:
	case UNIHAN_FIELD_kIRG_USOURCE:
	    g_string_append_printf(strBuf,"%s.%s",
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_MAPPING]);
	    break;
	case UNIHAN_FIELD_kIRG_GSOURCE:
	case UNIHAN_FIELD_kIRG_JSOURCE:
	case UNIHAN_FIELD_kIRG_KPSOURCE:
	case UNIHAN_FIELD_kIRG_KSOURCE:
	case UNIHAN_FIELD_kIRG_TSOURCE:
	case UNIHAN_FIELD_kIRG_VSOURCE:
	    g_string_append_printf(strBuf,"IRG_SOURCE_VALUE_CONCAT(%s.%s,%s.%s)%c AS %s",
		    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_MAPPING],
		    (need_right_parenthesis)? ')' : ' ',
		    UNIHAN_FIELD_NAMES[queryField]);
	    need_right_parenthesis=FALSE;
	    break;
	case UNIHAN_FIELD_kIRGKANGXI:
	case UNIHAN_FIELD_kKANGXI:
	    g_string_append_printf(strBuf,"KANGXI_VALUE_CONCAT(%s, %s, %s)%c AS %s",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_PAGE],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_CHARNUM],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_VIRTUAL],
		    (need_right_parenthesis)? ')' : ' ',
		    UNIHAN_FIELD_NAMES[queryField]);
	    need_right_parenthesis=FALSE;
	    break;
	case UNIHAN_FIELD_kHANYUPINLU:
	    g_string_append_printf(strBuf,"HANYU_PINLU_VALUE_CONCAT(%s, %s, %d)%c AS %s",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN_FREQ],
		    qOption,
		    (need_right_parenthesis)? ')' : ' ',
		    UNIHAN_FIELD_NAMES[queryField]);
	    need_right_parenthesis=FALSE;
	    break;
	case UNIHAN_FIELD_kRSADOBE_JAPAN1_6:
	    g_string_append_printf(strBuf,"ADOBE_RADICAL_STROKE_VALUE_CONCAT(%s, %s, %s, %s, %s)%c AS %s",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_CV],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT],
		    (need_right_parenthesis)? ')' : ' ',
		    UNIHAN_FIELD_NAMES[queryField]);
	    need_right_parenthesis=FALSE;
	    break;
	case UNIHAN_FIELD_kRSJAPANESE:
	case UNIHAN_FIELD_kRSKANGXI:
	case UNIHAN_FIELD_kRSKANWA:
	case UNIHAN_FIELD_kRSKOREAN:
	case UNIHAN_FIELD_kRSUNICODE:
	    g_string_append_printf(strBuf,"RADICAL_STROKE_VALUE_CONCAT(%s, %s)%c AS %s",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT],
		    (need_right_parenthesis)? ')' : ' ',
		    UNIHAN_FIELD_NAMES[queryField]);
	    need_right_parenthesis=FALSE;
	    break;
	case UNIHAN_FIELD_kSEMANTICVARIANT:
	case UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT:
	    g_string_append_printf(strBuf,"SEMANTIC_VARIANT_VALUE_CONCAT(%s.%s, %s, %s, %s, %s)%c AS %s",
		    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_FROM_DICT],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_SEMANTIC_T],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_SEMANTIC_B],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_SEMANTIC_Z],
		    (need_right_parenthesis)? ')' : ' ',
		    UNIHAN_FIELD_NAMES[queryField]);
	    need_right_parenthesis=FALSE;
	    break;
	case UNIHAN_FIELD_kZVARIANT:
	    g_string_append_printf(strBuf,"Z_VARIANT_VALUE_CONCAT(%s.%s, %s)%c AS %s",
		    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ZVARIANT_SOURCE],
		    (need_right_parenthesis)? ')' : ' ',
		    UNIHAN_FIELD_NAMES[queryField]);
	    need_right_parenthesis=FALSE;
	    break;
	default:
	    if (unihanField_is_mandarin(queryField)){
		if (queryField==UNIHAN_FIELD_ZHUYIN || (qOption & UNIHAN_QUERY_OPTION_ZHUYIN_FORCE_DISPLAY)){
		    g_string_append_printf(strBuf,"PINYIN_TO_ZHUYIN(%s.%s, %d)",
			    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_kMANDARIN],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_kMANDARIN],
			    UNIHAN_QUERY_OPTION_GET_ZHUYIN_FORMAT(qOption));
		}else{
		    g_string_append_printf(strBuf,
			    "PINYIN_CONVERT_ACCENT_FORMAT(%s.%s,%d,%d)",
			    UNIHAN_TABLE_NAMES[fromTable],
			    UNIHAN_FIELD_NAMES[queryField],
			    UNIHAN_QUERY_OPTION_GET_PINYIN_FORMAT(qOption),
			    ((qOption & UNIHAN_QUERY_OPTION_PINYIN_TONE_ACCENT) ? 0: 1));
		}
		g_string_append_printf(strBuf," AS %s", 
			UNIHAN_FIELD_NAMES[queryField]);
		need_right_parenthesis=FALSE;
	    }else{
		g_string_append_printf(strBuf,"%s.%s",UNIHAN_TABLE_NAMES[fromTable],UNIHAN_FIELD_NAMES[queryField]);
	    }
	    break;  
    }
    if (need_right_parenthesis){
	g_string_append(strBuf,")");
	need_right_parenthesis=FALSE;
    }
}

static char *unihan_generate_select_clause(UnihanField givenField,UnihanField queryField,UnihanQueryOption qOption){
    GString *strBuf=g_string_new(NULL);
 
    if (qOption & UNIHAN_QUERY_OPTION_SHOW_GIVEN_FIELD){
	unihan_generate_select_field_clause(strBuf, queryField, givenField,qOption);
	g_string_append_printf(strBuf," ,");
    }
    unihan_generate_select_field_clause(strBuf, givenField, queryField,qOption);

    return g_string_free(strBuf,FALSE);
}

/*=================================
 * FROM generating functions.
 */
static char *unihan_generate_from_clause(UnihanField givenField,UnihanField queryField){
    GString *strBuf=g_string_new(NULL);
    UnihanTable fromTable,givenTable,extraTable;
    gboolean first=TRUE;

    if (queryField!=UNIHAN_FIELD_CODE ){
	fromTable=unihanField_get_table(queryField);
	g_string_append(strBuf,UNIHAN_TABLE_NAMES[fromTable]);
	if (unihanField_is_IRG_Source(queryField)){
	    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME]);
	}else{
	    switch(queryField){
		case UNIHAN_FIELD_kSEMANTICVARIANT:
		case UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT:
		    extraTable=unihanField_get_extra_table(queryField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s ",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[fromTable],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[fromTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]
			    );
		    break;
                case UNIHAN_FIELD_kZVARIANT:
		    extraTable=unihanField_get_extra_table(queryField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[fromTable],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[fromTable],
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
	givenTable=unihanField_get_table(givenField);
	if (givenTable!=fromTable){
	    if (!first){
		g_string_append_c(strBuf,',');
	    }

	    g_string_append(strBuf,UNIHAN_TABLE_NAMES[givenTable]);
	    if (unihanField_is_IRG_Source(givenField)){
		g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
			UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
			UNIHAN_TABLE_NAMES[givenTable],
			UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
			UNIHAN_TABLE_NAMES[givenTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
			UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME]);
	    }else{
		switch(givenField){
		    case UNIHAN_FIELD_kSEMANTICVARIANT:
		    case UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT:
			extraTable=unihanField_get_extra_table(givenField);
			g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
				UNIHAN_TABLE_NAMES[extraTable],
				UNIHAN_TABLE_NAMES[givenTable],
				UNIHAN_TABLE_NAMES[extraTable],
				UNIHAN_TABLE_NAMES[givenTable],
				UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
				UNIHAN_TABLE_NAMES[extraTable],
				UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]
				);
			break;
		    case UNIHAN_FIELD_kZVARIANT:
			extraTable=unihanField_get_extra_table(givenField);
			g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
				UNIHAN_TABLE_NAMES[extraTable],
				UNIHAN_TABLE_NAMES[givenTable],
				UNIHAN_TABLE_NAMES[extraTable],
				UNIHAN_TABLE_NAMES[givenTable],
				UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
				UNIHAN_TABLE_NAMES[extraTable],
				UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
			break;
		    default:
			break;
		}
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

static void unihan_append_pinYinFreq_where_clause(GString *strBuf, UnihanField field,const char* composite_value){
    UnihanTable table=unihanField_get_table(field);
    GArray *gArray=pinYinFreqRec_parse(composite_value);
    char *strTmp=NULL;
    int i=0;
    PinYinFreqRec *rec=NULL;
    g_assert(table>=0);

    if (gArray->len>0){
	rec=&g_array_index(gArray,PinYinFreqRec,i);
	strTmp=sqlite3_mprintf(" %s.%s=%Q",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN],
		rec->pinYin);
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
	    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_kZVARIANT],
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
    char *valueTmp= NULL;
    if (unihanField_is_case_no_change(givenField)){
	valueTmp=g_strdup(value);
    }else if (unihanField_is_lowercase(givenField)){
	valueTmp=g_utf8_strdown(value,-1);
    }else{
	valueTmp=g_utf8_strup(value,-1);
    }

    if (unihanField_is_IRG_Source(givenField)){
	rec=unihanIRG_SourceRec_parse(givenField,valueTmp);
    }
    char *relStr=(qOption & UNIHAN_QUERY_OPTION_LIKE)? "LIKE": "=";
    char *strTmp=NULL;
    char *pinYinTmp=NULL;

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
	    case UNIHAN_FIELD_CODE:
		if (valueTmp[0]=='U'){
		    strTmp=sqlite3_mprintf("TO_SCALAR_STRING(%s.%s) %s %Q",
			    UNIHAN_TABLE_NAMES[fromTable],
			    UNIHAN_FIELD_NAMES[givenField],
			    relStr, valueTmp);
		}else{
		    strTmp=sqlite3_mprintf("%s.%s %s %Q",
			    UNIHAN_TABLE_NAMES[fromTable],
			    UNIHAN_FIELD_NAMES[givenField],
			    relStr, valueTmp);
		}
		break;
	    case UNIHAN_FIELD_kIRGKANGXI:
	    case UNIHAN_FIELD_kKANGXI:
		unihan_append_kangXi_where_clause(strBuf,givenField,valueTmp);
		break;
	    case UNIHAN_FIELD_kHANYUPINLU:
		unihan_append_pinYinFreq_where_clause(strBuf,givenField,valueTmp);
		break;
	    case UNIHAN_FIELD_kRSADOBE_JAPAN1_6:
		unihan_append_adobe_japan1_6_where_clause(strBuf,valueTmp);
		break;
	    case UNIHAN_FIELD_kRSJAPANESE:
	    case UNIHAN_FIELD_kRSKANGXI:
	    case UNIHAN_FIELD_kRSKANWA:
	    case UNIHAN_FIELD_kRSKOREAN:
	    case UNIHAN_FIELD_kRSUNICODE:
		unihan_append_radical_stroke_where_clause(strBuf, givenField, valueTmp);
		break;
	    case UNIHAN_FIELD_kSEMANTICVARIANT:
	    case UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT:
		unihan_append_semantic_where_clause(strBuf, givenField, valueTmp);
		break;
	    case UNIHAN_FIELD_kCOMPATIBILITYVARIANT:
	    case UNIHAN_FIELD_kSIMPLIFIEDVARIANT:
	    case UNIHAN_FIELD_kTRADITIONALVARIANT:
		strTmp=sqlite3_mprintf("%s.%s=SCALAR_STRING_PARSE(%Q)",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			valueTmp);
		break;
	    case UNIHAN_FIELD_kZVARIANT:
		unihan_append_zvariant_where_clause(strBuf, givenField, valueTmp);
		break;
	    case UNIHAN_FIELD_ZHUYIN:
		pinYinTmp=zhuYin_to_pinYin(valueTmp,PINYIN_ACCENT_UNIHAN,TRUE);
		strTmp=sqlite3_mprintf("%s.%s %s %Q",
			UNIHAN_TABLE_NAMES[UNIHAN_TABLE_kMANDARIN],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_kMANDARIN],
			relStr,
			pinYinTmp,
			valueTmp);
		g_free(pinYinTmp);
		break;
	    default:
		strTmp=sqlite3_mprintf("%s.%s %s %Q",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[givenField],
			relStr,valueTmp);

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
    }
    g_free(valueTmp);

    return g_string_free(strBuf,FALSE);
}

SQL_Result *unihan_find_all_matched(UnihanField givenField, const char *givenValue, 
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
	    case UNIHAN_FIELD_kSEMANTICVARIANT:
	    case UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT:
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

char* unihan_find_first_matched(UnihanField givenField, const char* givenValue, 
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
	GArray *pfArray=pinYinFreqRec_parse(value);
	if (pfArray->len>0){
	    PinYinFreqRec *rec=&g_array_index(pfArray,PinYinFreqRec,0);
	    stringList_insert(sList,rec->pinYin);
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

/*=================================
 * SQL wrapper functions.
 */

int unihanSql_exec(char *sqlClause, sqlite_exec_callback callback, 
	void *callbackOption,  char **errMsg_ptr){
    return sqlite3_exec(fieldCacheDb, sqlClause, callback, callbackOption, errMsg_ptr);
}

int unihanSql_count_matches(const char * sqlClause, char **errMsg_ptr){
    int ret=sqlite_count_matches(fieldCacheDb,sqlClause,errMsg_ptr);
    if (ret<0){
	verboseMsg_print(VERBOSE_MSG_ERROR, "Database error: %s\n", *errMsg_ptr);
    }
    return ret;
}

SQL_Result *unihanSql_get_sql_result(const char *sqlClause){
    return sqlite_get_sql_result(fieldCacheDb, sqlClause);
}


