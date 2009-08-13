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
#include "collection.h"
#include "Unihan.h"

#define MAX_FIELDS_OF_TABLE 10


/**
 * Enumeration of Unihan private fields.
 */

/**
 * @defgroup Dict_Ref_Fields Supporting fields for dictionary refering tables.
 * @{
 * @name Supporting fields for dictionary refering tables.
 *
 *
 * @{
 */
typedef enum{
    UNIHAN_FIELD_DICT_VOLUME=UNIHAN_FIELD_3RD_PARTY,		//!< Volume number in dictionary.
    UNIHAN_FIELD_DICT_PAGE,		//!< Page number in dictionary.
    UNIHAN_FIELD_DICT_POSITION,		//!< The character number in the page.
    UNIHAN_FIELD_DICT_VIRTUAL,		//!< Virtual position of the character in dictionary. 0 if the character is in the dictionary, greater than 0 for a character assigned a "virtual" position in the dictionary.
    UNIHAN_FIELD_DICT_VARIANT_SERIAL,	//!< Serial number of variant. 0 for a main entry and greater than 0 for a parenthesized variant.
    UNIHAN_FIELD_DICT_UNENCODED,	//!< Unencoded character in the dictionary which is replaced by one or more encoded variants. Currently used only by kXHC1983.

    UNIHAN_FIELD_FROM_DICT,		//!< The dictionary that define the semantic relation.
    UNIHAN_FIELD_ZVARIANT_SOURCE, 	//!< The "Source" of Z variants, such as "kHKGlyph"

    UNIHAN_FIELD_SERIAL,		//!< Hold an artificial sequence number for sorting.
    UNIHAN_FIELD_SERIAL_NO_JOIN,	//!< Similar with \c UNIHAN_FIELD_SERIAL, but this field will not be used in automatic join.

    UNIHAN_FIELD_PRIVATE_END
} UnihanField_BuiltIn_Private;
/**
 * @}
 * @}
 */

/**
 * UnihanPseudoFieldImportFormat describes how the pseudo field is imported.
 */
typedef struct{
    UnihanField pseudoField; //!< A pseudo field
    UnihanTable table;       //!< A table.
    gchar *importPattern;    //!< A import pattern.
    UnihanField fields[MAX_FIELDS_OF_TABLE];  //!< Fields of the table.
    const gchar *storeFormats[MAX_FIELDS_OF_TABLE]; //!< Store format for each table.
} UnihanPseudoFieldImportFormat;

typedef struct{
    UnihanField field;
    UnihanTable table;
    gchar *regex_pattern; //!< Search pattern.
    gchar *eval_str;  //!< Replace pattern.
} UnihanPseudoFieldImportFormatPost;

/**
 * Prototype of pseudo field importing index.
 */
typedef UnihanPseudoFieldImportFormat* unihanPseudoFieldImportFormat_index_callback(size_t index);


/**
 * An sqlite error callback function that print all error message except
 * known constraint error.
 *
 * This function is very similar to sqlite_error_callback_hide_constraint_error(),
 * but only hide the known Unihan.txt errors,
 * such as in KCantonese field.
 *
 * @param db The \a db from from sqlite_exec_handle_error().
 * @param sqlClause The original \a sqlClause from from sqlite_exec_handle_error().
 * @param error_code Return value of sqlite3_exec().
 * @param error_msg Error message from sqlite3_exec().
 * @param prompt  Prompt of error message. From \a error_option of sqlite_exec_handle_error().
 * @return Argument \a error_code will be returned.
 *
 * @see sqlite_error_callback
 * @see sqlite_exec_handle_error()
 * @see sqlite_error_callback_hide_constraint_error()
 */

gint sqlite_error_callback_hide_known_constraint_error(sqlite3 *db, const gchar *sqlClause, gint error_code,
	const gchar *error_msg, gpointer prompt);

/**
 * Return the preferred table of field (Builtin).
 *
 * libUnihan is field-orinted, that is, normally you only need to mention the field to get the desirable result.
 * This function returns the preferred table need to get that field.
 *
 * The field can be either \b real or \b pseudo.
 *
 * \note Some pseudo fields like UNIHAN_FIELD_kIRG_GSOURCE require more than one tables
 * to obtain full function. Use unihanField_get_required_table_builtin() instead if this is the case.
 *
 * Use unihanField_get_allTables() to obtain all the table that the field belongs to.
 *
 * @param field  the UnihanField.
 * @return The preferred table if a valid field is given;
 *    \c UNIHAN_INVALID_TABLE if invalid field is given.
 * @see unihanField_get_required_table_builtin()
 * @see unihanField_get_all_tables_builtin(UnihanField field)
 */
UnihanTable unihanField_get_preferred_table_builtin(UnihanField field);

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
 * Use free() or g_free() to free the result.
 *
 * @param field  the UnihanField.
 * @return a newly allocated array of tables  which are required by the given field;
 *    \c UNIHAN_INVALID_TABLE if invalid field is given.
 * @see unihanField_get_required_table_builtin()
 * @see unihanField_get_all_tables_builtin(UnihanField field)
 */
