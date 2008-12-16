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
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>
#include "allocate.h"
#include "collection.h"
#include "str_functions.h"
#include "verboseMsg.h"
#define MAX_STRING_BUFFER_SIZE 1000

/*=======================================
 * StringList functions
 */

#ifndef DEFAULT_G_STRING_CHUNK_SIZE
#define DEFAULT_G_STRING_CHUNK_SIZE 2048
#endif

StringList *stringList_new(){
    StringList *sList=NEW_INSTANCE(StringList);
    sList->chunk=g_string_chunk_new(DEFAULT_G_STRING_CHUNK_SIZE);
    sList->hTable=g_hash_table_new(g_str_hash,g_str_equal);
    sList->ptrArray=g_ptr_array_new();
    sList->chunk_size_inital=DEFAULT_G_STRING_CHUNK_SIZE;
    sList->len=0;
    g_ptr_array_add(sList->ptrArray,NULL);
    return sList;
}

StringList *stringList_sized_new(size_t chunk_size, size_t element_count){
    StringList *sList=NEW_INSTANCE(StringList);
    sList->chunk=g_string_chunk_new(chunk_size);
    sList->ptrArray=g_ptr_array_sized_new(element_count);
    sList->hTable=g_hash_table_new(g_str_hash,g_str_equal);
    sList->len=0;
    sList->chunk_size_inital= chunk_size;
    g_ptr_array_add(sList->ptrArray,NULL);
    return sList;
}

void stringList_clear(StringList *sList){
    g_assert(sList);
    sList->len=0;
    G_PTR_ARRAY_REMOVE_ALL(sList->ptrArray);
    g_ptr_array_add(sList->ptrArray,NULL);

    g_hash_table_remove_all(sList->hTable);
#ifdef HAVE_G_STRING_CHUNK_CLEAR
    g_string_chunk_clear(sList->chunk);
#else
    g_string_chunk_free(sList->chunk);
    sList->chunk=g_string_chunk_new(sList->chunk_size_inital);
#endif    
}

int stringList_find_string(StringList *sList,const gchar* str){
    guint i;
    for(i=0;i<sList->len;i++){
	if (strcmp(stringList_index(sList,i),str)==0){
	    return (int) i;
	}
    }
    return -1;
}

gchar **stringList_to_gcharPointerPointer(StringList *sList){
    return (gchar**) sList->ptrArray->pdata;
}

const gchar *stringList_index(StringList *sList,guint index){
    return g_ptr_array_index(sList->ptrArray,index);
}


guint stringList_insert(StringList *sList, const gchar *str){
    g_ptr_array_remove_index_fast (sList->ptrArray,sList->len);
    if (str){
	gchar *ptr=g_string_chunk_insert (sList->chunk,str);
	g_ptr_array_add(sList->ptrArray,ptr);
    }else{
	g_ptr_array_add(sList->ptrArray,NULL);
    }
    g_ptr_array_add(sList->ptrArray,NULL);
    sList->len++;
    return sList->len-1;


}

guint stringList_insert_const(StringList *sList, const gchar *str){
    g_ptr_array_remove_index_fast (sList->ptrArray,sList->len);
    gchar *strPtr=(gchar *) g_hash_table_lookup(sList->hTable,str);


    if (!strPtr){
	strPtr=g_string_chunk_insert_const (sList->chunk,str);
    }
    g_ptr_array_add(sList->ptrArray,strPtr);
    g_ptr_array_add(sList->ptrArray,NULL);
    sList->len++;
    return sList->len-1;
}

void stringList_free(StringList *sList){
    g_assert(sList);
    g_ptr_array_free(sList->ptrArray,TRUE);
    g_hash_table_destroy(sList->hTable);
    g_string_chunk_free(sList->chunk);
    g_free(sList);
}


// typedef gpointer (* Regex_Result_Callback) (gpointer option, const gchar* str, Regex_Result *result);

//RegexResult *regexResult_new(){
//    RegexResult *rResult=NEW_INSTANCE(RegexResult);
//    rResult->resultList=stringList_new();
//    rResult->startOffsets=g_array_new(FALSE,FALSE,int);
//    return rResult;
//}

//void regexResult_free(RegexResult *rResult){
//    stringList_free(rResult->resultList);
//    g_array_free(startOffsets,TRUE);
//    g_free(rResult);
//}

//RegexResult *regexResult_match_once_regex_t(regex_t *preg, const gchar* str, 
//        int eflags){
//    int i;
//    int nmatch=preg->re_nsub+1;
//    regmatch_t *pmatch=NEW_ARRAY_INSTANCE(nmatch,regmatch_t);
//    RegexResult *rResult=regexResult_new();

//    if (regexec(preg,currPtr,nmatch,pmatch,eflags)!=0){
//        /* No Match */
//        return rResult;
//    }
//    for(i=0;i<nmatch && pmatch[i].rm_so>=0;i++){
//        /* Put sub matchs ( pmatch[i] ) in rResult->resultList */
//        newStr=g_strndup(str+pmatch[i].rm_so, pmatch[counter].rm_eo - pmatch[i].rm_so);
//        stringList_insert(rResult->resultList,newStr);
//        g_array_append_val(rResult->startOffsets,pmatch[i].rm_so);
//        g_free(newStr);
//    }
//    g_free(pmatch);
//    return rResult;
//}

