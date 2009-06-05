/** 
 * @file Unihan_types.h
 * @brief Data types used in libUnihan.
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
#ifndef UNIHAN_TYPES_H_
#define UNIHAN_TYPES_H_
#include <glib.h>
#include "sqlite_functions.h"
#include "str_functions.h"
#include "Unihan_enum.h"

/**
 * @defgroup UnihanTable Unihan Table
 * @{
 * @name Unihan Table
 *
 * An Unihan table usually stores 2 or more fields,
 * one is always UNIHAN_FIELD_CODE ("code"),
 * UCS4 encoding of the character, 
 * and the other fields stores parts of Unihan tag value.
 *
 * Normally, each Unihan tag has a corresponding table, for example, 
 * UNIHAN_TABLE_kDEFINITION ("kDefinitionTable") has UNIHAN_FIELD_CODE and
 * UNIHAN_FIELD_kDEFITION which stores the value of the kDefinition tag.
 *
 * If a tag value is splittable and the parts are often utilized, 
 * the value is store in multiple fields.
 * For example, tag kHanyuPinlu has 2 parts, pinyin and its Pinlu (frequency).
 * Thus table UNIHAN_TABLE_kHANYU_PINLU ("kHanyuPinluTable")  has three fields:
 * UNIHAN_FIELD_CODE, UNIHAN_FIELD_PINYIN, and UNIHAN_FIELD_PINYIN_FREQ,
 * where UNIHAN_FIELD_PINYIN and UNIHAN_FIELD_PINYIN_FREQ store pinyin and 
 * its frequency respectively.
 * 
 * Some Unihan tag values consist optional fields, that is,
 * the fields that do not always have values.
 * Putting all these fields in one table violate the 1st normal form (no null fields).
 * To keep tables normalized, two types of tables are employed:
 * "main" tables  hold compulsory fields;
 * while "extra" tables  hold primary key fields 
 * and optional field.
 *
 * For example, value of tag kIRG_GSource can splits to 
 * compulsory field UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME and 
 * optional field UNIHAN_FIELD_IRG_SOURCE_MAPPING.
 * Tag values are stored in two tables:
 * the "main" table UNIHAN_TABLE_IRG_SOURCE stores UNIHAN_FIELD_CODE and UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME;
 * while the "extra" table UNIHAN_TABLE_IRG_SOURCE_EXTRA stores 
 * primary key fields (UNIHAN_FIELD_CODE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME), and the optional field
 * UNIHAN_FIELD_IRG_SOURCE_MAPPING.
 * Data structure of Unihan Field.
 *
 */
typedef gint UnihanTable;


/**
 * libUnihan table name.
 *
 * String representation of Unihan table.
 *
 * @since libUnihan 1.0
 */
typedef gchar UnihanTableName;

/** @} */
/** @} */

/**
 * Unihan Field Id.
 *
 * Fields are vital cores of libUnihan. Field are needed to perform queries and other operation.
 * For example, to get the pronunciation of "說",
 * fields \c utf8 and \c kMandarin should be specified in \c unihan_query.
 *
 * There are many types of fields.
 * In terms of database scheme, there are <b>real fields</b> and <b>pseudo fields</b>.
 * Real fields represent columns in  database tables; while pseudo fields on the other hand,
 * are derived from database functions and views.
 *
 * In terms of the origin, there are <b>original fields</b> and <b>supporting fields</b>.
 * Original fields directly come from Unicode's original data -- Unihan.txt;
 * while supporting fields do not exist in Unihan.txt, 
 * they either hold parts of the value from original Unihan tags, or provide convenient 
 * aliases for complex statements.
 */
typedef gint UnihanField;

/**
 * libUnihan field name.
 *
 * String representation of Unihan field, excluding the table name.
 *
 * @since libUnihan 1.0
 */
typedef gchar UnihanFieldName;


/**
 * Structure for field-table pair.
 *
 * This struct stores a pair of UnihanField and UnihanTable.
 */
typedef struct {
    UnihanField field; //!< Field Id.
    UnihanTable table; //!< Table Id.
} UnihanFieldTablePair;


/**
 * libUnihan full field name.
 *
 * String representation of Unihan field,
 * Note that field name does not include table name.
 *
 * @since libUnihan 1.0
 */
typedef struct{
    UnihanTableName *tableName;
    UnihanFieldName *fieldName;
} UnihanFullFieldName;

