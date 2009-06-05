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

#include <ctype.h>
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

#define STRING_BUFFER_SIZE_DEFAULT	2000
#define COREDB_ALIAS			"Core"
#define DEFAULTDB_ALIAS_DEFAULT		"default"
#define DEFAULTDB_FILENAME_DEFAULT	"Unihan_" DEFAULTDB_ALIAS_DEFAULT
#define METADB_FILENAME			"_meta.sqlite"

#define USAGE_MSG_CONVERTER_HEAD "Usage: %s [-h] [-V num] [-v] [-f] [-o outputDir] [-t dbTableFile] <Unihan.txt>\n"
#define USAGE_MSG_VALIDATER_HEAD "Usage: %s [-h] [-V num] [-v] <Unihan.txt>\n"
#define USAGE_MSG_OPTION "Options:\n\
  -h: Show this help\n\
  -V num: Set verbose level\n\
  -v: Show version\n\
  Unihan.txt: Unihan.txt from Unicode Unihan\n"

#define USAGE_MSG_CONVERTER_OPTION "Options for converter only:\n\
  -f: Force overwrite the old databases.\n\
  -o outputDir: directory for the outputted databases.\n\
  -t dbTableFile: DB-Table file which specifies what tables the db files contains.\n\
  defaultUnihan.sqlite: The default database that holds the tables that are not defined in dbTableFile.\n"

#define USAGE_MSG_CONVERTER USAGE_MSG_CONVERTER_HEAD USAGE_MSG_OPTION USAGE_MSG_CONVERTER_OPTION
#define USAGE_MSG_VALIDATER USAGE_MSG_VALIDATER_HEAD USAGE_MSG_OPTION

static FILE *logFile=NULL;
static FILE *dbTableFile=NULL;
static FILE *unihanTxtFile=NULL;

static sqlite3 *defaultDb=NULL;
static GStringChunk *dbAliasChunk=NULL; // Store db aliases
GHashTable *dbAliasHash=NULL; // Store db alias/db pair
static gint tableIdArray[UNIHAN_TABLE_3RD_PARTY];
GHashTable *tableHash=NULL; //Store table/db pair
static sqlite3 *metaDb=NULL;
static gchar outputDir[PATH_MAX];

#define FLAG_TEST_MODE		0x1
#define FLAG_FORCE_OVERWRITE	0x2
static guint flags=0;

static void printUsage(char **argv){
    if (flags & FLAG_TEST_MODE){
	printf(USAGE_MSG_VALIDATER,argv[0]);
    }else{
	printf(USAGE_MSG_CONVERTER,argv[0]);
    }
}

/*
 * Field_Property_Table:
 *      Stores field names and corresponding field properties (as bitwise flags).
 * DB_Alias_Table:
 * 	Stores db file names and their aliases.
 * DB_Alias_Content_Table:
 *      Stores db aliases and containing tables.
 * Exporting_Fields_Table:
 * 	Stores real fields that form pseudo fields.
 * Exporting_Pattern_Table:
 * 	Stores the SQL command patterns that form pseudo fields.
 *
 */
const gchar *meta_SQL_create_table_cmds[]={
    "CREATE TABLE Field_Property_Table"
	" (fieldName text NOT NULL, fieldProperties integer NOT NULL, "
	" PRIMARY KEY (FieldName));",
    "CREATE TABLE DB_Alias_Table"
        " (dbAlias text NOT NULL, dbFileName text NOT NULL, "
	" PRIMARY KEY (dbAlias));",
    "CREATE TABLE DB_Alias_Content_Table"
	" (dbAlias text NOT NULL, tableName text NOT NULL, "
	" PRIMARY KEY (dbAlias, tableName));",
    "CREATE TABLE Exporting_Fields_Table"
	" (pseudoFieldName text NOT NULL, fieldName text NOT NULL, tableName text NOT NULL,"
	" PRIMARY KEY (pseudoFieldName, fieldName, tableName));",
    "CREATE TABLE Exporting_Pattern_Table"
	" (pseudoFieldName text NOT NULL, resultSql text NOT NULL, fromSql text NOT NULL,"
	" PRIMARY KEY (pseudoFieldName));",
    NULL
};

/*=========================================================
 * Create meta dbs
 */
