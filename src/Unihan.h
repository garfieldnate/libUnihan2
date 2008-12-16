/** 
 * @file Unihan.h
 * @brief API for libUnihan.
 *
 *
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
#ifndef UNIHAN_H_
#define UNIHAN_H_
#include "Unihan_enum.h"
#include "Unihan_phonetic.h"
#include "sqlite_functions.h"
#include "str_functions.h"

/**
 * The default field cache file.
 *
 */
#define FIELD_CACHE_DB "field.cache"

/**
 * IRG source data.
 *
 * This struct contains a short source name and the corresponding description.
 *
 * @see unihanIRG_SourceData_get()
 */
typedef struct {
    const char *name; //!< short source name in string. (e.g. "G0").
    const char *description; //!< full description of the IRG source. (e.g. "GB2310-80").
} UnihanIRG_SourceData;

/**
 * Structure for field-table pair.
 *
 * This struct stores a pair of UnihanField and UnihanTable.
 */
typedef struct {
    UnihanField field;
    UnihanTable table;
} UnihanFieldTablePair;

/**
 * IRG source rec.
 *
 * This struct stores an IRG source ID for a character and 
 * the mapping/inner code/index
 *
 */
typedef struct {
    UnihanIRG_SourceId sourceId; //!< a IRG source ID.
    const char *sourceMapping;   //!< the mapping of the character in the source.
} UnihanIRG_SourceRec;


/**
 * Data structure of database supporting functions.
 *
 */
typedef struct {
    const char* funcName;                //!< Name to be referred in SQL.
    int argc;				 //!< Number of arguments.
    void (*func)(sqlite3_context *context, int argc, sqlite3_value **argv); //!< Scalar function. Can be NULL.
    void (*stepFunc)(sqlite3_context *context, int argc, sqlite3_value **argv);  //!< Aggregation step function. Can be NULL.
    void (*finalizeFunc)(sqlite3_context *context); //!< Aggregation finalize function. Can be NULL.
} DatabaseFuncStru;

/**
 * List of database supporting functions.
 *
 */
extern const DatabaseFuncStru DATABASE_FUNCS[];

/**
 * @name Unihan query options.
 */
/*@{*/
/**
 * Unihan query options.
 * Unihan query options provides additional control of query processing,
 * such as SQL like query and output format.
 *
 */
typedef guint UnihanQueryOption;

#define UNIHAN_QUERY_OPTION_LIKE		1   	//!< Using SQL LIKE in WHERE expression.
#define UNIHAN_QUERY_OPTION_SCALAR_STRING	1 << 1	//!< Show code point as string "U+xxxx".
#define UNIHAN_QUERY_OPTION_SHOW_GIVEN_FIELD    1 << 2  //!< Show the given field in results.
#define UNIHAN_QUERY_OPTION_PINYIN_TONE_ACCENT  1 << 3  //!< Use accent mark for pinyin tone.
#define UNIHAN_QUERY_OPTION_PINYIN_FORMAT_MASK  7 << 4  //!< Mask for pinyin format.
#define UNIHAN_QUERY_OPTION_ZHUYIN_FORCE_DISPLAY  1 << 7  //!< Force Zhuyin display.
#define UNIHAN_QUERY_OPTION_ZHUYIN_FORMAT_MASK  7 << 8  //!< Mask for zhuyin format.

#define UNIHAN_QUERY_OPTION_DEFAULT		(PINYIN_ACCENT_UNIHAN << 4) | (ZHUYIN_TONEMARK_ORIGINAL << 8)	
   //!< Default options, Pinyin format is Unihan; and Zhuyin format is Original.

/**
 * Get Pinyin format from UnihanQueryOption.
 *
 * @param options A UnihanQueryOption.
 * @return PinyinAccentFormat
 */
#define UNIHAN_QUERY_OPTION_GET_PINYIN_FORMAT(options) (options & UNIHAN_QUERY_OPTION_PINYIN_FORMAT_MASK) >> 4

/**
 * Set Pinyin format to UnihanQueryOption.
 *
 * @param options A UnihanQueryOption.
 * @param format PinyinAccentFormat.
 */
#define UNIHAN_QUERY_OPTION_SET_PINYIN_FORMAT(options,format) options |= format << 4

