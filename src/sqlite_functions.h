/**
 * @file sqlite_functions.h
 * @brief SQLite suppporting data structures and functions.
 *
 * This header file lists supporting data structures and functions of SQLite.
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

#ifndef SQLITE_FUNCTIONS_H_
#define SQLITE_FUNCTIONS_H_
#include <sqlite3.h>
#include "str_functions.h"

/**
 * @defgroup SQL_fileAccessFlags SQL file access flags.
 * @{
 * @name SQL file access flags.
 *
 * These flags are for SQLite 3.3.X and earlier, as those versions do not have following definitions.
 * @{
 */

#ifndef SQLITE_OPEN_READONLY
/**
 * The database is opened for reading only.
 */
#define SQLITE_OPEN_READONLY         0x00000001
#endif

#ifndef SQLITE_OPEN_READWRITE
/**
 * The database is opened for reading and writing.
 */
#define SQLITE_OPEN_READWRITE        0x00000002
#endif

#ifndef SQLITE_OPEN_CREATE
/**
 * The database is created if it does not already exist.
 *
 * This flag indicates that the database should be created if it does not
 * already exist. Usually use with \c SQLITE_OPEN_READWRITE.
 *
 * The flags for sqlite3_open() are <code>SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE</code>.
 */
#define SQLITE_OPEN_CREATE           0x00000004
#endif

/**
 * @}
 * @}
 */


/**
 * @defgroup SQL_initialParameter SQL_Result initial parameters.
 * @{
 * @name SQL_Result initial parameters.
 *
 * These parameters define the initial size of SQL_Result.
 * Change them by define -D&lt;parameter&gt;=&lt;param_value&gt; flag in CC.
 * @{
 */
#ifndef SQL_RESULT_FIELD_CHUNK_SIZE
/**
 * Chunk size for  field names.
 */
#   define SQL_RESULT_FIELD_CHUNK_SIZE 2048
#endif

#ifndef SQL_RESULT_FIELD_ELEMENT_COUNT
/**
 * Number of fields.
 */
#   define SQL_RESULT_FIELD_ELEMENT_COUNT 128
#endif

#ifndef SQL_RESULT_FIELD_CONST_COUNT
/**
 * Number of constant fields.
 * Normally you don't need to change this.
 */
#   define SQL_RESULT_FIELD_CONST_COUNT 0
#endif

#ifndef SQL_RESULT_RESULT_CHUNK_SIZE
/**
 * Chunk size for result names.
 */
#   define SQL_RESULT_RESULT_CHUNK_SIZE 65536
#endif

#ifndef SQL_RESULT_RESULT_ELEMENT_COUNT
/**
 * Number of results. It should be rol_count * col_count.
 */
#   define SQL_RESULT_RESULT_ELEMENT_COUNT 512
#endif

/**
 * @}
 * @}
 */

/**
 * Callback function prototype of  SQL execution (sqlite3_exec).
 */
typedef gint (*sqlite_exec_callback)(gpointer user_option,gint col_num,gchar **results,gchar **col_names);

/**
 * Callback function prototype of error handling for sqlite_exec_handle_error().
 *
 * This function prototype abstracts the sqlite_exec_handle_error() error
 * handling functions.
 *
 * A implementing function will be called if an error occurs in sqlite_exec_handle_error().
 * The return value will be the return value of sqlite_exec_handle_error().
 *
 * Return the argument \a error_code if implementing function does not need to tolerate error.
 *
 * @param db The \a db from from sqlite_exec_handle_error().
 * @param sqlClause The original \a sqlClause from from sqlite_exec_handle_error().
 * @param error_code Return value of sqlite3_exec().
 * @param error_msg Error message from sqlite3_exec().
 * @param error_option Other option that the callback function needs, come
 * from error_option of sqlite_exec_handle_error() .
 * @return new error code or \a error_code
 */
typedef gint (*sqlite_error_callback)(sqlite3 *db, const gchar *sqlClause, gint error_code, const gchar *error_msg, gpointer error_option);


/**
 * Open a sqlite database.
 *
 * This function is very similar to sqlite3_open_v2(). Except:
 * -# This function does not have argument \a zVfs.
 * -# It provide SQL file access \a flags for SQLite 3.3.X and eariler.
 *
 * @param filename The SQLite database to be opened.
 * @param ppDb Returned pointer to database connection handle.
 * @param flags SQL file access flags, see SQL_fileAccessFlags.
 * @return SQLITE_OK if success; otherwise returns corresponding
 * <a href="http://www.sqlite.org/c3ref/c_abort.html">SQLite error code</a>.
 *
 * @see sqlite3_open()
 * @see sqlite3_open_v2()
 * @see SQL_fileAccessFlags.
 */
