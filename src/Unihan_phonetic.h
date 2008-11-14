/** 
 * @file Unihan_phonetic.h
 * @brief Phonetic symbols (Pinyin and Zhuyin) processing functions.
 * 
 * This header file lists the functions for Pinyin and Zhuyin processing,
 * such as conversion between HanYu pinyin conversion C functions, and
 * corresponding SQL scalar functions.
 *
 * Pinyin is displayed and stored as uppercase, which is same with kMandarin 
 * in Unihan.
 *
 * Note that this header is included in Unihan.h, 
 * so no need to includes it explicitly if Unihan.h is also included.
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

#ifndef UNIHAN_PHONETIC_H_
#define UNIHAN_PHONETIC_H_

#include <sqlite3.h>

/**
 * Maximum length of pinyin in byte.
 */
#define PINYIN_MAX_LENGTH 9

/**
 * Maximum length of zhuyin in byte.
 */
#define ZHUYIN_MAX_LENGTH 13

/**
 * Zhuyin symbol.
 */
typedef gunichar  Zhuyin_Symbol;

/**
 * Pronunciation in Zhuyin UTF-8 string.
 */
typedef char Zhuyin;

/**
 * Pronunciation in Pinyin UTF-8 string.
 */
typedef char Pinyin;



/**
 * Enumeration of Zhuyin symbols.
 *
 * This enumeration lists the Zhuyin symbols, including the symbols for tone mark.
 * Corresponding Pinyin phonemes can also be located using these Ids.
 *
 * @see pinyin_phoneme_from_id()
 * @see pinyin_phoneme_get_id()
 * @see zhuyin_Symbol_from_id()
 * @see zhuyin_Symbol_get_id()
 *
 */
typedef enum {
    ZHUYIN_INVALID_SYMBOL= -1, //!< Invalid Zhuyin Symbol.
    ZHUYIN_SYMBOL_B,         //!< Zhuyin symbol 'ㄅ' 
    ZHUYIN_SYMBOL_P,         //!< Zhuyin symbol 'ㄆ'
    ZHUYIN_SYMBOL_M,         //!< Zhuyin symbol 'ㄇ'
    ZHUYIN_SYMBOL_F,         //!< Zhuyin symbol 'ㄈ'
    ZHUYIN_SYMBOL_D,         //!< Zhuyin symbol 'ㄉ'
    ZHUYIN_SYMBOL_T,         //!< Zhuyin symbol 'ㄊ'
    ZHUYIN_SYMBOL_N,         //!< Zhuyin symbol 'ㄋ'
    ZHUYIN_SYMBOL_L,         //!< Zhuyin symbol 'ㄌ'
    ZHUYIN_SYMBOL_G,         //!< Zhuyin symbol 'ㄍ'
    ZHUYIN_SYMBOL_K,         //!< Zhuyin symbol 'ㄎ'
    ZHUYIN_SYMBOL_H,         //!< Zhuyin symbol 'ㄏ'
    ZHUYIN_SYMBOL_J,         //!< Zhuyin symbol 'ㄐ'
    ZHUYIN_SYMBOL_Q,         //!< Zhuyin symbol 'ㄑ'
    ZHUYIN_SYMBOL_X,         //!< Zhuyin symbol 'ㄒ'
    ZHUYIN_SYMBOL_ZH,        //!< Zhuyin symbol 'ㄓ'
    ZHUYIN_SYMBOL_CH,        //!< Zhuyin symbol 'ㄔ'
    ZHUYIN_SYMBOL_SH,        //!< Zhuyin symbol 'ㄕ'
    ZHUYIN_SYMBOL_R,         //!< Zhuyin symbol 'ㄖ'
    ZHUYIN_SYMBOL_Z,         //!< Zhuyin symbol 'ㄗ'
    ZHUYIN_SYMBOL_C,         //!< Zhuyin symbol 'ㄘ'
    ZHUYIN_SYMBOL_S,         //!< Zhuyin symbol 'ㄙ'
    ZHUYIN_SYMBOL_I,        //!< Zhuyin symbol 'ㄧ'
    ZHUYIN_SYMBOL_U,        //!< Zhuyin symbol 'ㄨ'
    ZHUYIN_SYMBOL_U_DIAERESIS,       //!< Zhuyin symbol 'ㄩ'
    ZHUYIN_SYMBOL_A,         //!< Zhuyin symbol 'ㄚ'
    ZHUYIN_SYMBOL_O,         //!< Zhuyin symbol 'ㄛ'
    ZHUYIN_SYMBOL_E,         //!< Zhuyin symbol 'ㄜ'
    ZHUYIN_SYMBOL_E_CIRCUMFLEX,     //!< Zhuyin symbol 'ㄝ'
    ZHUYIN_SYMBOL_AI,        //!< Zhuyin symbol 'ㄞ'
    ZHUYIN_SYMBOL_EI,        //!< Zhuyin symbol 'ㄟ'
    ZHUYIN_SYMBOL_AO,        //!< Zhuyin symbol 'ㄠ'
    ZHUYIN_SYMBOL_OU,        //!< Zhuyin symbol 'ㄡ'
    ZHUYIN_SYMBOL_AN,        //!< Zhuyin symbol 'ㄢ'
    ZHUYIN_SYMBOL_EN,        //!< Zhuyin symbol 'ㄣ'
    ZHUYIN_SYMBOL_ANG,       //!< Zhuyin symbol 'ㄤ'
    ZHUYIN_SYMBOL_ENG,       //!< Zhuyin symbol 'ㄥ'
    ZHUYIN_SYMBOL_ER,        //!< Zhuyin symbol 'ㄦ'
    ZHUYIN_SYMBOL_1,         //!< Zhuyin 1st tone mark 'ˉ'
    ZHUYIN_SYMBOL_2,         //!< Zhuyin 2nd tone mark 'ˊ'
    ZHUYIN_SYMBOL_3,         //!< Zhuyin 3rd tone mark 'ˇ'
    ZHUYIN_SYMBOL_4,         //!< Zhuyin 4th tone mark 'ˋ'
    ZHUYIN_SYMBOL_NEUTRAL,   //!< Zhuyin neutral (5th) tone mark '˙'
} Zhuyin_Symbol_Id;