static int create_meta_db(const char *buildDir, sqlite3 **metaDb_ptr){
    gchar buf[PATH_MAX];
    g_strlcpy(buf,buildDir,PATH_MAX);
    path_concat(buf, METADB_FILENAME, PATH_MAX);
    if (filename_meets_accessMode(buf, FILE_MODE_EXIST | FILE_MODE_READ) && (flags & FLAG_FORCE_OVERWRITE)){
	if (remove(buf)){
	    fprintf(stderr, "Can't remove the old database: %s.\n", buf);
	    exit(1);
	}
    }
    int  ret= sqlite_open(buf,  metaDb_ptr,  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    if (ret) {
	fprintf(stderr, "Can't open to database: %s, err msg:%s\n", buf,sqlite3_errmsg(metaDb));
	sqlite3_close(*metaDb_ptr);
	exit(ret);
    }
    int i;
    for(i=0; meta_SQL_create_table_cmds[i]!=NULL; i++){
	verboseMsg_print(VERBOSE_MSG_INFO1,"[I1] %s\n",meta_SQL_create_table_cmds[i]);
	ret=sqlite_exec_handle_error(*metaDb_ptr, meta_SQL_create_table_cmds[i], NULL, NULL,
	       	sqlite_error_callback_print_message,
		"create_meta_db(): Error");
	if (ret) {
	    sqlite3_close(*metaDb_ptr);
	    exit(ret);
	}
    }
    return ret;
}

/* status: enable table name */
#define STATUS_TABLE_ENABLED 2
/* status: enable field name  */
#define STATUS_FIELD_ENABLED 1

#define STATUS_DEFAULT  (STATUS_TABLE_ENABLED | STATUS_FIELD_ENABLED)

static void resolve_directive(gchar *buf, UnihanFieldTablePair *tableFields, int index,int status){
    verboseMsg_print(VERBOSE_MSG_INFO5,"[I5] resolve_directive(%s,{%d,%d},%d,%d)\n",buf,tableFields[0].field,tableFields[0].table,index,status);
    if (status & STATUS_TABLE_ENABLED){
	g_strlcat(buf,unihanTable_to_string_builtin(tableFields[index].table),
		STRING_BUFFER_SIZE_DEFAULT);
    }
    if (status==STATUS_DEFAULT){
	g_strlcat(buf,".",
		STRING_BUFFER_SIZE_DEFAULT);
    }
    if (status & STATUS_FIELD_ENABLED){
	g_strlcat(buf,unihanField_to_string_builtin(tableFields[index].field),
		STRING_BUFFER_SIZE_DEFAULT);
    }
    verboseMsg_print(VERBOSE_MSG_INFO5,"[I5] [Done] resolve_directive() %s\n",buf);
}

static void resolve_pattern(gchar *buf,const gchar *pattern, UnihanFieldTablePair *tableFields){
    verboseMsg_print(VERBOSE_MSG_INFO4,"[I4] resolve_pattern(-,%s,{%d,%d})\n",pattern,tableFields[0].field,tableFields[0].table);
    int i,j,jLen=strlen(pattern);
    int b_ptr=0;
    /* index ==-2: init/fail value */
    /* index ==-1: * value */
    /* index >=0: valid index */
    int index=-2;

    int status= STATUS_DEFAULT;
    gboolean isDirective=FALSE;

    initString(buf);
    for(j=0;j<jLen;j++){
	verboseMsg_print(VERBOSE_MSG_INFO4,"[I4] resolve_pattern(-,%s,{%d,%d}) pattern[%d]=%c\n",pattern,tableFields[0].field,tableFields[0].table,j, pattern[j]);
	if (!isDirective){
	    if (pattern[j]=='#'){
		index=-2;
		isDirective=TRUE;
		status= STATUS_DEFAULT;
	    }else{
		/* Bypassing */
		g_assert(b_ptr<STRING_BUFFER_SIZE_DEFAULT-2);
		buf[b_ptr]=pattern[j];
		++b_ptr;
		buf[b_ptr]='\0';
	    }
	    continue;
	}
	/* is directive  */
	switch (pattern[j]){
	    case '*':
		index=-1;
		for(i=0;i<10;i++){
		    if (tableFields[i].field==UNIHAN_INVALID_FIELD){
			break;
		    }
		    if (i>0){
			g_strlcat(buf,", ",STRING_BUFFER_SIZE_DEFAULT);
		    }
		    resolve_directive(buf,tableFields,i, status);
		}
		status=STATUS_DEFAULT;
		b_ptr=strlen(buf);
		break;
	    case 'T':
		status=STATUS_TABLE_ENABLED;
		break;
	    case 'F':
		status=STATUS_FIELD_ENABLED;
		break;
	    default:
		isDirective=FALSE;
		if (!isdigit(pattern[j])){
		    /* Not the index, print the character to buf */
		    buf[b_ptr]=pattern[j];
		    ++b_ptr;
		    buf[b_ptr]='\0';
		    break;
		}
		verboseMsg_print(VERBOSE_MSG_INFO4,"[I4] index=%d\n",index);
		while(isdigit(pattern[j])){
		    verboseMsg_print(VERBOSE_MSG_INFO4,"[I4] resolve_pattern(-,%s,{%d,%d}) j=%d\n",pattern,tableFields[0].field,tableFields[0].table,j);
		    if (index<0)
			index=0;
		    index+=index*10+pattern[j]-'0';
		    j++;
		}
		j--;
		if (index<0){
		    g_error("Invalid SQL directive at char %d in %s",j,pattern);
		}
		verboseMsg_print(VERBOSE_MSG_INFO4,"[I4] resolve_pattern(-,%s,{%d,%d}) j=%d index=%d\n",pattern,tableFields[0].field,tableFields[0].table,j,index);
		resolve_directive(buf,tableFields,index, status);
		status=STATUS_DEFAULT;
		b_ptr=strlen(buf);
	}
    }
}

static int meta_db_fill_up_exportFormat(sqlite3 *db){
    int i;
    char buf[STRING_BUFFER_SIZE_DEFAULT];
    char buf2[STRING_BUFFER_SIZE_DEFAULT];
    char sqlBuf[STRING_BUFFER_SIZE_DEFAULT*2];
    Enumerate e;
    int ret=0;

    unihanPseudoFieldExportFormat_enumerate_init_builtin(&e);
    while(unihanPseudoFieldExportFormat_has_next_builtin(&e)){
	UnihanPseudoFieldExportFormat *format=unihanPseudoFieldExportFormat_next_builtin(&e);
	for(i=0;i<10;i++){
	    if (format->tableFields[i].field==UNIHAN_INVALID_FIELD){
		break;
	    }
	    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT,sqlBuf,
		    "INSERT INTO Exporting_Fields_Table VALUES (%Q, %Q, %Q)",
		    unihanField_to_string_builtin(format->pseudoField),
		    unihanField_to_string_builtin(format->tableFields[i].field),
		    unihanTable_to_string_builtin(format->tableFields[i].table));
	    verboseMsg_print(VERBOSE_MSG_INFO2,"[I2] %s\n",sqlBuf);
	    ret=sqlite_exec_handle_error(db, sqlBuf, NULL, NULL,
		    sqlite_error_callback_print_message,
		    "meta_db_fill_up(): Exporting_Fields_Table Error");
	    if (ret) {
		sqlite3_close(db);
		exit(ret);
	    }
	}
	resolve_pattern(buf, format->resultSqlPattern, format->tableFields);
	verboseMsg_print(VERBOSE_MSG_INFO2,"[I2] resolved resultSqlPattern:%s\n",buf);
	resolve_pattern(buf2, format->fromSqlPattern, format->tableFields);
	verboseMsg_print(VERBOSE_MSG_INFO2,"[I2] resolved fromSqlPattern:%s\n",buf2);

	sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT *2,sqlBuf,
		"INSERT INTO Exporting_Pattern_Table VALUES (%Q,%Q, %Q)",
		unihanField_to_string_builtin(format->pseudoField),buf,buf2);
	verboseMsg_print(VERBOSE_MSG_INFO1,"[I1] %s\n",sqlBuf);
	ret=sqlite_exec_handle_error(db, sqlBuf, NULL, NULL,
		sqlite_error_callback_print_message,
		"meta_db_fill_up_exportFormat(): Exporting_Pattern_Table Error");
	if (ret) {
	    sqlite3_close(db);
	    exit(ret);
	}
    }
    return ret;
}

