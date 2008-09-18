/** 
 * @file Unihan_Phonetic.h
 * @brief Phonetic symbols (PinYin and ZhuYin) processing functions.
 * 
 * This header file lists the functions for PinYin and ZhuYin processing,
 * such as conversion between HanYu pinyin conversion C functions, and
 * corresponding SQL scalar functions.
 *
 * Note that PinYin is represented as uppercase, which is same with kMandarin 
 * in Unihan.
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

/**
 * Maximum space that pinyin requires.
 * 
 */
#define PINYIN_MAX_LENGTH 9

/**
 * Maximum space that pinyin requires.
 * 
 */

#define ZHUYIN_MAX_LENGTH 10

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


/**
 * Enumeration of pinyin phoneme type.
 *
 * Four types of elements has been used in Chinese phonetic notation such as pinYin or zhuyin:
 * <ol>
 *  <li>initials (I) - are always in the front (but not vice versa, see below), 
 *      usually contain consonants.</li>
 *  <li>medials (M) - symbols like ㄓ(zh) can be in the front, following initials,
 *      but not following finals.  Some literatures regard them as finals.</li>
 *  <li>finals (F) - are either standalone, or in the end.</li>
 *  <li>tone marks - marking the tones. They are either in the end (after finals and other elements), 
 *      or on the top of medials and finals.</li>
 * </ol>
 *
 * Zhuyin symbols do not change by other elements, however, the pinyin phonemes 
 * do have different forms according to the presents of other elements.
 *
 * For example 弯 (meaning: band/twist, zhuyin: ㄨㄢ, pinyin: wan), 
 * 欢 (meaning: happy zhuyin: ㄏㄨㄢ, pinyin: huan).
 * In zhuyin the part ㄨㄢ are same, but in pinyin, 'u' is replaced by 'w'
 * if the initial does not exist.
 *
 * Sometimes, special conversion rules are required for  following case:
 * 擁( zhuyin: ㄩㄥ, pinyin: yong), 兄 ( zhuyin: ㄒㄩㄥ, pinyin: xiong),
 * 翁( zhuyin: ㄨㄥ, pinyin: weng), 哄 ( zhuyin: ㄏㄨㄥ, pinyin: hong).
 * -ong cannot be simply converted to ㄩㄥ, as it might be ㄨㄥ;
 * ㄨㄥ cannot be simply converted to -ong, as it might be -eng.
 * Thus we also have element special (S) to handle this kind of conversion. 
 * It has either one medial or one medial and one final, and is in the end.
 *
 * Valid formats of elements: I, IM, IF, IS, IMF, S, M, MF, F.
 */
typedef enum{
    PINYIN_PHONEME_INVALID_TYPE=-1,  //!< Invalid phoneme type.

    PINYIN_PHONEME_TYPE_INITIAL_ONLY, //!< Only initial present, no others.
    PINYIN_PHONEME_TYPE_INITIAL,      //!< Normal Initials.       

    PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL, //!< No Initial (leading) Special case.
    PINYIN_PHONEME_TYPE_SPECIAL,            //!< Special cases.

    PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL, //!< No initial in the front.
    PINYIN_PHONEME_TYPE_MEDIAL,            //!< Normal medials.

    PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL, //!< Finals with medial
    PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL, //!< Finals without medial
    PINYIN_PHONEME_TYPE_FINAL,             //!< Normal finals (which do not change form).

    PINYIN_PHONEME_TYPE_TONEMARK
} PinYin_Phoneme_Type;

/**
 * Number of PinYin phoneme type.
 */
#define PINYIN_PHONEME_TYPES_COUNT PINYIN_PHONEME_TYPE_TONEMARK+1


/**
 * Struct of PinYin-ZhuYin conversion rule.
 *
 * This struct shows a conversion rule between ZhuYin_Symbol
 * and PinYin Phoneme.
 *
 */
typedef struct {
    const char  *pinYin_phoneme; //<! PinYin phoneme.
    ZhuYin_Symbol zhuYin;   //<! ZhuYin.
    guint mask;             //<! The bits to be compare. (with AND)
    guint match;            //<! The masked bits should be exactly the same with match, or the rule will not be applied.
} P_Z_Rules;


/**
 * Struct of PinYin-ZhuYin conversion property.
 *
 * This struct shows a conversion rule between ZhuYin_Symbol
 * and PinYin Phoneme.
 *
 */
typedef struct {
    const char  *pinYin_phoneme; //<! PinYin phoneme.
    const char  *zhuYin;     //<! ZhuYin.
    PinYin_Phoneme_Type pType;	//<! Type of PinYin Phoneme.
} P_Z_Properties;

/**
 * Conversion property Tables.
 *
 * Example: To get the table of PINYIN_PHONEME_TYPE_INITIAL,
 * use PHONEMES_LIST[PINYIN_PHONEME_TYPE_INITIAL].
 *
 */
extern const P_Z_Properties * PHONEMES_LIST [];

/*==========================================================
 * PinYin functions.
 */

