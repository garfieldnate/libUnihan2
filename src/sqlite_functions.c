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

int sqlite_count_matches(sqlite3 *db,const char * sqlClause,char **errmsg){
    char **resultp = NULL;
    int nrow;
    int ncolumn;

    int ret = sqlite3_get_table(db, sqlClause, &resultp, &nrow, &ncolumn,
	    errmsg);
    sqlite3_free_table(resultp);
    if (ret) {
	return -1 * ret;
    }
    return nrow;
}

StringList *sqlite_get_fieldNames(sqlite3 *db,const char * sqlClause,char **errmsg){
    char **result = NULL;
    int nrow;
    int ncolumn;

    int ret = sqlite3_get_table(db, sqlClause, &result, &nrow, &ncolumn,
	    errmsg);
    if (ret) {
	sqlite3_free_table(result);
	return NULL;
    }
    StringList *sList=stringList_new();
    int i;
    for(i=0;i<ncolumn;i++){
	stringList_insert_const(sList,result[i]);
    }
    sqlite3_free_table(result);
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
    const char *separater=(sqlite3_value_type(argv[1])==SQLITE_TEXT) ? sqlite_value_signed_text_cloned(argv[1]): "";
    if (cStru->rowCount>0){
	g_string_append(cStru->strBuf,separater);
    }
    const char *str=NULL;
    long l;
    double d;
    switch(sqlite3_value_type(argv[1])){
	case SQLITE_TEXT:
	    str=sqlite_value_signed_text_cloned(argv[0]);
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

const char *sqlite_value_signed_text_buffer(char *buf,sqlite3_value *value){
    return unsignedStr_to_signedStr_buffer(buf, sqlite3_value_text(value));
}

const char *sqlite_value_signed_text_cloned(sqlite3_value *value){
    const unsigned char *str=sqlite3_value_text(value);
    char *buf=NEW_ARRAY_INSTANCE(strlen((const char *) str)+1, char);
    return unsignedStr_to_signedStr_buffer(buf, str);
}