/**
 * Total number of support Zhuyin symbols.
 */
#define ZHUYIN_SYMBOL_COUNT ZHUYIN_SYMBOL_NEUTRAL + 1 

/**
 * An array of Zhuyin symbols.
 */
extern const Zhuyin_Symbol ZHUYIN_SYMBOL_LIST[];

/**
 * Enumeration of Pinyin accent (not tone mark) handling modes.
 *
 * There are two Pinyin symbols with accents, diaeresis U (Ü,ㄩ), and circumflex E (Ê,ㄝ) .
 * As the their pronunciations are different from U and E.
 *
 * In Romanization of Chinese (ISO 7098:1991), under certain circumstances,
 * accents can be omitted, such as JÜ -&gt; JU , QÜ -&gt;QU. This is adopted in PRC education system.
 * Use PINYIN_ACCENT_ORIGINAL for this purpose.
 *
 * Unihan project does not have circumflex E (Ê), the other is same with ISO 7098.
 * Use PINYIN_ACCENT_UNIHAN for Unihan project.
 *
 * Because Ü is not on most of the keyboards, there are various ways to represent Ü.
 * For example, CEDICT use U: (PINYIN_ACCENT_TRAILING); while most of Chinese
 * input method use V as substitute (PINYIN_ACCENT_INPUT_METHOD).
 *
 * In English documents such as passport, the accent are usually ignores, use 
 * PINYIN_ACCENT_NONE for this purpose. 
 *
 * Preserving accents unconditionally makes conversion and education easier, 
 * use PINYIN_ACCENT_ALWAYS for this purpose.
 *
 * Note that this enumeration is not for the pinyin tone mark.
 * See pinyin_convert_accent_format() pinyin tone mark handling.
 *
 * @see pinyin_convert_accent_format()
 */
typedef enum{
    PINYIN_ACCENT_ALWAYS,   //!< Ü is always represented as Ü, Ê is always represented as Ê. 
    PINYIN_ACCENT_ORIGINAL, //!< MOE CN standard ISO 7098:1991.
    PINYIN_ACCENT_UNIHAN,   //!< Ü is represented as Ü, Ê is represented as E.
    PINYIN_ACCENT_TRAILING, //!< Ü is represented as U:, Ê is represented as E.
    PINYIN_ACCENT_INPUT_METHOD,  //!< Ü is represented as V, Ê is represented as E.
    PINYIN_ACCENT_NONE      //!< Ü is represented as U, Ê is represented as E.
} Pinyin_Accent_Format;