/**
 * Get Zhuyin format from UnihanQueryOption.
 *
 * @param options A UnihanQueryOption.
 * @return ZhuyinToneMarkFormat
 */
#define UNIHAN_QUERY_OPTION_GET_ZHUYIN_FORMAT(options) (options & UNIHAN_QUERY_OPTION_ZHUYIN_FORMAT_MASK) >> 8

/**
 * Set Zhuyin format to UnihanQueryOption.
 *
 * @param options A UnihanQueryOption.
 * @param format Zhuyin_Accent_Format.
 */
#define UNIHAN_QUERY_OPTION_SET_ZHUYIN_FORMAT(options,format) options |= format << 8

/*@}*/


/**
 * Find all matched results, given a field and its value.
 *
 * This function is a convenient wrapper of unihanSql_get_sql_result().
 *
 * Put the known field as <code>givenFiled</code> and its value as <code>givenValue</code>.
 * The values of field specified in <code>queryField</code> will be put in the result table.
 * 
 * Use sql_result_free() to free the pResults after the finish using result table.
 *
 * @param givenField the given (input) field.
 * @param givenValue the given value of the field.
 * @param queryField the result field.
 * @param qOption    the ::UnihanQueryOption.
 * @return a SQL_Result instance that stores the field names and result
 * records.
 *
 * @see unihan_find_firstMatched()
 * @see unihanSql_get_sql_result()
 * @see ::UnihanQueryOption
 * @see <a href="http://www.sqlite.org/c3ref/c_abort.html">SQLite result codes</a>
 */
SQL_Result *unihan_find_all_matched(UnihanField givenField, const char *givenValue, 
	UnihanField queryField, UnihanQueryOption qOption);

/**
 * Find the first matched result, given a field and its value.
 *
 * This is a simplified version of unihan_find_all_matched().
 * Instead of returning whole result table, it only returns the first matched result as string.
 *
 * Use g_free() to free the returned result.
 *
 * @param givenField the given (input) field.
 * @param givenValue the given value of the field.
 * @param queryField the result field.
 * @param qOption    the #UnihanQueryOption.
 * @return the first matched result string. NULL if nothing matched.
 *
 * @see unihan_find_all_matched()
 */
char* unihan_find_first_matched(UnihanField givenField, const char* givenValue, 
	UnihanField queryField, UnihanQueryOption qOption );

/**
 * Count number of matched records in a table.
 *
 * Also useful to avoid the duplication record.
 * For example, use 
 * <code>unihan_count_matched_record(UNIHAN_TABLE_KRSADOBE_JAPAN_1_6, valueArray)</code>
 * to check whether the kRSAdobe_Japan_1_6Table has the record (13317,"C",15387,"3",1,1)
 * before insertion,
 * where the valueArray[]={ "13317", "C","15387","3","1","1", NULL};
 * 
 * @param table		the database table to be looked at.
 * @param valueList 	Values in StringList.
 * @return number of matched record. Negative if error.
 */
int unihan_count_matched_record(UnihanTable table,StringList *valueList);

/**
 * Insert a record to table.
 * 
 * The value to be insert should be in string representation, as if put in plain text SQL command.
 *
 * @param table		The database table to be looked at.
 * @param valueList 	Values in StringList.
 * @return SQLite result code, SQLITE_OK (value 0) if the query executed successfully, 
 *         while non-zero value indicate error. 
 *
 * @see <a href="http://www.sqlite.org/c3ref/c_abort.html">SQLite result codes</a>
 * @see unihan_insert_no_duplicate()
 * @see unihan_insert_value()
 */
int unihan_insert(UnihanTable table,StringList *valueList);

/**
 * Insert a record to table with duplication check.
 *
 * It will check the duplication before insertion, otherwise is same with
 * unihan_insert(). Return negative value if the duplication is found.
 *
 * @param table		the database table to be looked at.
 * @param valueList 	Values in StringList.
 * @return Negative value is duplication is found.  SQLITE_OK (value 0) if inserted successfully, 
 *         while positive value indicate error. 
 */
int unihan_insert_no_duplicate(UnihanTable table,StringList *valueList);

