/** 
 * @file Unihan_builtin.c
 * @brief Functions for builtin tables and fields only.
 * 
 * This file contains the functions 
 *  which only deal for builtin tables and fields.
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

#include <glib.h>
#include <sqlite3.h>
#include "allocate.h"
#include "str_functions.h"
#include "verboseMsg.h"
#include "Unihan.h"

#include "Unihan_builtin_def.c"
#define MAX_STRING_BUFFER_SIZE 2000
#define UNIHAN_FIELD_ARRAY_MAX_LEN 200
#define UNIHAN_TABLE_ARRAY_MAX_LEN 800
extern FILE *logFile;


/*=========================================================
 * Functions
 */

UnihanTable unihanField_get_builtin_preferred_table(UnihanField field){
    int i;
    for(i=0;FIELD_PREFERRED_TABLES[i].field!=UNIHAN_INVALID_FIELD;i++){
	if (FIELD_PREFERRED_TABLES[i].field==field){
	    return FIELD_PREFERRED_TABLES[i].table;
	}
    }
    return UNIHAN_INVALID_TABLE;
}

UnihanTable *unihanField_get_builtin_required_tables(UnihanField field){
    int i,counter=0;
    UnihanTable *tables=NEW_ARRAY_INSTANCE(UNIHAN_TABLE_ARRAY_MAX_LEN, UnihanTable);
    for(i=0;PSEUDOFIELD_IMPORT_DATA[i].pseudoField!=UNIHAN_INVALID_FIELD;i++){
	if (PSEUDOFIELD_IMPORT_DATA[i].pseudoField==field){
	    tables[counter++]=PSEUDOFIELD_IMPORT_DATA[i].table;
	}
    }
    if (counter==0){
	/* Maybe a real field */
	tables[counter++]=unihanField_get_builtin_preferred_table(field);
    }
    tables[counter]=UNIHAN_INVALID_TABLE;
    return tables;
}

gboolean unihanField_builtin_has_flags(UnihanField field, guint flags){
    if (field<0 || field>UNIHAN_FIELD_3RD_PARTY){
	return FALSE;
    }
    return UNIHAN_FIELD_PROPERTIES[field].flags & flags;
}

UnihanField unihanField_builtin_parse(const char *str){
    UnihanField field;
    for(field=0;field<UNIHAN_FIELD_3RD_PARTY;field++){
	if (strcmp(UNIHAN_FIELD_PROPERTIES[field].fieldName,str)==0){
	    return field;
	}
    }
    return UNIHAN_INVALID_FIELD;
}

const char *unihanField_builtin_to_string(UnihanField field){
    if (field<0 || field>=UNIHAN_FIELD_3RD_PARTY){
	return NULL;
    }
    return UNIHAN_FIELD_PROPERTIES[field].fieldName;
}

UnihanField* unihanTable_get_builtin_fields(UnihanTable table){
    UnihanField *fields=NEW_ARRAY_INSTANCE(UNIHAN_FIELD_ARRAY_MAX_LEN,UnihanField);
    int i=0,j;
    if (table<0){
	fields[i]=UNIHAN_INVALID_FIELD;
	return fields;
    }
    fields[i++]=UNIHAN_FIELD_CODE;
    for(j=0;REALFIELD_TABLES[j].field!=UNIHAN_INVALID_FIELD;j++){
	if (REALFIELD_TABLES[j].table==table){
	    fields[i++]=REALFIELD_TABLES[j].field;
	}
    }
    fields[i]=UNIHAN_INVALID_FIELD;
    return fields;
}

UnihanTable unihanTable_builtin_parse(const char *str){
    UnihanTable table;
    for(table=0;table<UNIHAN_TABLE_3RD_PARTY;table++){
	if (strcmp(UNIHAN_TABLE_NAMES[table],str)==0){
	    return table;
	}
    }
    return UNIHAN_INVALID_TABLE;
}

const char *unihanTable_builtin_to_string(UnihanTable table){
    if (table<0 || table>=UNIHAN_TABLE_3RD_PARTY){
	return NULL;
    }
    return UNIHAN_TABLE_NAMES[table];
}

static UnihanImportData_Post *unihanField_get_builtin_importData_post(UnihanField field,UnihanTable table){
    int i;
    for(i=0; PSEUDOFIELD_IMPORT_DATA_POST[i].field!=UNIHAN_INVALID_FIELD; i++){
	if (field==PSEUDOFIELD_IMPORT_DATA_POST[i].field && table==PSEUDOFIELD_IMPORT_DATA_POST[i].table){
	    return &(PSEUDOFIELD_IMPORT_DATA_POST[i]);
	}
    }
    return NULL;
}

int unihanField_builtin_pseudo_import_data_next_index(UnihanField field,int previousIndex){
    int i;
    for(i=previousIndex+1;PSEUDOFIELD_IMPORT_DATA[i].pseudoField!=UNIHAN_INVALID_FIELD;i++){
	if (PSEUDOFIELD_IMPORT_DATA[i].pseudoField==field){
	    return i;
	}
    }
    return -1;
}

