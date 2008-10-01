/** 
 * @file Unihan_phonetic.h
 * @brief Phonetic symbols (PinYin and ZhuYin) processing functions.
 * 
 * This header file lists the functions for PinYin and ZhuYin processing,
 * such as conversion between HanYu pinyin conversion C functions, and
 * corresponding SQL scalar functions.
 *
 * PinYin is displayed and stored as uppercase, which is same with kMandarin 
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
 * Spaces that PinYin might occupy.
 *
 */
#define PINYIN_MAX_LENGTH 9

/**
 * Spaces that ZhuYin might occupy.
 */
#define ZHUYIN_MAX_LENGTH 13

/**
 * ZhuYin symbol.
 */
typedef gunichar  ZhuYin_Symbol;

/**
 * Pronunciation in ZhuYin UTF-8 string.
 */
typedef char ZhuYin;

/**
 * Pronunciation in PinYin UTF-8 string.
 */
typedef char PinYin;



/**
 * Enumeration of ZhuYin symbols.
 *
 * This enumeration lists the ZhuYin symbols, including the symbols for tone mark.
 * Corresponding PinYin phonemes can also be located using these Ids.
 *
 * @see pinYin_phoneme_from_id()
 * @see pinYin_phoneme_get_id()
 * @see zhuYin_Symbol_from_id()
 * @see zhuYin_Symbol_get_id()
 *
 */
typedef enum {
    ZHUYIN_INVALID_SYMBOL= -1, //!< Invalid ZhuYin Symbol.
    ZHUYIN_SYMBOL_B,         //!< ZhuYin symbol 'ㄅ' 
    ZHUYIN_SYMBOL_P,         //!< ZhuYin symbol 'ㄆ'
    ZHUYIN_SYMBOL_M,         //!< ZhuYin symbol 'ㄇ'
    ZHUYIN_SYMBOL_F,         //!< ZhuYin symbol 'ㄈ'
    ZHUYIN_SYMBOL_D,         //!< ZhuYin symbol 'ㄉ'
    ZHUYIN_SYMBOL_T,         //!< ZhuYin symbol 'ㄊ'
    ZHUYIN_SYMBOL_N,         //!< ZhuYin symbol 'ㄋ'
    ZHUYIN_SYMBOL_L,         //!< ZhuYin symbol 'ㄌ'
    ZHUYIN_SYMBOL_G,         //!< ZhuYin symbol 'ㄍ'
    ZHUYIN_SYMBOL_K,         //!< ZhuYin symbol 'ㄎ'
    ZHUYIN_SYMBOL_H,         //!< ZhuYin symbol 'ㄏ'
    ZHUYIN_SYMBOL_J,         //!< ZhuYin symbol 'ㄐ'
    ZHUYIN_SYMBOL_Q,         //!< ZhuYin symbol 'ㄑ'
    ZHUYIN_SYMBOL_X,         //!< ZhuYin symbol 'ㄒ'
    ZHUYIN_SYMBOL_ZH,        //!< ZhuYin symbol 'ㄓ'
    ZHUYIN_SYMBOL_CH,        //!< ZhuYin symbol 'ㄔ'
    ZHUYIN_SYMBOL_SH,        //!< ZhuYin symbol 'ㄕ'
    ZHUYIN_SYMBOL_R,         //!< ZhuYin symbol 'ㄖ'
    ZHUYIN_SYMBOL_Z,         //!< ZhuYin symbol 'ㄗ'
    ZHUYIN_SYMBOL_C,         //!< ZhuYin symbol 'ㄘ'
    ZHUYIN_SYMBOL_S,         //!< ZhuYin symbol 'ㄙ'
    ZHUYIN_SYMBOL_I,        //!< ZhuYin symbol 'ㄧ'
    ZHUYIN_SYMBOL_U,        //!< ZhuYin symbol 'ㄨ'
    ZHUYIN_SYMBOL_U_DIAERESIS,       //!< ZhuYin symbol 'ㄩ'
    ZHUYIN_SYMBOL_A,         //!< ZhuYin symbol 'ㄚ'
    ZHUYIN_SYMBOL_O,         //!< ZhuYin symbol 'ㄛ'
    ZHUYIN_SYMBOL_E,         //!< ZhuYin symbol 'ㄜ'
    ZHUYIN_SYMBOL_E_CIRCUMFLEX,     //!< ZhuYin symbol 'ㄝ'
    ZHUYIN_SYMBOL_AI,        //!< ZhuYin symbol 'ㄞ'
    ZHUYIN_SYMBOL_EI,        //!< ZhuYin symbol 'ㄟ'
    ZHUYIN_SYMBOL_AO,        //!< ZhuYin symbol 'ㄠ'
    ZHUYIN_SYMBOL_OU,        //!< ZhuYin symbol 'ㄡ'
    ZHUYIN_SYMBOL_AN,        //!< ZhuYin symbol 'ㄢ'
    ZHUYIN_SYMBOL_EN,        //!< ZhuYin symbol 'ㄣ'
    ZHUYIN_SYMBOL_ANG,       //!< ZhuYin symbol 'ㄤ'
    ZHUYIN_SYMBOL_ENG,       //!< ZhuYin symbol 'ㄥ'
    ZHUYIN_SYMBOL_ER,        //!< ZhuYin symbol 'ㄦ'
    ZHUYIN_SYMBOL_1,         //!< ZhuYin 1st tone mark 'ˉ'
    ZHUYIN_SYMBOL_2,         //!< ZhuYin 2nd tone mark 'ˊ'
    ZHUYIN_SYMBOL_3,         //!< ZhuYin 3rd tone mark 'ˇ'
    ZHUYIN_SYMBOL_4,         //!< ZhuYin 4th tone mark 'ˋ'
    ZHUYIN_SYMBOL_NEUTRAL,   //!< ZhuYin neutral (5th) tone mark '˙'
} ZhuYin_Symbol_Id;

