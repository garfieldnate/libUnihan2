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
#include "allocate.h"
#include "str_functions.h"
#include "verboseMsg.h"
#include "Unihan.h"

#define USAGE_MSG "Usage: %s [-V] <Unihan.txt> <Unihan.db>\n"
#define BUFFER_SIZE 2000
FILE *logFile=NULL;
gboolean testMode=FALSE;


int create_table(UnihanTable table){
    char *zErrMsg = NULL;
    GString *strBuf=g_string_new("CREATE TABLE ");
    g_string_append_printf(strBuf,"%s (",unihanTable_to_string(table));
    UnihanField *fields=unihanTable_get_fields(table);
    UnihanField *pKeys=unihanTable_get_primary_key_fields(table);
    int i;
    for(i=0;fields[i]>=0;i++){
	if (i>0)
	    g_string_append_c(strBuf,',');
	g_string_append_printf(strBuf," %s %s NOT NULL",
		unihanField_to_string(fields[i]),
		unihanField_is_integer(fields[i]) ? "integer" : "text");

    }
    g_string_append(strBuf,", PRIMARY KEY (");
    for(i=0;pKeys[i]>=0;i++){
	if (i>0)
	    g_string_append_c(strBuf,',');
	g_string_append_printf(strBuf," %s",unihanField_to_string(pKeys[i]));

    }
    g_string_append(strBuf,") );");
    printf("*** %s\n",strBuf->str);
    int ret=unihanSql_exec(strBuf->str, NULL, NULL, &zErrMsg);
    if (ret){
	fprintf(stderr, "Fail to create table %s, err msg:%s\n",unihanTable_to_string(table),zErrMsg);
    }
    g_string_free(strBuf,TRUE);
    return ret;
}

gboolean create_tables(){
    int i;
    for(i=0;i<UNIHAN_TABLES_COUNT;i++){
	if (create_table(i)){
	    return FALSE;
	}
    }
    return TRUE;
}

int create_index(UnihanTable table){
    char *zErrMsg = NULL;
    GString *strBuf=g_string_new("CREATE INDEX ");
    g_string_append_printf(strBuf,"%sIndex ON %s (",
	    unihanTable_to_string(table),
	    unihanTable_to_string(table));
    UnihanField *fields=unihanTable_get_fields(table);
    int i;
    for(i=0;fields[i]>=0;i++){
	if (!unihanField_is_indexed(fields[i])){
	    continue;
	}

	if (i>0)
	    g_string_append_c(strBuf,',');
	g_string_append_printf(strBuf," %s",
		unihanField_to_string(fields[i]));

    }
    g_string_append(strBuf,");");
    printf("*** %s\n",strBuf->str);
    int ret=unihanSql_exec(strBuf->str, NULL, NULL, &zErrMsg);
    if (ret){
	fprintf(stderr, "Fail to create index %s, err msg:%s\n",unihanTable_to_string(table),zErrMsg);
    }
    g_string_free(strBuf,TRUE);
    return ret;
}

gboolean create_indices(){
    int i;
    for(i=0;i<UNIHAN_TABLES_COUNT;i++){
	if (create_index(i)){
	    return FALSE;
	}
    }
    return TRUE;
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
    if ((i==1) && (j==1))
	return TRUE;
    return FALSE;    
}

