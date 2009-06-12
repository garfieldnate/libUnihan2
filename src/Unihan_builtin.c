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
#include "Unihan_builtin.h"

#include "Unihan_builtin_def.c"
#define STRING_BUFFER_SIZE_DEFAULT 2000
#define UNIHAN_FIELD_ARRAY_MAX_LEN 200
#define UNIHAN_TABLE_ARRAY_MAX_LEN 800
extern FILE *logFile;


/*=========================================================
 * Functions
 */

gint sqlite_error_callback_hide_known_constraint_error(sqlite3 *db, const gchar *sqlClause, gint error_code,
	const gchar *error_msg, gpointer prompt){
    gboolean errorKnown=FALSE;
    if (error_code== SQLITE_CONSTRAINT){
	if (strstr(sqlClause,unihanField_to_string_builtin(UNIHAN_FIELD_kCANTONESE))){
	    errorKnown=TRUE;
	}else if (strstr(sqlClause,unihanField_to_string_builtin(UNIHAN_FIELD_kJAPANESEKUN))){
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

/*==============================================================
 * Basic built field and table functions.
 */
UnihanTable unihanField_get_preferred_table_builtin(UnihanField field){
    int i;
    for(i=0;FIELD_PREFERRED_TABLES[i].field!=UNIHAN_INVALID_FIELD;i++){
	if (FIELD_PREFERRED_TABLES[i].field==field){
	    return FIELD_PREFERRED_TABLES[i].table;
	}
    }
    return UNIHAN_INVALID_TABLE;
}

UnihanTable *unihanField_get_required_tables_builtin(UnihanField field){
    int i,counter=0;
    UnihanTable *tables=NEW_ARRAY_INSTANCE(UNIHAN_TABLE_ARRAY_MAX_LEN, UnihanTable);
    for(i=0;PSEUDOFIELD_IMPORT_FORMAT[i].pseudoField!=UNIHAN_INVALID_FIELD;i++){
	if (PSEUDOFIELD_IMPORT_FORMAT[i].pseudoField==field){
	    tables[counter++]=PSEUDOFIELD_IMPORT_FORMAT[i].table;
	}
    }
    if (counter==0){
	/* Maybe a real field */
	tables[counter++]=unihanField_get_preferred_table_builtin(field);
    }
    tables[counter]=UNIHAN_INVALID_TABLE;
    return tables;
}

gboolean unihanField_has_flags_builtin(UnihanField field, guint flags){
    if (field<0 || field>UNIHAN_FIELD_3RD_PARTY){
	return FALSE;
    }
    return UNIHAN_FIELD_PROPERTIES[field].flags & flags;
}

UnihanField unihanField_parse_builtin(const char *str){
    UnihanField field;
    for(field=0;field<UNIHAN_FIELD_3RD_PARTY;field++){
	if (strcmp(UNIHAN_FIELD_PROPERTIES[field].fieldName,str)==0){
	    return field;
	}
    }
    return UNIHAN_INVALID_FIELD;
}

const char *unihanField_to_string_builtin(UnihanField field){
    if (field<0 || field>=UNIHAN_FIELD_3RD_PARTY){
	return NULL;
    }
    return UNIHAN_FIELD_PROPERTIES[field].fieldName;
}

void unihanFieldProperties_enumerate_init_builtin(Enumerate *e){
    e->index=0;
    e->userData=NULL;
}

gboolean unihanFieldProperties_has_next_builtin(Enumerate *e){
    if (UNIHAN_FIELD_PROPERTIES[e->index].fieldName!=NULL){
	return TRUE;
    }
    return FALSE;
}

const UnihanFieldProperties *unihanFieldProperties_next_builtin(Enumerate *e){
    if (unihanFieldProperties_has_next_builtin(e)){
	e->index++;
	return &UNIHAN_FIELD_PROPERTIES[e->index-1];
    }
    return NULL;
}


UnihanField* unihanTable_get_fields_builtin(UnihanTable table){
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

UnihanTable unihanTable_parse_builtin(const char *str){
    UnihanTable table;
    for(table=0;table<UNIHAN_TABLE_3RD_PARTY;table++){
	if (strcmp(UNIHAN_TABLE_NAMES[table],str)==0){
	    return table;
	}
    }
    return UNIHAN_INVALID_TABLE;
}

const char *unihanTable_to_string_builtin(UnihanTable table){
    if (table<0 || table>=UNIHAN_TABLE_3RD_PARTY){
	return NULL;
    }
    return UNIHAN_TABLE_NAMES[table];
}

/*==============================================================
 * Importing Format
 */

static gint field_ImportFormat_index_table[UNIHAN_FIELD_3RD_PARTY];

void unihanPseudoFieldImportFormat_enumerate_init_builtin(Enumerate *e, UnihanField *field){
    static gboolean initialized=FALSE;
    if (!initialized){
	/* Filling the field_ImportFormat_index_table */
	gint i,lastField=UNIHAN_INVALID_FIELD;
	for(i=0;i<UNIHAN_FIELD_3RD_PARTY;i++){
	    field_ImportFormat_index_table[i]=-1;
	}
	for(i=0;PSEUDOFIELD_IMPORT_FORMAT[i].pseudoField!=UNIHAN_INVALID_FIELD;i++){
	    if (PSEUDOFIELD_IMPORT_FORMAT[i].pseudoField!=lastField){
		field_ImportFormat_index_table[PSEUDOFIELD_IMPORT_FORMAT[i].pseudoField]=i;
		lastField=PSEUDOFIELD_IMPORT_FORMAT[i].pseudoField;
	    }
	}
    }
    e->index=field_ImportFormat_index_table[*field];
    e->userData=field;
}

gboolean unihanPseudoFieldImportFormat_enumerate_has_next_builtin(Enumerate *e){
    if (e->index>=0)
	return TRUE;
    return FALSE;
}

const UnihanPseudoFieldImportFormat *unihanPseudoFieldImportFormat_enumerate_next_builtin(Enumerate *e){
    glong i,prevIndex=e->index;
    e->index=-1;
    for(i=prevIndex+1;PSEUDOFIELD_IMPORT_FORMAT[i].pseudoField!=UNIHAN_INVALID_FIELD;i++){
	if (PSEUDOFIELD_IMPORT_FORMAT[i].pseudoField==*(UnihanField *)e->userData){
	    e->index=i;
	    break;
	}
    }
    if (prevIndex>=0)
	return &PSEUDOFIELD_IMPORT_FORMAT[prevIndex];
    return NULL;
}

const UnihanPseudoFieldImportFormatPost *unihanPseudoFieldImportFormatPost_find_builtin(UnihanField field,UnihanTable table){
    int i;
    for(i=0; PSEUDOFIELD_IMPORT_FORMAT_POST[i].field!=UNIHAN_INVALID_FIELD; i++){
	if (field==PSEUDOFIELD_IMPORT_FORMAT_POST[i].field && table==PSEUDOFIELD_IMPORT_FORMAT_POST[i].table){
	    return &(PSEUDOFIELD_IMPORT_FORMAT_POST[i]);
	}
    }
    return NULL;
}

/*==============================================================
 * Exporting Format
 */
void unihanPseudoFieldExportFormat_enumerate_init_builtin(Enumerate *e){
    e->index=0;
    e->userData=NULL;
}

gboolean unihanPseudoFieldExportFormat_has_next_builtin(Enumerate *e){
    if (UNIHAN_PSEUDOFIELD_EXPORT_FORMAT[e->index].pseudoField!= UNIHAN_INVALID_FIELD)
	return TRUE;
    return FALSE;
}

UnihanPseudoFieldExportFormat *unihanPseudoFieldExportFormat_next_builtin(Enumerate *e){
    if (unihanPseudoFieldExportFormat_has_next_builtin(e)){
	e->index++;
	return &UNIHAN_PSEUDOFIELD_EXPORT_FORMAT[e->index-1];
    }
    return NULL;
}

UnihanPseudoFieldExportFormat *unihanPseudoFieldExportFormat_get_by_pseudoField_builtin(UnihanField field){
    int i;
    for (i=0; UNIHAN_PSEUDOFIELD_EXPORT_FORMAT[i].pseudoField!= UNIHAN_INVALID_FIELD;i++){
	if (UNIHAN_PSEUDOFIELD_EXPORT_FORMAT[i].pseudoField==field){
	    return &UNIHAN_PSEUDOFIELD_EXPORT_FORMAT[i];
	}
    }
    return NULL;
}

gunichar unihanChar_parse(const char *str){
    char codeBuf[15];
    subString_buffer(codeBuf,str,2,strlen(str)-2);
    long code=strtol(codeBuf,(char**) NULL,16);
    return (gunichar) code;
}


