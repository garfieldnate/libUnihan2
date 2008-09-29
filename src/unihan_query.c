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

/** 
 * @file unihan_query.c
 * @brief Demostration program for Unihan database query.
 *
 * This program demonstrates how to query on Unihan database.
 * 
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gprintf.h>
#include <unistd.h>
#include <getopt.h>
#include "allocate.h"
#include "str_functions.h"
#include "Unihan.h"
#include "Unihan_phonetic.h"
#include "verboseMsg.h"

#define USAGE_MSG "Usage: \n\
    Field Query: unihan_query [-V] [-L] [-U] [-Z 0-3] <given_field> <given_value> <query_on_field>\n\
    SQL Query: unihan_query [-V] -S <SQL clause>\n"

#define CMD_OPTIONS "\
Options: \n\
\t-h: show this help.\n\
\t-V: increase the verbose level.\n\
\t-S: pass SQL clause.\n\
\n Field query only options:\n\
\t-L: like mode, specify the given_value is a pattern to be used in LIKE SQL search.\n\
\t-U: output decimal Unicode code point as Unicode scalar string (U+xxxxx).\n\
\t-Z [0-3]: ZhuYin tone mark format, 0 for always shows tone, 1 for  original ZhuYin format,\n\
\t          2 for input method ZhuYin format, 3 for showing as number.\n\
\t-P [0-5]: PinYin accent format, 0 for always shows accent if applicable, 1 for  original PinYin accent format,\n\
\t          2 for Unihan PinYin accent format,  3 for trailing (CCEDIT) format,\n\
\t          4 for input method accent (LV,NV) format,   5 for non-accent (passport) format.\n\
\n Show options:\n\
\t-t, --show-tables: show all the tables in the default db.\n\
\t-a, --show-all-fields: show all supported fields.\n\
\t-p, --show-pseudo-fields: show all pseudo fields.\n\
\t-r, --show-real-fields: show all non-pseudo fields.\n\
\t-f, --show-all-functions: show all supported functions\n"

static struct option longOptions[]={
    {"show-tables",0,NULL,'t'},
    {"show-all-fields",0,NULL,'a'},
    {"show-pseudo-fields",0,NULL,'p'},
    {"show-real-fields",0,NULL,'r'},
    {"show-all-functions",0,NULL,'f'},
    {0,0,0,0}
};

UnihanQueryOption qOption=UNIHAN_QUERY_OPTION_DEFAULT;
char *cmdSqlClause=NULL;
char *givenFieldStr=NULL;
char *givenValueStr=NULL;
char *queryFieldStr=NULL;
int verboseLevel=VERBOSE_MSG_ERROR;

int zhuYin_toFormat=-1;
int pinYin_toFormat=-1;
gboolean useTrailingNumber=TRUE;


static void printUsage(){
    printf(USAGE_MSG);
    printf(CMD_OPTIONS);
}

static StringList * get_tableNames(){
    SQL_Result *sResult=unihanDb_get_tableNames();
    if (sResult->execResult){
	verboseMsg_print(VERBOSE_MSG_CRITICAL, "Cannot get table names. %s\n",sResult->errMsg);
	sql_result_free(sResult,TRUE);
	unihanDb_close();
	exit (-1);
    }
    return sql_result_free(sResult,FALSE);
}

static void printTables(){
    int i;
    int ret=unihanDb_open_default();
    if (ret){
	fprintf(stderr, "Unable to open database " UNIHAN_DEFAULT_DB ".\n");
	exit(ret);
    }
    StringList *sList=get_tableNames();
    printf("Tables:\n");
    for(i=0;i<sList->len;i++){
	printf("\t%3d %s\n",i+1,stringList_index(sList,i));
    }
    stringList_free(sList);
    unihanDb_close();
}


static void printFields(char modeChar){
    int i,j,counter=0;
    StringList *sList=NULL;

    switch(modeChar){
	case 'a':
	case 'p':
	    if (modeChar=='a'){
		printf("All supported fields:\n");
	    }else{
		printf("Pseudo fields:\n");
	    }
	    for(i=0;i<UNIHAN_FIELDS_COUNT;i++){
		if (modeChar=='a' || unihanField_is_pseudo(i)){
		    counter++;
		    printf("\t%3d %s\n",counter,unihanField_to_string(i));
		}
	    }
	    break;
	case 'r':
	    printf("Real fields:\n");
	    int ret=unihanDb_open_default();
	    if (ret){
		fprintf(stderr, "Unable to open database " UNIHAN_DEFAULT_DB ".\n");
		exit(ret);
	    }
	    sList=get_tableNames();
	    UnihanTable table;
	    UnihanField *fields;
	    const char *tableName=NULL;
	    for(i=0;i<sList->len;i++){
		tableName=stringList_index(sList,i);
		table=unihanTable_parse(tableName);
		fields=unihanTable_get_db_fields(table);
		for(j=0;fields[j]>=0;j++){
		    counter++;
		    printf("\t%3d %s.%s\n",counter,tableName,unihanField_to_string(fields[j]));
		}
		printf("\n");
		g_free(fields);
	    }
	    stringList_free(sList);
	    unihanDb_close();
	    break;
    }
}

void printFuncs(){
    printf("Database functions:\n\tName                                        Argc\n");
    int i;
    for(i=0;DATABASE_FUNCS[i].argc!=0;i++){
	printf("\t%-40s\t%d\n",DATABASE_FUNCS[i].funcName,DATABASE_FUNCS[i].argc);
    }
}

/**
 * Whether the command line options are valid.
 */
