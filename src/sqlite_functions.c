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
#include <glib.h>
#include "allocate.h"
#include "sqlite_functions.h"
#include "file_functions.h"
#include "verboseMsg.h"

gint sqlite_open(const gchar *filename,  sqlite3 **ppDb,  gint flags){
    gint ret;
#ifdef HAVE_SQLITE3_OPEN_V2
    ret = sqlite3_open_v2(filename, ppDb, flags, NULL);
#else
    if (flags & SQLITE_OPEN_READONLY ){
	if (!isReadable(filename)){
	    verboseMsg_print(VERBOSE_MSG_ERROR, "sqlite_open(%s,%d): File is not readable\n",
		    filename,flags);
	    return -1;
	}
    }else if (flags & SQLITE_OPEN_CREATE){
	if (!isWritable(filename)){
	    verboseMsg_print(VERBOSE_MSG_ERROR, "sqlite_open(%s,%d): File is not writable\n",
		    filename,flags);
	    return -2;
	}
    }else if (flags & SQLITE_OPEN_READWRITE ){
	if (!isReadable(filename)){
	    verboseMsg_print(VERBOSE_MSG_ERROR, "sqlite_open(%s,%d): File is not readable\n",
		    filename,flags);
	    return -1;
	}
	if (!isWritable(filename)){
	    verboseMsg_print(VERBOSE_MSG_ERROR, "sqlite_open(%s,%d): File is not writable\n",
		    filename,flags);
	    return -2;
	}
    }
    ret=sqlite3_open(filename, ppDb);
#endif
    return ret;

}

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

static gint sqlite_count_matches_callback(void *data,gint colCount,gchar** value_array,gchar **fieldName_array){
    if (data==NULL){
	return SQLITE_ABORT;
    }
    gint *count=(gint *) data;
    (*count)++;
    return SQLITE_OK;
}

gint sqlite_count_matches(sqlite3 *db,const gchar * sqlClause,gchar **errMsg_ptr){
    g_assert(db);
    gint rowCount=0,execResult;
    execResult=sqlite3_exec(db,sqlClause,sqlite_count_matches_callback,&rowCount,errMsg_ptr);
    if (execResult) {
	return -1 * execResult;
    }
    return rowCount;
}

gint sqlite_error_callback_hide_constraint_error(sqlite3 *db, const gchar *sqlClause, gint error_code,
	const gchar *error_msg, gpointer prompt){
    if (error_code!= SQLITE_CONSTRAINT){
	sqlite_error_callback_print_message(db,sqlClause,error_code,error_msg,prompt);
    }
    return error_code;
}

gint sqlite_error_callback_show_constraint_warning(sqlite3 *db, const gchar *sqlClause, gint error_code,
	const gchar *error_msg, gpointer prompt){
    gchar *prompt_str=(gchar *) prompt;
    if (error_code!= SQLITE_CONSTRAINT){
	sqlite_error_callback_print_message(db,sqlClause,error_code,error_msg,prompt);
    }else{
	verboseMsg_print(VERBOSE_MSG_WARNING,"%s: [constragint warning]: %s\n",prompt_str,error_msg);
	verboseMsg_print(VERBOSE_MSG_WARNING,"%s: Caused by following SQL statement: %s\n",prompt_str,sqlClause);
    }
    return error_code;
}

gint sqlite_error_callback_print_message(sqlite3 *db, const gchar *sqlClause, gint error_code,
	const gchar *error_msg, gpointer prompt){
    gchar *prompt_str=(gchar *) prompt;
    verboseMsg_print(VERBOSE_MSG_WARNING,"%s: [Error] code: %d, message: %s\n",prompt_str,error_code,error_msg);
    verboseMsg_print(VERBOSE_MSG_WARNING,"%s: Caused by following SQL statement: %s\n",prompt_str,sqlClause);
    return error_code;
}

gint sqlite_exec_handle_error(sqlite3 *db, const gchar *sqlClause, sqlite_exec_callback exec_func,
	gpointer exec_option, sqlite_error_callback error_func, gpointer error_option ){
    gchar *errMsg_ptr=NULL;
    gint ret=sqlite3_exec(db,sqlClause,exec_func, exec_option, &errMsg_ptr);
    if (ret){
	ret=error_func(db,sqlClause,ret,errMsg_ptr,error_option);
	sqlite3_free(errMsg_ptr);
    }
    return ret;
}