/**
 * Total number of support ZhuYin symbols.
 */
#define ZHUYIN_SYMBOL_COUNT ZHUYIN_SYMBOL_NEUTRAL + 1 

/**
 * An array of ZhuYin symbols.
 */
extern const ZhuYin_Symbol ZHUYIN_SYMBOL_LIST[];

/**
 * Enumeration of PinYin accent (not tone mark) handling modes.
 *
 * There are two PinYin symbols with accents, diaeresis U (Ü,ㄩ), and circumflex E (Ê,ㄝ) .
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
 * See pinYin_convert_accent_format() pinyin tone mark handling.
 *
 * @see pinYin_convert_accent_format()
 */
typedef enum{
    PINYIN_ACCENT_ALWAYS,   //!< Ü is always represented as Ü, Ê is always represented as Ê. 
    PINYIN_ACCENT_ORIGINAL, //!< MOE CN standard ISO 7098:1991.
    PINYIN_ACCENT_UNIHAN,   //!< Ü is represented as Ü, Ê is represented as E.
    PINYIN_ACCENT_TRAILING, //!< Ü is represented as U:, Ê is represented as E.
    PINYIN_ACCENT_INPUT_METHOD,  //!< Ü is represented as V, Ê is represented as E.
    PINYIN_ACCENT_NONE      //!< Ü is represented as U, Ê is represented as E.
} PinYin_Accent_Format;


/**
 * Enumeration of ZhuYin tone mark handling.
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
 * @see zhuYin_convert_toneMark_format()
 */