/**
 * Insert a Unihan textual formated record to corresponding tables.
 * 
 * This function deals with the insertion of Unihan textual formated records (as shown in Unihan.txt),
 * which have 3 fields:
 * <ol>
 *   <li>code scalar value (e.g. U+5231)</li>
 *   <li>Unihan tag (e.g. kSemanticVariant)</li>
 *   <li>The corresponding value  (e.g. U+5275<kHanYu:TZ,kMeyerWempe)</li>
 * </ol>  
 *
 * This function will parse the value and insert the parsed result to corresponding tables.
 *
 * Before using this function,
 * convert first field to UCS4 (gunichar) format (using unihanChar_parse());
 * second to UnihanField (using unihanField_parse()).
 *
 * @param code		character in UCS4 (gunichar)
 * @param field         the UnihanField
 * @param value		the value in as in Unihan.txt.
 * @return Negative value is duplication is found.  SQLITE_OK (value 0) if inserted successfully, 
 *         while positive value indicate error. 
 */
int unihan_insert_value(gunichar code, UnihanField field, const char *value);

/**
 * Whether the character is associate with the given field.
 *
 * @param code		character in UCS4 (gunichar)
 * @param field		the UnihanField
 * @return TRUE if an non-NULL value is associate with the field, FALSE otherwise.
 */
gboolean unihanChar_has_field(gunichar code, UnihanField field);

/**
 * Whether the character appeared in given source.
 *
 * @param code		character in UCS4 (gunichar)
 * @param source 	IRG Source ID
 * @return TRUE if character appeared in source, FALSE otherwise.
 */
gboolean unihanChar_is_in_source(gunichar code, UnihanIRG_SourceId source);

/**
 * Find the first source which the character appears in.
 *
 * This function will return the first matched source, or until it reaches the end of
 * 
 * @param code		character in UCS4 (gunichar)
 * @param source 	IRG Source ID, use UNIHAN_INVALID_SOURCEID as indefinite value terminator.
 * @return the matched source id, or UNIHAN_INVALID_SOURCEID if none matched.
 */
UnihanIRG_SourceId unihanChar_is_in_sources(gunichar code, UnihanIRG_SourceId source, ...);

/**
 * Whether the character is common in the specified locale.
 *
 * "Common" characters are the ones which appear in the well-known source,
 * such as GB-2312 and JIS X 0208:1990. 
 * See <a href="#CommonLocale">Common sources for a locale</a> for exact sources.
 *
 * @param code		character in UCS4 (gunichar)
 * @param locale 	the locale.
 * @return TRUE if the character is common, FALSE otherwise.
 * @see <a href="#CommonLocale">Common sources for a locale</a>
 */
gboolean unihanChar_is_common_in_locale(gunichar code, UnihanLocale locale);

/**
 * Return the range which the character belong to.
 *
 * @param code		character in UCS4 (gunichar)
 * @return the range which the character belong to.
 * @see #UnihanRange
 */
UnihanRange unihanChar_in_range(gunichar code);

/**
 * Parses the string argument as a UCS4 (gunichar) character.
 *
 * @param str		the string to be parsed.
 * @return		the character represented by the str in UCS4.
 */
gunichar unihanChar_parse(const char *str);

/**
 * Returns a scalar string of a UCS4 character.
 *
 * This function converts the UCS4 integer to scalar value format (U+XXXXXX)
 * and returns a newly allocated string that holds it.
 *
 * Use free() or g_free() to free the result.
 *
 * @param code		the UCS4 character.
 * @return		a string representing the UCS4 character.
 */
char *unihanChar_to_scalar_string(gunichar code);


/**
 * Returns the db which libUnihan is using.
 *
 * Normally this function is not needed,
 * except to get additional control beyond SQL.
 * @return the db which libUnihan is using.
 */
sqlite3 *unihanDb_get();


/**
 * Returns the names of table in database.
 *
 * This function returns  all tables Id from DB files
 *  which are recorded in the cache DB.
 *
 * The result is returned as a newly allocated UnihanTable array.
 *
 * Use free() or g_free*( to free the result.
 *
 * @return An UnihanTable array that holds Ids of tables in cache DB.
 * @see unihanDb_get_all_tableNames()
 */