static int meta_db_fill_up_dbAlias(sqlite3 *db){
    char readBuf[STRING_BUFFER_SIZE_DEFAULT];
    char sqlBuf[STRING_BUFFER_SIZE_DEFAULT];
    const char *dbAlias=NULL;
    const char *dbFilename=NULL;
    const char *tableName=NULL;
    int ret=0;
    gboolean isDbFile=TRUE;

    gboolean tableAppeared[UNIHAN_TABLE_3RD_PARTY];
    memset(tableAppeared, 0, sizeof(gboolean)*UNIHAN_TABLE_3RD_PARTY);

    while(fgets(readBuf,STRING_BUFFER_SIZE_DEFAULT,dbTableFile)!=NULL){
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
	verboseMsg_print(VERBOSE_MSG_INFO2,"[I2] readBuf=%s\n",readBuf);
	StringList *sList=stringList_new_strsplit_set(readBuf," \t",2);
	dbAlias=stringList_index(sList,0);
	if (isDbFile){
	    dbFilename=stringList_index(sList,1);
	    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT,sqlBuf,
		    "INSERT INTO DB_Alias_Table VALUES (%Q, %Q);",
		    dbAlias,dbFilename);
	    ret=sqlite_exec_handle_error(db, sqlBuf, NULL, NULL,
		    sqlite_error_callback_show_constraint_warning,
		    "meta_db_fill_up_dbAlias():");
	    if (ret!=SQLITE_OK && ret!=SQLITE_CONSTRAINT) {
		sqlite3_close(db);
		exit(ret);
	    }
	}else{
	    /* Insert db alias content */
	    tableName=stringList_index(sList,1);
	    UnihanTable table=unihanTable_parse_builtin(tableName);

	    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT,sqlBuf,
		    "INSERT INTO DB_Alias_Content_Table VALUES (%Q, %Q);",
		    dbAlias,tableName);
	    ret=sqlite_exec_handle_error(db, sqlBuf, NULL, NULL,
		    sqlite_error_callback_print_message,
		    "meta_db_fill_up_dbAlias():  Error");
	    if (ret) {
		sqlite3_close(db);
		exit(ret);
	    }
	    tableAppeared[table]=TRUE;
	}
	stringList_free(sList);
    }
    fclose(dbTableFile);
    UnihanTable t;

    /* By default, un-listed tables go to the main db */
    for(t=0;t<UNIHAN_TABLE_3RD_PARTY;t++){
	if (!tableAppeared[t]){
	    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT,sqlBuf,
		    "INSERT INTO DB_Alias_Content_Table VALUES (%Q, %Q);",
		    DEFAULTDB_ALIAS_DEFAULT,
		    unihanTable_to_string_builtin(t));
	    ret=sqlite_exec_handle_error(db, sqlBuf, NULL, NULL,
		    sqlite_error_callback_print_message,
		    "meta_db_fill_up_dbAlias():  Error");
	    if (ret) {
		sqlite3_close(db);
		exit(ret);
	    }
	    tableAppeared[t]=TRUE;
	}
    }
    return ret;
}

