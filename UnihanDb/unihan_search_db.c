/** 
 * @file unihan_search_db.c
 * @brief Search and collect the fields and tables in Unihan database files from given paths.
 *
 * This program searches and collects the fields and tables in Unihan database files 
 * from given paths. If no path is given from the command line option, then use the 
 * path defined in \c UNIHAN_DEFAULT_DB_PATH.
 *
 * @since {libUnihan 0.6.0}
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
#include <glib/gprintf.h>
#include <glib/gstdio.h>
#include <libgen.h>
#include "allocate.h"
#include "verboseMsg.h"
#include "file_functions.h"
#include "str_functions.h"
#include "sqlite_functions.h"
#include "Unihan.h"

#define USAGE_MSG "Search and collect the fields and tables in Unihan database files from given paths.\n\
Usage: %s [-h] [-l] [-O outputPath] [-V num] [-v] [searchPath]\n\
   Specify SEARCH_PATH to search with custom search path,\n\
   otherwise default search path " UNIHAN_DB_SEARCH_PATH " will be used.\n\
   Use '%c' as path separater.\n\
Options:\
   -h: Show this help message.\n\
   -l: Search symbolic linked db as well.\n\
   -O outputPath: specify the directory to put the cache datbases.\n\
   -V [num]: Specify verbose level, the higher the num, the more detail is shown. \n\
      Default is 2 (show warning). \n\
   -v: Show libUnihan version number.\n"

#define BUFFER_SIZE 2000
#define PSEUDO_CACHE_DB "pseudo.cache"
#define FIELD_DB_POSTFIX ".db"
#define PSEUDO_DB_POSTFIX ".pseudo"
#define FIELD_DB_PATTERNS "*.db *.db*"
#define PSEUDO_DB_PATTERNS "*.pseudo *.pseudo*"


gchar *searchPath=NULL;

gchar *outputDir=NULL;

guint fileMode= FILE_MODE_READ | FILE_MODE_NO_SYMLINK; 

UnihanTable installedBuiltInTables[UNIHAN_TABLES_COUNT];
guint installedBuiltInTableIndex=0;


static gboolean unihanTable_exists(UnihanTable table ){
    int i;
    for(i=0;i<installedBuiltInTableIndex;i++){
	if (installedBuiltInTables[i]==table){
	    return TRUE;
	}
    }
    return FALSE;
}

static void printUsage(char **argv){
    printf(USAGE_MSG,argv[0],PATH_SEPARATOR);
}

/**
 * Whether the command line options are valid.
 */
static gboolean is_valid_arguments(int argc, char **argv) {
    int opt;
    int verboseLevel=VERBOSE_MSG_WARNING;
    outputDir=UNIHAN_DB_DEFAULT_PATH;
    searchPath=UNIHAN_DB_SEARCH_PATH;

    if (!argc){
	printUsage(argv);
	exit(0);
    }
    while ((opt = getopt(argc, argv, "hlO:V:v")) != -1) {
	switch (opt) {
	    case 'h':
		printUsage(argv);
		exit(0);
	    case 'l':
		fileMode &= ~ FILE_MODE_NO_SYMLINK;
		break;
	    case 'O':
		outputDir=optarg;
		break;
	    case 'V':
		verboseLevel=atoi(optarg);
		break;
	    case 'v':
		printf("libUnihan %s\n",PRJ_VER);
		exit(0);
	    default: /* ’? */
		printf("Unrecognized Option -%c\n\n",opt);
		return FALSE;
	}
    }
    if (argc >  optind+1){
	printf("Invalid number of options. argc=%d, optind=%d\n",argc,optind);
	return FALSE;
    }else if (argc == optind+1){
	searchPath=argv[optind];
    }
    verboseMsg_set_level(verboseLevel);
    return TRUE;
}

static StringList * get_tableNames(sqlite3 *db){
    SQL_Result *sResult=sqlite_get_tableNames(db);
    if (sResult->execResult){
	verboseMsg_print(VERBOSE_MSG_CRITICAL, "Cannot get table names. %s\n",sResult->errMsg);
	sql_result_free(sResult,TRUE);
	exit (-1);
    }
    return sql_result_free(sResult,FALSE);
}

static gchar* getDbName(gchar *buf, const gchar* dbFilename){
    gchar buf2[PATH_MAX];
    g_strlcpy(buf2,dbFilename,PATH_MAX);
    gchar *orig=basename(buf2);

    gchar *found=g_strrstr(orig,".db");
    if (!found){
	return buf;
    }
    char *ptr;
    int i=0;
    for(ptr=orig;ptr<found;ptr++){
	buf[i]=*ptr;
	i++;
    }
    buf[i]='\0';
    return buf;
}