//RegexResult *regexResult_match_regex_t(regex_t *preg,const gchar* str, int eflags, 
//        guint regexResultFlags){
//    gchar *currPtr=(gchar *)str;
//    int len=strlen(str);
//    int i;
//    int counter=0;
//    gchar *newStr;
//    RegexResult *currResult=NULL:
//    RegexResult *rResult=regexResult_new();  
//    gchar *resultStr;
//    int resultStr_so,resultStr_eo;
//    int maxEo;
//    while(currPtr<str+len){
//        maxEo=-1;
//        currResult=regexResult_match_once_regex_t(preg, currPtr, eflags);
//        if (currResult->resultList->len<=0){
//            /* No Match */
//            break;
//        }

//        for(i=1; i< currResult->resultList->len ;i++){
//            if (i==0 && (regexResultFlags & REGEX_RESULT_EXCLUDE_MAJOR_MATCH)){
//                /* Exclude major match ( pmatch[0] ) from rResult->resultList and rResult->startOffsets */
//                continue;
//            }
//            if (i>0 && (regexResultFlags & REGEX_RESULT_EXCLUDE_SUB_MATCH)){
//                /* Exclude sub matchs ( pmatch[i] ) from rResult->resultList and rResult->startOffsets */
//                break;
//            }
//            resultStr=stringList_index(currResult->resultList,i);
//            stringList_insert(rResult->resultList,resultStr);
//            resultStr_so=g_array_index(currResult->startOffsets,int,i);
//            g_array_append_val(rResult->startOffsets, resultStr_so);
//            resultStr_eo=resultStr_so+strlen(resultStr);

//            maxEo=(maxEo >= resultStr_eo) ? maxEo : resultStr_eo;
//        }
//        regexResult_free(currResult);
//        if (regexResultFlags & REGEX_RESULT_MATCH_ONCE){
//            break;
//        }
//        if (regexResultFlags & REGEX_RESULT_ALLOW_OVERLAP){
//            currPtr++;
//        }else{
//            currPtr+=maxEo;
//        }
//    }
//    g_free(pmatch);
//    return rResult;
//}

//RegexResult *regexResult_match(const gchar *pattern,const gchar *str, 
//        int cflags, int eflags, guint regexResultFlags){
//    regex_t *preg=NULL;
//    int ret;
//    if ((ret=regcomp(preg, pattern, cflags))!=0){
//        /* Invalid pattern */
//        char buf[MAX_STRING_BUFFER_SIZE];
//        regerror(ret,preg,buf,MAX_STRING_BUFFER_SIZE);
//        verboseMsg_print(VERBOSE_MSG_ERROR, "regex_multiple_match():Invalid pattern %s\n"
//                ,buf);
//        return NULL;
//    }
//    RegexResult *rResult=regexResult_match_regex_t(preg, str, eflags, regexResultFlags );
//    regfree(preg);
//    return rResult;
//}

#define SUBPATTERN_FLAG_IS_INVALID		0x1
#define SUBPATTERN_FLAG_IS_DOLLARSIGN		0x2 	//'$'
#define SUBPATTERN_FLAG_IS_EMPTY		0x4 	//'E'
#define SUBPATTERN_FLAG_IS_NONEMPTY		0x8 	//'N'
#define SUBPATTERN_FLAG_IS_UPPERCASE		0x10	//'U'
#define SUBPATTERN_FLAG_IS_LOWERCASE		0x20	//'L'
#define SUBPATTERN_FLAG_IS_PLUS			0x40	//'+'
#define SUBPATTERN_FLAG_IS_MINUS		0x80	//'-'
#define SUBPATTERN_FLAG_IS_PADDED_LEFT		0x100 	//'P'
#define SUBPATTERN_FLAG_IS_PADDED_RIGHT		0x200 	//'p'
#define SUBPATTERN_FLAG_IS_HEXADECIMAL		0x400 	//'X'
#define SUBPATTERN_FLAG_IS_UTF8			0x800 	//'T'
#define SUBPATTERN_FLAG_IS_SUBSTRING		0x1000 	//'S'
#define SUBPATTERN_FLAG_IS_IDENTICAL			0x2000 	//'I'

typedef enum{
    REGEX_EVAL_STAGE_INIT,
    REGEX_EVAL_STAGE_FLAG,
    REGEX_EVAL_STAGE_INDEX,
    REGEX_EVAL_STAGE_OPTION1,
    REGEX_EVAL_STAGE_OPTION2,
    REGEX_EVAL_STAGE_OPTION3,
    REGEX_EVAL_STAGE_DONE
} RegexReplaceStage;


/* 
 * Return >=0: index of subpattern
 *         -1: escaped char, not error,
 *         -2: error
 */
