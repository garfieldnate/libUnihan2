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
 * The database is opened for reading and writing, and is creates it if  it does not already exist. 
 *
 * This is the behavior that is always used for  sqlite3_open().
 */
#define SQLITE_OPEN_CREATE           0x00000004
#endif

/**
 * @}
 */

/**
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

#ifndef SQL_RESULT_RESULT_CONST_COUNT
/**
 * Number of constant results.
 */
#   define SQL_RESULT_RESULT_CONST_COUNT 0
#endif 
/**
 * @}
 */


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
    int colCount;		//!< Column count. Value 0 usually implied that no matched results.
    int execResult;		//!< sqlite3_exec result code. Initial value is -1, which means the result is not ready.
    char *errMsg;		//!< Eroor messages from sqlite3_exec().
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
int sqlite_count_matches(sqlite3 *db,const char * sqlClause,char **errMsg_ptr);

/**
 * Get the results of SQL clause.
 *
 * @param db The database. 
 * @param sqlClause SQL clause.
 * @return SQL_Result that stores the results.
 */
SQL_Result *sqlite_get_sql_result(sqlite3 *db, const char *sqlClause);

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
StringList *sqlite_get_fieldNames(sqlite3 *db,const char * sqlClause, int *execResult_ptr, char **errMsg_ptr);

/**
 * Return the value as signed string.
 *
 * sqlite3_value_text() returns unsigned char array, unfortunately,
 * this is not expected for most of string functions.
 * This function return the value as a signed string.
 *
 * @param value the value from SQLite.
 * @return a newly allocated signed string that stores the value. Free it with sqlite3_free().
 * @see sqlite_value_signed_text_buffer()
 */

char *sqlite_value_signed_text(sqlite3_value *value);

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
char *sqlite_value_signed_text_buffer(char *buf,sqlite3_value *value);

#endif /* SQLITE_FUNCTIONS_H_ */