static int meta_db_fill_up(sqlite3 *metaDb){
    Enumerate e;
    int ret=0;
    char buf[PATH_MAX];

    unihanFieldProperties_enumerate_init_builtin(&e);
    while(unihanFieldProperties_has_next_builtin(&e)){
	const UnihanFieldProperties *fieldProperties=unihanFieldProperties_next_builtin(&e);
	sqlite3_snprintf(PATH_MAX,buf,
		"INSERT INTO Field_Property_Table VALUES (%Q, %u)",
		fieldProperties->fieldName,fieldProperties->flags);
	verboseMsg_print(VERBOSE_MSG_INFO1,"[I2] %s\n",buf);
	ret=sqlite_exec_handle_error(metaDb, buf, NULL, NULL,
		sqlite_error_callback_print_message,
		"meta_db_fill_up(): Field_Property_Table Error");
	if (ret) {
	    sqlite3_close(metaDb);
	    exit(ret);
	}
    }

    ret=meta_db_fill_up_exportFormat(metaDb);
    if (ret) {
	sqlite3_close(metaDb);
	exit(ret);
    }

    if (dbTableFile){
	ret=meta_db_fill_up_dbAlias(metaDb);
    }

    return ret;
}

/*=========================================================
 * Import Unihan.txt
 */
static void unihan_import_value_append(gchar *sqlClause, UnihanField field, const gchar *value){
    char sqlBuf[STRING_BUFFER_SIZE_DEFAULT];
    char codeBuf[20];
    long int coding;
    if (unihanField_has_flags_builtin(field, UNIHAN_FIELDFLAG_INTEGER)){
	if (unihanField_has_flags_builtin(field, UNIHAN_FIELDFLAG_UCS4)){
	    /* Convert UCS4 to str */
	    g_snprintf(codeBuf,20,"%lu", (gulong) unihanChar_parse(value));
	    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT, sqlBuf, ", %s",  codeBuf);
	}else if (unihanField_has_flags_builtin(field, UNIHAN_FIELDFLAG_HEXADECIMAL_16)){
	    coding=strtol(value,NULL,16);
	    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT, sqlBuf, ", %d",  coding);
	}else{
	    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT, sqlBuf, ", %s",  value);
	}
    }else{
	sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT, sqlBuf, ", %Q",  value);
    }
    g_strlcat(sqlClause,sqlBuf, STRING_BUFFER_SIZE_DEFAULT);
}

static sqlite3* unihanTable_get_db(UnihanTable table){
    return (sqlite3 *) g_hash_table_lookup(tableHash,&table);
}

static int dB_write(sqlite3 *db, const gchar *sqlClause){
    verboseMsg_print(VERBOSE_MSG_INFO2,"[I2] dB_write() Executing: %s\n",sqlClause);
    return sqlite_exec_handle_error(db, sqlClause, NULL, NULL,
	    sqlite_error_callback_hide_known_constraint_error, "dB_write()" );
}

static int unihan_import_realField(gunichar code, UnihanField field,
	const char *tagValue_normalized, int *counter_ptr){
    char sqlClause[STRING_BUFFER_SIZE_DEFAULT];
    UnihanTable table=unihanField_get_preferred_table_builtin(field);

    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT, sqlClause, "INSERT INTO %s VALUES (%lu",
	    unihanTable_to_string_builtin(table),code);
    unihan_import_value_append(sqlClause,field,tagValue_normalized);
    g_strlcat(sqlClause,");",STRING_BUFFER_SIZE_DEFAULT);

    return dB_write(unihanTable_get_db(table), sqlClause);
}