static int string_formatted_output_expand_subSubIndex(const gchar *format, StringList *sList,guint *currPos_ptr, GString *optionStr){
    char c=format[*currPos_ptr];
    gboolean hasIndex=FALSE;
    int subIndex=0;
    if (c=='\0'){
	verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_expand_getSubSubIndex(): At character %d: Characters expected after '$'",*currPos_ptr);
	return -2;
    }
    while(isdigit(c)){
	hasIndex=TRUE;
	subIndex=subIndex*10+c-'0';
	c=format[*currPos_ptr++];
    }
    if (!hasIndex){
	/* No index, escaped  */
	g_string_append_c(optionStr,c);
	return -1;
    }
    if (subIndex>=sList->len){
	verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_expand_subSubIndex():index %d should be less than the number of string in stringList %d\n",subIndex,sList->len);
	return -2;
    }

    g_string_append(optionStr,stringList_index(sList,subIndex));
    guint currPos=*currPos_ptr--;
    verboseMsg_print(VERBOSE_MSG_INFO5,"***** string_formatted_output_expand_subSubIndex():currPos=%d\n",currPos);
    return subIndex;
}

/* 
 * Return >=0: index of subpattern
 *         -1: escaped char, not error,
 *         -2: error
 */
static int string_formatted_output_getSubIndex(const gchar *format, StringList *sList,guint *currPos_ptr, guint *statusFlags_ptr, 
	gchar **option1_ptr, gchar **option2_ptr, gchar **option3_ptr){
    int index=0;
    int subIndex=-1;
    *statusFlags_ptr=0;
    gchar c;
    gboolean error=FALSE;
    RegexReplaceStage stage=REGEX_EVAL_STAGE_INIT;
    GString *option1Str=NULL;
    GString *option2Str=NULL;
    GString *option3Str=NULL;
    *option1_ptr=*option2_ptr=*option3_ptr=NULL;
    verboseMsg_print(VERBOSE_MSG_INFO3,"*** string_formatted_getSubIndex() start\n");

    do{
    
	c=format[*currPos_ptr];
	verboseMsg_print(VERBOSE_MSG_INFO4,"**** string_formatted_getSubIndex() stage=%d c=%c(%d)\n",stage,c,c);
	switch(stage){
	    case REGEX_EVAL_STAGE_INIT:
		if (c=='\0'){
		    error=TRUE;
		    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t_getSubIndex(): At character %d: Characters expected after '$'",*currPos_ptr);
		    break;
		}
		if (isdigit(c)){
		    stage=REGEX_EVAL_STAGE_INDEX;
		    index=c-'0';
		    break;
		}
		if (c=='E'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_EMPTY;
		    break;
		}else if (c=='N'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_NONEMPTY;
		    break;
		}else if (c=='U'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_UPPERCASE;
		    break;
		}else if (c=='L'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_LOWERCASE;
		    break;
		}else if (c=='+'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_PLUS;
		    break;
		}else if (c=='-'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_MINUS;
		    break;
		}else if (c=='P'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_PADDED_LEFT;
		    break;
		}else if (c=='p'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_PADDED_RIGHT;
		    break;
		}else if (c=='X'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_HEXADECIMAL;
		    break;
		}else if (c=='T'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_UTF8;
		    break;
		}else if (c=='S'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_SUBSTRING;
		    break;
		}else if (c=='I'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_IDENTICAL;
		    break;
		}else if (c=='$'){
		    stage=REGEX_EVAL_STAGE_DONE;
		    *statusFlags_ptr |=SUBPATTERN_FLAG_IS_DOLLARSIGN;
		    break;
		}
		error=TRUE;
		verboseMsg_print(VERBOSE_MSG_ERROR,
			"string_formatted_output_regex_t_getSubIndex(): At character %d : Invalid flag %c.",
			*currPos_ptr,c);
		break;
	    case REGEX_EVAL_STAGE_FLAG:
		if (c=='\0'){
		    error=TRUE;
		    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t_getSubIndex(): No sub pattern index!\n");
		    break;
		}
		if (isdigit(c)){
		    stage=REGEX_EVAL_STAGE_INDEX;
		    index=index*10+c-'0';
		    break;
		}
		verboseMsg_print(VERBOSE_MSG_ERROR,
			"string_formatted_output_regex_t_getSubIndex(): At character %d : Should only have at most one flag.",
			*currPos_ptr);
		error=TRUE;
		break;

	    case REGEX_EVAL_STAGE_INDEX:
		if (isdigit(c)){
		    stage=REGEX_EVAL_STAGE_INDEX;
		    index=index*10+c-'0';
		    break;
		}
		if (c=='{'){
		    stage=REGEX_EVAL_STAGE_OPTION1;
		    break;
		}
		stage=REGEX_EVAL_STAGE_DONE;
		break;

	    case REGEX_EVAL_STAGE_OPTION1:
		if (c==','){
		    stage=REGEX_EVAL_STAGE_OPTION2;
		    break;
		}else if (c=='}'){
		    (*currPos_ptr)++;
		    stage=REGEX_EVAL_STAGE_DONE;
		    break;
		}
		if (!option1Str){
		    option1Str=g_string_new(NULL);
		}
		if (c=='$'){
		    (*currPos_ptr)++;
		    subIndex=string_formatted_output_expand_subSubIndex(format, sList,currPos_ptr,option1Str);
		    if (subIndex<=-2){
			/* Verbose message already printed in string_formatted_output_expand_subSubIndex() */
			error=TRUE;
			break;
		    }
		    break;
		}
		g_string_append_c(option1Str,c);
		break;

	    case REGEX_EVAL_STAGE_OPTION2:
		if (c==','){
		    stage=REGEX_EVAL_STAGE_OPTION3;
		    break;
		}else if (c=='}'){
		    (*currPos_ptr)++;
		    stage=REGEX_EVAL_STAGE_DONE;
		    break;
		}
		if (!option2Str){
		    option2Str=g_string_new(NULL);
		}
		if (c=='$'){
		    (*currPos_ptr)++;
		    subIndex=string_formatted_output_expand_subSubIndex(format, sList,currPos_ptr,option2Str);
		    if (subIndex<=-2){
			/* Verbose message already printed in string_formatted_output_expand_subSubIndex() */
			error=TRUE;
			break;
		    }
		    break;
		}
		g_string_append_c(option2Str,c);
		break;
	    case REGEX_EVAL_STAGE_OPTION3:
		if (c=='}'){
		    (*currPos_ptr)++;
		    stage=REGEX_EVAL_STAGE_DONE;
		    break;
		}
		if (!option3Str){
		    option3Str=g_string_new(NULL);
		}
		if (c=='$'){
		    (*currPos_ptr)++;
		    subIndex=string_formatted_output_expand_subSubIndex(format, sList,currPos_ptr,option2Str);
		    if (subIndex<=-2){
			/* Verbose message already printed in string_formatted_output_expand_subSubIndex() */
			error=TRUE;
			break;
		    }
		    break;
		}
		g_string_append_c(option3Str,c);
		break;
	    case REGEX_EVAL_STAGE_DONE:
		break;
	}
	if (!error && stage!=REGEX_EVAL_STAGE_DONE){
	    (*currPos_ptr)++;
	}
    }while(!error && stage!=REGEX_EVAL_STAGE_DONE);
    verboseMsg_print(VERBOSE_MSG_INFO3,"*** string_formatted_getSubIndex() stage=%d error=%d\n",stage,error);
    if (error){
	if (option1Str)
	    g_string_free(option1Str,TRUE);

	if (option2Str)
	    g_string_free(option2Str,TRUE);

	if (option3Str)
	    g_string_free(option3Str,TRUE);
	verboseMsg_print(VERBOSE_MSG_INFO3,"*** string_formatted_getSubIndex() return -2\n");
	return -2;
    }

    if (*statusFlags_ptr & SUBPATTERN_FLAG_IS_DOLLARSIGN){
	if (option1Str)
	    g_string_free(option1Str,TRUE);

	if (option2Str)
	    g_string_free(option2Str,TRUE);
	
	if (option3Str)
	    g_string_free(option3Str,TRUE);
	verboseMsg_print(VERBOSE_MSG_INFO3,"*** string_formatted_getSubIndex() return -1\n");
	return -1;
    }

    if (option1Str)
	*option1_ptr=g_string_free(option1Str,FALSE);

    if (option2Str)
	*option2_ptr=g_string_free(option2Str,FALSE);

    if (option3Str)
	*option3_ptr=g_string_free(option3Str,FALSE);
    verboseMsg_print(VERBOSE_MSG_INFO3,"*** string_formatted_getSubIndex() return %d\n",index);
    return index;
}