/**
 * Struct of Field Properties.
 *
 * This struct defines the properties of a field, include the field name, and 
 * field flags which are described in @ref Unihan_Field_Flags.
 */
typedef struct {
    const UnihanFieldName *fieldName;	//!< Field Name.
    guint flags;		//!< Combined Unihan field flags.
} UnihanFieldProperties;

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
 * @name Unihan query options.
 *
 * Unihan query options.
 * 
 * Unihan query option is composed by various option flags which
 * controls the query processing or output format.
 *
 * Since libUnihan 1.0, pinyin accent format definitions are replaced 
 * by Pinyin_Format_Flag, and zhuyin tone mark format definitions are  
 * replaced by Zhuyin_Format_Flag. Following table shows the conversion:
 *
 * <table border>
 * <tr><th>&lt;=0.5.X</th><th>&gt;=0.9.9</th></tr>
 * <tr><td><code>UNIHAN_QUERY_OPTION_PINYIN_TONE_ACCENT, \c UNIHAN_QUERY_OPTION_PINYIN_FORMAT_MASK</code></td>
 *     <td><code>UNIHAN_QUERY_OPTION_PINYIN_FORMAT_FLAGS_START, UNIHAN_QUERY_OPTION_PINYIN_FORMAT_FLAGS_MASK</code></td>
 * </tr>   
 * <tr><td><code>UNIHAN_QUERY_OPTION_ZHUYIN_FORMAT_MASK</code></td>
 *     <td><code>UNIHAN_QUERY_OPTION_ZHUYIN_FORMAT_FLAGS_START, UNIHAN_QUERY_OPTION_ZHUYIN_FORMAT_FLAGS_MASK</code></td>
 * </tr>
 * </table>
 * @{
 */
typedef guint UnihanQueryOption;		//!< Data structure that holds Unihan query options.
#define UNIHAN_QUERY_OPTION_LIKE		1   	//!< Using SQL LIKE in WHERE expression.
#define UNIHAN_QUERY_OPTION_SCALAR_STRING	1 << 1	//!< Show UCS4 code as scalar string -- "U+xxxx".
#define UNIHAN_QUERY_OPTION_UTF8    		1 << 2  //!< Show UCS4 code as corresponding UTF8 string. @since libUnihan 1.0
#define UNIHAN_QUERY_OPTION_SHOW_GIVEN_FIELD    1 << 3  //!< Show the given field in results.
#define UNIHAN_QUERY_OPTION_PINYIN_FORMAT_FLAGS_START   4  //!< Starting bit of pinyin format flags. @since libUnihan 1.0
#define UNIHAN_QUERY_OPTION_PINYIN_FORMAT_FLAGS_MASK  31 << UNIHAN_QUERY_OPTION_PINYIN_FORMAT_FLAGS_START  //!< Mask for pinyin format flags. @since libUnihan 1.0
#define UNIHAN_QUERY_OPTION_ZHUYIN_FORCE_DISPLAY  1 << 10 //!< Force Zhuyin display.
#define UNIHAN_QUERY_OPTION_ZHUYIN_FORMAT_FLAGS_START  11  //!< Starting bit of zhuyin format flags. @since libUnihan 1.0
#define UNIHAN_QUERY_OPTION_ZHUYIN_FORMAT_FLAGS_MASK  15 << UNIHAN_QUERY_OPTION_ZHUYIN_FORMAT_FLAGS_START  //!< Mask for zhuyin format flags. @since libUnihan 1.0

#define UNIHAN_QUERY_OPTION_DEFAULT (UNIHAN_QUERY_OPTION_PINYINYIN_FORMAT_FLAGS_DEFAULT << UNIHAN_QUERY_OPTION_PINYIN_FORMAT_FLAGS_START) \
    |  (ZHUYIN_FORMAT_FLAGS_DEFAULT << UNIHAN_QUERY_OPTION_ZHUYIN_FORMAT_FLAGS_START) \
//!< Default options, Pinyin format is Unihan; and Zhuyin format is Original.
/** @} */

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
 * Exporting format for pseudo fields.
 *
 */
typedef struct{
    UnihanField pseudoField;			//!< Pseudo field to be exported.
    UnihanFieldTablePair tableFields[10];	//!< Required tables and fields.
    gchar resultSqlPattern[100];		//!< SQL command pattern for pseudo field export.
    gchar *fromSqlPattern;			//!< SQL command that come after 'FROM' keyword (excluding 'FROM').
} UnihanPseudoFieldExportFormat;



#endif /* UNIHAN_TYPES_H_ */