static int create_fieldCacheDb_tables(sqlite3 *field_cache_db){
    /* Create DbFileTable */
    if (sqlite_exec_handle_error(field_cache_db,"CREATE TABLE DbFileTable "
	    "(DbName text NOT NULL, DBPath text NOT NULL,"
	    "PRIMARY KEY(DbName));",NULL,NULL,
	    sqlite_error_callback_hide_constraint_error,"Error on creating DbFileTable")){
	return 2;
    }

    /* Create TableIdTable */
    if (sqlite_exec_handle_error(field_cache_db,"CREATE TABLE TableIdTable "
	    "(TableId integer NOT NULL, TableName text NOT NULL,"
	    "PRIMARY KEY(TableId));",NULL,NULL,
	    sqlite_error_callback_hide_constraint_error,"Error on creating TableIdTable")){
	return 3;
    }

    /* Create FieldIdTable */
    if (sqlite_exec_handle_error(field_cache_db,"CREATE TABLE FieldIdTable "
	    "(FieldId integer NOT NULL, FieldName text NOT NULL, "
	    "Pseudo integer NOT NULL, "
	    "PRIMARY KEY(FieldId));",NULL,NULL,
	    sqlite_error_callback_hide_constraint_error,"Error on creating FieldIdTable")){
	return 4;
    }


    /* Create RealFieldTable */
    if (sqlite_exec_handle_error(field_cache_db,"CREATE TABLE RealFieldTable "
	    "(FieldId integer NOT NULL, TableId integer NOT NULL, "
	    " DBName text NOT NULL, Preferred integer NOT NULL,"
	    "PRIMARY KEY(FieldId, TableId, DBName));",NULL,NULL,
	    sqlite_error_callback_hide_constraint_error,"Error on creating RealFieldTable")){	    
	return 5;
    }

    /* Create PseudoFieldRequireTable */
    if (sqlite_exec_handle_error(field_cache_db,"CREATE TABLE PseudoFieldRequireTable "
		"(FieldId integer NOT NULL, TableId integer NOT NULL, "
		"PRIMARY KEY(FieldId, TableId));",NULL,NULL,
		sqlite_error_callback_hide_constraint_error,"Error on creating PseudoFieldRequireTable")){	    
	return 5;
    }

    return 0;
}

static int create_fieldCacheDb_indexes(sqlite3 *field_cache_db){
    if (sqlite_exec_handle_error(field_cache_db,"CREATE INDEX DbFileIndex ON DbFileTable (DbName);"
	    ,NULL,NULL,
	    sqlite_error_callback_hide_constraint_error,"DbFileIndex create")){
	return 11;
    }

    if (sqlite_exec_handle_error(field_cache_db,"CREATE INDEX TableIdIndex ON TableIdTable (TableId);"
	    ,NULL,NULL,
	    sqlite_error_callback_hide_constraint_error,"TableIdIndex create")){
	return 12;
    }

    if (sqlite_exec_handle_error(field_cache_db,"CREATE INDEX RealFieldIdIndex ON FieldIdTable (FieldId);"
	    ,NULL,NULL,
	    sqlite_error_callback_hide_constraint_error,"RealFieldIdIndex create")){
	return 13;
    }

    if (sqlite_exec_handle_error(field_cache_db,
	    "CREATE INDEX RealFieldIndex ON RealFieldTable (FieldId, TableId, DbName);"
	    ,NULL,NULL,
	    sqlite_error_callback_hide_constraint_error,"RealFieldIndex create")){
	return 14;
    }

    if (sqlite_exec_handle_error(field_cache_db,
		"CREATE INDEX PseudoFieldRequireIndex ON PseudoFieldRequireTable (FieldId, TableId);"
		,NULL,NULL,
		sqlite_error_callback_hide_constraint_error,"Error on creating PseudoFieldRequireTable")){	    
	return 5;
    }
    return 0;
}