int unihan_test_record(gunichar code, UnihanField field, char *value){
    char codeStr[10];
    g_snprintf(codeStr,10,"%d",code);

    char *charStr=ucs4_to_utf8(code);
    int ret;
    gboolean found=FALSE;
    int i;
    int colCount,rowCount;

    /* code -> value */
    printf("=== code -> value \n");
    SQL_Result *sResult=unihan_find_all_matched(UNIHAN_FIELD_CODE,codeStr,field, UHIHAN_QUERY_OPTION_SCALAR_STRING);
    ret=sResult->execResult;
    if (ret) {
	printf(" Database error:%s\n", sResult->errMsg);
	sql_result_free(sResult,TRUE);
	unihanDb_close();
	exit(ret);
    }
    colCount=sResult->colCount;
    rowCount=sResult->resultList->len;

    if (rowCount<=0){
	printf(" Field %s of character %d(%s) does not have any value\n",unihanField_to_string(field),code, charStr);
	exit(-10);
    }

    for(i=0;i<rowCount;i++){
        switch(field){
            case UNIHAN_FIELD_KSEMANTICVARIANT:
            case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
                found=isKSemanticValue_matched(value,stringList_index(sResult->resultList,(i+1)*colCount-1));
                break;
            default:
		if (strcmp(value,stringList_index(sResult->resultList,(i+1)*colCount-1))==0){
	            found=TRUE;
                }
	        break;
	} 
	if (found){    
                break;
        }
	
    }
    if (!found){
	printf(" Field %s of character %d(%s) value: [%s]  does not equal the original value [%s]\n",
		unihanField_to_string(field),code, charStr, stringList_index(sResult->resultList,rowCount*colCount-1), value );
	exit(-11);
    }
    sql_result_free(sResult,TRUE);

    
    /* value -> utf8 */
    printf("=== value -> utf8 \n");
    

    char buf[1000];
    gunichar c;
    found=FALSE;

    switch(field){
	case UNIHAN_FIELD_KCOMPATIBILITYVARIANT:
	case UNIHAN_FIELD_KSIMPLIFIEDVARIANT:
	case UNIHAN_FIELD_KTRADITIONALVARIANT:
	    c=unihanChar_parse(value);
	    g_snprintf(buf,1000,"%d",c);
	    break;
	default:
	    g_strlcpy(buf,value,1000);
	    break;
    }

    sResult=unihan_find_all_matched(UNIHAN_FIELD_CODE,codeStr,field, UHIHAN_QUERY_OPTION_SCALAR_STRING);
    ret=sResult->execResult;
    if (ret) {
	printf(" Database error:%s\n", sResult->errMsg);
	sql_result_free(sResult,TRUE);
	unihanDb_close();
	exit(ret);
    }
    colCount=sResult->colCount;
    rowCount=sResult->resultList->len;


    if (rowCount<=0){
	printf(" Cannot found value %s in field %s.\n",value,unihanField_to_string(field));
	exit(-12);
    }

    for(i=0;i<rowCount;i++){
	verboseMsg_print(VERBOSE_MSG_INFO3,"  Result returned from database: %s\n",
		stringList_index(sResult->resultList,(i+1)*colCount-1));
	if (strcmp(value,stringList_index(sResult->resultList,(i+1)*colCount-1))==0){
	    found=TRUE;
	    break;
	}
    }
    if (!found){
	printf(" Field %s of character %d(%s) does not associate with value %s \n",
		unihanField_to_string(field),code,charStr,value);
	exit(-13);
    }

    sql_result_free(sResult,TRUE);
    g_free(charStr);
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

    gunichar code=unihanChar_parse(fields[0]);
    static gunichar lastCode=0;
    if ((code!=lastCode) && (!testMode)){
	gchar* utf8Str=ucs4_to_utf8((gunichar) code);
	unihan_insert_value(code, UNIHAN_FIELD_UTF8, utf8Str );
	g_free(utf8Str);
	lastCode=code;
    }

    UnihanField field=unihanField_parse(fields[1]);

    if (unihanField_is_singleton(field)){
	if (testMode){
	    unihan_test_record(code, field, fields[2]);
	}else{
	    ret=unihan_insert_value(code, field, fields[2]);
	}
    }else{
	gchar** values=g_strsplit(fields[2]," ",-1);
	int i;
	for(i=0;values[i]!=NULL;i++){
	    if (testMode){
		ret=unihan_test_record(code, field, values[i]);
	    }else{
		ret=unihan_insert_value(code, field, values[i]);
	    }
	}
	g_strfreev(values);
    }
    g_strfreev(fields);
    if (ret>0){
	fprintf(stderr,"parse_record(): Database error!\n");
	if (logFile){
	    fclose(logFile);
	}
	exit(ret);
    }
}

/**
 * Whether the command line options are valid.
 */
static gboolean is_valid_arguments(int argc, char **argv) {
    int opt;
    int verboseLevel=VERBOSE_MSG_WARNING;
    if (!argc){
	printf("%s\n",USAGE_MSG);
	exit(0);
    }
    while ((opt = getopt(argc, argv, "V")) != -1) {
	switch (opt) {
	    case 'h':
		printf("%s\n",USAGE_MSG);
		exit(0);
	    case 'V':
		verboseLevel++;
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
	printf(USAGE_MSG,argv[0]);
	exit(-1);
    }
    FILE *inF=NULL;
    if ((inF=fopen(argv[optind],"r"))==NULL){
	fprintf(stderr, "Unable to read from file %s\n",argv[optind]);
	return -2;
    }

    int ret = unihanDb_open(argv[optind+1],SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

    if (ret) {
        sqlite3 *db=unihanDb_get();
	fprintf(stderr, "Can't open to database: %s, err msg:%s\n", argv[optind+1],sqlite3_errmsg(db));
	unihanDb_close();
	exit(ret);
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
	if (!create_tables()){
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
    if (!testMode){
	create_indices();
    }
    unihanDb_close();
    fclose(inF);
    if (!testMode){
	fclose(logFile);
    }
    
    return 0;
}