static gint sqlite_get_sql_result_callback(void *data,gint colCount,gchar** value_array,gchar **fieldName_array){
    if (data==NULL){
	return SQLITE_ABORT;
    }
    SQL_Result *sResult=(SQL_Result *) data;
    gint i;
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

SQL_Result *sqlite_get_sql_result(sqlite3 *db, const gchar *sqlClause){
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

static gint sqlite_get_fieldNames_callback(void *data,gint colCount,gchar** value_array,gchar **fieldName_array){
    StringList *sList=(StringList *) data;
    gint i;
    for(i=0;i<colCount;i++){
	stringList_insert(sList,fieldName_array[i]);
    }
    /* Just run once, no need to run all the records. */
    return SQLITE_ABORT;
}

StringList *sqlite_get_fieldNames(sqlite3 *db,const gchar * sqlClause, gint *execResult_ptr, gchar **errMsg_ptr){
    g_assert(db);
    StringList *sList=stringList_new();
    *execResult_ptr=sqlite3_exec(db,sqlClause,sqlite_get_fieldNames_callback,sList,errMsg_ptr);
    if (*execResult_ptr==SQLITE_ABORT){
	/* Just run once, no need to run all the records. */
	sqlite3_free(*errMsg_ptr);
	/* Got result, change the result code as SQLITE_OK */
	*execResult_ptr=SQLITE_OK;
	*errMsg_ptr=NULL;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"sqlite_get_fieldNames(): %s\n",*errMsg_ptr);
	stringList_free(sList);
	return NULL;
    }
    return sList;
}

//void sqlite_eval_output_db_Func(sqlite3_context *context, gint argc, sqlite3_value **argv){
//    g_assert(argc>=1);
//    gint i,counter=1;
//    const gchar *format=sqlite_value_signed_text(argv[0]);
//    GString *strBuf=g_string_new(NULL);

//
//    for(i=1;i<argc;i++){

//    }


//
//

//    gchar *pStr=g_string_free(strBuf,FALSE);
//    sqlite3_result_text(context,pStr,-1,g_free);

//}
/*==============================================================
 * signed<->unsigned conversion.
 */
gchar *sqlite_value_signed_text_buffer(gchar *buf,sqlite3_value *value){
    return unsignedStr_to_signedStr_buffer(buf, sqlite3_value_text(value));
}

gchar *sqlite_value_signed_text(sqlite3_value *value){
    const guchar *str=sqlite3_value_text(value);
    gchar *buf=NEW_ARRAY_INSTANCE(strlen((const gchar *) str)+1, gchar);
    return unsignedStr_to_signedStr_buffer(buf, str);
}

/*==============================================================
 * SQL scalar functions.
 */
static void sqlite_string_formatted_combine_scalar_function(sqlite3_context *context, gint argc, sqlite3_value **argv){
    g_assert(argc>2);
    StringPtrList *sPtrList=stringPtrList_new();
    gint i,counter=0;
    gchar *format=sqlite_value_signed_text(argv[0]);
    for(i=1;i<argc;i++){
	stringPtrList_insert(sPtrList,sqlite_value_signed_text(argv[i]));
    }
    gchar *buf=string_formatted_combine(format, sPtrList, &counter);
    stringPtrList_free_deep(sPtrList);
    sqlite3_result_text(context,buf,-1,g_free);
}

gint sqlite_create_string_formatted_combine_scalar_function(sqlite3 *db, const gchar *function_name){
    return sqlite3_create_function(db, function_name, 2,SQLITE_UTF8,NULL,
	    sqlite_string_formatted_combine_scalar_function,NULL,NULL);
}

/*==============================================================
 * SQL aggregation functions.
 */
typedef struct {
    gint rowCount;
    GString *strBuf;
} SqliteConcatStru;

static void sqlite_concat_aggregation_step_Func(sqlite3_context *context, gint argc, sqlite3_value **argv){
    g_assert(argc==2);
    SqliteConcatStru *cStru = (SqliteConcatStru *) sqlite3_aggregate_context(context, sizeof(*cStru));
    if (cStru->rowCount==0){
	cStru->strBuf=g_string_new(NULL);
    }
    const gchar *separater=(sqlite3_value_type(argv[1])==SQLITE_TEXT) ? sqlite_value_signed_text(argv[1]): "";
    if (cStru->rowCount>0){
	g_string_append(cStru->strBuf,separater);
    }
    const gchar *str=NULL;
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

static void sqlite_concat_aggregation_finalized_Func(sqlite3_context *context){
    SqliteConcatStru *cStru = (SqliteConcatStru *) sqlite3_aggregate_context(context, sizeof(*cStru));

    if (cStru->rowCount>0){
	gchar *buf=g_string_free(cStru->strBuf,FALSE);
	sqlite3_result_text(context,buf,-1,g_free);
    }
}

gint sqlite_create_concat_aggregation_function(sqlite3 *db, const gchar *function_name){
    return sqlite3_create_function(db, function_name, 2,SQLITE_UTF8,NULL,
	    NULL,sqlite_concat_aggregation_step_Func,sqlite_concat_aggregation_finalized_Func);
}