typedef enum{
    ZHUYIN_TONEMARK_ALWAYS,   //!<  Neutral (fifth) tone mark is put in the end, while the first tone mark is kept.
    ZHUYIN_TONEMARK_ORIGINAL,   //!< Neutral (fifth) tone mark is put in the front, while the first tone mark is omitted.
    ZHUYIN_TONEMARK_INPUT_METHOD,  //!< Neutral (fifth) tone mark is put in the front, while the first tone mark is omitted.
    ZHUYIN_TONEMARK_NUMERICAL,  //!< Tone mark are represented as numerical, in the end of Zhuyin.
} ZhuYin_ToneMark_Format;


/*==========================================================
 * PinYin functions.
 */

/**
 * New a PinYin instance.
 *
 * This function allocate a new PinYin instance.
 * Non pinYin_str will be copied to the newly allocated PinYin instance and
 * converted to uppercase.
 * Note that the PinYin instance only hold #PINYIN_MAX_LENGTH bytes, 
 * including the EOL ('\0') character. Longer pinYin will be truncated.
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param pinYin_str the PinYin in string, NULL for blank instance.
 * @return new PinYin instances.
 */
PinYin *pinYin_new(const char *pinYin_str);


/**
 * Return the explicit-specified tone of PinYin.
 *
 * This function finds and returns the explicit-specified tone of pinYin.
 * Thus 0 will be returned if pinYin does not have any explicit-specified tone.
 * 
 * This function acts this way in order to accommodate 
 * the SQL LIKE query such as <code>... WHERE kMandarin LIKE 'KE%'</code>.
 *
 * Sometimes, 5th tone mark is omitted, please convert the value 0 to 5
 * if this is the case. 
 *
 * @param pinYin the pinYin instance to be stripped.
 * @return the tone id from 1 to 5 if the tone is explicit-specified, 0
 * otherwise.
 * @see pinYin_strip_tone()
 */
guint pinYin_get_tone(const PinYin* pinYin);

/**
 * Strip the tone mark of PinYin and return explicit-specified the tone Id.
 *
 * This function strips the tone mark of pinYin,
 * otherwise is similar to pinYin_get_tone().
 *
 * @param pinYin the pinYin instance to be stripped.
 * @return the tone id from 1 to 5 if the tone is explicit-specified, 0
 * @see pinYin_get_tone()
 */
guint pinYin_strip_tone(PinYin* pinYin);

/**
 * Add the tone mark to pinYin.
 *
 * This function add tone mark to zhuYin, existing tone will be removed before adding new tone.
 * If tone is 0, then existing tone will be removed, but no new tone will be added.
 * 
 * The result will be stored in pinYin, so backup it with strdup() or g_strdup() to keep the original.
 *
 * @param pinYin the pinYin instance to be processed.
 * @param tone the tone to be added.
 * @param useTrailNumber TRUE trailing number is preferred, FALSE to use traditional tonemark.
 */
void pinYin_add_tone(PinYin* pinYin, guint tone, gboolean useTrailNumber);

/**
 * Convert a PinYin to new accent formatReturn a newly allocated PinYin instance which contains the converted content.
 *
 * Unlike pinYin_get_tone() and pinYin_strip_tone() which only identify the explicit-specified tone,
 * this function treats the unspecified tone as 5th tone,  unless SQL
 * wild characters '%' and '_' are encountered. 
 *
 * Use g_free to free the newly allocated instance.
 *
 * @param pinYin the PinYin to be converted.
 * @param toFormat the PinYin accent mode to be converted to.
 * @param useTrailNumber TRUE trailing number is preferred, FALSE to use traditional tonemark.
 * @return a newly allocated converted PinYin instance.
 * @see zhuYin_to_pinYin()
 */
PinYin *pinYin_convert_accent_format(const PinYin *pinYin, PinYin_Accent_Format toFormat, gboolean useTrailNumber);


/**
 * PinYin to ZhuYin
 *
 * @param pinYin the PinYin to be converted.
 * @param toFormat the ZhuYin tone mark mode.
 * @return a newly located ZhuYin instance.
 * @see zhuYin_convert_toneMark_format()
 */