/**
 * Enumeration of Zhuyin tone mark handling.
 * Originally, the neutral (fifth) tone mark of zhuyin is put in the front, while the first tone mark is omitted.
 * Use ZHUYIN_TONEMARK_ORIGINAL for this.
 *
 * However, for Zhuyin based input method, the neutral is put in the back.
 * Use ZHUYIN_TONEMARK_INPUT_METHOD for this.
 *
 * If preserving tonemark is desireable, then 
 * use ZHUYIN_TONEMARK_ALWAYS, in which the first tone is not omitted,
 * otherwise is same with ZHUYIN_TONEMARK_INPUT_METHOD.
 *
 * If numerical tone mark is desired, use ZHUYIN_TONEMARK_NUMERICAL.
 *
 * @see zhuyin_convert_toneMark_format()
 */
typedef enum{
    ZHUYIN_TONEMARK_ALWAYS,   //!<  Neutral (fifth) tone mark is put in the end, while the first tone mark is kept.
    ZHUYIN_TONEMARK_ORIGINAL,   //!< Neutral (fifth) tone mark is put in the front, while the first tone mark is omitted.
    ZHUYIN_TONEMARK_INPUT_METHOD,  //!< Neutral (fifth) tone mark is put in the front, while the first tone mark is omitted.
    ZHUYIN_TONEMARK_NUMERICAL,  //!< Tone mark are represented as numerical, in the end of Zhuyin.
} Zhuyin_ToneMark_Format;


/*==========================================================
 * Pinyin functions.
 */

/**
 * New a Pinyin instance.
 *
 * This function allocate a new Pinyin instance.
 * Non pinyin_str will be copied to the newly allocated Pinyin instance and
 * converted to uppercase.
 * Note that the Pinyin instance only hold #PINYIN_MAX_LENGTH bytes, 
 * including the EOL ('\0') character. Longer pinyin will be truncated.
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param pinyin_str the Pinyin in string, NULL for blank instance.
 * @return new Pinyin instances.
 */
Pinyin *pinyin_new(const char *pinyin_str);


/**
 * Return the explicit-specified tone of Pinyin.
 *
 * This function finds and returns the explicit-specified tone of pinyin.
 * Thus 0 will be returned if pinyin does not have any explicit-specified tone.
 * 
 * This function acts this way in order to accommodate 
 * the SQL LIKE query such as <code>... WHERE kMandarin LIKE 'KE%'</code>.
 *
 * Sometimes, 5th tone mark is omitted, please convert the value 0 to 5
 * if this is the case. 
 *
 * @param pinyin the pinyin instance to be stripped.
 * @return the tone id from 1 to 5 if the tone is explicit-specified, 0
 * otherwise.
 * @see pinyin_strip_tone()
 */
guint pinyin_get_tone(const Pinyin* pinyin);

/**
 * Strip the tone mark of Pinyin and return explicit-specified the tone Id.
 *
 * This function strips the tone mark of pinyin,
 * otherwise is similar to pinyin_get_tone().
 *
 * @param pinyin the pinyin instance to be stripped.
 * @return the tone id from 1 to 5 if the tone is explicit-specified, 0
 * @see pinyin_get_tone()
 */
guint pinyin_strip_tone(Pinyin* pinyin);

/**
 * Add the tone mark to pinyin.
 *
 * This function add tone mark to zhuyin, existing tone will be removed before adding new tone.
 * If tone is 0, then existing tone will be removed, but no new tone will be added.
 * 
 * The result will be stored in pinyin, so backup it with strdup() or g_strdup() to keep the original.
 *
 * @param pinyin the pinyin instance to be processed.
 * @param tone the tone to be added.
 * @param useTrailNumber TRUE trailing number is preferred, FALSE to use traditional tonemark.
 */
void pinyin_add_tone(Pinyin* pinyin, guint tone, gboolean useTrailNumber);