UnihanTable *unihanDb_get_all_tables();

/**
 * Returns the names of table in database.
 *
 * This function returns names of all tables from DB files
 *  which are recorded in the cache DB.
 * 
 * The result is returned as a newly allocated SQL_Result instance.
 *
 *
 * Use sql_result_free() to free the result.
 * @return the tables in SQL_Result form.
 * @see unihanDb_get_all_tables()
 */
SQL_Result *unihanDb_get_all_tableNames();


/**
 * Open a Unihan db.
 *
 * The flags parameter provides additional control of database access.
 * It is supported by sqlite3_open_v2(), thus it takes one of the following three values,
 * optionally combined with the SQLITE_OPEN_NOMUTEX flag, just like the flags
 * parameter of sqlite3_open_v2():
 * <dl>
 *    <dt>SQLITE_OPEN_READONLY</dt>
 *      <dd>The database is opened in read-only mode. If the database does not already exist, 
 *          an error is returned.</dd>
 *    <dt>SQLITE_OPEN_READWRITE</dt>
 *    <dd>The database is opened for reading and writing if possible, 
 *        or reading only if the file is write protected by the operating system.
 *        In either case the database must already exist, otherwise an error is returned.</dd>
 *    <dt>SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE</dt>
 *    <dd>The database is opened for reading and writing, and is creates it if 
 *        it does not already exist. This is the behavior that is always used for 
 *        sqlite3_open() and sqlite3_open16().</dd>
 * </dl>
 * See the sqlite3_open() for detail explanation of SQLITE_OPEN_NOMUTEX.
 *
 * Note that SQLITE_OPEN_NOMUTEX flags is not supported in SQLite 3.3.X and earlier.
 *
 * @param filename name of db file to be open.
 * @param flags  Database access flags.
 * @return SQLite result code, SQLITE_OK (value 0) if the query executed successfully, 
 *         while non-zero value indicate error. 
 *
 * @see <a href="http://www.sqlite.org/c3ref/c_abort.html">SQLite result codes</a>
 * @see <a
 * href="http://www.sqlite.org/capi3ref.html#sqlite3_open">sqlite3_open()</a>
 */
int unihanDb_open(const char *filename, int flags);

/**
 * Open the system default Unihan Db as read-only.
 *
 * @return SQLite result code, SQLITE_OK (value 0) if the query executed successfully, 
 *         while non-zero value indicate error. 
 *
 * @see <a href="http://www.sqlite.org/c3ref/c_abort.html">SQLite result codes</a>
 */
int unihanDb_open_default();

/**
 * Close Unihan db.
 *
 * @return SQLite result code, SQLITE_OK (value 0) if the query executed successfully, 
 *         while non-zero value indicate error. 
 *
 * @see <a href="http://www.sqlite.org/c3ref/c_abort.html">SQLite result codes</a>
 */
int unihanDb_close();

/**
 * Return the index of a UnihanField in array.
 *
 * @param field Field to be found
 * @param fieldArray the array of UnihanFields.
 * @return index of the #UnihanField, -1 if the field is not found.
 */
int unihanField_array_index(UnihanField field,  const UnihanField* fieldArray);

/**
 * Return the corresponding IRG source if the field is IRG source field.
 *
 * @param field  the UnihanField.
 * @return corresponding IRG source if the field is IRG source field; 
 * #UNIHAN_INVALID_IRG_SOURCE if the field is not an IRG source field.
 */
UnihanIRG_Source unihanField_get_IRG_source(UnihanField field);

/**
 * Return the table that contains the key.
 *
 * This function only returns one table.
 * If the field is in more than one table, then returns #UNIHAN_AMBIGUOUS_TABLE.
 * Returns #UNIHAN_INVALID_TABLE if invalid field is given.
 *
 * Use unihanField_get_allTables() to obtain all the table that the field belongs to.
 *
 * @param field  the UnihanField.
 * @return corresponding table if the field only appears in that table;
 *    #UNIHAN_AMBIGUOUS_TABLE if the field appears in multiple tables;
 *    #UNIHAN_INVALID_TABLE if invalid field is given.
 * @see unihanField_get_all_tables()
 * @see unihanField_get_extra_table()
 */
