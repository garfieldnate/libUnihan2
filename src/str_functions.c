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
#include <glib.h>
#include <limits.h>
#include <regex.h>
#include <sys/types.h>
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


StringList *regex_subString_match_regex_t(regex_t *preg,const gchar* str, int eflags, guint regexSubStringFlags ){
    gchar *currPtr=str;
    int len=strlen(str);
    int i,ret;
    int counter=0;
    int nmatch=preg->re_nsub+1;
    gchar *newStr;
    regmatch_t *pmatch=NEW_ARRAY_INSTANCE(nmatch,regmatch_t);   
    StringList *sList= stringList_new();
    int maxEo;
    while(currPtr<str+len){
	maxEo=-1;
	if (regexec(preg,currPtr,nmatch,pmatch,eflags)!=0){
	    /* No Match */
	    break;
	}
	i=0;
	if (!(regexSubstringFlags & REGEX_SUBSTRING_EXCLUDE_MAJOR_MATCH)){
	    /* Put whole match ( pmatch[0] ) in sList */
	    newStr=g_strndup(currPtr+pmatch[i].rm_so, pmatch[counter].rm_eo - pmatch[i].rm_so);
	    stringList_insert(sList,newStr);
	    g_free(newStr);
	    maxEo=(maxEo >= pmatch[i].rm_eo) ? maxEo : pmatch[i].rm_eo;
	}
	if (!(regexSubstringFlags & REGEX_SUBSTRING_EXCLUDE_SUB_MATCH)){
	    for(i=1;i<nmatch && pmatch[i].rm_so>=0;i++){
		/* Put sub matchs ( pmatch[i] ) in sList */
		newStr=g_strndup(currPtr+pmatch[i].rm_so, pmatch[counter].rm_eo - pmatch[i].rm_so);
		stringList_insert(sList,newStr);
		g_free(newStr);
		maxEo=(maxEo >= pmatch[i].rm_eo) ? maxEo : pmatch[i].rm_eo;
	    }
	}
	if (regexSubstringFlags & REGEX_SUBSTRING_ALLOW_OVERLAP){
	    currPtr++;
	}else{
	    currPtr+=maxEo;
	}
    }
    g_free(pmatch);
    return sList;
}

StringList *regex_subString_match(const gchar *pattern,const gchar *str, 
	int cflags, int eflags, guint regexSubstringFlags){
    regex_t *preg=NULL;
    int ret;
    if ((ret=regcomp(&preg, pattern, int cflags))!=0){
	/* Invalid pattern */
	char buf[MAX_STRING_BUFFER_SIZE];
	regerror(ret,pattern,buf,MAX_STRING_BUFFER_SIZE);
	verboseMsg_print(VERBOSE_MSG_ERROR, "regex_multiple_match():Invalid pattern %s\n"
		,buf);
	return NULL;
    }
    StringList *sList=regex_subString_match_regex_t(preg, str, eflags, regexSubStringFlags );
    regfree(preg);
    return sList;
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
subString(gchar *buf, const gchar *str,int beginIndex,int length){
    int i=0;
    for(i=0;i<length;i++){
	if (str[beginIndex+i]=='\0'){
	    break;
	}
        buf[i]=str[beginIndex+i];
    }
    buf[i]='\0';
    return buf;
}



gunigchar* utf8_to_ucs4(const gchar* utf8_str){
    glong items_read;
    glong items_written;
    GError *err = NULL;
    gunigchar*   ucs4Str=g_utf8_to_ucs4(utf8_str, -1,&items_read, &items_written, &err);
    if (err!=NULL){
	verboseMsg_print(VERBOSE_MSG_CRITICAL,"UTF-8 to UCS-4 conversion error: on char %ld in \"%s\"\n",items_read,utf8_str);
	verboseMsg_print(VERBOSE_MSG_CRITICAL,"Error message:  \"%s\"\n",err->message);
	exit(1);
    }
    return ucs4Str;
}

gchar* ucs4_to_utf8(gunigchar ucs4_code){
    gchar *utf8_str;
    gint len=g_unigchar_to_utf8(ucs4_code,NULL);
    utf8_str=NEW_ARRAY_INSTANCE(MAX(len+1,6),gchar);
    g_unigchar_to_utf8(ucs4_code,utf8_str);
    utf8_str[len]='\0';
    return utf8_str;
}

gchar* utf8_concat_ucs4(gchar* utf8_str,gunigchar ucs4_code){
    gchar *ucs4_str=ucs4_to_utf8(ucs4_code);
    strcat(utf8_str,ucs4_str);
    g_free(ucs4_str);
    return utf8_str;
}

int strcmp_unsigned_signed(const unsigned gchar *str1, const gchar *str2){
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

unsigned gchar *signedStr_to_unsignedStr(const gchar *str){
    unsigned gchar *cloneStr=NEW_ARRAY_INSTANCE(strlen(str)+1,unsigned gchar);
    unsigned gchar *result=signedStr_to_unsignedStr_buffer(cloneStr,str);
    if (!result)
	g_free(cloneStr);
    return result;
}

unsigned gchar *signedStr_to_unsignedStr_buffer(unsigned gchar *resultBuf, const gchar *str){
    unsigned gchar c;
    int i=0;
    do{
	c=(unsigned gchar) str[i];
	resultBuf[i]=c;
	i++;
    }while(c!=0 );
    return resultBuf;
}

gchar *unsignedStr_to_signedStr(const unsigned gchar *str){
    gchar* cloneStr=NEW_ARRAY_INSTANCE(strlen((const gchar *)str)+1,gchar);
    gchar *result=unsignedStr_to_signedStr_buffer(cloneStr,str);
    if (!result)
	g_free(cloneStr);
    return result;
}

gchar *unsignedStr_to_signedStr_buffer(gchar* resultBuf, const unsigned gchar *str){
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