gchar *string_formatted_output(const gchar *format,StringList *sList,int *counter_ptr){
    GString *strBuf=g_string_new(NULL);

    int subIndex=0;
    gunichar ucs4_code;
    guint j,formatLen=strlen(format);
    guint statusFlags;
    gboolean error=FALSE;
    const gchar *str=NULL;
    gchar *option1Str=NULL;
    gchar *option2Str=NULL;
    gchar *option3Str=NULL;
    gchar *strtolEnd_ptr=NULL;
    gchar *strTmp=NULL;
    gchar *paddedStr;
    int beginIndex,length;
    gchar buf[MAX_STRING_BUFFER_SIZE];

    for(j=0;j<formatLen && (!error);j++){
	verboseMsg_print(VERBOSE_MSG_INFO3,"*** string_formatted_output():Current strBuf=%s|\n",strBuf->str);
	if (format[j]=='$'){
	    j++;
	    subIndex=string_formatted_output_getSubIndex(format, sList, &j, &statusFlags,  
		    &option1Str, &option2Str, &option3Str);
	    paddedStr=NULL;
	    if (verboseMsg_get_level()>=VERBOSE_MSG_INFO4){
		verboseMsg_print(VERBOSE_MSG_INFO4,"**** string_formatted_output(): j=%d, subIndex=%d",j,subIndex);
		if (option1Str){
		    verboseMsg_print(VERBOSE_MSG_INFO4," option1Str=%s",option1Str);
		}
		if (option2Str){
		    verboseMsg_print(VERBOSE_MSG_INFO4," option2Str=%s",option2Str);
		}
		if (option3Str){
		    verboseMsg_print(VERBOSE_MSG_INFO4," option3Str=%s",option3Str);
		}
		verboseMsg_print(VERBOSE_MSG_INFO4,"\n");
	    }
	    if (subIndex>=0){
		if (subIndex>=sList->len){
		    error=TRUE;
		    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output():index %d should be less than the number of string in stringList %d\n",subIndex,sList->len);
		    break;
		}
		str=stringList_index(sList,subIndex);
		if (isEmptyString(str)){
		    /* This substring is not empty */
		    if (statusFlags & SUBPATTERN_FLAG_IS_EMPTY && option1Str){
			g_string_append(strBuf,option1Str);
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_NONEMPTY && option2Str){
			g_string_append(strBuf,option2Str);
		    }
		}else{
		    /* This substring is not empty */
		    if (statusFlags & SUBPATTERN_FLAG_IS_NONEMPTY){
			if (option1Str)
			    g_string_append(strBuf,option1Str);
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_EMPTY){
			if (option2Str)
			    g_string_append(strBuf,option2Str);
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_UPPERCASE){
			strTmp=g_utf8_strup(str,-1);
			g_string_append(strBuf,strTmp);
			g_free(strTmp);
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_LOWERCASE){
			strTmp=g_utf8_strdown(str,-1);
			g_string_append(strBuf,strTmp);
			g_free(strTmp);
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_PADDED_LEFT){
			length=(int) strtol(option1Str,&strtolEnd_ptr,10);
			verboseMsg_print(VERBOSE_MSG_INFO4,
				"**** string_formatted_output() SUBPATTERN_FLAG_IS_PADDED_LEFT length=%d\n",
				length);
			if (strtolEnd_ptr==option1Str){
			    /* Length is not number! */
			    error=TRUE;
			    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t():index %d:  should have an integer number instead of %s\n",subIndex,option1Str);
			    break;
			}
			if (option2Str){
			    paddedStr=option2Str;
			}else{
			    paddedStr=" ";
			}
			strTmp=string_padding_left(str,paddedStr,length);
			g_string_append(strBuf,strTmp);
			g_free(strTmp);
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_PADDED_RIGHT){
			length=(int) strtol(option1Str,&strtolEnd_ptr,10);
			verboseMsg_print(VERBOSE_MSG_INFO4,
				"**** string_formatted_output() SUBPATTERN_FLAG_IS_PADDED_RIGHT length=%d\n",
				length);
			if (strtolEnd_ptr==option1Str){
			    /* Length is not number! */
			    error=TRUE;
			    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t():index %d:  should have an integer number instead of %s\n",subIndex,option1Str);
			    break;
			}
			if (option2Str){
			    paddedStr=option2Str;
			}else{
			    paddedStr=" ";
			}
			strTmp=string_padding_right(str,paddedStr,length);
			g_string_append(strBuf,strTmp);
			g_free(strTmp);
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_PLUS && counter_ptr){
			g_string_append_printf(strBuf,"%d",++(*counter_ptr));
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_MINUS && counter_ptr){
			g_string_append_printf(strBuf,"%d",--(*counter_ptr));
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_HEXADECIMAL){
				ucs4_code=(gunichar) strtol(str,&strtolEnd_ptr,10);
			verboseMsg_print(VERBOSE_MSG_INFO4,"**** string_formatted_output() ucs_code=%ld(%X)\n"
				,ucs4_code,ucs4_code);
			if (strtolEnd_ptr==str){
			    /* Number string is expected. */
			    error=TRUE;
			    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t():index %d:  should have an integer number instead of %s\n",subIndex,str);
			    break;
			}
			g_snprintf(buf,MAX_STRING_BUFFER_SIZE,"%X",ucs4_code);
			if (option1Str){
			    length=(int) strtol(option1Str,&strtolEnd_ptr,10);
			    if (strtolEnd_ptr==option1Str){
				/* Length is not number! */
				error=TRUE;
				verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t():index %d:  should have an integer number instead of %s\n",subIndex,option1Str);
				break;
			    }
			    strTmp=string_padding_left(buf,"0",length);
			    g_string_append(strBuf,strTmp);
			    g_free(strTmp);
			}else{
			    g_string_append(strBuf,buf);
			}
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_UTF8){
			ucs4_code=(gunichar) strtol(str,&strtolEnd_ptr,10);
			if (strtolEnd_ptr==str){
			    /* Number string is expected. */
			    error=TRUE;
			    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t():index %d:  should have an integer number instead of %s\n",subIndex,str);
			    break;
			}
			strTmp=ucs4_to_utf8(ucs4_code);
			g_string_append(strBuf,strTmp);
			g_free(strTmp);
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_SUBSTRING){
			verboseMsg_print(VERBOSE_MSG_INFO4,
				"**** string_formatted_output() SUBPATTERN_FLAG_IS_SUBSTRING\n");
			if (option1Str){
			    beginIndex=(int) strtol(option1Str,&strtolEnd_ptr,10);
			    if (strtolEnd_ptr==option1Str){
				/* Start is not number! */
				error=TRUE;
				verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t():index %d:  should have an integer number instead of %s\n",subIndex,option1Str);
				break;
			    }
			}else{
			    /* No Start ! */
			    error=TRUE;
			    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t():index %d:  should have an integer number as start!\n",subIndex);
			    break;
			}
			if (option2Str){
			    length=(int) strtol(option2Str,&strtolEnd_ptr,10);
			    if (strtolEnd_ptr==option2Str){
				/* Length is not number! */
				error=TRUE;
				verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_output_regex_t():index %d:  should have an integer number instead of %s\n",subIndex,option2Str);
				break;
			    }
			}else{
			    length=-1;
			}
			subString_buffer(buf,str,beginIndex,length);
			g_string_append(strBuf,buf);
		    }else if (statusFlags & SUBPATTERN_FLAG_IS_IDENTICAL){
			verboseMsg_print(VERBOSE_MSG_INFO4,
				"**** string_formatted_output() SUBPATTERN_FLAG_IS_IDENTICAL\n");
			if (!option1Str){
			    /* No expression ! */
			    error=TRUE;
			    verboseMsg_print(VERBOSE_MSG_ERROR,
				    "string_formatted_output_regex_t():index %d: flag I require compare_str\n");
			    break;
			}
			if (!option2Str){
			    /* No true substitute ! */
			    error=TRUE;
			    verboseMsg_print(VERBOSE_MSG_ERROR,
				    "string_formatted_output_regex_t():index %d: flag I require true substitute\n");
			    break;
			}

			if (strcmp(str,option1Str)==0){
			    g_string_append(strBuf,option2Str);
			}else if (option3Str){
			    g_string_append(strBuf,option3Str);
			}
		    }else{
			g_string_append(strBuf,str);
		    }
		}
		j--;
		if (option1Str)
		    g_free(option1Str);
		if (option2Str)
		    g_free(option2Str);
		if (option3Str)
		    g_free(option3Str);
	    }else if (subIndex==-1){
		/* Dollar sign */
		g_string_append_c(strBuf,'$');
	    }else{
		/* replace pattern error */
		error=TRUE;
		break;
	    }
	}else{
	    /* Normal character */
	    g_string_append_c(strBuf,format[j]);
	}
    }
    if (error){
	g_string_free(strBuf,TRUE);
	return NULL;
    }
    return g_string_free(strBuf,FALSE);
    
}