UnihanTable unihanField_get_table(UnihanField field);

/**
 * Return all the tables that contains the key.
 *
 * This function returns an array of tables, terminated by #UNIHAN_INVALID_TABLE.
 * Use unihanField_get_allTables() to obtain all the table that the field belongs to.
 *
 * @param field  the UnihanField.
 * @return arrays of UnihanTables; NULL if the field is invalid.
 * @see unihanField_get_table()
 * @see unihanField_get_extra_table()
 */
UnihanTable *unihanField_get_all_tables(UnihanField field);

/**
 * Return the corresponding extra table if the field needs one.
 *
 * A extra table is a table that provide additional information for pseudo field.
 * For example, kSemanticVariant is a pseudo field which combines fields in
 * kSemanticVariantTable and kSemanticVariantTableExtra.
 *
 * unihanFIeld_get_table(UNIHAN_KSEMANTIC_VARIANT) returns kSemanticVariantTable
 * while unihanFIeld_get_extra_table returns the extra table kSemanticVariantTableExtra.
 *
  * Pseudo fields usually associate with extra tables, 
 * see unihanField_is_pseudo() for details.
 * 
 * @param field  the UnihanField.
 * @return the extra table if exist, UNIHAN_INVALID_TABLE otherwise.
 * @see unihanField_is_pseudo().
 */
UnihanTable unihanField_get_extra_table(UnihanField field);

/**
 * Return the built-in tables that required by the built-in field.
 *
 * The function returns built-in tables that required by the specified built-in field.
 * This function is designed for handling only the build-in fields.
 * It returns an UnihanTable array with \c UNIHAN_INVALID_TABLE at index 0, 
 * if 3rd party fields is given.
 *
 * Free the returned array with free() or g_free().
 *
 * @param field  the UnihanField.
 * @return An newly allocated array of UnihanTable that \c field requires, terminated by UNIHAN_INVALID_TABLE.
 * @see unihanField_get_table()
 * @see unihanField_get_extra_table()
 */
UnihanTable *unihanField_get_required_tables(UnihanField field);

/**
 * Whether the field is IRG_Source.
 *
 * It is a convenient wrapper of unihanField_get_IRG_source().
 * @param field  the UnihanField.
 * @return TRUE if the field is IRG_Source; FALSE otherwise.
 */
gboolean unihanField_is_IRG_Source(UnihanField field);


/**
 * Whether the field is indexed.
 *
 * Indexed field are non-pseudo fields which are indexed in database.
 * Note that UNIHAN_FIELD_KDEFITION is not indexed as well.
 *
 * @param field the UnihanField
 * @return TRUE if the field is indexed; FALSE otherwise.
 * @see unihanField_is_pseudo()
 */
gboolean unihanField_is_indexed(UnihanField field);

/**
 * Whether the field is an integer field.
 *
 * @param field the UnihanField
 * @return TRUE if the field is integer; FALSE otherwise.
 */
gboolean unihanField_is_integer(UnihanField field);


/**
 * Whether the value in the field is stored as uppercase.
 *
 * Some Unihan tag values are always stored as uppercase, such as
 * \c UNIHAN_FIELD_KMANDARIN, \c UNIHAN_FIELD_PINYIN.
 *
 *
 * @param field the UnihanField
 * @return TRUE if the value of field is stored as lowercase; FALSE otherwise.
 * @see unihanField_is_lowercase()
 */

gboolean unihanField_is_uppercase(UnihanField field);

/**
 * Whether the value in the field is stored as lowercase.
 *
 * Usually, the Unihan tag values are stored as uppercase, such as
 * \c UNIHAN_FIELD_KMANDARIN, \c UNIHAN_FIELD_PINYIN.
 *
 * However, there are exceptions such as field \c UNIHAN_FIELD_KCANTONESE 
 * which always stores as lowercase; 
 * while field \c UNIHAN_FIELD_KDEFINITION, on the other hand, may have uppercase
 * and lowercase characters.
 *
 * @param field the UnihanField
 * @return TRUE if the value of field is stored as lowercase; FALSE otherwise.
 * @see unihanField_is_uppercase()
 */
gboolean unihanField_is_lowercase(UnihanField field);