/**
 * Convert a Pinyin to new accent formatReturn a newly allocated Pinyin instance which contains the converted content.
 *
 * Unlike pinyin_get_tone() and pinyin_strip_tone() which only identify the explicit-specified tone,
 * this function treats the unspecified tone as 5th tone,  unless SQL
 * wild characters '%' and '_' are encountered. 
 *
 * Use g_free to free the newly allocated instance.
 *
 * @param pinyin the Pinyin to be converted.
 * @param toFormat the Pinyin accent mode to be converted to.
 * @param useTrailNumber TRUE trailing number is preferred, FALSE to use traditional tonemark.
 * @return a newly allocated converted Pinyin instance.
 * @see zhuyin_to_pinyin()
 */
Pinyin *pinyin_convert_accent_format(const Pinyin *pinyin, Pinyin_Accent_Format toFormat, gboolean useTrailNumber);


/**
 * Pinyin to Zhuyin
 *
 * @param pinyin the Pinyin to be converted.
 * @param toFormat the Zhuyin tone mark mode.
 * @return a newly located Zhuyin instance.
 * @see zhuyin_convert_toneMark_format()
 */
Zhuyin *pinyin_to_zhuyin(const Pinyin* pinyin, Zhuyin_ToneMark_Format toFormat);

/*==========================================================
 * Zhuyin functions.
 */

/**
 * New a Zhuyin instance.
 *
 * This function allocate a new Zhuyin instance.
 * Non-NULL zhuyin_str will be copied to the new Zhuyin instance and 
 * converted to uppercase.
 * Note that the Zhuyin instance only holds #ZHUYIN_MAX_LENGTH bytes, 
 * including the EOL ('\0') character. Longer zhuyin will be truncated.
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param zhuyin_str the Zhuyin in string, NULL for blank instance.
 * @return new Zhuyin instances.
 */
Zhuyin *zhuyin_new(const char *zhuyin_str);


/**
 * Return the explicit-specified tone of Zhuyin.
 *
 * This function finds and returns the explicit-specified tone of zhuyin.
 * Thus 0 will be returned if zhuyin does not have any explicit-specified tone.
 * 
 * This function acts this way in order to accommodate 
 * the SQL LIKE query such as <code>... WHERE zhuyin LIKE 'ㄊㄧㄢ%'</code>.
 *
 * Sometimes, 1th tone mark is omitted, please convert the value 0 to 1
 * if this is the case. 
 *
 * @param zhuyin the zhuyin instance to be stripped.
 * @return the tone id from 1 to 5 if the tone is explicit-specified, 0
 * otherwise.
 * @see zhuyin_strip_tone()
 */
guint zhuyin_get_tone(const Zhuyin* zhuyin);


/**
 * Strip the tone mark of Zhuyin and return explicit-specified the tone Id.
 *
 * This function strips the tone mark of zhuyin,
 * otherwise is similar to zhuyin_get_tone().
 *
 * @param zhuyin the zhuyin instance to be stripped.
 * @return the tone id from 1 to 5 if the tone is explicit-specified, 0
 * @see zhuyin_get_tone()
 */
guint zhuyin_strip_tone(Zhuyin* zhuyin);

/**
 * Add the tone mark to zhuyin.
 *
 * This function add tone mark to zhuyin, existing tone will be removed before adding new tone.
 * If tone is 0, then existing tone will be removed, but no new tone will be added.
 * 
 * The result will be stored in zhuyin, so backup it with strdup() or g_strdup() to keep the original.
 *
 * @param zhuyin the zhuyin instance to be processed.
 * @param tone the tone to be added.
 * @param toFormat the Zhuyin tone mark mode to be converted to.
 */
void zhuyin_add_tone(Zhuyin* zhuyin, guint tone, Zhuyin_ToneMark_Format toFormat);

/**
 * Convert zhuyin to another tone mark format.
 *
 * Unlike zhuyin_get_tone() and zhuyin_strip_tone() which only identify the explicit-specified tone,
 * this function treats the unspecified tone as 1st tone,  unless SQL
 * wild characters '%' and '_' are encountered. 
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param zhuyin the Zhuyin to be converted.
 * @param toFormat the Zhuyin tone mark mode to be converted to.
 * @return the newly allocated Zhuyin instance that 
 * @see pinyin_to_zhuyin()
 */
Zhuyin *zhuyin_convert_toneMark_format(const Zhuyin* zhuyin, Zhuyin_ToneMark_Format toFormat);

/**
 * Zhuyin to Pinyin
 *
 * @param zhuyin the Zhuyin to be converted.
 * @param toFormat the Pinyin accent mode.
 * @param useTrailNumber TRUE trailing number is preferred, FALSE to use traditional tonemark.
 * @return a newly located Pinyin instance.
 * @see pinyin_convert_accent_format()
 */