ZhuYin *pinYin_to_zhuYin(const PinYin* pinYin, ZhuYin_ToneMark_Format toFormat);

/*==========================================================
 * ZhuYin functions.
 */

/**
 * New a ZhuYin instance.
 *
 * This function allocate a new ZhuYin instance.
 * Non-NULL zhuYin_str will be copied to the new ZhuYin instance and 
 * converted to uppercase.
 * Note that the ZhuYin instance only holds #ZHUYIN_MAX_LENGTH bytes, 
 * including the EOL ('\0') character. Longer zhuYin will be truncated.
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param zhuYin_str the ZhuYin in string, NULL for blank instance.
 * @return new ZhuYin instances.
 */
ZhuYin *zhuYin_new(const char *zhuYin_str);


/**
 * Return the explicit-specified tone of ZhuYin.
 *
 * This function finds and returns the explicit-specified tone of zhuYin.
 * Thus 0 will be returned if zhuYin does not have any explicit-specified tone.
 * 
 * This function acts this way in order to accommodate 
 * the SQL LIKE query such as <code>... WHERE zhuYin LIKE 'ㄊㄧㄢ%'</code>.
 *
 * Sometimes, 1th tone mark is omitted, please convert the value 0 to 1
 * if this is the case. 
 *
 * @param zhuYin the zhuYin instance to be stripped.
 * @return the tone id from 1 to 5 if the tone is explicit-specified, 0
 * otherwise.
 * @see zhuYin_strip_tone()
 */
guint zhuYin_get_tone(const ZhuYin* zhuYin);


/**
 * Strip the tone mark of ZhuYin and return explicit-specified the tone Id.
 *
 * This function strips the tone mark of zhuYin,
 * otherwise is similar to zhuYin_get_tone().
 *
 * @param zhuYin the zhuYin instance to be stripped.
 * @return the tone id from 1 to 5 if the tone is explicit-specified, 0
 * @see zhuYin_get_tone()
 */
guint zhuYin_strip_tone(ZhuYin* zhuYin);

/**
 * Add the tone mark to zhuYin.
 *
 * This function add tone mark to zhuYin, existing tone will be removed before adding new tone.
 * If tone is 0, then existing tone will be removed, but no new tone will be added.
 * 
 * The result will be stored in zhuYin, so backup it with strdup() or g_strdup() to keep the original.
 *
 * @param zhuYin the zhuYin instance to be processed.
 * @param tone the tone to be added.
 * @param toFormat the ZhuYin tone mark mode to be converted to.
 */
void zhuYin_add_tone(ZhuYin* zhuYin, guint tone, ZhuYin_ToneMark_Format toFormat);

/**
 * Convert zhuyin to another tone mark format.
 *
 * Unlike zhuYin_get_tone() and zhuYin_strip_tone() which only identify the explicit-specified tone,
 * this function treats the unspecified tone as 1st tone,  unless SQL
 * wild characters '%' and '_' are encountered. 
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param zhuYin the ZhuYin to be converted.
 * @param toFormat the ZhuYin tone mark mode to be converted to.
 * @return the newly allocated ZhuYin instance that 
 * @see pinYin_to_zhuYin()
 */
ZhuYin *zhuYin_convert_toneMark_format(const ZhuYin* zhuYin, ZhuYin_ToneMark_Format toFormat);

/**
 * ZhuYin to PinYin
 *
 * @param zhuYin the ZhuYin to be converted.
 * @param toFormat the PinYin accent mode.
 * @param useTrailNumber TRUE trailing number is preferred, FALSE to use traditional tonemark.
 * @return a newly located PinYin instance.
 * @see pinYin_convert_accent_format()
 */
PinYin *zhuYin_to_pinYin(const ZhuYin* zhuYin, PinYin_Accent_Format toFormat, gboolean useTrailNumber);


/*----------------------------------------------------------
 * ZhuYin symbol functions.
 */