static gchar *string_get_matched_substring(const gchar *str, regmatch_t *pmatch, guint index){
    if (pmatch[index].rm_so<0 || pmatch[index].rm_so==pmatch[index].rm_eo){
	return NULL;
    }
    gchar *result=NEW_ARRAY_INSTANCE(pmatch[index].rm_eo-pmatch[index].rm_so+1,gchar);
    int i;
    for(i=0;i<pmatch[index].rm_eo-pmatch[index].rm_so;i++){
	result[i]=str[pmatch[index].rm_so+i];
    }
    result[i]='\0';
    return result;
}

gchar *string_regex_formatted_output_regex_t(const gchar *str, const regex_t *preg, const gchar *format, 
	int eflags, int *counter_ptr){
    guint nmatch=preg->re_nsub+1;
    regmatch_t *pmatch=NEW_ARRAY_INSTANCE(nmatch,regmatch_t);
    if (regexec(preg,str,nmatch,pmatch,eflags)!=0){
	/* No Match */
	return NULL;
    }
    guint i;
    gchar *strTmp=NULL;


    StringList *sList=stringList_new();
    for(i=0;i<nmatch;i++){
	if ( pmatch[i].rm_so<0 || pmatch[i].rm_so==pmatch[i].rm_eo){
	    /* This subpattern is empty */
	    stringList_insert(sList,NULL);
	}else{
	    /* This subpattern is not empty */
	    strTmp=string_get_matched_substring(str,pmatch,i);
	    stringList_insert(sList,strTmp);
	    g_free(strTmp);
	}
    }
    gchar *result=string_formatted_output(format,sList,counter_ptr);
    stringList_free(sList);
    return result;
}

