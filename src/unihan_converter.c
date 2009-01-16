/** 
 * @file unihan_converter.c
 * @brief Convert original Unihan.txt to SQL database.
 *
 * This program converts original Unihan.txt to SQL database.
 * If calling this program with _validation postfix (e.g. unihan_field_validation),
 * it will verify the generated Unihan database by comparing the field values 
 * from the database and original Unihan.txt
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <glib/gprintf.h>
#include "allocate.h"
#include "str_functions.h"
#include "file_functions.h"
#include "verboseMsg.h"
#include "Unihan_builtin.h"
#include "Unihan.h"

#define USAGE_MSG "Usage: %s [-h] [-V num] [-v] [-t dbTableFile] <Unihan.txt> <mainUnihan.db>\n\
 -h: this help\n\
 -V num: verbose level\n\
 -v: show version\n\
 -t dbTableFile: DB-Table file which specifies what tables the db files contains.\n\
 Unihan.txt: Unihan.txt from Unicode Unihan\n\
 mainUnihan.db: Main unihan.db holds every tables that are not defined in dbTableFile\n"

#define BUFFER_SIZE 2000
FILE *logFile=NULL;
FILE *dbTableFile=NULL;
gboolean testMode=FALSE;
sqlite3 *mainDb=NULL;
StringList *dbAliasList=NULL;
StringList *dbFileNameList=NULL;
GHashTable *dbAliasHash=NULL;
GHashTable *dbHash=NULL;
StringList *createdTableList=NULL;

static void printUsage(char **argv){
    printf(USAGE_MSG,argv[0]);
}

static int create_index(UnihanTable table, sqlite3 *db, const char* databaseName){
    GString *strBuf=g_string_new("CREATE INDEX ");
    if (databaseName){
	g_string_append_printf(strBuf,"%s.",databaseName);
    }
    UnihanField *fields=unihanTable_get_builtin_fields(table);
    int i;

    /* Create index */
    g_string_append_printf(strBuf,"%sIndex ON %s ( ",
	    unihanTable_builtin_to_string(table),
	    unihanTable_builtin_to_string(table));
    for(i=0;fields[i]>=0;i++){
	if (unihanField_builtin_has_flags(fields[i], UNIHAN_FIELDFLAG_NO_INDEX | UNIHAN_FIELDFLAG_SINGLETON))
	    continue;
	if (i>0)
	    g_string_append_c(strBuf,',');
	g_string_append_printf(strBuf," %s",
		unihanField_builtin_to_string(fields[i]));

    }
    g_string_append(strBuf,");");
    verboseMsg_print(VERBOSE_MSG_INFO1,"[I1] %s\n",strBuf->str);
    int ret=sqlite_exec_handle_error(db, strBuf->str, NULL, NULL, sqlite_error_callback_print_message, 
	    "create_table(): Index Error");

    g_string_free(strBuf,TRUE);
    g_free(fields);
    return ret;
}


static int create_table(UnihanTable table, sqlite3 *db, const char* databaseName){
    GString *strBuf=g_string_new("CREATE TABLE ");
    if (databaseName){
	g_string_append_printf(strBuf,"%s.",databaseName);
    }
    g_string_append_printf(strBuf,"%s (",unihanTable_builtin_to_string(table));
    UnihanField *fields=unihanTable_get_builtin_fields(table);
    int i;
    for(i=0;fields[i]>=0;i++){
	if (i>0)
	    g_string_append_c(strBuf,',');
	g_string_append_printf(strBuf," %s %s NOT NULL",
		unihanField_builtin_to_string(fields[i]),
		unihanField_builtin_has_flags(fields[i], UNIHAN_FIELDFLAG_INTEGER) ? "integer" : "text");

    }
    g_string_append(strBuf,", PRIMARY KEY (");
    for(i=0;fields[i]>=0;i++){
	if (unihanField_builtin_has_flags(fields[i], UNIHAN_FIELDFLAG_NO_PRIMARYKEY | UNIHAN_FIELDFLAG_SINGLETON))
	    continue;
	if (i>0)
	    g_string_append_c(strBuf,',');
	g_string_append_printf(strBuf," %s",unihanField_builtin_to_string(fields[i]));

    }
    g_string_append(strBuf,") );");
    verboseMsg_print(VERBOSE_MSG_INFO1,"[I1] %s\n",strBuf->str);
    int ret=sqlite_exec_handle_error(db, strBuf->str, NULL, NULL, sqlite_error_callback_print_message, 
	    "create_table(): Error");


    g_string_free(strBuf,TRUE);
    g_free(fields);

    if (!ret){
	create_index(table, db, NULL);
    }
    return ret;
}

//static int create_indices(sqlite3 *db){
//    UnihanTable table;
//    int ret;
//    for(table=0;table<UNIHAN_TABLE_3RD_PARTY;table++){
//        ret=create_index(table,db,NULL);
//        if (ret)
//            break;
//    }
//    return ret;
//}