/**
 * Whether the field contains mandarin pronunciation.
 *
 * @param field the UnihanField
 * @return TRUE if the field is integer; FALSE otherwise.
 */
gboolean unihanField_is_mandarin(UnihanField field);

/**
 * Whether the field is a pseudo field.
 *
 * A pseudo field is a field whose value is not derived directly from table but database functions.
 * Field zhuyin, for example, is not in database but derived from function PINYIN_TO_ZHUYIN().
 * It is deemed to be a short cut for database functions.
 *
 *
 * Another example is field kSemanticVariant, which is a pseudo field which combines:
 * kSemanticVariantTable.varinatCode, kSemanticVariantTableExtra.fromDict,
 * kSemanticVariantTableExtra.semanticT, kSemanticVariantTableExtra.semanticB and
 * kSemanticVariantTableExtra.semanticZ
 *
 *
 * @param field the UnihanField
 * @return TRUE if the field is a pseudo field; FALSE otherwise.
 */
gboolean unihanField_is_pseudo(UnihanField field);

/**
 * Whether the field holds UCS4 value.
 *
 * UCS4 fields can be displayed in the form of Unicode scalar string (U+xxxxx)
 *
 * @param field the UnihanField 
 * @return TRUE if the field holds a UCS4 value; FALSE otherwise.
 */
gboolean unihanField_is_ucs4(UnihanField field);

/**
 * Whether the field is a singleton field.
 *
 * A singleton field is a field whose value cannot be further split, and 
 * is functional dependent to the UNIHAN_FIELD_CODE.
 *
 * Most of tag value in Unihan.txt is delimited by space, however
 * kDefinition, for example, should not be split in this way.
 *
 *
 *
 * @param field the UnihanField 
 * @return TRUE if the field is a singleton field; FALSE otherwise.
 */
gboolean unihanField_is_singleton(UnihanField field);

/**
 * Parses the string argument as a UnihanField.
 *
 * @param str		the string to be parsed.
 * @return		the UnihanField represented by the str in UCS4.
 */
UnihanField unihanField_parse(const char *str);

/**
 * Returns a string representing a UnihanField.
 *
 * @param field		the UnihanField.
 * @return		a string representing the #UnihanField.
 */
const char* unihanField_to_string(UnihanField field);

/**
 * Whether the SourceId has mapping.
 *
 * Some IRG sources (such as \c UNIHAN_SOURCE_GKX, \c UNIHAN_SOURCE_G4K) does not 
 * have mapping index (inner code). This function tells whether a 
 * Source ID has mapping.
 *
 * @param sourceId the IRG source ID.
 * @return TRUE if the source ID has no mapping; FALSE otherwise.
 */
gboolean unihanIRG_Source_has_no_mapping(UnihanIRG_SourceId sourceId);

/**
 * Return the Unihan IRG_Source Data.
 *
 * Note: the returned data is static, not need to be freed.
 * @param sourceId Unihan IRG source ID.
 * @return the Unihan IRG_Source Data.  
 */
const UnihanIRG_SourceData *unihanIRG_SourceData_get(UnihanIRG_SourceId sourceId);

/**
 * Parse the string argument as Unihan IRG Source ID.
 *
 * @param sourceShortName	the string to be parsed.
 * @return 			the UnihanIRG_SourceID.
 */
UnihanIRG_SourceId unihanIRG_SourceId_parse(const char *sourceShortName);

/**
 * Parse the string argument as Unihan IRG Source Rec.
 *
 * @note {Use unihanIRG_SourceRec_free() to free the generated rec.}
 *
 * @param field 	the UnihanField 
 * @param value		the string to be parsed.
 * @return 		the UnihanIRG_SourceRec.
 */
UnihanIRG_SourceRec* unihanIRG_SourceRec_parse(UnihanField field,const char *value);

/**
 * Free the UnihanIRG_SourceRec.
 *
 * @param rec			the unihanIRG_SourceRec
 */
void unihanIRG_SourceRec_free(UnihanIRG_SourceRec *rec);