gchar *string_regex_formatted_output(const gchar *str, const gchar *pattern, const gchar *format, 
	int cflags, int eflags, int *counter_ptr){


    regex_t preg;
    int ret;

    if ((ret=regcomp(&preg, pattern, cflags))!=0){
	/* Invalid pattern */
	char buf[MAX_STRING_BUFFER_SIZE];
	regerror(ret,&preg,buf,MAX_STRING_BUFFER_SIZE);
	verboseMsg_print(VERBOSE_MSG_ERROR, "string_formatted_output():Invalid pattern %s\n"
		,buf);
	return NULL;
    }
    gchar *result=string_regex_formatted_output_regex_t(str, &preg, format, eflags, counter_ptr);
    regfree(&preg);
    return result;
}


gchar *string_regex_replace_regex_t(const gchar *str, const regex_t *preg, const gchar *format, 
	int eflags, int *counter_ptr){

    guint i;
    guint len=strlen(str);
    guint nmatch=preg->re_nsub+1;
    regmatch_t *pmatch=NEW_ARRAY_INSTANCE(nmatch,regmatch_t);
    if (regexec(preg,format,nmatch,pmatch,eflags)!=0){
	/* No Match */
	return NULL;
    }

    GString *strBuf=g_string_sized_new(len);

    /* Chars before matched */
    for(i=0;i<pmatch[0].rm_so;i++){
	g_string_append_c(strBuf,str[i]);
    }

    gchar *evalStr=string_regex_formatted_output_regex_t(str, preg, format, eflags, counter_ptr);
    
    if (evalStr){
	g_string_append(strBuf,evalStr);
	g_free(evalStr);
    }else{
	g_string_free(strBuf,TRUE);
	return NULL;
    }


    /* Char after matched */
    for(i=pmatch[0].rm_eo;i<len;i++){
	g_string_append_c(strBuf,str[i]);
    }

    return g_string_free(strBuf,FALSE);
}