static int unihan_import_pseudoField(gunichar code, UnihanField field,
	const char *tagValue_normalized, int *counter_ptr, const UnihanPseudoFieldImportFormat *importFormat){
    verboseMsg_print(VERBOSE_MSG_INFO3,"[I3] unihan_import_pseudoField(%u,%d,%s,-,-)\n",code,field,tagValue_normalized);
    int j,ret=0,regexRet;
    int counter_post;
    const gchar *storeFormat=NULL;
    gchar *value;
    gboolean empty;

    char *tagValuePtr=NULL,*tagValuePtr_tmp=NULL;
    char sqlClause[STRING_BUFFER_SIZE_DEFAULT];
    char sqlClause_values[STRING_BUFFER_SIZE_DEFAULT];
    char buf[STRING_BUFFER_SIZE_DEFAULT];
    regex_t preg, preg_post;

    const UnihanPseudoFieldImportFormatPost *importFormatPost=unihanPseudoFieldImportFormatPost_find_builtin(field,importFormat->table);

    /* Prepare regex_t */
    if (importFormatPost){
	if ((regexRet=regcomp(&preg_post, importFormatPost->regex_pattern, REG_EXTENDED))!=0){
	    /* Invalid pattern */
	    regerror(ret,&preg_post,buf,STRING_BUFFER_SIZE_DEFAULT);
	    verboseMsg_print(VERBOSE_MSG_ERROR,
		    "unihan_import_table_tagValue_builtin():Invalid import post pattern %s\n" ,buf);
	    exit(regexRet);
	}
    }

    if ((regexRet=regcomp(&preg, importFormat->importPattern, REG_EXTENDED))!=0){
	/* Invalid pattern */
	regerror(ret,&preg,buf,STRING_BUFFER_SIZE_DEFAULT);
	verboseMsg_print(VERBOSE_MSG_ERROR,
		"unihan_import_table_tagValue_builtin():Invalid pattern %s\n"	,buf);
	exit(regexRet);
    }

    tagValuePtr= (char *)tagValue_normalized;
    counter_post=0;

    /* If importFormatPost!=NULL, then do until no more match in ImportFormatPost */
    do{
	/* sqlClause: INSERT INTO <table> (fields..) */
	/* sqlClause_value: VALUES(field_values...); */
	for(j=0;importFormat->fields[j]!=UNIHAN_INVALID_FIELD;j++){
	    storeFormat= importFormat->storeFormats[j];
	    value=string_regex_formatted_combine_regex_t(tagValuePtr, &preg, storeFormat, 0, counter_ptr);
	    if (j==0){
		if (value){
		    empty=FALSE;
		    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT, sqlClause, "INSERT INTO %s (code",
			    unihanTable_to_string_builtin(importFormat->table));
		    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT, sqlClause_values, " VALUES (%lu",
			    code);
		}else{
		    empty=TRUE;
		    break;
		}
	    }
	    g_strlcat(sqlClause,", ",STRING_BUFFER_SIZE_DEFAULT);
	    g_strlcat(sqlClause, unihanField_to_string_builtin(importFormat->fields[j]),STRING_BUFFER_SIZE_DEFAULT);
	    if (value){
		unihan_import_value_append(sqlClause_values,importFormat->fields[j],value);
		g_free(value);
	    }else{
		verboseMsg_print(VERBOSE_MSG_CRITICAL,
			"unihan_import_table_tagValue_builtin():2nd value should not zero!: str=%s, pattern=%s, substitute=%s\n",
			tagValuePtr,importFormat->importPattern,storeFormat);
		exit(1);
	    }
	}
	g_strlcat(sqlClause,") ",STRING_BUFFER_SIZE_DEFAULT);
	if (!empty){
	    g_strlcat(sqlClause,sqlClause_values,STRING_BUFFER_SIZE_DEFAULT);
	    g_strlcat(sqlClause,");",STRING_BUFFER_SIZE_DEFAULT);
	    ret=dB_write(unihanTable_get_db(importFormat->table), sqlClause);
	    if (ret){
		break;
	    }
	}

	if (importFormatPost){
	    /* See if there is additional match */
	    tagValuePtr_tmp=string_regex_formatted_combine_regex_t(tagValuePtr, &preg_post,
		    importFormatPost->eval_str, 0, &counter_post);
	    if (tagValuePtr!=tagValue_normalized){
		/* Free the old tagValuePtr */
		g_free(tagValuePtr);
	    }
	    if (tagValuePtr_tmp){
		tagValuePtr=tagValuePtr_tmp;
	    }else{
		tagValuePtr=NULL;
	    }
	}else{
	    tagValuePtr=NULL;
	}
	if (ret)
	    break;

    }while(tagValuePtr);
    regfree(&preg);
    if (importFormatPost){
	regfree(&preg_post);
    }
    return ret;
}

/**
 * Import a tag value of a character from Unihan.txt to dbfile.
 *
 * omittable
 * This function imports a tag value of a character from Unihan.txt to dbfile.
 * Note that this function assumes that \a tagValue is singleton, that is.
 * no need to be further split.
 *
 * @param code the UCS4 representation of the character.
 * @param field The UnihanField to be import.
 * @param tagValue The value of the field.
 * @param counter_ptr Pointer to an integer counter. Can be NULL if $+ or $- flags are not used.
 * @return 0 if success, otherwise return nonzero value.
 * @see unihan_import_table_tagValue_builtin().
 */
static int unihan_import_table_single_tagValue_builtin(gunichar code, UnihanField field,
	const char *tagValue, int *counter_ptr){
    verboseMsg_print(VERBOSE_MSG_INFO3,"[I3] unihan_import_table_single_tagValue_builtin(%u,%d,%s,-)\n",code,field,tagValue);
    char *tagValue_normalized=g_utf8_normalize(tagValue,-1,G_NORMALIZE_NFD);
    int ret=0;
    Enumerate e;
    unihanPseudoFieldImportFormat_enumerate_init_builtin(&e,&field);
    if (unihanPseudoFieldImportFormat_enumerate_has_next_builtin(&e)){
	/* Is Pseudo field */
	while(unihanPseudoFieldImportFormat_enumerate_has_next_builtin(&e)){
	    const UnihanPseudoFieldImportFormat *importFormat=unihanPseudoFieldImportFormat_enumerate_next_builtin(&e);
	    if ((ret=unihan_import_pseudoField(code, field, tagValue_normalized, counter_ptr,importFormat))!=0){
		break;
	    }
	}
    }else{
	/* Is Real field */
	ret=unihan_import_realField(code, field, tagValue_normalized, counter_ptr);
    }
    g_free(tagValue_normalized);
    verboseMsg_print(VERBOSE_MSG_INFO4,"[I4] [Done] unihan_import_table_single_tagValue_builtin() ret=%d\n",ret);
    return ret;
}