UnihanTable *unihanField_get_required_tables_builtin(UnihanField field);

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
gboolean unihanField_has_flags_builtin(UnihanField field, guint flags);

/**
 * Parses the string argument as a UnihanField.
 *
 * Parses the string argument as a UnihanField.
 * Note that the match is case-sensitive.
 *
 * @param str		the string to be parsed.
 * @return		the equivalent UnihanField; UNIHAN_INVALID_FIELD if str does not match any of the field name.
 */
UnihanField unihanField_parse_builtin(const char *str);

/**
 * Returns a string representing a built-in UnihanField.
 *
 * @param field		the UnihanField.
 * @return		a string representing the #UnihanField.
 */
const char *unihanField_to_string_builtin(UnihanField field);

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
UnihanField* unihanTable_get_fields_builtin(UnihanTable table);

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
void unihanFieldProperties_enumerate_init_builtin(Enumerate *e);

/**
 * Returns TRUE if the enumeration has more elements.
 *
 * @param e enumerate handle.
 * @return TRUE if there is more elements; FALSE otherwise.
 * @see unihanFieldProperties_enumerate_init()
 * @see unihanFieldProperties_next()
 */
gboolean unihanFieldProperties_has_next_builtin(Enumerate *e);

/**
 * Returns the next element in the enumeration.
 *
 * @param e enumerate handle.
 * @return The next element; NULL if no such element.
 * @see unihanFieldProperties_enumerate_init()
 * @see unihanFieldProperties_next()
 */
const UnihanFieldProperties *unihanFieldProperties_next_builtin(Enumerate *e);

/**
 * Parses the string argument as a UnihanTable.
 *
 * Parses the string argument as a UnihanTable.
 * Note that the match is case-sensitive.
 *
 * @param str		the string to be parsed.
 * @return		the equivalent UnihanTable; UNIHAN_INVALID_Table if str does not match any of the table name.
 */
UnihanTable unihanTable_parse_builtin(const char *str);

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
UnihanField* unihanTable_get_fields_builtin(UnihanTable table);

/**
 * Returns a string representing a built-in UnihanTable.
 *
 * @param table		An UnihanTable.
 * @return		a string representing the #UnihanTable.
 */
const char *unihanTable_to_string_builtin(UnihanTable table);

/**
 * Initialize an unihanPseudoFieldImportFormat enumerate handle.
 *
 * An unihanPseudoFieldImportFormat enumerate list all the import format
 * for a UnihanField
 *
 * @param e An enumerate handle.
 * @param field An UnihanField.
 */
void unihanPseudoFieldImportFormat_enumerate_init_builtin(Enumerate *e, UnihanField *field);
gboolean unihanPseudoFieldImportFormat_enumerate_has_next_builtin(Enumerate *e);
const UnihanPseudoFieldImportFormat *unihanPseudoFieldImportFormat_enumerate_next_builtin(Enumerate *e);

const UnihanPseudoFieldImportFormatPost *unihanPseudoFieldImportFormatPost_find_builtin(UnihanField field,UnihanTable table);

/**
 * Initialize an unihanPseudoFieldExportFormat enumerate handle.
 *
 * An unihanPseudoFieldExportFormat enumerate list all the
 * pseudo field exporting formats for libUnihan.
 *
 * Example code:
 * <pre>
 * Enumerate e;
 * unihanPseudoFieldExportFormat_enumerate_init_builtin(&e);
 * while(unihanPseudoFieldExportFormat_has_next_builtin(&e)){
 *      UnihanPseudoFieldExportFormat *format=unihanPseudoFieldExportFormat_next_builtin(&e);
 *      ...do something with format...
 * }
 * </pre>
 *
 * @param e enumerate handle to be initialized.
 * @see unihanPseudoFieldExportFormat_has_next_builtin()
 * @see unihanPseudoFieldExportFormat_next_builtin()
 */
void unihanPseudoFieldExportFormat_enumerate_init_builtin(Enumerate *e);

/**
 * Returns TRUE if the enumeration has more elements.
 *
 * @param e enumerate handle.
 * @return TRUE if there is more elements; FALSE otherwise.
 * @see unihanPseudoFieldExportFormat_enumerate_init_builtin()
 * @see unihanPseudoFieldExportFormat_next_builtin()
 */
gboolean unihanPseudoFieldExportFormat_has_next_builtin(Enumerate *e);

/**
 * Returns the next element in the enumeration.
 *
 * @param e enumerate handle.
 * @return The next element; NULL if no such element.
 * @see unihanPseudoFieldExportFormat_enumerate_init_builtin()
 * @see unihanPseudoFieldExportFormat_next_builtin()
 */
UnihanPseudoFieldExportFormat *unihanPseudoFieldExportFormat_next_builtin(Enumerate *e);

/**
 * Returns the exporting format regarding the pseudo field.
 *
 * @param field The pseudo field.
 * @return The e exporting format regarding the \a field; NULL if no such format.
 */
UnihanPseudoFieldExportFormat *unihanPseudoFieldExportFormat_get_by_pseudoField_builtin(UnihanField field);

#endif /* UNIHAN_BUILTIN_H_ */