gint sqlite_open(const gchar *filename,  sqlite3 **ppDb,  gint flags);

/**
 * Data structure that holds the result of SQL functions and command.
 *
 * Note that returned results are represented in one-dimension.
 * For example, if the returned results are:
 *
 * <table>
 * <tr><th>Name</th><th>Weight</th></tr>
 * <tr><td>Mary</td><td>50</td></tr>
 * <tr><td>John</td><td>70</td></tr>
 * <tr><td>Sumo</td><td>120</td></tr>
 * </table>
 * result[0] stores "Mary", result[1] stores "50",
 * result[2] stores "John", result[3] stores "70",
 * result[4] stores "Sumo", result[5] stores "120".
 *
 * Where result[X] is a short expression of \c stringList_index(resultList,x).
 *
 * @see sqlite_result_new()
 * @see sqlite_result_free().
 */
typedef struct {
    StringList *fieldList;      //!< StringList that holds returned fields.
    StringList *resultList;     //!< StringList that holds returned results.
    gint colCount;		//!< Column count. Value 0 usually implied that no matched results.
    gint execResult;		//!< sqlite3_exec result code. Initial value is -1, which means the result is not ready.
    gchar *errMsg;		//!< Eroor messages from sqlite3_exec().
} SQL_Result;

/**
 * New a SQL_Result instance.
 *
 * @return the newly allocated SQL_Result instance.
 */
SQL_Result *sql_result_new();

/**
 * Free a SQL_Result instance.
 *
 * @param sResult SQL_Result to be freed.
 * @param freeResult TRUE for free the whole SQL_Result; while FALSE keep the \a sResult->resultList but free everything else.
 * @return NULL if \a freeResult is TRUE; sResult->resultList if \a freeResult is FALSE.
 */
StringList *sql_result_free(SQL_Result *sResult, gboolean freeResult);

/**
 * Count the matches returned by SQL clause.
 *
 * The error message passed back through the \a errMsg is held in memory obtained from sqlite3_malloc().
 * To avoid a memory leak, the calling application should call sqlite3_free() on any error message returned
 * through the \a errMsg parameter when it has finished using the error message.
 *
 * @param db The database.
 * @param sqlClause SQL clause.
 * @param errMsg_ptr The error message will be written here. Free it with sqlite3_free().
 * @return 0 if no matches found. Positive number is number of  matched founded. Negative number is  sqlite3_exec result code multiplied by -1.
 */
gint sqlite_count_matches(sqlite3 *db,const gchar * sqlClause,gchar **errMsg_ptr);

/**
 * An sqlite error callback function that prgint all error message except
 * constragint error.
 *
 * This function is just like sqlite_error_callback_print_message(),
 * except the constragint error messages are hidden. This is useful
 * when the invalid records (which do not meet the constraint) are expected
 * and skipped.
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
 * @see sqlite_error_callback_print_message()
 */
gint sqlite_error_callback_hide_constraint_error(sqlite3 *db, const gchar *sqlClause, gint error_code,
	const gchar *error_msg, gpointer prompt);

/**
 * An sqlite error callback function that prgint all error message except
 * prgint constragint error as warning.
 *
 * This function is just like sqlite_error_callback_hide_constraint_error(),
 * except the constragint error messages are printed as warning.
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
 * @see sqlite_error_callback_print_message()
 */
gint sqlite_error_callback_show_constraint_warning(sqlite3 *db, const gchar *sqlClause, gint error_code,
	const gchar *error_msg, gpointer prompt);

/**
 * An sqlite error callback function that prgint error messages.
 *
 * This function is an implementation of sqlite_error_callback,
 * which can be called by sqlite_exec_handle_error().
 *
 * It outputs error message in following format:
 *
 * \a prompt: Error on SQL statement: \a sqlClause.
 * Error code: \a error_code message: \a error_msg.
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
gint sqlite_error_callback_print_message(sqlite3 *db, const gchar *sqlClause, gint error_code,
	const gchar *error_msg, gpointer prompt);


/**
 * Sqlite exec function with error handling.
 *
 * This function adds error handle to sqlite3_exec().
 *
 * It calls sqlite3_exec() for DB operations.
 * When encounter error, \a error_func will be called for error handling.
 * See sqlite_error_callback for the function prototype.
 *
 *
 * @param db Database for DB operation.
 * @param sqlClause SQL caluse
 * @param exec_func Callback function for sqlite3_exec().
 * @param exec_option Option for \a exec_func.
 * @param error_func Error handling callback function.
 * @param error_option Option for \a err_func
 * @return <a href="http://www.sqlite.org/c3ref/c_abort.html">SQLite result codes</a>
 * @see <a href="http://www.sqlite.org/c3ref/exec.html">sqlite3_exec()</a>
 * @see sqlite_exec_callback
 * @see sqlite_error_callback
 * @see sqlite_error_callback_print_message()
 * @see sqlite_error_callback_hide_constraint_error()
 */