static void unihan_import_value_append(gchar *sqlClause, UnihanField field, const gchar *value){
    char sqlBuf[MAX_STRING_BUFFER_SIZE];
    char codeBuf[20];
    long int coding;
    if (unihanField_builtin_has_flags(field, UNIHAN_FIELDFLAG_INTEGER)){
	if (unihanField_builtin_has_flags(field, UNIHAN_FIELDFLAG_UCS4)){
	    /* Convert UCS4 to str */
	    g_snprintf(codeBuf,20,"%lu", (gulong) unihanChar_parse(value));
	    sqlite3_snprintf(MAX_STRING_BUFFER_SIZE, sqlBuf, ", %s",  codeBuf);
	}else if (unihanField_builtin_has_flags(field, UNIHAN_FIELDFLAG_HEXADECIMAL_16)){
	    coding=strtol(value,NULL,16);
	    sqlite3_snprintf(MAX_STRING_BUFFER_SIZE, sqlBuf, ", %d",  coding);
	}else{
	    sqlite3_snprintf(MAX_STRING_BUFFER_SIZE, sqlBuf, ", %s",  value);
	}
    }else{
	sqlite3_snprintf(MAX_STRING_BUFFER_SIZE, sqlBuf, ", %Q",  value);
    }
    g_strlcat(sqlClause,sqlBuf, MAX_STRING_BUFFER_SIZE);
}

gint sqlite_error_callback_hide_known_constraint_error(sqlite3 *db, const gchar *sqlClause, gint error_code, 
	const gchar *error_msg, gpointer prompt){
    gboolean errorKnown=FALSE;
    if (error_code== SQLITE_CONSTRAINT){
	if (strstr(sqlClause,unihanField_builtin_to_string(UNIHAN_FIELD_kCANTONESE))){
	    errorKnown=TRUE;
	}else if (strstr(sqlClause,unihanField_builtin_to_string(UNIHAN_FIELD_kJAPANESEKUN))){
	    errorKnown=TRUE;
	}
	if (errorKnown){
	    verboseMsg_print(VERBOSE_MSG_WARNING,"[WW] Command %s is duplicated!\n"
		    ,sqlClause);
	    return SQLITE_OK;
	}

    }
    sqlite_error_callback_print_message(db,sqlClause,error_code,error_msg,prompt);
    return error_code;
}



static int writeToDb(sqlite3 *db, const gchar *sqlClause){
    verboseMsg_print(VERBOSE_MSG_INFO2," Executing: %s\n",sqlClause);
    return sqlite_exec_handle_error(db, sqlClause, NULL, NULL,
	    sqlite_error_callback_hide_known_constraint_error, "writeToDb()" );
}

/**
 * Import a tag value of a character from Unihan.txt to dbfile.
 *
 * omittable 
 * This function imports a tag value of a character from Unihan.txt to dbfile.
 * Note that this function assumes that \a tagValue is singleton, that is.
 * no need to be further split. 
 * 
 * @param db Db handle
 * @param code the UCS4 representation of the character.
 * @param field The UnihanField to be import.
 * @param tagValue The value of the field.
 * @param counter_ptr Pointer to an integer counter. Can be NULL if $+ or $- flags are not used.
 * @return 0 if success, otherwise return nonzero value.
 * @see unihan_import_builtin_table_tagValue().
 */