gchar *string_regex_replace(const gchar *str, const gchar *pattern, const gchar *format, 
	int cflags, int eflags, int *counter_ptr){

    regex_t preg;
    int ret;
    if ((ret=regcomp(&preg, pattern, cflags))!=0){
	/* Invalid pattern */
	char buf[MAX_STRING_BUFFER_SIZE];
	regerror(ret,&preg,buf,MAX_STRING_BUFFER_SIZE);
	verboseMsg_print(VERBOSE_MSG_ERROR, "string_regex_replace():Invalid pattern %s\n"
		,buf);
	return NULL;
    }
    gchar *result=string_regex_formatted_output_regex_t(str, &preg, format, eflags, counter_ptr);
    regfree(&preg);
    return result;
}



gchar*
initString(gchar *str){
    if (str==NULL){
        str=(gchar *) NEW_ARRAY_INSTANCE(MAX_STRING_BUFFER_SIZE,gchar);
    }
    str[0]='\0';
    return str;
}

gboolean
isEmptyString(const gchar *str){
    if (str==NULL)
        return TRUE;
    if (strlen(str)==0)
        return TRUE;
    return FALSE;
}

static gchar* string_padding(const gchar *str, const gchar *padding_str, size_t length, gboolean left){
    int len=strlen(str);
    int len_padding=strlen(padding_str);
    int i=0;
    /* length need to be convert as signed */
    int len_fill=(int) (length-len-len_padding+1);
    GString *strBuf=g_string_new(NULL);
    if (left){
	for(i=0; i<len_fill ;i+=len_padding){
	    g_string_append(strBuf,padding_str);
	}
    }
    g_string_append(strBuf,str);
    if (!left){
	for(i=0;i<len_fill;i+=len_padding){
	    g_string_append(strBuf,padding_str);
	}
    }
    return g_string_free(strBuf,FALSE);
}

gchar* string_padding_left(const gchar *str, const gchar *padding_str, size_t length){
    return string_padding(str, padding_str, length, TRUE);
}

gchar* string_padding_right(const gchar *str, const gchar *padding_str, size_t length){
    return string_padding(str, padding_str, length, FALSE);
}

void string_trim(gchar *str){
    int i,j,k,len=strlen(str);
    gboolean whiteSpaces=TRUE;
    for(i=len-1;i>=0;i--){
	switch(str[i]){
	    case ' ':
	    case '\n':
	    case '\t':
	    case '\r':
		break;
	    default:
		whiteSpaces=FALSE;
		break;
	}
	if (!whiteSpaces){
	    break;
	}
    }
    if (i==0 && whiteSpaces){
	str[0]='\0';
	return;
    }
    str[i+1]='\0';
    whiteSpaces=TRUE;

    for(j=0;j<i;j++){
	switch(str[j]){
	    case ' ':
	    case '\n':
	    case '\t':
	    case '\r':
		break;
	    default:
		whiteSpaces=FALSE;
		break;
	}
	if (!whiteSpaces){
	    break;
	}
    }

    for(k=0;k< i-j+1;k++){
	str[k]=str[k+j];
    }
    str[k]='\0';
}

gchar*
subString(const gchar *str,int beginIndex,int length){
    size_t actualLength= (length >=0)? length: strlen(str)-beginIndex;
    gchar *buf=NEW_ARRAY_INSTANCE(actualLength+1,gchar);
    return subString_buffer(buf, str, beginIndex, length);
}


gchar*
subString_buffer(gchar *buf, const gchar *str,int beginIndex, int length){
    int i;
    for(i=0;str[i+beginIndex]!='\0';i++){
	if (length>=0 && i>=length){
	    break;
	}
	buf[i]=str[beginIndex+i];
    }
    buf[i]='\0';
    return buf;
}



gunichar* utf8_to_ucs4(const gchar* utf8_str){
    glong items_read;
    glong items_written;
    GError *err = NULL;
    gunichar*   ucs4Str=g_utf8_to_ucs4(utf8_str, -1,&items_read, &items_written, &err);
    if (err!=NULL){
	verboseMsg_print(VERBOSE_MSG_CRITICAL,"UTF-8 to UCS-4 conversion error: on char %ld in \"%s\"\n",items_read,utf8_str);
	verboseMsg_print(VERBOSE_MSG_CRITICAL,"Error message:  \"%s\"\n",err->message);
	exit(1);
    }
    return ucs4Str;
}