Pinyin *zhuyin_to_pinyin(const Zhuyin* zhuyin, Pinyin_Accent_Format toFormat, gboolean useTrailNumber);


/*----------------------------------------------------------
 * Zhuyin symbol functions.
 */

/**
 * Return the Zhuyin symbol by its Id.
 * 
 *
 * @param id Zhuyin symbol Id.
 * @return the corresponding symbol, or 0 if the id is negative.
 */
Zhuyin_Symbol zhuyin_Symbol_from_id(Zhuyin_Symbol_Id id);


/**
 * Return the Id of a Zhuyin symbol
 * 
 * @param zSym  Zhuyin symbol.
 * @return the corresponding Id.
 */
Zhuyin_Symbol_Id zhuyin_Symbol_get_id(Zhuyin_Symbol zSym);

/**
 * Whether the zhuyin symbol is an initial.
 *
 * @param zSym  Zhuyin symbol.
 * @return TRUE if the zhuyin symbol is an initial, FALSE otherwise.
 */
gboolean zhuyin_Symbol_is_initial(Zhuyin_Symbol zSym);

/**
 * Whether the zhuyin symbol is an medial.
 *
 * @param zSym  Zhuyin symbol.
 * @return TRUE if the zhuyin symbol is an medial, FALSE otherwise.
 */
gboolean zhuyin_Symbol_is_medial(Zhuyin_Symbol zSym);

/**
 * Whether the zhuyin symbol is an final.
 *
 * @param zSym  Zhuyin symbol.
 * @return TRUE if the zhuyin symbol is an final, FALSE otherwise.
 */
gboolean zhuyin_Symbol_is_final(Zhuyin_Symbol zSym);

/**
 * Whether the zhuyin symbol is either a toneMark or number which indicates the tone.
 *
 * @param zSym  Zhuyin symbol.
 * @return TRUE if the zhuyin symbol is either a toneMark or number which indicates the tone, FALSE otherwise.
 */
gboolean zhuyin_Symbol_is_tone(Zhuyin_Symbol zSym);

/**
 * Return the tone id of given tone mark.
 *
 * @param zSym  Zhuyin symbol.
 * @return tone id if zSym is tone mark, 0 otherwise.
 */
guint zhuyin_Symbol_to_toneMark_id(Zhuyin_Symbol zSym);

/**
 * Return the tone mark of given tone id.
 *
 * @param toneMark_id  toneMark_id.
 * @return the Zhuyin symbol if id is between 1 to 5; returns 0 otherwise.
 */
Zhuyin_Symbol zhuyin_Symbol_from_toneMark_id(guint toneMark_id);

/**
 * Pinyin convert accent format scalar function for SQL command call.
 *
 * This function is meant to be called by sqlite3_create_function()
 * and used in SQL command. Do not use it directly.
 *
 * @param context The sqlite3_context.
 * @param argc Number of argument expected.
 * @param argv Arguments for this scalar function .
 */
void pinyin_convert_accent_format_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv);

/**
 * Pinyin to Zhuyin converting scalar function for SQL command call.
 *
 * This function is meant to be called by sqlite3_create_function()
 * and used in SQL command. Do not use it directly.
 *
 * @param context The sqlite3_context.
 * @param argc Number of argument expected.
 * @param argv Arguments for this scalar function .
 */
void pinyin_to_zhuyin_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv);

/**
 * Zhuyin convert accent format scalar function for SQL command call.
 *
 * This function is meant to be called by sqlite3_create_function()
 * and used in SQL command. Do not use it directly.
 *
 * @param context The sqlite3_context.
 * @param argc Number of argument expected.
 * @param argv Arguments for this scalar function .
 */
void zhuyin_convert_toneMark_format_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv);


/**
 * Zhuyin to Pinyin converting scalar function for SQL command call.
 *
 * This function is meant to be called by sqlite3_create_function()
 * and used in SQL command. Do not use it directly.
 *
 * @param context The sqlite3_context.
 * @param argc Number of argument expected.
 * @param argv Arguments for this scalar function .
 */
void zhuyin_to_pinyin_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv);

#endif /* UNIHAN_PHONETIC_H_ */