int unihan_import_builtin_table_single_tagValue(sqlite3 *db, gunichar code, UnihanField field, 
	const char *tagValue, int *counter_ptr){
    int i,j,ret=0,regexRet;
    int counter_post;
    int pseudoNextIndex=unihanField_builtin_pseudo_import_data_next_index(field,-1);
    UnihanTable table;
    const gchar *importPattern=NULL;
    const gchar **storeFormats=NULL;
    const gchar *storeFormat=NULL;
    gchar *value;
    gboolean empty;
    const UnihanField *fields;
    UnihanImportData_Post *importData_post_ptr=NULL;

    char *tagValuePtr=NULL,*tagValuePtr_tmp=NULL;
    char sqlClause[MAX_STRING_BUFFER_SIZE];
    char sqlClause_values[MAX_STRING_BUFFER_SIZE];
    char buf[MAX_STRING_BUFFER_SIZE];
    regex_t preg, preg_post;
    char *tagValue_normalized=g_utf8_normalize(tagValue,-1,G_NORMALIZE_NFD);
    

    if (pseudoNextIndex>=0){
	/* Is Pseudo field */
	while(pseudoNextIndex>=0){
	    table=PSEUDOFIELD_IMPORT_DATA[pseudoNextIndex].table;
	    fields=PSEUDOFIELD_IMPORT_DATA[pseudoNextIndex].fields;
	    importPattern=PSEUDOFIELD_IMPORT_DATA[pseudoNextIndex].importPattern;
	    
	    storeFormats= (const gchar **) PSEUDOFIELD_IMPORT_DATA[pseudoNextIndex].storeFormats;
	    importData_post_ptr=unihanField_get_builtin_importData_post(field,table);
	    if (importData_post_ptr){
		if ((regexRet=regcomp(&preg_post, importData_post_ptr->regex_pattern, REG_EXTENDED))!=0){
		    /* Invalid pattern */
		    regerror(ret,&preg_post,buf,MAX_STRING_BUFFER_SIZE);
		    verboseMsg_print(VERBOSE_MSG_ERROR, 
			    "unihan_import_builtin_table_tagValue():Invalid import post pattern %s\n" ,buf);
		    exit(regexRet);
		}
	    }
	    
	    if ((regexRet=regcomp(&preg, importPattern, REG_EXTENDED))!=0){
		/* Invalid pattern */
		regerror(ret,&preg,buf,MAX_STRING_BUFFER_SIZE);
		verboseMsg_print(VERBOSE_MSG_ERROR, 
			"unihan_import_builtin_table_tagValue():Invalid pattern %s\n"	,buf);
		exit(regexRet);
	    }

	    tagValuePtr=tagValue_normalized;
	    counter_post=0;
	    do{
		for(j=0;fields[j]!=UNIHAN_INVALID_FIELD;j++){
		    storeFormat= storeFormats[j];
		    value=string_regex_formatted_combine_regex_t(tagValuePtr, &preg, storeFormat, 0, counter_ptr);
		    if (j==0){
			if (value){
			    empty=FALSE;
			    sqlite3_snprintf(MAX_STRING_BUFFER_SIZE, sqlClause, "INSERT INTO %s (code",
				    unihanTable_builtin_to_string(table));
			    sqlite3_snprintf(MAX_STRING_BUFFER_SIZE, sqlClause_values, ") VALUES (%lu",
				    code);
			}else{
			    
			    empty=TRUE;
			    break;
			}
		    }
		    g_strlcat(sqlClause,", ",MAX_STRING_BUFFER_SIZE);
		    g_strlcat(sqlClause, unihanField_builtin_to_string(fields[j]),MAX_STRING_BUFFER_SIZE);
		    if (value){
			unihan_import_value_append(sqlClause_values,fields[j],value);
			g_free(value);
		    }else{
			verboseMsg_print(VERBOSE_MSG_CRITICAL,
				"unihan_import_builtin_table_tagValue():2nd value should not zero!: str=%s, pattern=%s, substitute=%s\n",
				tagValue,importPattern,storeFormat);
			exit(1);
		    }
		}
		if (!empty){
		    g_strlcat(sqlClause,sqlClause_values,MAX_STRING_BUFFER_SIZE);
		    g_strlcat(sqlClause,");",MAX_STRING_BUFFER_SIZE);
		    ret=writeToDb(db, sqlClause);
		    if (ret){
			break;
		    }
		}

		
		if (importData_post_ptr){
                    /* Generate new tagValue */
		    tagValuePtr_tmp=string_regex_formatted_combine_regex_t(tagValuePtr, &preg_post, 
			    importData_post_ptr->eval_str, 0, &counter_post);
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
	    
	    pseudoNextIndex=unihanField_builtin_pseudo_import_data_next_index(field,pseudoNextIndex);
	    regfree(&preg);
	    if (importData_post_ptr){
		regfree(&preg_post);
	    }
	}
    }else{
	/* Is Real field */
	for(i=0;REALFIELD_TABLES[i].field!=UNIHAN_INVALID_FIELD;i++){
	    if (REALFIELD_TABLES[i].field==field){
	       sqlite3_snprintf(MAX_STRING_BUFFER_SIZE, sqlClause, "INSERT INTO %s VALUES (%lu",
		       unihanTable_builtin_to_string(REALFIELD_TABLES[i].table),code);
	       unihan_import_value_append(sqlClause,field,tagValue_normalized);
	       g_strlcat(sqlClause,");",MAX_STRING_BUFFER_SIZE);
	       ret=writeToDb(db, sqlClause);
	       break;
	    }
	}
    }

    g_free(tagValue_normalized);
    return ret;
}

int unihan_import_builtin_table_tagValue(sqlite3 *db, gunichar code, UnihanField field, const char *tagValue){
    int counter=0;
    if (UNIHAN_FIELD_PROPERTIES[field].flags & UNIHAN_FIELDFLAG_SINGLETON){
	return unihan_import_builtin_table_single_tagValue(db,code,field,tagValue,&counter);
    }
    int ret,i;
    gchar **values=g_strsplit_set(tagValue," ",-1);
    for(i=0;values[i]!=NULL;i++){
	ret=unihan_import_builtin_table_single_tagValue(db,code,field,values[i],&counter);
	if (ret!=SQLITE_OK){
	    return ret;
	}
    }
    g_strfreev(values);
    return ret;
}

    
gunichar unihanChar_parse(const char *str){
    char codeBuf[15];
    subString_buffer(codeBuf,str,2,strlen(str)-2);
    long code=strtol(codeBuf,(char**) NULL,16);
    return (gunichar) code;
}