static int unihan_import_table_tagValue_builtin(gunichar code, UnihanField field, const char *tagValue){
    verboseMsg_print(VERBOSE_MSG_INFO3,"[I3] unihan_import_table_tagValue_builtin(%u,%d,%s)\n",code,field,tagValue);
    int counter=0;
    if (unihanField_has_flags_builtin(field, UNIHAN_FIELDFLAG_SINGLETON)){
	return unihan_import_table_single_tagValue_builtin(code,field,tagValue,&counter);
    }
    int ret,i;
    gchar **values=g_strsplit_set(tagValue," ",-1);
    for(i=0;values[i]!=NULL;i++){
	ret=unihan_import_table_single_tagValue_builtin(code,field,values[i],&counter);
	if (ret!=SQLITE_OK){
	    verboseMsg_print(VERBOSE_MSG_INFO4,"[I4] [Err] unihan_import_table_tagValue_builtin() ret=%d\n",ret);
	    return ret;
	}
    }
    g_strfreev(values);
    verboseMsg_print(VERBOSE_MSG_INFO4,"[I4] [Done] unihan_import_table_tagValue_builtin() ret=%d\n",ret);
    return ret;
}

/*=========================================================
 * Create data dbs
 */
static int create_table(UnihanTable table, sqlite3 *db, const char* databaseName){
    GString *strBuf=g_string_new("CREATE TABLE ");
    if (databaseName){
	g_string_append_printf(strBuf,"%s.",databaseName);
    }
    g_string_append_printf(strBuf,"%s (",unihanTable_to_string_builtin(table));
    UnihanField *fields=unihanTable_get_fields_builtin(table);
    int i;
    for(i=0;fields[i]>=0;i++){
	if (i>0)
	    g_string_append_c(strBuf,',');
	g_string_append_printf(strBuf," %s %s NOT NULL",
		unihanField_to_string_builtin(fields[i]),
		unihanField_has_flags_builtin(fields[i], UNIHAN_FIELDFLAG_INTEGER) ? "integer" : "text");

    }
    g_string_append(strBuf,", PRIMARY KEY (");
    for(i=0;fields[i]>=0;i++){
	if (unihanField_has_flags_builtin(fields[i], UNIHAN_FIELDFLAG_NO_PRIMARYKEY | UNIHAN_FIELDFLAG_SINGLETON))
	    continue;
	if (i>0)
	    g_string_append_c(strBuf,',');
	g_string_append_printf(strBuf," %s",unihanField_to_string_builtin(fields[i]));

    }
    g_string_append(strBuf,") );");
    verboseMsg_print(VERBOSE_MSG_INFO1,"[I1] %s\n",strBuf->str);
    int ret=sqlite_exec_handle_error(db, strBuf->str, NULL, NULL, sqlite_error_callback_print_message,
	    "create_table(): Error");

    g_string_free(strBuf,TRUE);
    g_free(fields);

    return ret;
}

static int create_index(UnihanTable table, sqlite3 *db, const char* databaseName){
    GString *strBuf=g_string_new("CREATE INDEX ");
    if (databaseName){
	g_string_append_printf(strBuf,"%s.",databaseName);
    }
    UnihanField *fields=unihanTable_get_fields_builtin(table);
    int i;

    /* Create index */
    g_string_append_printf(strBuf,"%sIndex ON %s ( ",
	    unihanTable_to_string_builtin(table),
	    unihanTable_to_string_builtin(table));
    for(i=0;fields[i]>=0;i++){
	if (unihanField_has_flags_builtin(fields[i], UNIHAN_FIELDFLAG_NO_INDEX | UNIHAN_FIELDFLAG_SINGLETON))
	    continue;
	if (i>0)
	    g_string_append_c(strBuf,',');
	g_string_append_printf(strBuf," %s",
		unihanField_to_string_builtin(fields[i]));

    }
    g_string_append(strBuf,");");
    verboseMsg_print(VERBOSE_MSG_INFO1,"[I1] %s\n",strBuf->str);
    int ret=sqlite_exec_handle_error(db, strBuf->str, NULL, NULL, sqlite_error_callback_print_message,
	    "create_index(): Index Error");

    g_string_free(strBuf,TRUE);
    g_free(fields);
    return ret;
}

static void index_create_callback(gpointer key, gpointer value, gpointer userData){
    UnihanTable table=* (UnihanTable *) key;
    sqlite3 *db=(sqlite3 *) value;
    create_index(table,db,NULL);
}