gboolean isKSemanticValue_matched(const char *value, const char *resultField){
    char** resultArray=g_strsplit_set(resultField,"<,", -1);
    char** valueArray=g_strsplit_set(value,"<,",-1);

    if (strcmp(resultArray[0],valueArray[0])!=0){
	g_strfreev(resultArray);
	g_strfreev(valueArray);
	return FALSE;
    }
    int i=1,j=1;
    for(i=1;resultArray[i]!=NULL;i++){
	for(j=1;valueArray[j]!=NULL;j++){
	    if (strcmp(resultArray[i],valueArray[j])==0){
		g_strfreev(resultArray);
		g_strfreev(valueArray);
		return TRUE;
	    }
	}
    }    
    g_strfreev(resultArray);
    g_strfreev(valueArray);
    if (i==1 && j==1){
	/* No further dictionary information */
	return TRUE;
    }
    return FALSE;    
}
int unihan_test_record(gunichar code, UnihanField field, char *value){
    char codeStr[10];
    g_snprintf(codeStr,10,"%d",code);

//    char *charStr=ucs4_to_utf8(code);
//    int ret;
//    gboolean found=FALSE;
//    int i;
//    int colCount,totalCount;

//    /* code -> value */
//    printf("=== code -> value \n");
//    SQL_Result *sResult=unihan_find_all_matched(UNIHAN_FIELD_CODE,codeStr,field, UNIHAN_QUERY_OPTION_SCALAR_STRING);
//    ret=sResult->execResult;
//    if (ret) {
//        printf(" Database error:%s\n", sResult->errMsg);
//        sql_result_free(sResult,TRUE);
//        unihanDb_close();
//        exit(ret);
//    }
//    colCount=sResult->colCount;
//    totalCount=sResult->resultList->len;

//    if (totalCount<=0){
//        printf(" Field %s of character %d(%s) does not have any value\n",unihanField_to_string(field),code, charStr);
//        exit(-10);
//    }

//    for(i=0;i<totalCount;i++){
//        switch(field){
//            case UNIHAN_FIELD_kSEMANTICVARIANT:
//            case UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT:
//                found=isKSemanticValue_matched(value,stringList_index(sResult->resultList,(i+1)*colCount-1));
//                break;
//            default:
//                if (strcmp(value,stringList_index(sResult->resultList,(i+1)*colCount-1))==0){
//                    found=TRUE;
//                }
//                break;
//        } 
//        if (found){    
//                break;
//        }
//        
//    }
//    if (!found){
//        printf(" Field %s of character %d(%s) value: [%s]  does not equal the original value [%s]\n",
//                unihanField_to_string(field),code, charStr, stringList_index(sResult->resultList,totalCount-1), value );
//        exit(-11);
//    }
//    sql_result_free(sResult,TRUE);

//    
//    /* value -> utf8 */
//    printf("=== value -> utf8 \n");
//    

//    char buf[1000];
//    gunichar c;
//    found=FALSE;

//    switch(field){
//        case UNIHAN_FIELD_kCOMPATIBILITYVARIANT:
//        case UNIHAN_FIELD_kSIMPLIFIEDVARIANT:
//        case UNIHAN_FIELD_kTRADITIONALVARIANT:
//            c=unihanChar_parse(value);
//            g_snprintf(buf,1000,"%d",c);
//            break;
//        default:
//            g_strlcpy(buf,value,1000);
//            break;
//    }

//    sResult=unihan_find_all_matched(field,buf,UNIHAN_FIELD_CODE, UNIHAN_QUERY_OPTION_DEFAULT);

//    ret=sResult->execResult;
//    if (ret) {
//        printf(" Database error:%s\n", sResult->errMsg);
//        sql_result_free(sResult,TRUE);
//        unihanDb_close();
//        exit(ret);
//    }
//    colCount=sResult->colCount;
//    totalCount=sResult->resultList->len;


//    if (totalCount<=0){
//        printf(" Cannot found value %s in field %s.\n",buf,unihanField_to_string(field));
//        exit(-12);
//    }

//    for(i=0;i<totalCount;i++){
//        verboseMsg_print(VERBOSE_MSG_INFO3,"  Result returned from database: %s\n",
//                stringList_index(sResult->resultList,(i+1)*colCount-1));
//        if (strcmp(codeStr,stringList_index(sResult->resultList,(i+1)*colCount-1))==0){
//            found=TRUE;
//            break;
//        }
//    }
//    if (!found){
//        printf(" Field %s of character %d(%s) does not associate with value %s \n",
//                unihanField_to_string(field),code,charStr,value);
//        exit(-13);
//    }

//    sql_result_free(sResult,TRUE);
//    g_free(charStr);
    return 0;
}