/**
 * New a PinYin instance.
 *
 * This function allocate a new PinYin instance.
 * Non-NULL pinYinStr will be copied to the new PinYin instance and 
 * converted to uppercase.
 * Note that the PinYin instance only hold #PINYIN_MAX_LENGTH bytes, 
 * including the EOL ('\0') character. Longer pinYin will be truncated.
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param pinYinStr the PinYin in string, NULL for blank instance.
 * @return new PinYin instances.
 */
PinYin *pinYin_new(const char *pinYin_str);

/**
 * Strip the tone mark of PinYin and return the tone Id.
 *
 * This function strips the tone mark of pinYin and return the id (0 to 5) of stripped tone mark.
 * Tone mark 0 will be returned if pinYin does not have any tone mark.
 * The result will be stored in pinYin, so backup it with strdup() or g_strdup() to keep the original.
 *
 * @param pinYin the pinYin instance to be stripped.
 * @return the stripped tone mark, from 1 to 5.
 */
guint pinYin_strip_toneMark(PinYin* pinYin);

/**
 * Add the tone mark to pinYin.
 *
 * The result will be stored in pinYin, so backup it with strdup() or g_strdup() to keep the original.
 *
 * @param pinYin the pinYin instance to be processed.
 * @param tone the tone to be added.
 * @param useTrailNumber TRUE trailing number is preferred, FALSE to use traditional tonemark.
 */
void pinYin_add_toneMark(PinYin* pinYin, guint tone, gboolean useTrailNumber);

/**
 * Convert a PinYin to new accent formatReturn a newly allocated PinYin instance which contains the converted content.
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param pinYin the PinYin to be converted.
 * @param toFormat the PinYin accent mode to be converted to.
 * @param useTrailNumber TRUE trailing number is preferred, FALSE to use traditional tonemark.
 * @return a newly allocated converted PinYin instance.
 */
PinYin *pinYin_convert_accent_format(const PinYin *pinYin, PinYin_Accent_Format toFormat, gboolean useTrailNumber);


/**
 * PinYin to ZhuYin
 *
 * @param pinYin the PinYin to be converted.
 * @param toFormat the ZhuYin tone mark mode.
 * @return a newly located ZhuYin instance.
 */
ZhuYin *pinYin_to_zhuYin(const PinYin* pinYin, ZhuYin_ToneMark_Format toFormat);

/*==========================================================
 * ZhuYin functions.
 */

/**
 * New a ZhuYin instance.
 *
 * This function allocate a new ZhuYin instance.
 * Non-NULL zhuYinStr will be copied to the new ZhuYin instance and 
 * converted to uppercase.
 * Note that the ZhuYin instance only holds #ZHUYIN_MAX_LENGTH bytes, 
 * including the EOL ('\0') character. Longer zhuYin will be truncated.
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param zhuYinStr the ZhuYin in string, NULL for blank instance.
 * @return new ZhuYin instances.
 */
ZhuYin *zhuYin_new(const char *zhuYin_str);

/**
 * Strip tone mark of ZhuYin.
 *
 * This function strips the tone mark of zhuYin and return the id (1 to 5) of stripped tone mark.
 * Tone mark 1 will be returned if zhuYin does not have any tone mark.
 * The result will be stored in zhuYin, so backup it with g_strdup() to keep the original.
 * 
 *
 * @param zhuYin the ZhuYin instance to be stripped.
 * @return the stripped tone mark, from 1 to 5.
 */
guint zhuYin_strip_toneMark(ZhuYin* zhuYin);

/**
 * Add the tone mark to zhuYin.
 *
 * The result will be stored in zhuYin, so backup it with strdup() or g_strdup() to keep the original.
 *
 * @param zhuYin the zhuYin instance to be processed.
 * @param tone the tone to be added.
 * @param toFormat the ZhuYin tone mark mode to be converted to.
 */
void zhuYin_add_toneMark(ZhuYin* zhuYin, guint tone, ZhuYin_ToneMark_Format toFormat);

/**
 * Convert zhuyin to another tone mark format.
 *
 * Note: use g_free to free the newly allocated instance.
 *
 * @param zhuYin the ZhuYin to be converted.
 * @param toFormat the ZhuYin tone mark mode to be converted to.
 * @return the newly allocated ZhuYin instance that 
 */
ZhuYin *zhuYin_convert_toneMark_format(const ZhuYin* zhuYin, ZhuYin_ToneMark_Format toFormat);

/**
 * ZhuYin to PinYin
 *
 * @param zhuYin the ZhuYin to be converted.
 * @param toFormat the PinYin accent mode.
 * @param useTrailNumber TRUE trailing number is preferred, FALSE to use traditional tonemark.
 * @return a newly located PinYin instance.
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


gboolean zhuYin_Symbol_is_initial(ZhuYin_Symbol zSym);

gboolean zhuYin_Symbol_is_medial(ZhuYin_Symbol zSym);

gboolean zhuYin_Symbol_is_final(ZhuYin_Symbol zSym);

gboolean zhuYin_Symbol_is_toneMark(ZhuYin_Symbol zSym);

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


const P_Z_Properties *pzProperties_from_pinyin_prefix(const char *pinYin_str, PinYin_Phoneme_Type pType);
const P_Z_Properties *pzProperties_from_zhuyin_prefix(const char *zhuYin_str, PinYin_Phoneme_Type pType);



#endif /* UNIHAN_PHONETIC_H_ */
