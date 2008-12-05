/** 
 * @file Unihan_builtin.h
 * @brief Data structures and functions for built-in tables and fields only.
 * 
 * This file contains the data structures and functions 
 *  which only deal for built-in tables and fields.
 *
 * These function are mainly for rebuilding database only, i.e.
 * Normally not needed.
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

/**
 * Return the preferred table of field (Builtin).
 *
 * libUnihan is field-center, that is, normally you only need to mention the field to get the desirable result.
 * This function returns the preferred table need to get that field.
 *
 * The field can be either \b real or \b pseudo.
 *
 * \note Some pseudo fields like UNIHAN_FIELD_kIRG_GSOURCE require more than one tables 
 * to obtain full function. Use unihanField_get_builtin_required_table() instead if this is the case.
 *
 *
 * Use unihanField_get_allTables() to obtain all the table that the field belongs to.
 *
 * @param field  the UnihanField.
 * @return The preferred table if a valid field is given;
 *    \c UNIHAN_INVALID_TABLE if invalid field is given.
 * @see unihanField_get_builtin_required_table()
 * @see unihanField_get_all_builtin_tables(UnihanField field)
 */
UnihanTable unihanField_get_builtin_preferred_table(UnihanField field);


/**
 * Return an array of tables which are required by the given field (Builtin).
 *
 * This function returns a newly allocated array of tables  which are required by the given field.
 * \c UNIHAN_INVALID_TABLE marks the end of the array.
 *
 * If a \b real field is given, then it returns an array that has the preferred table.
 *
 * If a \b pseudo field is given, then it returns an array which contains all tables it need to 
 * generate it.
 *
 *
 * Use free() or g_free() to free the result.
 *
 * @param field  the UnihanField.
 * @return a newly allocated array of tables  which are required by the given field;
 *    \c UNIHAN_INVALID_TABLE if invalid field is given.
 * @see unihanField_get_builtin_required_table()
 * @see unihanField_get_all_builtin_tables(UnihanField field)
 */
UnihanTable *unihanField_get_builtin_required_tables(UnihanField field);

/**
 * Import a field value of a character from Unihan.txt.
 *
 * This function imports a single field valueof character from Unihan.txt. 
 * Note that multi-valued fields should use unihan_import_builtin_table_tagValue_original() instread.
 * 
 * @param db Db handle
 * @param code the UCS4 representation of the character.
 * @param field 
 */
int unihan_import_builtin_table_tagValue(sqlite3 *db, gunichar code, UnihanField field, 
	const char *tagValue, int *counter_ptr);

int unihan_import_builtin_table_tagValue_original(sqlite3 *db, gunichar code, UnihanField field, const char *tagValue_original);