gint sqlite_exec_handle_error(sqlite3 *db, const gchar *sqlClause, sqlite_exec_callback exec_func,
	gpointer exec_option, sqlite_error_callback error_func, gpointer error_option);

/**
 * Get the results of SQL clause.
 *
 * @param db The database.
 * @param sqlClause SQL clause.
 * @return SQL_Result that stores the results.
 */
SQL_Result *sqlite_get_sql_result(sqlite3 *db, const gchar *sqlClause);

/**
 * Get the list of table names in the database.
 *
 * @param db The database.
 * @return SQL_Result that stores the results. Specifically, in \c resultList.
 */
SQL_Result *sqlite_get_tableNames(sqlite3 *db);

/**
 * Get the fields of result table of a SQL clause.
 *
 * The result code is store in execResult_ptr, calling application should provide a int-type variable
 * to store the result code.
 *
 * The error message passed back through the \a errMsg is held in memory obtained from sqlite3_malloc().
 * To avoid a memory leak, the calling application should call sqlite3_free() on any error message returned
 * through the \a errMsg parameter when it has finished using the error message.
 *
 * @param db The database.
 * @param sqlClause SQL clause.
 * @param execResult_ptr The result code will be written here.
 * @param errMsg_ptr The error message will be written here.
 * @return SQL_Result that stores the results.
 */
StringList *sqlite_get_fieldNames(sqlite3 *db,const gchar * sqlClause, gint *execResult_ptr, gchar **errMsg_ptr);

/*==============================================================
 * signed<->unsigned conversion.
 */

/**
 * Return the value as signed string.
 *
 * sqlite3_value_text() returns unsigned gchar array, unfortunately,
 * this is not expected for most of string functions.
 * This function return the value as a signed string.
 *
 * @param value the value from SQLite.
 * @return a newly allocated signed string that stores the value. Free it with sqlite3_free().
 * @see sqlite_value_signed_text_buffer()
 */

gchar *sqlite_value_signed_text(sqlite3_value *value);

/**
 * Store the value as signed string to provided buffer.
 *
 * It is similar with sqlite3_value_text(), except developers can provide their own buffer space to s
 * \note This function does not check the buffer overflow, it is developers' responsibility
 * to ensure the provided buffer has enough space.
 *
 * @param buf the provided buffer.
 * @param value the value from SQLite.
 * @return same as \a buf.
 * @see sqlite_value_signed_text()
 */
gchar *sqlite_value_signed_text_buffer(gchar *buf,sqlite3_value *value);

/*==============================================================
 * SQL scalar functions.
 */

/**
 * Create a SQL scalar function that combines columns into a specified format.
 *
 * This function creates a SQL scalar function that combines columns into a specified format.
 * The first argument of that scalar function is \c format, the rest arguments are columns to be combined.
 *
 * @param db The Db connection which the scalar function be added on.
 * @param function_name Name for the SQL scalar function.
 * @return  SQLITE_OK if success; SQLITE_ERROR if the function name is longer than 255 bytes.
 * @see string_formatted_combine().
 */
gint sqlite_create_string_formatted_combine_scalar_function(sqlite3 *db, const gchar *function_name);

/*==============================================================
 * SQL aggregation functions.
 */

/**
 * Create a SQL aggregation function that concatenates string values of a column.
 *
 * This function creates a SQL aggregation function that concatenates string values of a column.
 *
 * @param db The Db connection which the aggregation function be added on.
 * @param function_name Name for the SQL aggregation function.
 * @return  SQLITE_OK if success; SQLITE_ERROR if the function name is longer than 255 bytes.
 */
gint sqlite_create_concat_aggregation_function(sqlite3 *db, const gchar *function_name);

#endif /* SQLITE_FUNCTIONS_H_ */