gchar* ucs4_to_utf8(gunichar ucs4_code){
    gchar *utf8_str;
    gint len=g_unichar_to_utf8(ucs4_code,NULL);
    utf8_str=NEW_ARRAY_INSTANCE(MAX(len+1,6),gchar);
    g_unichar_to_utf8(ucs4_code,utf8_str);
    utf8_str[len]='\0';
    return utf8_str;
}

gchar* utf8_concat_ucs4(gchar* utf8_str,gunichar ucs4_code){
    gchar *ucs4_str=ucs4_to_utf8(ucs4_code);
    strcat(utf8_str,ucs4_str);
    g_free(ucs4_str);
    return utf8_str;
}

int strcmp_unsigned_signed(const unsigned char *str1, const gchar *str2){
    int c1, c2,i=0;
    do{
	c1=(int) str1[i];
	c2=(int) str2[i];
	if (c1<c2){
	    return -1;
	}else if (c2<c1){
	    return 1;
	}
	i++;
    }while(c1!=0 && c2!=0 );
    return 0;
}

unsigned char *signedStr_to_unsignedStr(const gchar *str){
    unsigned char *cloneStr=NEW_ARRAY_INSTANCE(strlen(str)+1,unsigned char);
    unsigned char *result=signedStr_to_unsignedStr_buffer(cloneStr,str);
    if (!result)
	g_free(cloneStr);
    return result;
}

unsigned char *signedStr_to_unsignedStr_buffer(unsigned char *resultBuf, const gchar *str){
    unsigned char c;
    int i=0;
    do{
	c=(unsigned char) str[i];
	resultBuf[i]=c;
	i++;
    }while(c!=0 );
    return resultBuf;
}

gchar *unsignedStr_to_signedStr(const unsigned char *str){
    gchar* cloneStr=NEW_ARRAY_INSTANCE(strlen((const gchar *)str)+1,gchar);
    gchar *result=unsignedStr_to_signedStr_buffer(cloneStr,str);
    if (!result)
	g_free(cloneStr);
    return result;
}

gchar *unsignedStr_to_signedStr_buffer(gchar* resultBuf, const unsigned char *str){
    gchar c;
    int i=0;
    do{
	c=(gchar) str[i];
	resultBuf[i]=c;
	i++;
    }while(c!=0 );
    return resultBuf;
}

int longestCommonSubsequence_get_length(const gchar *s1, const gchar *s2, int ***lcsTablePtr){
    int n1=strlen(s1);
    int n2=strlen(s2);
    int **table= NEW_ARRAY2D_INSTANCE(n2,n1,int);
    int i1,i2;
    int prev;
    for(i2=n2-1;i2>=0;i2--){
	for(i1=n1-1;i1>=0;i1--){
	    if (i2==n2-1){
		if (i1==n1-1){
		    prev=0;
		}else{
		    prev=table[i2][i1+1];
		}
	    }else{
		if (i1==n1-1){
		    prev=table[i2+1][i1];
		}else{
		    prev=(table[i2+1][i1] >= table[i2][i1+1] ) ? table[i2+1][i1] : table[i2][i1+1];
		}
	    }

	    if (s2[i2]==s1[i1]){
		table[i2][i1]=prev+1;
	    }else{
		table[i2][i1]=prev;
	    }
	}
    }
    *lcsTablePtr=table;
    return table[0][0];
}


gchar* longestCommonSubsequence_get_subsequence(const gchar *s1, const gchar *s2, int **lcsTable){
    int n1=strlen(s1);
    int n2=strlen(s2);
    int len=lcsTable[0][0];
    if (len==0){
	return NULL;
    }
    gchar *subsequence= (gchar *) calloc(len+1,sizeof(gchar));
    int i1=0,i2=0;
    int counter=0;
    subsequence[len]='\0';
    while(counter<len){
	if (s1[i1]==s2[i2]){
	    subsequence[counter++]=s1[i1];
	    i1++; i2++;
	    continue;
	}
	if (i2==n2-1){
	    i1++;
	    g_assert(i1<n1);
	    continue;
	}
	if (i1==n1-1){
	    i2++;
	    g_assert(i2<n2);
	    continue;
	}

	if (lcsTable[i2+1][i1]>=lcsTable[i2][i1+1]){
	    i2++;
	}else{
	    i1++;
	}
    }
    return subsequence;
}


//int main(int argc, gchar** argv){
//    int **table=NULL;
//    int len=longestCommonSubsequence_get_length(argv[1],argv[2], &table);
//    gchar* str=longestCommonSubsequence_get_subsequence(argv[1],argv[2], table);
//    if (str==NULL)
//        str="NULL";
//    printf("lcs length:%d, subsequence:%s\n",len,str);
//    array2D_free((void **)table);
//    return 0;
//}