/**
 * Return the ZhuYin symbol by its Id.
 * 
 *
 * @param id ZhuYin symbol Id.
 * @return the corresponding symbol, or 0 if the id is negative.
 */
ZhuYin_Symbol zhuYin_Symbol_from_id(ZhuYin_Symbol_Id id);


/**
 * Return the Id of a ZhuYin symbol
 * 
 * @param zSym  ZhuYin symbol.
 * @return the corresponding Id.
 */
ZhuYin_Symbol_Id zhuYin_Symbol_get_id(ZhuYin_Symbol zSym);

/**
 * Whether the zhuYin symbol is an initial.
 *
 * @param zSym  ZhuYin symbol.
 * @return TRUE if the zhuYin symbol is an initial, FALSE otherwise.
 */
gboolean zhuYin_Symbol_is_initial(ZhuYin_Symbol zSym);

/**
 * Whether the zhuYin symbol is an medial.
 *
 * @param zSym  ZhuYin symbol.
 * @return TRUE if the zhuYin symbol is an medial, FALSE otherwise.
 */
gboolean zhuYin_Symbol_is_medial(ZhuYin_Symbol zSym);

/**
 * Whether the zhuYin symbol is an final.
 *
 * @param zSym  ZhuYin symbol.
 * @return TRUE if the zhuYin symbol is an final, FALSE otherwise.
 */
gboolean zhuYin_Symbol_is_final(ZhuYin_Symbol zSym);

/**
 * Whether the zhuYin symbol is either a toneMark or number which indicates the tone.
 *
 * @param zSym  ZhuYin symbol.
 * @return TRUE if the zhuYin symbol is either a toneMark or number which indicates the tone, FALSE otherwise.
 */
gboolean zhuYin_Symbol_is_tone(ZhuYin_Symbol zSym);

/**
 * Return the tone id of given tone mark.
 *
 * @param zSym  ZhuYin symbol.
 * @return tone id if zSym is tone mark, 0 otherwise.
 */
guint zhuYin_Symbol_to_toneMark_id(ZhuYin_Symbol zSym);

/**
 * Return the tone mark of given tone id.
 *
 * @param toneMark_id  toneMark_id.
 * @return the ZhuYin symbol if id is between 1 to 5; returns 0 otherwise.
 */
ZhuYin_Symbol zhuYin_Symbol_from_toneMark_id(guint toneMark_id);

/**
 * PinYin convert accent format scalar function for SQL command call.
 *
 * This function is meant to be called by sqlite3_create_function()
 * and used in SQL command. Do not use it directly.
 *
 * @param context The sqlite3_context.
 * @param argc Number of argument expected.
 * @param argv Arguments for this scalar function .
 */
void pinYin_convert_accent_format_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv);

/**
 * PinYin to ZhuYin converting scalar function for SQL command call.
 *
 * This function is meant to be called by sqlite3_create_function()
 * and used in SQL command. Do not use it directly.
 *
 * @param context The sqlite3_context.
 * @param argc Number of argument expected.
 * @param argv Arguments for this scalar function .
 */
void pinYin_to_zhuYin_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv);

/**
 * ZhuYin convert accent format scalar function for SQL command call.
 *
 * This function is meant to be called by sqlite3_create_function()
 * and used in SQL command. Do not use it directly.
 *
 * @param context The sqlite3_context.
 * @param argc Number of argument expected.
 * @param argv Arguments for this scalar function .
 */
void zhuYin_convert_toneMark_format_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv);


/**
 * ZhuYin to PinYin converting scalar function for SQL command call.
 *
 * This function is meant to be called by sqlite3_create_function()
 * and used in SQL command. Do not use it directly.
 *
 * @param context The sqlite3_context.
 * @param argc Number of argument expected.
 * @param argv Arguments for this scalar function .
 */
void zhuYin_to_pinYin_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv);

#endif /* UNIHAN_PHONETIC_H_ */
