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
#define STRING_BUFFER_SIZE_DEFAULT 1000


/*=======================================
 * StringPtrList functions
 */
StringPtrList *stringPtrList_new(){
    StringPtrList *sPtrList=g_ptr_array_new();
    g_ptr_array_add(sPtrList,NULL);
    return sPtrList;
}

StringPtrList *stringPtrList_sized_new(size_t element_count){
    StringPtrList *sPtrList=g_ptr_array_sized_new(element_count);
    g_ptr_array_add(sPtrList,NULL);
    return sPtrList;
}

void stringPtrList_clear(StringPtrList *sPtrList){
    gint i,len=sPtrList->len-1;
    for(i=0;i<len;i++){
	gchar *str=g_ptr_array_index(sPtrList,i);
	g_free(str);
    }
    g_ptr_array_remove_range(sPtrList,0,len);
}

gint stringPtrList_find_string(StringPtrList *sPtrList,const gchar* str){
    gint i,len=sPtrList->len-1;
    for(i=0;i<len;i++){
	if (strcmp(g_ptr_array_index(sPtrList,i),str)==0){
	    return i;
	}
    }
    return -1;
}

void stringPtrList_free_deep(StringPtrList *sPtrList){
    stringPtrList_clear(sPtrList);
    g_ptr_array_free(sPtrList,TRUE);
}

gboolean stringPtrList_has_string(StringPtrList *sPtrList,const gchar* str){
    if (stringPtrList_find_string(sPtrList,str)<0)
	return FALSE;
    return TRUE;
}

const gchar *stringPtrList_index(StringPtrList *sPtrList,guint index){
    return g_ptr_array_index(sPtrList,index);
}

static guint stringPtrList_insert_private(StringPtrList *sPtrList, const gchar *strPtr){
    sPtrList->pdata[sPtrList->len-1] = (gpointer) strPtr;
    g_ptr_array_add(sPtrList,NULL);
    return sPtrList->len-1;
}

gint stringPtrList_insert(StringPtrList *sPtrList, const gchar *str){
    return stringPtrList_insert_private(sPtrList, str);
}

gchar **stringPtrList_to_gcharPointerPointer(StringPtrList *sPtrList){
    return (gchar**) sPtrList->pdata;
}

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
    sList->ptrArray=stringPtrList_new();
    sList->chunk_size_inital=DEFAULT_G_STRING_CHUNK_SIZE;
    sList->len=0;
    return sList;
}

StringList *stringList_sized_new(size_t chunk_size, size_t element_count){
    StringList *sList=NEW_INSTANCE(StringList);
    sList->chunk=g_string_chunk_new(chunk_size);
    sList->ptrArray=stringPtrList_sized_new(element_count);
    sList->hTable=g_hash_table_new(g_str_hash,g_str_equal);
    sList->chunk_size_inital= chunk_size;
    sList->len=0;
    return sList;
}