static int create_fieldCacheDb(sqlite3 *field_cache_db, StringList *dbFile_list){
    int i,j,k,ret;
    UnihanField field,field_tmp;
    UnihanField field_3rdParty_index=UNIHAN_FIELD_3RD_PARTY;
    UnihanTable table,table_tmp;
    UnihanField table_3rdParty_index=UNIHAN_TABLE_3RD_PARTY;

    sqlite3 *db;
    StringList *tableList=NULL,*fieldList=NULL;
    char sqlCmd_buf[BUFFER_SIZE];
    char dbName[PATH_MAX];
    char *errMsg_ptr;

    ret=create_fieldCacheDb_tables(field_cache_db);
    if (ret){
	return ret;
    }

    
    for(i=0;i<dbFile_list->len;i++){
	verboseMsg_print(VERBOSE_MSG_INFO1,"Opening %s \t",stringList_index(dbFile_list,i));
	ret=sqlite_open(stringList_index(dbFile_list,i),&db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
	if (ret){
	    verboseMsg_print(VERBOSE_MSG_ERROR,"DB open error:%s\n",sqlite3_errmsg(db));
	    sqlite3_close(db);
	    continue;
	}
	verboseMsg_print(VERBOSE_MSG_INFO1,"OK.\n",stringList_index(dbFile_list,i));

	tableList=get_tableNames(db);
	for(j=0;j<tableList->len;j++){
	    table_tmp=unihanTable_parse(stringList_index(tableList,j));

	    if (table_tmp>=0){
		table=table_tmp;
		if (!unihanTable_exists(table)){
		    installedBuiltInTables[installedBuiltInTableIndex++]=table;
		    installedBuiltInTables[installedBuiltInTableIndex]=UNIHAN_INVALID_TABLE;
		}
	    }else{
		/* Not found in built-in record, should be 3rd party. */
		table=table_3rdParty_index++;
	    }
	    g_snprintf(sqlCmd_buf,BUFFER_SIZE,"SELECT * FROM %s;",stringList_index(tableList,j));
	    fieldList=sqlite_get_fieldNames(db, sqlCmd_buf , &ret, &errMsg_ptr);
	    if (ret){
		verboseMsg_print(VERBOSE_MSG_ERROR," SQL Error:%s msg:%s\n",sqlite3_errmsg(db),errMsg_ptr);
		continue;
	    }

	    for(k=0; k<fieldList->len; k++){
		field_tmp=unihanField_parse(stringList_index(fieldList,k));
		if (field_tmp>=0){
		    field=field_tmp;
		}else{
		    /* Not found in built-in record, should be 3rd party. */
		    field=field_3rdParty_index++;
		}

		if (j==0){
		    /* 
		     * Only insert to DbFileTable if there are at least one
		     * fields
		     */
		    getDbName(dbName,stringList_index(dbFile_list,i));
		    sqlite3_snprintf(BUFFER_SIZE,sqlCmd_buf,
			    "INSERT INTO DbFileTable VALUES (%Q, %Q);",
			    dbName, stringList_index(dbFile_list,i) );
		    ret=sqlite_exec_handle_error(field_cache_db,sqlCmd_buf,NULL,NULL,
			    sqlite_error_callback_hide_constraint_error,"TableIdTable insert");
		    verboseMsg_print(VERBOSE_MSG_INFO2,"%s\n",sqlCmd_buf);

		}
		if (k==0){
		    /* 
		     * Only insert to TableIdTable if there are at least one
		     * fields
		     */
		    sqlite3_snprintf(BUFFER_SIZE,sqlCmd_buf,
			    "INSERT INTO TableIdTable VALUES (%d, %Q);",
			    table, stringList_index(tableList,j) );
		    ret=sqlite_exec_handle_error(field_cache_db,sqlCmd_buf,NULL,NULL,
			    sqlite_error_callback_hide_constraint_error,"TableIdTable insert");
		    verboseMsg_print(VERBOSE_MSG_INFO2,"%s\n",sqlCmd_buf);

		}

		sqlite3_snprintf(BUFFER_SIZE,sqlCmd_buf,
			"INSERT INTO FieldIdTable VALUES (%d, %Q, 0);",
			table, stringList_index(tableList,j) );
		ret=sqlite_exec_handle_error(field_cache_db,sqlCmd_buf,NULL,NULL,
			sqlite_error_callback_hide_constraint_error,"FieldIdTable insert");
		verboseMsg_print(VERBOSE_MSG_INFO2,"%s\n",sqlCmd_buf);


		sqlite3_snprintf(BUFFER_SIZE,sqlCmd_buf,
			"INSERT INTO RealFieldTable VALUES (%d, %d, %Q, %d);",
			field, table, dbName, 0);	
		verboseMsg_print(VERBOSE_MSG_INFO2,"%s\n",sqlCmd_buf);
		ret=sqlite_exec_handle_error(field_cache_db,sqlCmd_buf,NULL,NULL,
			sqlite_error_callback_hide_constraint_error,"RealFieldTable insert");
	    }
	    stringList_free(fieldList);
	}
	stringList_free(tableList);
	sqlite3_close(db);
    }

    return 0;
}

static StringList *find_dbs(const char *searchPath, const gchar *file_pattern){
    StringList *path_list=path_split(searchPath);
    int i;
    StringList *dbFile_list=NULL,*result=NULL;
    dbFile_list=stringList_new();
    for (i=0;i<path_list->len;i++){
	result=lsDir_append(dbFile_list,stringList_index(path_list,i), file_pattern, fileMode, TRUE);
	if (result==NULL){
	    fprintf(stderr,"Error in finding files in %s\n",stringList_index(path_list,i));
	}
    }
    stringList_free(path_list);
    return dbFile_list;
}

static sqlite3 *backup_and_create_cache_db(const gchar *cacheFilename){
    char path_tmp[PATH_MAX],path_orig_tmp[PATH_MAX];
    /* Rename the orig DB_CACHE file */
    g_strlcpy(path_tmp,outputDir,PATH_MAX);
    path_concat(path_tmp,cacheFilename,PATH_MAX);
    g_snprintf(path_orig_tmp,PATH_MAX,"%s.orig",path_tmp);
    if (filename_meets_accessMode(path_tmp, FILE_MODE_EXIST| FILE_MODE_WRITE)){
	g_rename(path_tmp, path_orig_tmp);
    }
    sqlite3 *db=NULL;

    int ret=sqlite_open(path_tmp,&db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    if (ret){
	verboseMsg_print(VERBOSE_MSG_ERROR,"DB create error on %s: %s\n",cacheFilename,sqlite3_errmsg(db));
	sqlite3_close(db);
	return NULL;
    }
    return db;
}



static int add_internal_pseudo_fields(sqlite3 *db){
    int j;
    UnihanField field;
    gboolean pass;
    gchar sqlCmd_buf[BUFFER_SIZE];

    UnihanTable *tables=NULL;
    for(field=0; field< UNIHAN_FIELD_3RD_PARTY;field++){
	if (unihanField_is_pseudo(field)){
	    pass=TRUE;
	    tables=unihanField_get_required_tables(field);
	    for(j=0; tables[j]!=UNIHAN_INVALID_TABLE; j++){
		if (!unihanTable_exists(tables)){
		    pass=FALSE;
		    break;
		}
	    }
	    if (pass){
		for(j=0; tables[j]!=UNIHAN_INVALID_TABLE; j++){
		    sqlite3_snprintf(BUFFER_SIZE,sqlCmd_buf,
			    "INSERT INTO PseudoFieldRequireTable VALUES (%d, %d);",
			    field, tables[j] );
		}
		sqlite3_snprintf(BUFFER_SIZE,sqlCmd_buf,
			"INSERT INTO FieldIdTable VALUES (%d, %Q, 1);",
			field, unihanField_to_string(field) );

	    }
	    free(tables);
	}
    }
    return 0;
}

int main(int argc,char** argv){
    if (!is_valid_arguments(argc, argv)){
	printUsage(argv);
	exit(-1);
    }
    verboseMsg_print(VERBOSE_MSG_INFO3,"searchPath=%s outputDir=%s\n",searchPath,outputDir);
    installedBuiltInTables[0]=UNIHAN_INVALID_TABLE;

    /* Create field cache db */
    StringList *fieldDb_list=find_dbs(searchPath, FIELD_DB_PATTERNS);
    if (fieldDb_list->len<=0){
	fprintf(stderr,"No file matched.\n");
	return -2;
    }

    sqlite3 *field_cache_db=backup_and_create_cache_db(FIELD_CACHE_DB);
    if (!field_cache_db){
	verboseMsg_print(VERBOSE_MSG_ERROR,"Field cache DB create error.\n");
	return 1;
    }

    int ret=create_fieldCacheDb(field_cache_db,fieldDb_list);
    if (ret){
	return ret;
    }
    
    ret=create_fieldCacheDb_indexes(field_cache_db);
    if (ret){
	return ret;
    }
    sqlite3_close(field_cache_db);

    stringList_free(fieldDb_list);
    verboseMsg_print(VERBOSE_MSG_CRITICAL,"Done.\n");
    return 0;
}