/**
 * Parse record line.
 */
void parse_record(gchar* rec_string){
    if (testMode){
	verboseMsg_print(VERBOSE_MSG_WARNING,"\nTesting on %s\n",rec_string);
    }else{
	verboseMsg_print(VERBOSE_MSG_INFO2,"===buf=%s\n",rec_string);
    }
    gchar** fields=g_strsplit(rec_string,"\t",3);
    int ret=0;

    gunichar code=  unihanChar_parse(fields[0]);
    static gunichar lastCode=0;
    char sqlBuf[BUFFER_SIZE];
    if ((code!=lastCode) && (!testMode)){
	g_snprintf(sqlBuf, BUFFER_SIZE, "INSERT INTO codeTable VALUES (%u);",code);
	ret=sqlite_exec_handle_error(mainDb, sqlBuf, NULL, NULL, sqlite_error_callback_print_message, 
		"create_table(): Error");
	if (ret)
	    exit(ret);
	lastCode=code;
    }

    UnihanField field=unihanField_builtin_parse(fields[1]);

    if (testMode){
	if (unihanField_builtin_has_flags(field,UNIHAN_FIELDFLAG_SINGLETON)){
	    unihan_test_record(code, field, fields[2]);
	}else{
	    gchar** values=g_strsplit(fields[2]," ",-1);
	    int i;
	    for(i=0;values[i]!=NULL;i++){
		ret=unihan_test_record(code, field, values[i]);
		if (ret>0){
		    break;
		}
	    }
	    g_strfreev(values);
	}
    }else{
	/* Import Mode */
	ret=unihan_import_builtin_table_tagValue(mainDb, code, field, fields[2]);
    }

    g_strfreev(fields);
    if (ret>0){
	if (logFile){
	    fclose(logFile);
	}
	exit(ret);
    }
}

static void dbHash_foreach_func(gpointer key, gpointer value, gpointer user_data){
    char sqlBuf[PATH_MAX];
    char *dbAlias=(char *)key;
    sqlite3 *db=(sqlite3 *)value;
    verboseMsg_print(VERBOSE_MSG_INFO2,"[I2 ] dbHash_foreach_func(%s,-,NULL)\n",dbAlias);
    char *openPath=(char *)g_hash_table_lookup(dbAliasHash,dbAlias);
    sqlite3_close(db);
    sqlite3_snprintf(PATH_MAX,sqlBuf,"ATTACH DATABASE %Q AS %q;",openPath,dbAlias);
    verboseMsg_print(VERBOSE_MSG_INFO2,"[I2 ] sqlBuf=%s\n",sqlBuf);
    int ret=sqlite_exec_handle_error(mainDb, sqlBuf, NULL, NULL, 
	    sqlite_error_callback_print_message,  "createDbs(): Error");
    if (ret)
	exit(ret);

}