StringList *stringList_new_strsplit_set(const gchar *string, const gchar *delimiters, gint max_tokens){
    StringList *sList=stringList_new();
    gchar **string_set=g_strsplit_set(string,delimiters,max_tokens);
    gint i;
    for(i=0;string_set[i]!=NULL;i++){
	stringList_insert(sList,string_set[i]);
    }
    g_strfreev(string_set);
    return sList;
//    GString *strBuf=g_string_new(NULL);
//    gint counter=0,i=-1;
//    gint j,jLen=strlen(delimiters);
//    gboolean isDelimiter;
//    while(string[++i]!='\0'){
//        if (max_tokens>0 && counter>=max_tokens){
//            g_string_free(strBuf, TRUE);
//            return sList;
//        }
//        isDelimiter=FALSE;
//        for(j=0;j<jLen;j++){
//            if (string[i]==delimiters[j]){
//                isDelimiter=TRUE;
//                break;
//            }
//        }
//        if (isDelimiter){
//            if (strBuf->len>0){
//                stringList_insert(sList,strBuf->str);
//                g_string_set_size(strBuf,0);
//                counter++;
//            }
//            continue;
//        }
//        g_string_append_c(strBuf,string[i]);
//    }
//    if (strBuf->len>0){
//        stringList_insert(sList,strBuf->str);
//    }
//    g_string_free(strBuf, TRUE);
//    return sList;
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

gint stringList_find_string(StringList *sList,const gchar* str){
    return stringPtrList_find_string(sList->ptrArray,str);
}

gboolean stringList_has_string(StringList *sList,const gchar* str){
    if (stringList_find_string(sList,str)<0)
	return FALSE;
    return TRUE;
}

gchar **stringList_to_gcharPointerPointer(StringList *sList){
    return stringPtrList_to_gcharPointerPointer(sList->ptrArray);
}

const gchar *stringList_index(StringList *sList,guint index){
    return g_ptr_array_index(sList->ptrArray,index);
}

guint stringList_insert(StringList *sList, const gchar *str){
    gchar *strPtr=NULL;
    if (str){
	strPtr=g_string_chunk_insert (sList->chunk,str);
    }
    sList->len++;
    return stringPtrList_insert_private(sList->ptrArray, strPtr);
}

guint stringList_insert_const(StringList *sList, const gchar *str){
    gchar *strPtr=(gchar *) g_hash_table_lookup(sList->hTable,str);
    if (!strPtr){
	strPtr=g_string_chunk_insert_const (sList->chunk,str);
    }
    sList->len++;
    return stringPtrList_insert_private(sList->ptrArray, strPtr);
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
//        gint eflags){
//    gint i;
//    gint nmatch=preg->re_nsub+1;
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

//RegexResult *regexResult_match_regex_t(regex_t *preg,const gchar* str, gint eflags,
//        guint regexResultFlags){
//    gchar *currPtr=(gchar *)str;
//    gint len=strlen(str);
//    gint i;
//    gint counter=0;
//    gchar *newStr;
//    RegexResult *currResult=NULL:
//    RegexResult *rResult=regexResult_new();
//    gchar *resultStr;
//    gint resultStr_so,resultStr_eo;
//    gint maxEo;
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
//        gint cflags, gint eflags, guint regexResultFlags){
//    regex_t *preg=NULL;
//    gint ret;
//    if ((ret=regcomp(preg, pattern, cflags))!=0){
//        /* Invalid pattern */
//        char buf[STRING_BUFFER_SIZE_DEFAULT];
//        regerror(ret,preg,buf,STRING_BUFFER_SIZE_DEFAULT);
//        verboseMsg_print(VERBOSE_MSG_ERROR, "regex_multiple_match():Invalid pattern %s\n"
//                ,buf);
//        return NULL;
//    }
//    RegexResult *rResult=regexResult_match_regex_t(preg, str, eflags, regexResultFlags );
//    regfree(preg);
//    return rResult;
//}

#define SUBPATTERN_FLAG_IS_ESCAPED		0x1     //'$' or escaped character
#define SUBPATTERN_FLAG_IS_EMPTY		0x2 	//'E'
#define SUBPATTERN_FLAG_IS_NONEMPTY		0x4 	//'N'
#define SUBPATTERN_FLAG_IS_UPPERCASE		0x8	//'U'
#define SUBPATTERN_FLAG_IS_LOWERCASE		0x10	//'L'
#define SUBPATTERN_FLAG_IS_PLUS			0x20	//'+'
#define SUBPATTERN_FLAG_IS_MINUS		0x40	//'-'
#define SUBPATTERN_FLAG_IS_PADDED_LEFT		0x80 	//'P'
#define SUBPATTERN_FLAG_IS_PADDED_RIGHT		0x100 	//'p'
#define SUBPATTERN_FLAG_IS_HEXADECIMAL		0x200 	//'X'
#define SUBPATTERN_FLAG_IS_UTF8			0x400 	//'T'
#define SUBPATTERN_FLAG_IS_SUBSTRING		0x800 	//'S'
#define SUBPATTERN_FLAG_IS_IDENTICAL		0x1000 	//'I'

typedef enum{
    REGEX_EVAL_STAGE_INIT,
    REGEX_EVAL_STAGE_FLAG,
    REGEX_EVAL_STAGE_INDEX,
    REGEX_EVAL_STAGE_OPTION1,
    REGEX_EVAL_STAGE_OPTION2,
    REGEX_EVAL_STAGE_OPTION3,
    REGEX_EVAL_STAGE_DONE
} RegexReplaceStage;

typedef struct {
    gint errno;
    gint index;
    guint statusFlags;
    gchar *option1;
    gchar *option2;
    gchar *option3;
} FormattedCombineDirective;

static FormattedCombineDirective *formattedCombineDirective_new(){
    FormattedCombineDirective *directive=NEW_INSTANCE(FormattedCombineDirective);
    directive->errno=0;
    directive->index=0;
    directive->statusFlags=0;
    directive->option1=directive->option2=directive->option3=NULL;
    return directive;
};

static void formattedCombineDirective_free(FormattedCombineDirective* directive){
    g_free(directive->option1);
    g_free(directive->option2);
    g_free(directive->option3);
    g_free(directive);
};

static gint  string_formatted_combine_expand_directive(
	GString *strBuf, StringPtrList *sPtrList, gint *counter_ptr, FormattedCombineDirective* directive);

/*
 * errno 0: index of subpattern
 *       >0: error
 */
static FormattedCombineDirective* string_formatted_combine_get_directive(
	const gchar *format, StringPtrList *sPtrList,guint *currPos_ptr,gint *counter_ptr){
    gchar c;
    RegexReplaceStage stage=REGEX_EVAL_STAGE_INIT;
    GString *option1Str=NULL;
    GString *option2Str=NULL;
    GString *option3Str=NULL;
    verboseMsg_print(VERBOSE_MSG_INFO5,"*** string_formatted_combine_get_directive() start\n");
    FormattedCombineDirective *directive=formattedCombineDirective_new();
    FormattedCombineDirective *subDirective=NULL;
    gint ret;

    do{
	c=format[*currPos_ptr];
	verboseMsg_print(VERBOSE_MSG_INFO6,
		"**** string_formatted_combine_get_directive() stage=%d c=%c(%d)\n",stage,c,c);
	switch(stage){
	    case REGEX_EVAL_STAGE_INIT:
		if (c=='\0'){
		    directive->errno=1;
		    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_get_directive(): ");
		    verboseMsg_print(VERBOSE_MSG_ERROR,"At character %u: Characters expected after '$'\n",*currPos_ptr);
		    break;
		}
		if (isdigit(c)){
		    stage=REGEX_EVAL_STAGE_INDEX;
		    directive->index=c-'0';
		    break;
		}
		if (c=='E'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_EMPTY;
		    break;
		}else if (c=='N'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_NONEMPTY;
		    break;
		}else if (c=='U'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_UPPERCASE;
		    break;
		}else if (c=='L'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_LOWERCASE;
		    break;
		}else if (c=='+'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_PLUS;
		    break;
		}else if (c=='-'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_MINUS;
		    break;
		}else if (c=='P'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_PADDED_LEFT;
		    break;
		}else if (c=='p'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_PADDED_RIGHT;
		    break;
		}else if (c=='X'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_HEXADECIMAL;
		    break;
		}else if (c=='T'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_UTF8;
		    break;
		}else if (c=='S'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_SUBSTRING;
		    break;
		}else if (c=='I'){
		    stage=REGEX_EVAL_STAGE_FLAG;
		    directive->statusFlags |=SUBPATTERN_FLAG_IS_IDENTICAL;
		    break;
		}
		/* Escaped character */
		directive->statusFlags |=SUBPATTERN_FLAG_IS_ESCAPED;
		directive->option1=NEW_ARRAY_INSTANCE(2,gchar);
		directive->option1[0]=c;
		directive->option1[1]='\0';
		stage=REGEX_EVAL_STAGE_DONE;
		break;
	    case REGEX_EVAL_STAGE_FLAG:
		if (c=='\0'){
		    directive->errno=1;
		    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_regex_t_getSubIndex(): No sub pattern directive->index!\n");
		    break;
		}
		if (isdigit(c)){
		    stage=REGEX_EVAL_STAGE_INDEX;
		    directive->index=directive->index*10+c-'0';
		    break;
		}
		directive->errno=3;
		verboseMsg_print(VERBOSE_MSG_ERROR,
			"string_formatted_combine_regex_t_getSubIndex(): At character %d : Should only have at most one flag.",
			*currPos_ptr);
		break;

	    case REGEX_EVAL_STAGE_INDEX:
		if (isdigit(c)){
		    stage=REGEX_EVAL_STAGE_INDEX;
		    directive->index=directive->index*10+c-'0';
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
		    subDirective=string_formatted_combine_get_directive(format, sPtrList, currPos_ptr, counter_ptr);
		    if (verboseMsg_get_level()>=VERBOSE_MSG_INFO6){
			if (subDirective->option1){
			    verboseMsg_print(VERBOSE_MSG_INFO6," option1=%s",subDirective->option1);
			}
			if (subDirective->option2){
			    verboseMsg_print(VERBOSE_MSG_INFO6," option2=%s",subDirective->option2);
			}
			if (subDirective->option3){
			    verboseMsg_print(VERBOSE_MSG_INFO6," option3=%s",subDirective->option3);
			}
			verboseMsg_print(VERBOSE_MSG_INFO6,"\n");
		    }
		    if (subDirective->errno>0){
			formattedCombineDirective_free(subDirective);
			directive->errno=6;
			break;
		    }
		    ret=string_formatted_combine_expand_directive(option1Str, sPtrList, counter_ptr, subDirective);
		    formattedCombineDirective_free(subDirective);
		    if (ret){
			directive->errno=6;
			break;
		    }
		    (*currPos_ptr)--;
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
		    subDirective=string_formatted_combine_get_directive(format, sPtrList, currPos_ptr, counter_ptr);
		    if (verboseMsg_get_level()>=VERBOSE_MSG_INFO6){
			verboseMsg_print(VERBOSE_MSG_INFO6,
				"**** string_formatted_combine_get_directive(): subDirective: ");
			verboseMsg_print(VERBOSE_MSG_INFO6,"currPos=%d index=%d errno=%d\n",
				*currPos_ptr,subDirective->index,subDirective->errno);

			if (subDirective->option1){
			    verboseMsg_print(VERBOSE_MSG_INFO6," option1=%s",subDirective->option1);
			}
			if (subDirective->option2){
			    verboseMsg_print(VERBOSE_MSG_INFO6," option2=%s",subDirective->option2);
			}
			if (subDirective->option3){
			    verboseMsg_print(VERBOSE_MSG_INFO6," option3=%s",subDirective->option3);
			}
			verboseMsg_print(VERBOSE_MSG_INFO6,"\n");
		    }
		    if (subDirective->errno>0){
			formattedCombineDirective_free(subDirective);
			directive->errno=6;
			break;
		    }
		    ret=string_formatted_combine_expand_directive(option2Str, sPtrList, counter_ptr,  subDirective);
		    formattedCombineDirective_free(subDirective);
		    if (ret){
			directive->errno=6;
			break;
		    }
		    (*currPos_ptr)--;
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
		    subDirective=string_formatted_combine_get_directive(format, sPtrList, currPos_ptr, counter_ptr);
		    if (verboseMsg_get_level()>=VERBOSE_MSG_INFO6){
			verboseMsg_print(VERBOSE_MSG_INFO6,
				"**** string_formatted_combine_get_directive(): subDirective: ");
			verboseMsg_print(VERBOSE_MSG_INFO6,"currPos=%d index=%d errno=%d\n",
				*currPos_ptr,subDirective->index,subDirective->errno);

			if (subDirective->option1){
			    verboseMsg_print(VERBOSE_MSG_INFO6," option1=%s",subDirective->option1);
			}
			if (subDirective->option2){
			    verboseMsg_print(VERBOSE_MSG_INFO6," option2=%s",subDirective->option2);
			}
			if (subDirective->option3){
			    verboseMsg_print(VERBOSE_MSG_INFO6," option3=%s",subDirective->option3);
			}
			verboseMsg_print(VERBOSE_MSG_INFO6,"\n");
		    }
		    if (subDirective->errno>0){
			formattedCombineDirective_free(subDirective);
			directive->errno=6;
			break;
		    }
		    ret=string_formatted_combine_expand_directive(option3Str, sPtrList, counter_ptr,  subDirective);
		    formattedCombineDirective_free(subDirective);
		    if (ret){
			formattedCombineDirective_free(subDirective);
			directive->errno=6;
			break;
		    }
		    (*currPos_ptr)--;
		    break;
		}
		g_string_append_c(option3Str,c);
		break;
	    case REGEX_EVAL_STAGE_DONE:
		break;
	}
	if (directive->errno<=0 && stage!=REGEX_EVAL_STAGE_DONE){
	    (*currPos_ptr)++;
	}
    }while(directive->errno<=0 && stage!=REGEX_EVAL_STAGE_DONE);
    verboseMsg_print(VERBOSE_MSG_INFO5,"*** string_formatted_combine_get_directive() stage=%d error=%d\n",
	    stage,directive->errno);
    if (!directive->errno){
	if (option1Str)
	    directive->option1=g_string_free(option1Str,FALSE);

	if (option2Str)
	    directive->option2=g_string_free(option2Str,FALSE);

	if (option3Str)
	    directive->option3=g_string_free(option3Str,FALSE);
    }else{
	if (option1Str)

	    g_string_free(option1Str,TRUE);

	if (option2Str)
	    g_string_free(option2Str,TRUE);

	if (option3Str)
	    g_string_free(option3Str,TRUE);
    }

    if (directive->index >=sPtrList->len-1 ){
	directive->errno=5;
	verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_get_directive():");
	verboseMsg_print(VERBOSE_MSG_ERROR,"index %d should be less than the number of string in stringPtrList %d\n",
		directive->index,sPtrList->len-1);
    }
    return directive;
}

/*
 * Expend the directive.
 * Return 0 for success.
 */
static gint  string_formatted_combine_expand_directive(
	GString *strBuf, StringPtrList *sPtrList, gint *counter_ptr, FormattedCombineDirective* directive){
    gchar *strtolEnd_ptr=NULL;
    gchar *strTmp=NULL;
    gchar *paddedStr=NULL;

    const gchar *str=NULL;
    gint beginIndex,length;
    gchar buf[STRING_BUFFER_SIZE_DEFAULT];
    gunichar ucs4_code;


    if (directive->errno){
	return -1;
    }
    if (directive->statusFlags & SUBPATTERN_FLAG_IS_ESCAPED){
	g_string_append(strBuf,directive->option1);
	return 0;
    }
    str=stringPtrList_index(sPtrList,directive->index);
    if (isEmptyString(str)){
	/* This substring is not empty */
	if (directive->statusFlags & SUBPATTERN_FLAG_IS_EMPTY && directive->option1){
	    g_string_append(strBuf,directive->option1);
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_NONEMPTY && directive->option2){
	    g_string_append(strBuf,directive->option2);
	}
    }else{
	/* This substring is not empty */
	if (directive->statusFlags & SUBPATTERN_FLAG_IS_NONEMPTY){
	    if (directive->option1)
		g_string_append(strBuf,directive->option1);
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_EMPTY){
	    if (directive->option2)
		g_string_append(strBuf,directive->option2);
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_UPPERCASE){
	    strTmp=g_utf8_strup(str,-1);
	    g_string_append(strBuf,strTmp);
	    g_free(strTmp);
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_LOWERCASE){
	    strTmp=g_utf8_strdown(str,-1);
	    g_string_append(strBuf,strTmp);
	    g_free(strTmp);
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_PADDED_LEFT){
	    length=(int) strtol(directive->option1,&strtolEnd_ptr,10);
	    verboseMsg_print(VERBOSE_MSG_INFO6,
		    "**** string_formatted_combine_expand_directive() SUBPATTERN_FLAG_IS_PADDED_LEFT length=%d\n",
		    length);
	    if (strtolEnd_ptr==directive->option1){
		/* Length is not number! */
		verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_expand_directive():index %d:  should have an integer number instead of %s\n",directive->index,directive->option1);
		return 1;
	    }
	    if (directive->option2){
		paddedStr=directive->option2;
	    }else{
		paddedStr=" ";
	    }
	    strTmp=string_padding_left(str,paddedStr,length);
	    g_string_append(strBuf,strTmp);
	    g_free(strTmp);
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_PADDED_RIGHT){
	    length=(int) strtol(directive->option1,&strtolEnd_ptr,10);
	    verboseMsg_print(VERBOSE_MSG_INFO6,
		    "**** string_formatted_combine_expand_directive() SUBPATTERN_FLAG_IS_PADDED_RIGHT length=%d\n",
		    length);
	    if (strtolEnd_ptr==directive->option1){
		/* Length is not number! */
		verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_expand_directive():index %d:  should have an integer number instead of %s\n",directive->index,directive->option1);
		return 1;
	    }
	    if (directive->option2){
		paddedStr=directive->option2;
	    }else{
		paddedStr=" ";
	    }
	    strTmp=string_padding_right(str,paddedStr,length);
	    g_string_append(strBuf,strTmp);
	    g_free(strTmp);
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_PLUS && counter_ptr){
	    g_string_append_printf(strBuf,"%d",++(*counter_ptr));
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_MINUS && counter_ptr){
	    g_string_append_printf(strBuf,"%d",--(*counter_ptr));
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_HEXADECIMAL){
	    ucs4_code=(gunichar) strtol(str,&strtolEnd_ptr,10);
	    verboseMsg_print(VERBOSE_MSG_INFO6,"**** string_formatted_combine_expand_directive() ucs_code=%ld(%X)\n"
		    ,ucs4_code,ucs4_code);
	    if (strtolEnd_ptr==str){
		/* Number string is expected. */
		verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_expand_directive():index %d:  should have an integer number instead of %s\n",directive->index,str);
		return 1;
	    }
	    g_snprintf(buf,STRING_BUFFER_SIZE_DEFAULT,"%X",ucs4_code);
	    if (directive->option1){
		length=(int) strtol(directive->option1,&strtolEnd_ptr,10);
		if (strtolEnd_ptr==directive->option1){
		    /* Length is not number! */
		    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_expand_directive():index %d:  should have an integer number instead of %s\n",directive->index,directive->option1);
		    return 1;
		}
		strTmp=string_padding_left(buf,"0",length);
		g_string_append(strBuf,strTmp);
		g_free(strTmp);
	    }else{
		g_string_append(strBuf,buf);
	    }
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_UTF8){
	    ucs4_code=(gunichar) strtol(str,&strtolEnd_ptr,10);
	    if (strtolEnd_ptr==str){
		/* Number string is expected. */
		verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_expand_directive():index %d:  should have an integer number instead of %s\n",directive->index,str);
		return 1;
	    }
	    strTmp=ucs4_to_utf8(ucs4_code);
	    g_string_append(strBuf,strTmp);
	    g_free(strTmp);
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_SUBSTRING){
	    verboseMsg_print(VERBOSE_MSG_INFO6,
		    "**** string_formatted_combine() SUBPATTERN_FLAG_IS_SUBSTRING\n");
	    if (directive->option1){
		beginIndex=(int) strtol(directive->option1,&strtolEnd_ptr,10);
		if (strtolEnd_ptr==directive->option1){
		    /* Start is not number! */
		    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_expand_directive():index %d:  should have an integer number instead of %s\n",directive->index,directive->option1);
		    return 1;
		}
	    }else{
		/* No Start ! */
		verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_expand_directive():index %d:  should have an integer number as start!\n",directive->index);
		return 1;
	    }
	    if (directive->option2){
		length=(int) strtol(directive->option2,&strtolEnd_ptr,10);
		if (strtolEnd_ptr==directive->option2){
		    /* Length is not number! */
		    verboseMsg_print(VERBOSE_MSG_ERROR,"string_formatted_combine_expand_directive():index %d:  should have an integer number instead of %s\n",directive->index,directive->option2);
		    return 1;
		}
	    }else{
		length=-1;
	    }
	    subString_buffer(buf,str,beginIndex,length);
	    g_string_append(strBuf,buf);
	}else if (directive->statusFlags & SUBPATTERN_FLAG_IS_IDENTICAL){
	    verboseMsg_print(VERBOSE_MSG_INFO6,
		    "**** string_formatted_combine_expand_directive() SUBPATTERN_FLAG_IS_IDENTICAL\n");
	    if (!directive->option1){
		/* No expression ! */
		verboseMsg_print(VERBOSE_MSG_ERROR,
			"string_formatted_combine_expand_directive():index %d: flag I require compare_str.\n");

		return 1;
	    }
	    if (!directive->option2){
		/* No true substitute ! */
		verboseMsg_print(VERBOSE_MSG_ERROR,
			"string_formatted_combine_expand_directive():index %d: flag I require true substitute\n");
		return 1;
	    }

	    if (strcmp(str,directive->option1)==0){
		g_string_append(strBuf,directive->option2);
	    }else if (directive->option3){
		g_string_append(strBuf,directive->option3);
	    }
	}else{
	    g_string_append(strBuf,str);
	}
    }
    return 0;
}


gchar *string_formatted_combine(const gchar *format,StringPtrList *sPtrList,gint *counter_ptr){
    GString *strBuf=g_string_new(NULL);

    gint ret;
    guint j,formatLen=strlen(format);
    FormattedCombineDirective* directive=NULL;

    for(j=0;j<formatLen;j++){
	verboseMsg_print(VERBOSE_MSG_INFO6,"*** string_formatted_combine():Current strBuf=%s|\n",strBuf->str);
	if (format[j]=='$'){
	    j++;
	    directive=string_formatted_combine_get_directive(format, sPtrList, &j, counter_ptr);
	    if (verboseMsg_get_level()>=VERBOSE_MSG_INFO6){
		verboseMsg_print(VERBOSE_MSG_INFO6,"**** string_formatted_combine(): directive:");
		verboseMsg_print(VERBOSE_MSG_INFO6,"j=%d index=%d errno=%d\n",
			j,directive->index,directive->errno);
		if (directive->option1){
		    verboseMsg_print(VERBOSE_MSG_INFO6," option1=%s",directive->option1);
		}
		if (directive->option2){
		    verboseMsg_print(VERBOSE_MSG_INFO6," option2=%s",directive->option2);
		}
		if (directive->option3){
		    verboseMsg_print(VERBOSE_MSG_INFO6," option3=%s",directive->option3);
		}
		verboseMsg_print(VERBOSE_MSG_INFO6,"\n");
	    }
	    if (directive->errno>0){
		formattedCombineDirective_free(directive);
		g_string_free(strBuf,TRUE);
		return NULL;
	    }
	    ret=string_formatted_combine_expand_directive(strBuf, sPtrList, counter_ptr,  directive);
	    formattedCombineDirective_free(directive);
	    if (ret){
		g_string_free(strBuf,TRUE);
		return NULL;
	    }
	    j--;
	}else{
	    /* Normal character */
	    g_string_append_c(strBuf,format[j]);
	}
    }
    return g_string_free(strBuf,FALSE);

}

static gchar *string_get_matched_substring(const gchar *str, regmatch_t *pmatch, guint index){
    if (pmatch[index].rm_so<0 || pmatch[index].rm_so==pmatch[index].rm_eo){
	/* This subpattern is empty */
	return NULL;
    }
    /* This subpattern is not empty */
    gint i;
    gchar *result=NEW_ARRAY_INSTANCE(pmatch[index].rm_eo-pmatch[index].rm_so+1,gchar);
    for(i=0;i<pmatch[index].rm_eo-pmatch[index].rm_so;i++){
	result[i]=str[pmatch[index].rm_so+i];
    }
    result[i]='\0';
    return result;
}

gchar *string_regex_formatted_combine_regex_t(const gchar *str, const regex_t *preg, const gchar *format,
	gint eflags, gint *counter_ptr){
    guint nmatch=preg->re_nsub+1;
    regmatch_t *pmatch=NEW_ARRAY_INSTANCE(nmatch,regmatch_t);
    if (regexec(preg,str,nmatch,pmatch,eflags)!=0){
	/* No Match */
	g_free(pmatch);
	return NULL;
    }
    guint i;
    gchar *strTmp=NULL;

    StringPtrList *sPtrList=stringPtrList_new();
    for(i=0;i<nmatch;i++){
        strTmp=string_get_matched_substring(str,pmatch,i);
        stringPtrList_insert(sPtrList,strTmp);
    }
    gchar *result=string_formatted_combine(format,sPtrList,counter_ptr);
    stringPtrList_free_deep(sPtrList);
    g_free(pmatch);
    return result;
}

gchar *string_regex_formatted_combine(const gchar *str, const gchar *pattern, const gchar *format,
	gint cflags, gint eflags, gint *counter_ptr){
    regex_t preg;
    gint ret;

    if ((ret=regcomp(&preg, pattern, cflags))!=0){
	/* Invalid pattern */
	char buf[STRING_BUFFER_SIZE_DEFAULT];
	regerror(ret,&preg,buf,STRING_BUFFER_SIZE_DEFAULT);
	verboseMsg_print(VERBOSE_MSG_ERROR, "string_formatted_combine():Invalid pattern %s\n"
		,buf);
	return NULL;
    }
    gchar *result=string_regex_formatted_combine_regex_t(str, &preg, format, eflags, counter_ptr);
    regfree(&preg);
    return result;
}


gchar *string_regex_replace_regex_t(const gchar *str, const regex_t *preg, const gchar *format,
	gint eflags, gint *counter_ptr){

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

    gchar *evalStr=string_regex_formatted_combine_regex_t(str, preg, format, eflags, counter_ptr);

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
	gint cflags, gint eflags, gint *counter_ptr){

    regex_t preg;
    gint ret;
    if ((ret=regcomp(&preg, pattern, cflags))!=0){
	/* Invalid pattern */
	char buf[STRING_BUFFER_SIZE_DEFAULT];
	regerror(ret,&preg,buf,STRING_BUFFER_SIZE_DEFAULT);
	verboseMsg_print(VERBOSE_MSG_ERROR, "string_regex_replace():Invalid pattern %s\n"
		,buf);
	return NULL;
    }
    gchar *result=string_regex_formatted_combine_regex_t(str, &preg, format, eflags, counter_ptr);
    regfree(&preg);
    return result;
}



gchar*
initString(gchar *str){
    if (str==NULL){
	return NULL;
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

gchar* string_append_c(gchar *str, const char ch,size_t length){
    gint len=strlen(str);
    if (len>=length-1){
	return NULL;
    }
    str[len]=ch;
    str[len+1]='\0';
    return str;
}

gboolean string_is_decomposed_fast(const gchar *str){
    gchar* str_norm=g_utf8_normalize(str,-1,G_NORMALIZE_NFD);
    size_t len=strlen(str);
    size_t len_norm=strlen(str_norm);
    if (len==len_norm){
	return TRUE;
    }
    return FALSE;
}


static gchar* string_padding(const gchar *str, const gchar *padding_str, size_t length, gboolean left){
    gint len=strlen(str);
    gint len_padding=strlen(padding_str);
    gint i=0;
    /* length need to be convert as signed */
    gint len_fill=(int) (length-len-len_padding+1);
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
    gint i,j,k,len=strlen(str);
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
subString(const gchar *str,gint beginIndex,gint length){
    size_t actualLength= (length >=0)? length: strlen(str)-beginIndex;
    gchar *buf=NEW_ARRAY_INSTANCE(actualLength+1,gchar);
    return subString_buffer(buf, str, beginIndex, length);
}


gchar*
subString_buffer(gchar *buf, const gchar *str,gint beginIndex, gint length){
    gint i;
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

gint strcmp_unsigned_signed(const guchar *str1, const gchar *str2){
    gint c1, c2,i=0;
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

guchar *signedStr_to_unsignedStr(const gchar *str){
    guchar *cloneStr=NEW_ARRAY_INSTANCE(strlen(str)+1,guchar);
    guchar *result=signedStr_to_unsignedStr_buffer(cloneStr,str);
    if (!result)
	g_free(cloneStr);
    return result;
}

guchar *signedStr_to_unsignedStr_buffer(guchar *resultBuf, const gchar *str){
    guchar c;
    gint i=0;
    do{
	c=(guchar) str[i];
	resultBuf[i]=c;
	i++;
    }while(c!=0 );
    return resultBuf;
}

gchar *unsignedStr_to_signedStr(const guchar *str){
    gchar* cloneStr=NEW_ARRAY_INSTANCE(strlen((const gchar *)str)+1,gchar);
    gchar *result=unsignedStr_to_signedStr_buffer(cloneStr,str);
    if (!result)
	g_free(cloneStr);
    return result;
}

gchar *unsignedStr_to_signedStr_buffer(gchar* resultBuf, const guchar *str){
    gchar c;
    gint i=0;
    do{
	c=(gchar) str[i];
	resultBuf[i]=c;
	i++;
    }while(c!=0 );
    return resultBuf;
}

gint longestCommonSubsequence_get_length(const gchar *s1, const gchar *s2, gint ***lcsTablePtr){
    gint n1=strlen(s1);
    gint n2=strlen(s2);
    gint **table= NEW_ARRAY2D_INSTANCE(n2,n1,int);
    gint i1,i2;
    gint prev;
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


gchar* longestCommonSubsequence_get_subsequence(const gchar *s1, const gchar *s2, gint **lcsTable){
    gint n1=strlen(s1);
    gint n2=strlen(s2);
    gint len=lcsTable[0][0];
    if (len==0){
	return NULL;
    }
    gchar *subsequence= (gchar *) calloc(len+1,sizeof(gchar));
    gint i1=0,i2=0;
    gint counter=0;
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


//gint main(gint argc, gchar** argv){
//    gint **table=NULL;
//    gint len=longestCommonSubsequence_get_length(argv[1],argv[2], &table);
//    gchar* str=longestCommonSubsequence_get_subsequence(argv[1],argv[2], table);
//    if (str==NULL)
//        str="NULL";
//    printf("lcs length:%d, subsequence:%s\n",len,str);
//    array2D_free((void **)table);
//    return 0;
//}