static int create_indices(){
    verboseMsg_print(VERBOSE_MSG_INFO4,"[I4] create_indices(), size=%u\n",g_hash_table_size(tableHash));
    int ret=0;
    g_hash_table_foreach(tableHash,index_create_callback,NULL);
    return ret;
}

/*
 * create db callback
 */
static gint db_create_callback(gpointer user_option,gint col_num,gchar **results,gchar **col_names){
    const gchar *dirName=(const gchar *) user_option;
    gchar pathBuf[PATH_MAX];
    g_strlcpy(pathBuf,dirName,PATH_MAX);
    gchar *openPath=path_concat(pathBuf,results[1],PATH_MAX);
    verboseMsg_print(VERBOSE_MSG_INFO3,"[I3] Openpath=%s, db alias=%s\n",openPath,results[0]);
    sqlite3 *db=NULL;

    if (filename_meets_accessMode(openPath, FILE_MODE_EXIST | FILE_MODE_READ) && (flags & FLAG_FORCE_OVERWRITE)){
	if (remove(openPath)){
	    fprintf(stderr, "Can't remove the old database: %s.\n", openPath);
	    exit(1);
	}
    }
    gint ret= sqlite_open(openPath,  &db,  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    if (ret) {
	fprintf(stderr, "db_create_callback() file: %s error %d: %s \n", openPath, ret, sqlite3_errmsg(db));
	sqlite3_close(db);
	return ret;
    }
    g_hash_table_insert(dbAliasHash,(gpointer) g_string_chunk_insert(dbAliasChunk,results[0]), (gpointer) db);
    return 0;
}

static gint table_create_callback(gpointer user_option,gint col_num,gchar **results,gchar **col_names){
    sqlite3 *db=(sqlite3 *) g_hash_table_lookup(dbAliasHash,results[0]);
    UnihanTable table=unihanTable_parse_builtin(results[1]);
    create_table(table,db,NULL);
    g_hash_table_insert(tableHash,&(tableIdArray[table]), (gpointer) db);
    return 0;
}

static gint createDbs(){
    int ret;
    gchar sqlBuf[STRING_BUFFER_SIZE_DEFAULT];

    ret=create_meta_db(outputDir,&metaDb);
    if (ret) {
	fprintf(stderr, "Can't open/create meta-db database: %s/" METADB_FILENAME ", err msg:%s\n", outputDir, sqlite3_errmsg(metaDb));
	sqlite3_close(metaDb);
	exit(ret);
    }
    ret=meta_db_fill_up(metaDb);
    if (ret) {
	fprintf(stderr, "Can't insert meta-db database: %s/" METADB_FILENAME ", err msg:%s\n", outputDir, sqlite3_errmsg(metaDb));
	sqlite3_close(metaDb);
	exit(ret);
    }

    /* Create data Dbs */
    dbAliasChunk=g_string_chunk_new(256);
    dbAliasHash=g_hash_table_new_full(g_str_hash,g_str_equal,NULL,NULL);
    g_hash_table_insert(dbAliasHash,(gpointer) DEFAULTDB_ALIAS_DEFAULT, (gpointer) defaultDb);
    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT,sqlBuf,"SELECT dbAlias, dbFilename FROM DB_Alias_Table;");
    //    DbCreateData dcData;

    ret=sqlite_exec_handle_error(metaDb, sqlBuf, db_create_callback, outputDir, sqlite_error_callback_print_message, "createDbs(): create data dbs ");

    gchar defaultDb_filename[PATH_MAX];
    g_strlcpy(defaultDb_filename,outputDir,PATH_MAX);
    path_concat(defaultDb_filename,DEFAULTDB_FILENAME_DEFAULT,PATH_MAX);
    ret= sqlite_open(defaultDb_filename,  &defaultDb,  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    if (ret) {
	fprintf(stderr, "Can't open to database: %s, err msg:%s\n", defaultDb_filename,sqlite3_errmsg(defaultDb));
	sqlite3_close(defaultDb);
	exit(ret);
    }

    /* Create tables */
    int i;
    for(i=0;i<UNIHAN_TABLE_3RD_PARTY;i++){
	tableIdArray[i]=i;
    }
    tableHash=g_hash_table_new_full(g_int_hash,g_int_equal,NULL,NULL);
    sqlite3_snprintf(STRING_BUFFER_SIZE_DEFAULT,sqlBuf,"SELECT dbAlias, tableName FROM DB_Alias_Content_Table;");
    ret=sqlite_exec_handle_error(metaDb,sqlBuf, table_create_callback, outputDir, sqlite_error_callback_print_message, "createDbs(): create data tables ");

    return 0;
}


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
static void parse_record(gchar* rec_string){
    if (flags & FLAG_TEST_MODE){
	verboseMsg_print(VERBOSE_MSG_WARNING,"\nTesting on %s\n",rec_string);
    }else{
	verboseMsg_print(VERBOSE_MSG_INFO2,"===buf=%s\n",rec_string);
    }
    gchar** fields=g_strsplit(rec_string,"\t",3);
    int ret=0;

    gunichar code=  unihanChar_parse(fields[0]);
    static gunichar lastCode=0;
    char sqlBuf[STRING_BUFFER_SIZE_DEFAULT];
    static sqlite3 *coreDb=NULL;
    if (!coreDb){
	coreDb=(sqlite3 *) g_hash_table_lookup(dbAliasHash,COREDB_ALIAS);
    }

    if ((code!=lastCode) && (!(flags & FLAG_TEST_MODE))){
	g_snprintf(sqlBuf, STRING_BUFFER_SIZE_DEFAULT, "INSERT INTO codeTable VALUES (%u);",code);
	ret=sqlite_exec_handle_error(coreDb, sqlBuf, NULL, NULL, sqlite_error_callback_print_message,
		"parse_record()");
	if (ret)
	    exit(ret);
	lastCode=code;
    }

    UnihanField field=unihanField_parse_builtin(fields[1]);
    if (flags & FLAG_TEST_MODE){
	if (unihanField_has_flags_builtin(field,UNIHAN_FIELDFLAG_SINGLETON)){
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
	ret=unihan_import_table_tagValue_builtin(code, field, fields[2]);
    }

    g_strfreev(fields);
    if (ret>0){
	if (logFile){
	    verboseMsg_close_logFile();
	}
	exit(ret);
    }
}

//static void dbHash_foreach_func(gpointer key, gpointer value, gpointer user_data){
//    char sqlBuf[PATH_MAX];
//    char *dbAlias=(char *)key;
//    sqlite3 *db=(sqlite3 *)value;
//    verboseMsg_print(VERBOSE_MSG_INFO2,"[I2] dbHash_foreach_func(%s,-,NULL)\n",dbAlias);
//    char *openPath=(char *)g_hash_table_lookup(dbAliasHash,dbAlias);
//    sqlite3_close(db);
//    sqlite3_snprintf(PATH_MAX,sqlBuf,"ATTACH DATABASE %Q AS %q;",openPath,dbAlias);
//    verboseMsg_print(VERBOSE_MSG_INFO2,"[I2] sqlBuf=%s\n",sqlBuf);
//    int ret=sqlite_exec_handle_error(defaultDb, sqlBuf, NULL, NULL,
//            sqlite_error_callback_print_message,  "createDbs(): Error");
//    if (ret)
//        exit(ret);
//}

/**
 * Whether the command line options are valid.
 */
static gboolean is_valid_arguments(int argc, char **argv) {
    int opt;
    int verboseLevel=VERBOSE_MSG_WARNING;

    if (g_strrstr(argv[0],"_validation")){
	flags|=FLAG_TEST_MODE;
    }
    if (!argc){
	printUsage(argv);
	exit(0);
    }
    outputDir[0]='\0';
    while ((opt = getopt(argc, argv, "hfV:vo:t:")) != -1) {
	switch (opt) {
	    case 'h':
		printUsage(argv);
		exit(0);
	    case 'f':
		flags |=FLAG_FORCE_OVERWRITE;
		break;
	    case 'v':
		printf("libUnihan %s\n",PRJ_VERSION);
		exit(0);
	    case 'V':
		verboseLevel=atoi(optarg);
		break;
	    case 'o':
		g_strlcpy(outputDir,optarg,PATH_MAX);
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
    if (argc !=  optind+1){
	printf("Invalid number of options. argc=%d, optind=%d\n",argc,optind);
	return FALSE;
    }

    if ((unihanTxtFile=fopen(argv[optind],"r"))==NULL){
	fprintf(stderr, "Unable to read from file %s\n",argv[optind]);
	exit(-2);
    }

    if (outputDir[0]=='\0'){
	g_strlcpy(outputDir,".",PATH_MAX);
    }
    gchar logFile_name[PATH_MAX];
    g_strlcpy(logFile_name,outputDir,PATH_MAX);
    path_concat(logFile_name,"Unihan.log",PATH_MAX);
    if ((logFile=fopen("logFile_name","w"))==NULL){
	fprintf(stderr, "Unable to open log file %s\n",logFile_name);
	return -2;
    }

    verboseMsg_set_level(verboseLevel);
    verboseMsg_set_logFile(logFile);
    verboseMsg_set_fileLevel(verboseMsg_get_level());

    return TRUE;
}

#define BUFFER_SIZE 1000

void process_unihan_txt(){
    char readBuf[BUFFER_SIZE];

    while(fgets(readBuf,BUFFER_SIZE,unihanTxtFile)!=NULL){
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
}

int main(int argc,char** argv){
    if (!is_valid_arguments(argc, argv)){
	printUsage(argv);
	exit(-1);
    }

    if (!(flags & FLAG_TEST_MODE)){
	if (createDbs()){
	    fprintf(stderr, "Unable to create database files.\n");
	    return 3;
	}
    }

    process_unihan_txt();
    fclose(unihanTxtFile);
    if (!(flags & FLAG_TEST_MODE)){
	create_indices();
	verboseMsg_close_logFile();
    }
    g_hash_table_destroy(dbAliasHash);
    g_hash_table_destroy(tableHash);
    g_string_chunk_free(dbAliasChunk);
    return 0;
}