static int createDbs(const char *mainDbFilename){
    int ret;
    ret= sqlite_open(mainDbFilename,  &mainDb,  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    if (ret) {
	fprintf(stderr, "Can't open to database: %s, err msg:%s\n", mainDbFilename,sqlite3_errmsg(mainDb));
	sqlite3_close(mainDb);
	exit(ret);
    }

    char *pathTmp=g_strdup(mainDbFilename);
    char *dirName=dirname(pathTmp);
    char pathBuf[PATH_MAX];
    createdTableList=stringList_new();
    dbAliasList=stringList_new();
    dbFileNameList=stringList_new();
    gboolean isDbFile=TRUE;
    UnihanTable table;
    StringList *sList;

    if (dbTableFile){
	char readBuf[BUFFER_SIZE];
	char *openPath=NULL;
	sqlite3 *db=NULL;
	const char *dbAlias=NULL;
	const char *dbFilename=NULL;
	const char *tableName=NULL;
	dbAliasHash=g_hash_table_new_full(g_str_hash,g_str_equal,NULL,NULL);
	dbHash=g_hash_table_new_full(g_str_hash,g_str_equal,NULL,NULL);
	int dbIndex,aliasIndex;

	while(fgets(readBuf,BUFFER_SIZE,dbTableFile)!=NULL){
	    g_strstrip(readBuf);
	    if (isEmptyString(readBuf)){
		continue;
	    }
	    if (readBuf[0]=='#'){
		// Comment line, skip
		continue;
	    }
	    if (readBuf[0]=='='){
		isDbFile=FALSE;
		continue;
	    }
	    printf("*** readBuf=%s\n",readBuf);
	    sList=stringList_new_strsplit_set(readBuf," \t",2);
	    dbAlias=stringList_index(sList,0);
	    if (isDbFile){
		dbFilename=stringList_index(sList,1);
		if (!stringList_has_string(dbAliasList,dbAlias)){
		    g_strlcpy(pathBuf,dirName,PATH_MAX);
		    openPath=path_concat(pathBuf,dbFilename,PATH_MAX);
		    aliasIndex=stringList_insert(dbAliasList,dbAlias);
		    dbIndex=stringList_insert(dbFileNameList,openPath);
		    verboseMsg_print(VERBOSE_MSG_INFO3,"[I3  ] Openpath=%s, db alias=%s\n",openPath,dbAlias);
		    ret= sqlite_open(openPath,  &db,  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		    if (ret) {
			fprintf(stderr, "Can't open to database: %s, err msg:%s\n", openPath, sqlite3_errmsg(db));
			sqlite3_close(db);
			exit(ret);
		    }
		    g_hash_table_insert(dbAliasHash, (gpointer) stringList_index(dbAliasList,aliasIndex), (gpointer)stringList_index(dbFileNameList,dbIndex));
		    g_hash_table_insert(dbHash, (gpointer)stringList_index(dbAliasList,aliasIndex),db);
		}
	    }else{
		tableName=stringList_index(sList,1);
		/* Create table */
		table=unihanTable_builtin_parse(tableName);
		db= (sqlite3 *) g_hash_table_lookup(dbHash,dbAlias);
		if ((ret=create_table(table,db,NULL))==0){
		    stringList_insert_const(createdTableList,tableName);
		    verboseMsg_print(VERBOSE_MSG_INFO2,"[I2 ] Table %s in Db %s is created\n",tableName,dbAlias);
		}else{
		    return ret;
		}
	    }
	    stringList_free(sList);
	}

	/* Attach dbs */
	g_hash_table_foreach(dbHash,dbHash_foreach_func, NULL);

	fclose(dbTableFile);
	g_hash_table_destroy(dbHash);
	g_hash_table_destroy(dbAliasHash);
    }

    /* Create rest tables in main db */
    for (table=0;table<UNIHAN_TABLE_3RD_PARTY;table++){
	if (!stringList_has_string(createdTableList,unihanTable_builtin_to_string(table))){
	    if ((ret=create_table(table,mainDb,NULL))!=0){
		/* Return error */
		return ret;
	    }
	}
    }
    g_free(pathTmp);

    return 0;
}

/**
 * Whether the command line options are valid.
 */
static gboolean is_valid_arguments(int argc, char **argv) {
    int opt;
    int verboseLevel=VERBOSE_MSG_WARNING;
    if (!argc){
	printUsage(argv);
	exit(0);
    }
    while ((opt = getopt(argc, argv, "hV:vt:")) != -1) {
	switch (opt) {
	    case 'h':
		printUsage(argv);
		exit(0);
	    case 'v':
		printf("libUnihan %s\n",PRJ_VERSION);
		exit(0);
	    case 'V':
		verboseLevel=atoi(optarg);
		break;
	    case 't':
		if ((dbTableFile=fopen(optarg,"r"))==NULL){
		    fprintf(stderr, "Unable to read from file %s\n",argv[optind]);
		    exit (-2);
		}
		break;
	    default: /* ’? */
		printf("Unrecognized Option -%c\n\n",opt);
		return FALSE;
	}
    }
    if (argc !=  optind+2){
	printf("Invalid number of options. argc=%d, optind=%d\n",argc,optind);
	return FALSE;
    }
    verboseMsg_set_level(verboseLevel);
    return TRUE;
}


int main(int argc,char** argv){
    if (!is_valid_arguments(argc, argv)){
	printUsage(argv);
	exit(-1);
    }
    FILE *inF=NULL;
    if ((inF=fopen(argv[optind],"r"))==NULL){
	fprintf(stderr, "Unable to read from file %s\n",argv[optind]);
	return -2;
    }

    if ((logFile=fopen("Unihan.log","w"))==NULL){
	fprintf(stderr, "Unable to open log file Unihan.log\n");
	return -2;
    }


    char readBuf[BUFFER_SIZE];

    if (g_strrstr(argv[0],"_validation")){
	testMode=TRUE;
    }else{
	verboseMsg_set_logFile(logFile);
	verboseMsg_set_fileLevel(verboseMsg_get_level());
	if (createDbs(argv[optind+1])){
	    fprintf(stderr, "Unable to create database files.\n");
	    return 3;
	}
    }

    while(fgets(readBuf,BUFFER_SIZE,inF)!=NULL){
	g_strstrip(readBuf);
	if (isEmptyString(readBuf)){
	    continue;
	}
	if (readBuf[0]=='#'){
	    // Comment line, skip
	    continue;
	}
	parse_record(readBuf);
    }

//    /* Create index */
//    create_indices(mainDb);
    sqlite3_close(mainDb);
    fclose(inF);
    if (!testMode){
	fclose(logFile);
    }
    verboseMsg_print(VERBOSE_MSG_ERROR,"Done\n.");
    return 0;
}