/**
 * Count the number of matches.
 *
 * @param sqlClause SQL command to be passed to Unihan db.
 * @param errMsg_ptr pointer for error message.
 * @return Negative number if the command does not execute successfully, 
 * ( -1 * <a href="http://www.sqlite.org/c3ref/c_abort.html">SQLite_result_code</a>);
 *  Non-negative number is the number of matches.
 */
int unihanSql_count_matches(const char * sqlClause, char **errMsg_ptr);

/**
 * Execute the SQL to Unihan db.
 *
 * A convenient wrapper of <a href="http://www.sqlite.org/c3ref/exec.html">sqlite3_exec()</a>.
 * @param sqlClause SQL command to be passed to Unihan db.
 * @param callback callback function for each match record, can be NULL.
 * @param callbackOption option for callback function, can be NULL.
 * @param errMsg_ptr pointer for error message.
 * @return <a href="http://www.sqlite.org/c3ref/c_abort.html">SQLite result codes</a>
 * @see <a href="http://www.sqlite.org/c3ref/exec.html">sqlite3_exec()</a>
 */
int unihanSql_exec(char *sqlClause, sqlite_exec_callback callback, 
 void *callbackOption,  char **errMsg_ptr);

/**
 * Obtains a SQL_Result table of SQL command.
 *
 * @param sqlClause SQL command to be passed to Unihan db.
 * @return an instance of SQL_Result that stores the results of the SQL command.
 * @see unihan_find_all_matched()
 */
SQL_Result *unihanSql_get_sql_result(const char *sqlClause);


/**
 * Parse the string argument as Unihan Locale.
 *
 * @param str 			the string to be parsed.
 * @return 			the UnihanLocate.
 */
UnihanLocale unihanLocale_parse(char *str);

/**
 * Returns a string representing a UnihanLocale.
 *
 * Note: the return string is static, not need to free it.
 *
 * @param locale		the UnihanLocale.
 * @return		a string representing the #UnihanLocale.
 */
const char *unihanLocale_to_string(UnihanLocale locale);

/**
 * Returns a string representing a UnihanLocale.
 *
 * Note: the return string is static, not need to free it.
 *
 * @param uRange		the UnihanRange.
 * @return		a string representing the #UnihanRange.
 */
const char *unihanRange_to_string(UnihanRange uRange);

/**
 * Parse the string argument as UnihanTable.
 *
 * @param tableName		the string to be parsed.
 * @return 			the UnihanTable.
 */
UnihanTable unihanTable_parse(const char * tableName);

/**
 * Returns a string representing a UnihanTable.
 *
 * Note: the return string is static, not need to free it.
 *
 * @param table		the UnihanTable.
 * @return		a string representing the #UnihanTable.
 */
const char *unihanTable_to_string(UnihanTable table);


/**
 * Returns the actual data table fields in an UnihanField array.
 *
 * Unlike unihanTable_get_fields(), this function will retrieves the actual fields
 * from the database. Hence, it is slower than unihanTable_get_fields().
 *
 * The returned UnihanField array is terminated by UNIHAN_INVALID_FIELD.
 * Note: use g_free to free the UnihanField array.
 *
 * @param table		the UnihanTable.
 * @return		all fields of the table in an UnihanField array.
 */
UnihanField* unihanTable_get_db_fields(UnihanTable table);

/**
 * Returns all fields of the table in an UnihanField array.
 *
 * Unlike unihanTable_get_db_fields(), this function returns the fields that
 * supposedly in the given data table.
 * It will not check the database, therefore it is faster than
 * unihanTable_get_db_fields();
 *
 * The returned UnihanField array is terminated by UNIHAN_INVALID_FIELD.
 * Note: use g_free to free the UnihanField array.
 *
 * @param table		the UnihanTable.
 * @return		all fields of the table in an UnihanField array.
 */
UnihanField* unihanTable_get_fields(UnihanTable table);

/**
 * Returns all primary key fields of the given table in an UnihanField array.
 *
 * The returned UnihanField array is terminated by UNIHAN_INVALID_FIELD.
 * Note: use g_free to free the UnihanField array.
 *
 * @param table		the UnihanTable.
 * @return		all primary key fields of the given table in an UnihanField array.
 */
UnihanField* unihanTable_get_primary_key_fields(UnihanTable table);
#endif /* UNIHAN_H */