static gboolean is_valid_arguments(int argc, char **argv) {
    int opt;
    int option_index=0;

    while ((opt = getopt_long(argc, argv, "tarpfhUVLS:Z:",longOptions,&option_index)) != -1) {
	switch (opt) {
	    case 'h':
		printUsage();
		exit(0);
	    case 'L':
		qOption |= UNIHAN_QUERY_OPTION_LIKE;
		break;
	    case 'S':
		cmdSqlClause=optarg;
		break;
	    case 'U':
		qOption |= UNIHAN_QUERY_OPTION_SCALAR_STRING;
		break;
	    case 'V':
		verboseLevel++;
		break;
	    case 'Z':
		zhuYin_toFormat=atoi(optarg);
		break;
	    case 't':
		/* Print tables */
		printTables();
		exit(0);
	    case 'a':
	    case 'p':
	    case 'r':
		/* Print fields */
		printFields(opt);
		exit(0);
	    case 'f':
		/* Print fields */
		printFuncs();
		exit(0);
	    default: /* ’? */
                printf("Unrecognized Option -%c\n\n",opt);
		printUsage();
                return FALSE;
        }
    }
    if (qOption & UNIHAN_QUERY_OPTION_LIKE && cmdSqlClause){
	printf("-L and -S cannot be used together!\n");
	printUsage();
	return FALSE;
    }
    if (qOption & UNIHAN_QUERY_OPTION_SCALAR_STRING && cmdSqlClause){
	printf("-U and -S cannot be used together!\n");
	printUsage();
	return FALSE;
    }
    if (!cmdSqlClause){
	if (argc-optind!=3){
	    printf("Too %s parmeters!\n",(argc-optind>3)? "many": "few");
	    printUsage();
	    return FALSE;
	}
	givenFieldStr=argv[optind];
	givenValueStr=argv[optind+1];
	queryFieldStr=argv[optind+2];
    }else{
	/* SQL mode */
	if (argc-optind!=0){
	    printf("Too %s parmeters!\n",(argc-optind>0)? "many": "few");
	    printUsage();
	    return FALSE;
	}
    }
    verboseMsg_set_level(verboseLevel);
    return TRUE;
}

SQL_Result *fieldQuery(){
    UnihanField givenField=unihanField_parse(givenFieldStr);
    UnihanField queryField=unihanField_parse(queryFieldStr);
    if (givenField<0){
	verboseMsg_print(VERBOSE_MSG_CRITICAL,"Invalid given field: %s\n",givenFieldStr);
	exit(-2);
    }
    if (queryField<0){
	verboseMsg_print(VERBOSE_MSG_CRITICAL,"Invalid query field: %s\n",queryFieldStr);
	exit(-2);
    }
    return unihan_find_all_matched(givenField, givenValueStr, queryField,qOption);
}

SQL_Result *sqlQuery(){
    return unihanSql_get_sql_result(cmdSqlClause);
}

void printResult(SQL_Result *sResult){
    int i,j;
    int colCount=sResult->colCount;
    if (colCount<=0){
	printf("No matched results, colCount=%d\n",colCount);
	return;
    }
    int rowCount=sResult->resultList->len/colCount;
    if (rowCount<=0){
	printf("No matched results, rowCount=%d\n",rowCount);
	return;
    }

    const char *resultStr=NULL;
    char *resultTmp=NULL;
    UnihanField queryField;


    for(j=0;j<colCount;j++){
	if (j>0){
	    printf(" |");
	}
	printf("%s",stringList_index(sResult->fieldList, j));
    }
    printf("\n");
    for(i=0;i<rowCount;i++){
	for(j=0;j<colCount;j++){
	    if (j>0){
		printf(" |");
	    }
	    resultStr=stringList_index(sResult->resultList, i*colCount+j);
	    queryField=unihanField_parse(stringList_index(sResult->fieldList, j));
	    if (unihanField_is_mandarin(queryField)){
		if (zhuYin_toFormat>=0){
		    resultTmp=pinYin_to_zhuYin(resultStr,zhuYin_toFormat);
		    resultStr=resultTmp;
		}
	    }
	    printf("%s",resultStr);
	    if (resultTmp){
		resultStr=NULL;
		g_free(resultTmp);
	    }
	}
	printf("\n");
    }
}


int main(int argc, char** argv){
    int ret=0;
    if (!is_valid_arguments(argc,argv)){
	exit(-1);
    }
    ret=unihanDb_open_default();
    if (ret){
	fprintf(stderr, "Unable to open database " UNIHAN_DEFAULT_DB ".\n");
	exit(ret);
    }
    SQL_Result *sResult=NULL;

    if (cmdSqlClause){
	sResult=sqlQuery();
    }else{
	sResult=fieldQuery();
    }
    ret=sResult->execResult;
    if (ret){
	verboseMsg_print(VERBOSE_MSG_CRITICAL, "Query failed.:%s\n",sResult->errMsg);
    }else{
	printResult(sResult);
    }
    sql_result_free(sResult,TRUE);
    unihanDb_close();
    return ret;
}
