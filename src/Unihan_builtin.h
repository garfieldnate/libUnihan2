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

#ifndef UNIHAN_BUILTIN_H_
#define UNIHAN_BUILTIN_H_
#include "Unihan.h"


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
 * Whether field has given flags.
 *
 * Whether field has given flags. 
 * Always return FALSE if field is  UNIHAN_INVALID_FIELD or 
 * field is not built-in (field >=UNIHAN_FIELD_3RD_PARTY).
 *
 * @param field field to be checked.
 * @param flags flags to be checked.
 * @return TRUE if \a field has \a flags; FALSE otherwise.
 */
gboolean unihanField_builtin_has_flags(UnihanField field, guint flags);

/**
 * Parses the string argument as a UnihanField.
 *
 * Parses the string argument as a UnihanField. 
 * Note that the match is case-sensitive.
 *
 * @param str		the string to be parsed.
 * @return		the equivalent UnihanField; UNIHAN_INVALID_FIELD if str does not match any of the field name.
 */
UnihanField unihanField_builtin_parse(const char *str);

/**
 * Returns a string representing a built-in UnihanField.
 *
 * @param field		the UnihanField.
 * @return		a string representing the #UnihanField.
 */
const char *unihanField_builtin_to_string(UnihanField field);

/**
 * Returns all built-in fields of the table in an UnihanField array.
 *
 * Returns all built-in fields of the table in an UnihanField array.
 * The returned UnihanField array is terminated by UNIHAN_INVALID_FIELD.
 * Use free() or g_free() to free the UnihanField array.
 *
 * @param table		the UnihanTable.
 * @return		all fields of the table in an UnihanField array.
 */
UnihanField* unihanTable_get_builtin_fields(UnihanTable table);

/**
 * Initialize an unihanFieldProperties enumerate handle.
 *
 * An unihanFieldProperties enumerate list all the 
 * field properties for libUnihan. 
 *
 * Example code:
 * <pre>
 * Enumerate e;
 * unihanFieldProperties_enumerate_init(&e);
 * while(unihanFieldProperties_has_next(&e)){
 *      UnihanFieldProperties *format=unihanFieldProperties_next(&e);
 *      ...do something with format...
 * }
 * </pre>
 *
 * @param e enumerate handle to be initialized.
 * @see unihanFieldProperties_has_next()
 * @see unihanFieldProperties_next()
 */
void unihanFieldProperties_builtin_enumerate_init(Enumerate *e);

/**
 * Returns TRUE if the enumeration has more elements.
 *
 * @param e enumerate handle.
 * @return TRUE if there is more elements; FALSE otherwise.
 * @see unihanFieldProperties_enumerate_init()
 * @see unihanFieldProperties_next()
 */
gboolean unihanFieldProperties_builtin_has_next(Enumerate *e);

/**
 * Returns the next element in the enumeration.
 *
 * @param e enumerate handle.
 * @return The next element; NULL if no such element.
 * @see unihanFieldProperties_enumerate_init()
 * @see unihanFieldProperties_next()
 */
UnihanField* unihanTable_get_builtin_fields(UnihanTable table);

/**
 * Parses the string argument as a UnihanTable.
 *
 * Parses the string argument as a UnihanTable.
 * Note that the match is case-sensitive.
 *
 * @param str		the string to be parsed.
 * @return		the equivalent UnihanTable; UNIHAN_INVALID_Table if str does not match any of the table name.
 */
UnihanTable unihanTable_builtin_parse(const char *str);

/**
 * Returns all built-in fields of the table in an UnihanField array.
 *
 * Returns all built-in fields of the table in an UnihanField array.
 * The returned UnihanField array is terminated by UNIHAN_INVALID_FIELD.
 * Use free() or g_free() to free the UnihanField array.
 *
 * @param table		the UnihanTable.
 * @return		all fields of the table in an UnihanField array.
 */
const char *unihanTable_builtin_to_string(UnihanTable table);

/**
 * Returns a string representing a built-in UnihanTable.
 *
 * @param table		the UnihanTable.
 * @return		a string representing the #UnihanTable.
 */
const char *unihanTable_builtin_to_string(UnihanTable table);


/**
 * Import a tag value of a character from a line of Unihan.txt.
 *
 * This function imports a line in Unihan.txt to database \c db.
 * For non-singleton fields (fields which may have multiple values for each character),
 * the tag value is split with the delimiter ' ', and each 
 * chunk is passed to unihan_import_builtin_table_single_tagValue() for further process.
 *
 * 
 * @param db Db handle
 * @param code the UCS4 representation of the character.
 * @param field The UnihanField to be import.
 * @param tagValue The value of the field.
 * @return 0 if success, otherwise return nonzero value.
 * @see unihan_import_builtin_table_tagValue_original.
 */
int unihan_import_builtin_table_tagValue(sqlite3 *db, gunichar code, UnihanField field, const char *tagValue);

/**
 * Initialize an unihanPseudoFieldExportingFormat enumerate handle.
 *
 * An unihanPseudoFieldExportingFormat enumerate list all the 
 * pseudo field exporting formats for libUnihan. 
 *
 * Example code:
 * <pre>
 * Enumerate e;
 * unihanPseudoFieldExportingFormat_builtin_enumerate_init(&e);
 * while(unihanPseudoFieldExportingFormat_builtin_has_next(&e)){
 *      UnihanPseudoFieldExportingFormat *format=unihanPseudoFieldExportingFormat_builtin_next(&e);
 *      ...do something with format...
 * }
 * </pre>
 *
 * @param e enumerate handle to be initialized.
 * @see unihanPseudoFieldExportingFormat_builtin_has_next()
 * @see unihanPseudoFieldExportingFormat_builtin_next()
 */
void unihanPseudoFieldExportingFormat_builtin_enumerate_init(Enumerate *e);

/**
 * Returns TRUE if the enumeration has more elements.
 *
 * @param e enumerate handle.
 * @return TRUE if there is more elements; FALSE otherwise.
 * @see unihanPseudoFieldExportingFormat_builtin_enumerate_init()
 * @see unihanPseudoFieldExportingFormat_builtin_next()
 */
gboolean unihanPseudoFieldExportingFormat_builtin_has_next(Enumerate *e);

/**
 * Returns the next element in the enumeration.
 *
 * @param e enumerate handle.
 * @return The next element; NULL if no such element.
 * @see unihanPseudoFieldExportingFormat_builtin_enumerate_init()
 * @see unihanPseudoFieldExportingFormat_builtin_next()
 */
UnihanPseudoFieldExportingFormat *unihanPseudoFieldExportingFormat_builtin_next(Enumerate *e);

/**
 * Returns the exporting format regarding the pseudo field.
 *
 * @param field The pseudo field.
 * @return The e exporting format regarding the \a field; NULL if no such format.
 */
UnihanPseudoFieldExportingFormat *unihanPseudoFieldExportingFormat_builtin_get_by_pseudoField(UnihanField field);

#endif /* UNIHAN_BUILTIN_H_ */
