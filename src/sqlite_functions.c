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
#include "allocate.h"
#include "sqlite_functions.h"
#include "str_functions.h"
#include "verboseMsg.h"

SQL_Result *sql_result_new(){
    SQL_Result *sResult=NEW_INSTANCE(SQL_Result);
    sResult->fieldList=stringList_sized_new(SQL_RESULT_FIELD_CHUNK_SIZE,
	    SQL_RESULT_FIELD_ELEMENT_COUNT);
    sResult->resultList=stringList_sized_new(SQL_RESULT_RESULT_CHUNK_SIZE,
	    SQL_RESULT_RESULT_ELEMENT_COUNT);
    sResult->colCount=0;
    sResult->execResult=-1; 
    sResult->errMsg=NULL;
    return sResult;
}

StringList *sql_result_free(SQL_Result *sResult, gboolean freeResult){
    g_assert(sResult);
    StringList *resultList=NULL;
    stringList_free(sResult->fieldList);
    if (freeResult){
	stringList_free(sResult->resultList);
    }else{
	resultList=sResult->resultList;
//	sResult->resultList=NULL;
    }
    if (sResult->errMsg)
	sqlite3_free(sResult->errMsg);
    g_free(sResult);
    return resultList;
}

static int sqlite_count_matches_callback(void *data,int colCount,char** value_array,char **fieldName_array){
    if (data==NULL){
	return SQLITE_ABORT;
    }
    int *count=(int *) data;
    (*count)++;
    return SQLITE_OK;
}


int sqlite_count_matches(sqlite3 *db,const char * sqlClause,char **errMsg_ptr){
    g_assert(db);
    int rowCount=0,execResult;
    execResult=sqlite3_exec(db,sqlClause,sqlite_count_matches_callback,&rowCount,errMsg_ptr);
    if (execResult) {
	return -1 * execResult;
    }
    return rowCount;
}


static int sqlite_get_sql_result_callback(void *data,int colCount,char** value_array,char **fieldName_array){
    if (data==NULL){
	return SQLITE_ABORT;
    }
    SQL_Result *sResult=(SQL_Result *) data;
    int i;
    verboseMsg_print(VERBOSE_MSG_INFO4," sqlite_get_sql_result_callback(,%d,,): \n",colCount);
    if (!(sResult->colCount)){
	for(i=0;i<colCount;i++){
	    verboseMsg_print(VERBOSE_MSG_INFO5,"  field_array[%d]=%s\n",i,fieldName_array[i]);
	    stringList_insert(sResult->fieldList,fieldName_array[i]);
	}
	sResult->colCount=colCount;
    }
    for(i=0;i<colCount;i++){
	verboseMsg_print(VERBOSE_MSG_INFO5,"  value_array[%d]=%s\n",i,value_array[i]);
	stringList_insert(sResult->resultList,value_array[i]);
    }
    return SQLITE_OK;
}

SQL_Result *sqlite_get_sql_result(sqlite3 *db, const char *sqlClause){
    g_assert(db);
    SQL_Result *sResult=sql_result_new();

    sResult->execResult=sqlite3_exec(db,sqlClause,sqlite_get_sql_result_callback,sResult,&sResult->errMsg);
    if (sResult->execResult){
	verboseMsg_print(VERBOSE_MSG_ERROR,"sqlite_get_stringList(): %s\n",sResult->errMsg);
    }
    return sResult;
}

SQL_Result *sqlite_get_tableNames(sqlite3 *db){
    return sqlite_get_sql_result(db, "SELECT name FROM sqlite_master WHERE type='table'");
}

static int sqlite_get_fieldNames_callback(void *data,int colCount,char** value_array,char **fieldName_array){
    StringList *sList=(StringList *) data;
    int i;
    for(i=0;i<colCount;i++){
	stringList_insert(sList,fieldName_array[i]);
    }
    /* Just run once, no need to run all the records. */
    return SQLITE_ABORT;
}


StringList *sqlite_get_fieldNames(sqlite3 *db,const char * sqlClause, int *execResult_ptr, char **errMsg_ptr){
    g_assert(db);
    StringList *sList=stringList_new();
    *execResult_ptr=sqlite3_exec(db,sqlClause,sqlite_get_fieldNames_callback,sList,errMsg_ptr);
    if (*execResult_ptr==SQLITE_ABORT){
	/* Just run once, no need to run all the records. */
	sqlite3_free(*errMsg_ptr);
	*errMsg_ptr=NULL;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"sqlite_get_fieldNames(): %s\n",*errMsg_ptr);
	stringList_free(sList);
	return NULL;
    }
    return sList;
}



typedef struct {
    int rowCount;
    GString *strBuf;
} SqliteConcatStru;

void sqlite_concat_aggregation_step_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==2);
    SqliteConcatStru *cStru = (SqliteConcatStru *) sqlite3_aggregate_context(context, sizeof(*cStru));
    if (cStru->rowCount==0){
	cStru->strBuf=g_string_new(NULL);
    }
    const char *separater=(sqlite3_value_type(argv[1])==SQLITE_TEXT) ? sqlite_value_signed_text(argv[1]): "";
    if (cStru->rowCount>0){
	g_string_append(cStru->strBuf,separater);
    }
    const char *str=NULL;
    long l;
    double d;
    switch(sqlite3_value_type(argv[1])){
	case SQLITE_TEXT:
	    str=sqlite_value_signed_text(argv[0]);
	    g_string_append(cStru->strBuf,separater);
	    break;
	case SQLITE_INTEGER:
	    l=sqlite3_value_int64(argv[0]);
	    g_string_append_printf(cStru->strBuf,"%ld",l);
	    break;
	case SQLITE_FLOAT:
	    d=sqlite3_value_double(argv[0]);
	    g_string_append_printf(cStru->strBuf,"%f",d);
	    break;
    }
    if (separater)
	g_free((gpointer) separater);
    if (str)
	g_free((gpointer) str);
    cStru->rowCount++;
}

void sqlite_concat_aggregation_finalized_Func(sqlite3_context *context){
    SqliteConcatStru *cStru = (SqliteConcatStru *) sqlite3_aggregate_context(context, sizeof(*cStru));

    if (cStru->rowCount>0){
	char *buf=g_string_free(cStru->strBuf,FALSE);
	sqlite3_result_text(context,buf,-1,g_free);
    }
}

int sqlite_create_concat_aggregation_function(sqlite3 *db, const char *function_name){
    return sqlite3_create_function(db, function_name, 2,SQLITE_UTF8,NULL,
	    NULL,sqlite_concat_aggregation_step_Func,sqlite_concat_aggregation_finalized_Func);
}

char *sqlite_value_signed_text_buffer(char *buf,sqlite3_value *value){
    return unsignedStr_to_signedStr_buffer(buf, sqlite3_value_text(value));
}

char *sqlite_value_signed_text(sqlite3_value *value){
    const unsigned char *str=sqlite3_value_text(value);
    char *buf=NEW_ARRAY_INSTANCE(strlen((const char *) str)+1, char);
    return unsignedStr_to_signedStr_buffer(buf, str);
}


