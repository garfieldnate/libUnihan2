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
#include "str_function.h"
#include "Unihan.h"

#include "Unihan_builtin_def.c"
#define MAX_BUFFER_SIZE 2000
#define UNIHAN_FIELD_ARRAY_MAX_LEN 200
#define UNIHAN_TABLE_ARRAY_MAX_LEN 800



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
    return UNIHAN_INVAILD_TABLE;
}

UnihanTable *unihanField_get_builtin_required_tables(UnihanField field){
    int i,counter=0;
    UnihanTable *tables=NEW_ARRAY_INSTANCES(UNIHAN_TABLE_ARRAY_MAX_LEN, UnihanTable);
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

static UnihanImportData_Post *unihanField_get_builtin_importData_post(UnihanField field,UnihanTable table){
    int i;
    UnihanImportData_Post *importData_post_ptr=NULL;
    for(i=0; PSEUDOFIELD_IMPORT_DATA_POST[i].field!=UNIHAN_INVALID_FIELD; i++){
	if (field==PSEUDOFIELD_IMPORT_DATA_POST[i].field && table==PSEUDOFIELD_IMPORT_DATA_POST[i].table){
	    return &(PSEUDOFIELD_IMPORT_DATA_POST[i]);
	}
    }
    return NULL;
}

gboolean unihanField_builtin_has_flags(UnihanField field, guint flags){
    return UNIHAN_FIELD_PROPERTIES[field].flags & flags;
}

const char *unihanTable_builtin_to_string(UnihanTable table){
    if (table<0){
	return NULL;
    }
    return UNIHAN_TABLE_NAMES[table];
}

const char *unihanField_builtin_to_string(UnihanField field){
    if (table<0){
	return NULL;
    }
    return UNIHAN_FIELD_PROPERTIES[field].fieldName;
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

static void unihan_import_field_paste(gchar *sqlClause, UnihanField field, gchar *value){
    char sqlBuf[MAX_BUFFER_SIZE];
    if (unihanField_builtin_has_flags(field, UNIHAN_FIELDFLAG_INTEGER)){
	sqlite_snprintf(MAX_BUFFER_SIZE, sqlBuf, ", %s",  tagValue);
    }else{
	sqlite_snprintf(MAX_BUFFER_SIZE, sqlBuf, ", %Q",  tagValue);
    }
    g_strlcat(sqlClause,sqlBuf, MAX_BUFFER_SIZE);
}

int unihan_import_builtin_table_tagValue(sqlite3 *db, gunichar code, UnihanField field, 
	const char *tagValue, int *counter_ptr){
    int i,j,ret=0,regexRet;
    int counter_post;
    int pseudoNextIndex=unihanField_builtin_pseudo_import_data_index(field,-1);
    UnihanTable table;
    gchar *importPattern=NULL;
    gchar **storeFormats=NULL,*storeFormat=NULL;
    gchar *value;
    gboolean empty;
    UnihanField *fields;
    UnihanField currentField;
    UnihanImportData_Post *importData_post_ptr=NULL;

    char *tagValuePtr=NULL,*tagValuePtr_tmp=NULL;
    char sqlClause[MAX_BUFFER_SIZE];
    char sqlClause_values[MAX_BUFFER_SIZE];
    char buf[MAX_BUFFER_SIZE];
    regex_t *preg=NULL, *preg_post=NULL;
    char *tagValue_normalized=g_utf8_normalize(tagValue,-1,G_NORMALIZE_NFD);


    if (pseudoNextIndex>=0){
	/* Is Pseudo field */
	while(pseudoNextIndex>=0){
	    table=PSEUDOFIELD_IMPORT_DATA[pseudoNextIndex].table;
	    fields=PSEUDOFIELD_IMPORT_DATA[pseudoNextIndex].fields;
	    importPattern=PSEUDOFIELD_IMPORT_DATA[pseudoNextIndex].importPattern;
	    storeFormats=PSEUDOFIELD_IMPORT_DATA[pseudoNextIndex].storeFormats;
	    importData_post_ptr=unihanField_get_builtin_importData_post(field,table);
	    if (importData_post_ptr){
		if ((regexRet=regcomp(preg_post, importData_post_ptr->regex_pattern, REG_EXTENDED))!=0){
		    /* Invalid pattern */
		    regerror(ret,preg_post,buf,MAX_STRING_BUFFER_SIZE);
		    verboseMsg_print(VERBOSE_MSG_ERROR, 
			    "unihan_import_builtin_table_tagValue():Invalid import post pattern %s\n" ,buf);
		    exit(regexRet);
		}
	    }

	    if ((regexRet=regcomp(preg, importPattern, REG_EXTENDED))!=0){
		/* Invalid pattern */
		regerror(ret,preg,buf,MAX_STRING_BUFFER_SIZE);
		verboseMsg_print(VERBOSE_MSG_ERROR, 
			"unihan_import_builtin_table_tagValue():Invalid pattern %s\n"	,buf);
		exit(regexRet);
	    }

	    tagValuePtr=tagValue_normalized;
	    counter_post=0;
	    do{
		for(j=0;(currField=fields[j])!=UNIHAN_INVALID_FIELDS;j++){
		    storeFormat=storeFormat[j];
		    value=string_regex_eval_regex_t(tagValuePtr, preg, storeFormat, 0, counter_ptr);
		    if (j==0){
			if (value){
			    empty=FALSE;
			    sqlite_snprintf(MAX_BUFFER_SIZE, sqlClause, "INSERT INTO %s (code",
				    unihanTable_builtin_to_string(table),code);
			    sqlite_snprintf(MAX_BUFFER_SIZE, sqlClause_values, ") VALUES (%lu",
				    unihanTable_builtin_to_string(table),code);
			}else{
			    empty=TRUE;
			    break;
			}
		    }else{
			g_strlcat(sqlClause,", ",MAX_BUFFER_SIZE);
			g_strlcat(sqlClause, unihanField_builtin_to_string(currField),MAX_BUFFER_SIZE);
			g_strlcat(sqlClause_values,", ",MAX_BUFFER_SIZE);
			if (value){
			    unihan_import_field_paste(sqlClause_values,currField,value);
			    g_free(value);
			}else{
			    verboseMsg_print(VERBOSE_MSG_CRITICAL,
				    "unihan_import_builtin_table_tagValue():2nd value should not zero!: str=%s, pattern=%s, substitute=%s\n",
				    tagValue,importPattern,storeFormat);
			    exit(1);
			}
		    }
		}
		if (!empty){
		    g_strlcat(sqlClause,");",MAX_BUFFER_SIZE);
		    verboseMsg_print(VERBOSE_MSG_INFO2," Executing: %s\n",sqlClause);
		    ret=sqlite_exec_handle_error(db, sqlClause, NULL, NULL,
			    sqlite_error_callback_print_message, "unihan_import_builtin_table_tagValue()" );
		    if (ret){
			break;
		    }
		}

		if (importData_post_ptr){
		    /* Need post process */
		    tagValuePtr_tmp=string_regex_eval_regex_t(tagValuePtr, preg_post, 
			    importData_post_ptr->eval_str, 0, &counter_post);
		    if (tagValuePtr!=tagValue){
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
	    pseudoNextIndex=unihanField_builtin_pseudo_import_data_index(field,pseudoNextIndex);
	}
    }else{
	/* Is Real field */
	for(i=0;REALFIELD_TABLES[i].field!=UNIHAN_INVALID_FIELD;i++){
	    if (REALFIELD_TABLES[i].field==field){
	       sqlite_snprintf(MAX_BUFFER_SIZE, sqlClause, "INSERT INTO %s VALUES (%lu",
		   unihanTable_builtin_to_string(table),code);
	       unihan_import_field_paste(sqlClause,field,tagValue);
	       g_strlcat(sqlClause,");",MAX_BUFFER_SIZE);

	    }
	}
    }
    g_free(tagValue_normalized);
    return ret;
}

int unihan_import_builtin_table_tagValue_original(sqlite3 *db, gunichar code, UnihanField field, const char *tagValue_original){
    int counter=0;
    if (UNIHAN_FIELD_PROPERTIES[field].flags & UNIHAN_FIELDFLAG_SINGLETON){
	int ret,i;
	values=g_strsplit_set(tagValue_original," ",-1);
	for(i=0;values[i]!=NULL;i++){
	    ret=unihan_import_builtin_table_tagValue(db,code,field,values[i],&counter);
	    if (ret!=SQLITE_OK){
		return ret;
	    }
	}
	return ret;
    }
    return unihan_import_builtin_table_tagValue(db,code,field,tagValue_original,&counter);
}

    

