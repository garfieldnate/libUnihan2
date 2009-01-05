/** 
 * @file Unihan_phonetic.h
 * @brief Phonetic symbols (Pinyin and Zhuyin) processing functions.
 * 
 * This header file lists the functions for Pinyin and Zhuyin processing,
 * such as conversion between HanYu pinyin conversion C functions, and
 * corresponding SQL scalar functions.
 *
 * From libUnihan 1.0, pinyin is stored as lowercase,
 * so as to be consistent with other phonetic fields.
 * Though field UNIHAN_FIELD_kMANDARIN still outputs uppercase to make it compatible with the original Unihan.txt.
 *
 *
 * Note that this header is included in Unihan.h, 
 * thus no need to explicitly include it if Unihan.h is already included.
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
#include "Unihan_phonetic-private.h"

/**
 * Maximum length of pinyin in byte.
 */
#define PINYIN_MAX_LENGTH 13

/**
 * Maximum length of zhuyin in byte.
 */
#define ZHUYIN_MAX_LENGTH 13

/**
 * Maximum length of transcription in syllable in byte.
 */
#define TRANSCRIPTION_MAX_LENGTH 13

/**
 * Zhuyin symbol.
 */
typedef gunichar  ZhuyinSymbol;

/**
 * Pronunciation in Zhuyin UTF-8 string.
 */
typedef char Zhuyin;

/**
 * Pronunciation in Pinyin UTF-8 string.
 */
typedef char Pinyin;

/**
 * Syllable holds transcription and tone.
 *
 * Syllable contains a unit of organization for a sequence of speech sounds. 
 * In libUnihan, it contains a toneless-transcription and a tone.
 *
 * A transcription is a sequence of phonemes that represents sounds.
 * Unlike Pinyin that stores various format, transcription store only
 * the internal format, such as PINYIN_ACCENT_INTERNAL.
 * This makes conversion to/from other Pinyin or Zhuyin easier.
 *
 * A tone notates the pitch contour. Valid values for Mandarin are 1-5,
 * where 0 if tone is not given.
 *
 */
typedef struct{
    char transcription[TRANSCRIPTION_MAX_LENGTH];  //!< A phonemes that represents sounds. Can be Pinyin or Zhuyin.
    guint tone;		  //!< Notation of pitch contour.
} Syllable;

/**
 * @defgroup Pinyin_Regex Regex pattern and output format for Pinyin importing.
 * @{
 * @name Regex pattern and store format for Pinyin importing.
 *
 * These define the regex pattern and out format for Pinyin related field
 * importing.
 * The input string  must be normalized as NFD.
 * @{
 */
/**
 * Regex pattern for tone accents.
 */
#define PINYIN_REGEX_IMPORT PINYIN_REGEX_IMPORT_PRIVATE

#define PINYIN_IMPORT_SUBSTITUTE PINYIN_IMPORT_SUBSTITUTE_PRIVATE

/**
 * Pinyin tone accent mark pattern substitute (store format).
 */
#define PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT_PRIVATE

/**
 * Pinyin tone number pattern substitute (store format).
 */
#define PINYIN_IMPORT_SUBSTITUTE_TONE PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT "$20"


/**
 * Pinyin pattern substitute (store format) for Xiandai Hanyu Cidian (XHC1983).
 *
 * Similar to \c PINYIN_IMPORT_SUBSTITUTE, but for kXHC1983 only.
 */
#define PINYIN_IMPORT_SUBSTITUTE_XHC PINYIN_IMPORT_SUBSTITUTE_XHC_PRIVATE

/**
 * Pinyin tone accent mark pattern substitute (store format) for Xiandai Hanyu Cidian (XHC1983).
 *
 * Similar to \c PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT, but for kXHC1983 only.
 */
#define PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT_XHC PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT_XHC_PRIVATE 

/**
 * Pinyin tone number pattern substitute (store format) for Xiandai Hanyu Cidian (XHC1983).
 *
 * Similar to \c PINYIN_IMPORT_SUBSTITUTE_TONE, but for kXHC1983 only.
 */
#define PINYIN_IMPORT_SUBSTITUTE_TONE_XHC PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT_XHC "$24"


/**
 * @}
 * @}
 */

/**
 * Enumeration of Zhuyin symbols.
 *
 * This enumeration lists the Zhuyin symbols, including the symbols for tone mark.
 * Corresponding Pinyin phonemes can also be located using these Ids.
 *
 * @see pinyin_phoneme_from_id()
 * @see pinyin_phoneme_get_id()
 * @see zhuyinSymbol_from_id()
 * @see zhuyinSymbol_get_id()
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
} ZhuyinSymbolId;

/**
 * Total number of support Zhuyin symbols.
 */
#define ZHUYIN_SYMBOL_COUNT ZHUYIN_SYMBOL_NEUTRAL + 1 

/**
 * An array of Zhuyin symbols.
 */
extern const ZhuyinSymbol ZHUYIN_SYMBOL_LIST[];


/**
 * @defgroup Pinyin_Format_Flags Pinyin format flags.
 * @{
 * @name Pinyin format flags.
 *
 * These bitwise flags specify the pinyin string output format.
 * There are various way to represent Hanyu pinyin, 
 * some employ combining accent mark to represent certain phonemes and tones, 
 * some use alternate symbols for those phonemes and tones for easier input.
 * See #PinyinAccentFormat for widely adopted format.
 *
 *
 * @see PinyinAccentFormat
 * @{
 */
/**
 * Data structure for Pinyin format flags.
 */
typedef guint PinyinFormatFlags;

/**
 * Flag for removing trivial accents.
 *
 * This flag indicate that trivial accents, that is, combining circumflex '^' (U+0302) 
 * or diaeresis accent '‥' (U+0302) which are omissible, should be stripped.
 */
#define PINYIN_FORMAT_FLAG_STRIP_TRIVIAL_ACCENT 0x1 
#define PINYIN_FORMAT_FLAG_STRIP_CIRCUMFLEX	0x2  //!< Flag for forcedly removing combining circumflex  '^' (U+0302) from ü.
#define PINYIN_FORMAT_FLAG_STRIP_DIAERESIS	0x4  //!< Flag for forcedly removing combining diaeresis  '‥' (U+0308) from ü.
#define PINYIN_FORMAT_FLAG_NFD			0x8  //!< Flag Decompose into Normalized form D (NFD).
/**
 * Flag for forcedly showing in ASCII symbols.
 *
 * With this flag, ü is outputted as v, and ê is as E.
 * If \s PINYIN_FORMAT_FLAG_NFD is also set, 
 * diaeresis  '‥' (U+0302) is converted to ':';
 * while circumflex '^' (U+0302) is converted.
 */
#define PINYIN_FORMAT_FLAG_ASCII_ONLY		0x10  //!< Show only ASCII symbol, ü is outputted as v, and ê is as E,
                                         
/**
 * Flag for showing tone as accent.
 *
 * By default the tone is represented as trailing number of 
 * With this flag, ü is outputted as v, and ê is as E.
 * If \s PINYIN_FORMAT_FLAG_NFD is also set, 
 * diaeresis  '‥' (U+0302) is converted to ':';
 * while circumflex '^' (U+0302) is converted.
 */
#define PINYIN_FORMAT_FLAG_TONE_AS_ACCENT		0x20

/**
 * Flag for stripping the trivial (5-th) tone.
 *
 */
#define PINYIN_FORMAT_FLAG_STRIP_TRIVIAL_TONE		0x40

/**
 * @}
 * @}
 */

/**
 * @name Pinyin format flags.
 * Enumeration of Pinyin accent (not tone mark) formats.
 *
 * There are two Pinyin symbols with accents, diaeresis u (ü,ㄩ), and circumflex e (ê,ㄝ) .
 * As the their pronunciations are different from u and e.
 *
 * In Romanization of Chinese (ISO 7098:1991), under certain circumstances,
 * accents can be omitted, such as jü -&gt; ju , qü -&gt;qu. This is adopted in PRC education system.
 * Use PINYIN_ACCENT_ORIGINAL for this purpose.
 *
 * Unihan does not have circumflex e (ê), otherwise it is same with ISO 7098.
 * Use PINYIN_ACCENT_UNIHAN for Unihan.
 *
 * Because ü is not on most of the keyboards, there are various ways to represent ü.
 * For example, CEDICT use u: (PINYIN_ACCENT_TRAILING); while most of Chinese
 * input method use v as substitute (PINYIN_ACCENT_INPUT_METHOD).
 *
 * In English documents such as passport, the accent are usually stripped, use 
 * PINYIN_ACCENT_NONE for this purpose. 
 *
 * libUnihan itself uses #PINYIN_ACCENT_INTERNAL to store pinyin.
 * It converts ü to v, and ê to E. By doing so, the pinyin strings can be easily processed by
 * legacy string functions as the strings are all in ASCII, yet carry over all phonetic information
 * for Pinyin and Zhuyin manipulation.
 *
 * Preserving accents unconditionally makes conversion and education easier, 
 * use PINYIN_ACCENT_ALWAYS for this purpose.
 *
 * Note that this enumeration is not for the pinyin tone mark.
 * See pinyin_convert_accent_format() pinyin tone mark handling.
 *
 * @see pinyin_convert_accent_format()
 * @{
 */
typedef enum{
    PINYIN_ACCENT_ALWAYS,   //!< ü is always represented as ü, ê is always represented as ê. 
    PINYIN_ACCENT_ORIGINAL, //!< MOE CN standard ISO 7098:1991. Trivial accent mark is omitted.
    PINYIN_ACCENT_UNIHAN,   //!< ü is represented as ü, ê is represented as e.
    PINYIN_ACCENT_TRAILING, //!< ü is represented as u:, ê is represented as e.
    PINYIN_ACCENT_INPUT_METHOD,  //!< ü is represented as v, ê is represented as e.
    PINYIN_ACCENT_NONE,      //!< ü is represented as u, ê is represented as e.
    PINYIN_ACCENT_INTERNAL  //!< ü is represented as v, ê is represented as E.
} PinyinAccentFormat;
/* @} */


/**
 * @defgroup Zhuyin_Format_Flags Zhuyin format flags.
 * @{
 * @name Zhuyin format flags.
 *
 * These bitwise flags specify the zhuyin string output format.
 * There are various way to represent Zhuyin, 
 * some put the neutral (5th) tone in the front, some omits the first tone.
 * See #ZhuyinAccentFormat for widely adopted format.
 *
 *
 * @see ZhuyinAccentFormat
 * @{
 */
/**
 * Data structure for Zhuyin format flags.
 */
typedef guint ZhuyinFormatFlags;

/**
 * Flag for strip the first tone.
 */
#define ZHUYIN_FORMAT_FLAG_STRIP_1ST_TONE	0x1
/**
 * Flag for putting 5-th tone in the front
 */
#define ZHUYIN_FORMAT_FLAG_FRONT_5TH_TONE	0x2
/**
 * Flag for showing tone as number.
 */
#define ZHUYIN_FORMAT_FLAG_NUMERICAL_TONE	0x4

/**
 * @}
 * @}
 */


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
    ZHUYIN_TONEMARK_INPUT_METHOD,  //!< Neutral (fifth) tone mark is put in the end, while the first tone mark is omitted.
    ZHUYIN_TONEMARK_NUMERICAL,  //!< Tone mark are represented as numerical, in the end of Zhuyin.
} ZhuyinToneMarkFormat;


/*==========================================================
 * Syllable functions.
 */

Syllable *syllable_new();
Syllable *syllable_new_pinyin(const Pinyin *pinyin_str);
Syllable *syllable_new_zhuyin(const Zhuyin *zhuyin_str);
Syllable *syllable_clone(Syllable *syl);

/**
 * Output syllable as pinyin.
 * 
 * This function returns a newly allocated \c Pinyin instance as result.
 * Note that if \c PINYIN_FORMAT_FLAG_STRIP_TRIVIAL_TONE is not set in \a formatFlags,
 * this function will "guess" the tone if it is not previously given.
 * 
 * @param syl The syllable to be outputted.
 * @param formatFlags The format of the outputted pinyin.
 * @return A newly allocated Pinyin instance as result.
 */
Pinyin *syllable_to_pinyin(Syllable *syl,PinyinFormatFlags formatFlags);

/**
 * Output syllable as zhuyin.
 * 
 * This function returns a newly allocated \c Zhunyin instance as result.
 * Note that if \c ZHUYIN_FORMAT_FLAG_STRIP_1ST_TONE is not set in \a formatFlags,
 * this function will "guess" the tone if it is not previously given.
 * 
 * @param syl The syllable to be outputted.
 * @param formatFlags The format of the outputted pinyin.
 * @return A newly allocated Zhuyin instance as result.
 */
Zhuyin *syllable_to_zhuyin(Syllable *syl,ZhuyinFormatFlags formatFlags);
gboolean syllable_is_zhuyin(Syllable *syl);
gboolean syllable_is_zhuyin_fast(Syllable *syl);

void syllable_free(Syllable *syl);

/**
 * Initialize all pinyin/zhuyin related regex expressions for subsequent search.
 *
 * This function compiles regex expressions into forms that are
 *   suitable for subsequent regexec() searches.
 *
 * @return 0 if success; otherwise return the error code of reg_comp().
 */
int syllabel_regex_t_init();


/*==========================================================
 * Pinyin functions.
 */

/**
 * New a Pinyin instance.
 *
 * This function allocates a new Pinyin instance.
 * If \c pinyin_str is given, it will be copied to the newly allocated Pinyin instance.
 * Note that the Pinyin instance only hold #PINYIN_MAX_LENGTH bytes, 
 * including the EOL ('\0') character. Longer pinyin will be truncated.
 *
 * \note From libUnihan 1.0, pinyin_new() no longer convert \c pinyin_str to upper case.
 *
 * Use free() or g_free() to free the newly allocated instance.
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

guint pinyin_strip_tone_normalized(Pinyin* pinyin);

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
void pinyin_add_tone_formatFlags(Pinyin* pinyin, guint tone, PinyinFormatFlags formatFlags);


/**
 * Convert pinyin to new format.
 * Return a newly allocated Pinyin instance which contains the converted content.
 *
 * This function converts pinyin to new accent format and return the result as a newly allocated pinyin instance.
 * Unlike pinyin_get_tone() and pinyin_strip_tone(), 
 * it treats the toneless pinyin as if it is in neutral (5-th) tone, 
 * unless SQL wild characters '%' and '_' also present.
 *
 * Use free() or g_free() to free the newly allocated instance.
 *
 *
 * @param pinyin the Pinyin to be converted.
 * @param formatFlags Pinyin Format Flags.
 * @return a newly allocated converted Pinyin instance.
 * @see zhuyin_to_pinyin()
 * @see PinyinFormatFlags
 * @see pinyin_convert_accent_format()
 */
Pinyin *pinyin_convert_formatFlags(const Pinyin *pinyin, PinyinFormatFlags formatFlags);


/**
 * Convert pinyin to new accent format.
 *
 * This function performs exactly the same with pinyin_convert_format()
 * except this function accepts PinyinAccentFormat and a boolean value as arguments.
 *
 * Use free() or g_free() to free the newly allocated instance.
 *
 * @param pinyin the Pinyin to be converted.
 * @param toFormat the Pinyin accent mode to be converted to.
 * @param useTrailNumber TRUE to present tone as  trailing number, FALSE to present tone as combining accent.
 * @return a newly allocated converted Pinyin instance.
 * @see zhuyin_to_pinyin()
 * @see PinyinAccentFormat
 * @see pinyin_convert_formatFlags()
 */
Pinyin *pinyin_convert_accent_format(const Pinyin *pinyin, PinyinAccentFormat toFormat, gboolean useTrailNumber);



/**
 * Pinyin to Zhuyin
 *
 * @param pinyin the Pinyin to be converted.
 * @param toFormat the Zhuyin tone mark mode.
 * @return a newly located Zhuyin instance.
 * @see zhuyin_convert_toneMark_format()
 */
Zhuyin *pinyin_to_zhuyin(const Pinyin* pinyin, ZhuyinToneMarkFormat toFormat);
Zhuyin *pinyin_to_zhuyin_formatFlags(const Pinyin* pinyin, ZhuyinFormatFlags formatFlags);

int pinyin_regex_t_init();

/**
 * Combine sub-matches of a pinyin regex import search into a specified format.
 *
 * This function used the compiled pinyin regex import expression, #PINYIN_REGEX_IMPORT,
 * for search, then matched sub patterns are combined as specified in \a format.
 * 
 *
 * @param str String to be searched.
 * @param format Format of the output string.
 * @return An newly allocated combined string, or NULL if no match or have error.
 * @see PINYIN_REGEX_IMPORT
 */
gchar *pinyin_regex_import_formatted_combine(const gchar *str, const gchar *format);

gchar *pinyin_regex_formatted_combine(const gchar *str, const gchar *format);

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
void zhuyin_add_tone(Zhuyin* zhuyin, guint tone, ZhuyinToneMarkFormat toFormat);
void zhuyin_add_tone_formatFlags(Zhuyin* zhuyin, guint tone, ZhuyinFormatFlags formatFlags);

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
Zhuyin *zhuyin_convert_toneMark_format(const Zhuyin* zhuyin, ZhuyinToneMarkFormat toFormat);
Zhuyin *zhuyin_convert_formatFlags(const Zhuyin *zhuyin, PinyinFormatFlags formatFlags);

/**
 * Zhuyin to Pinyin
 *
 * @param zhuyin the Zhuyin to be converted.
 * @param toFormat the Pinyin accent mode.
 * @param useTrailNumber TRUE to present tone as  trailing number, FALSE to present tone as combining accent.
 * @return a newly located Pinyin instance.
 * @see pinyin_convert_accent_format()
 */
Pinyin *zhuyin_to_pinyin(const Zhuyin* zhuyin, PinyinAccentFormat toFormat, gboolean useTrailNumber);
Pinyin *zhuyin_to_pinyin_formatFlags(const Zhuyin* zhuyin, PinyinFormatFlags formatFlags);

gchar *zhuyin_regex_formatted_combine(const gchar *str, const gchar *format);
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
ZhuyinSymbol zhuyinSymbol_from_id(ZhuyinSymbolId id);


/**
 * Return the Id of a Zhuyin symbol
 * 
 * @param zSym  Zhuyin symbol.
 * @return the corresponding Id.
 */
ZhuyinSymbolId zhuyinSymbol_get_id(ZhuyinSymbol zSym);

/**
 * Whether the zhuyin symbol is an initial.
 *
 * @param zSym  Zhuyin symbol.
 * @return TRUE if the zhuyin symbol is an initial, FALSE otherwise.
 */
gboolean zhuyinSymbol_is_initial(ZhuyinSymbol zSym);

/**
 * Whether the zhuyin symbol is an medial.
 *
 * @param zSym  Zhuyin symbol.
 * @return TRUE if the zhuyin symbol is an medial, FALSE otherwise.
 */
gboolean zhuyinSymbol_is_medial(ZhuyinSymbol zSym);

/**
 * Whether the zhuyin symbol is an final.
 *
 * @param zSym  Zhuyin symbol.
 * @return TRUE if the zhuyin symbol is an final, FALSE otherwise.
 */
gboolean zhuyinSymbol_is_final(ZhuyinSymbol zSym);

/**
 * Whether the zhuyin symbol is either a toneMark or number which indicates the tone.
 *
 * @param zSym  Zhuyin symbol.
 * @return TRUE if the zhuyin symbol is either a toneMark or number which indicates the tone, FALSE otherwise.
 */
gboolean zhuyinSymbol_is_tone(ZhuyinSymbol zSym);

/**
 * Return the tone id of given tone mark.
 *
 * @param zSym  Zhuyin symbol.
 * @return tone id if zSym is tone mark, 0 otherwise.
 */
guint zhuyinSymbol_to_toneMark_id(ZhuyinSymbol zSym);

/**
 * Return the tone mark of given tone id.
 *
 * @param toneMark_id  toneMark_id.
 * @return the Zhuyin symbol if id is between 1 to 5; returns 0 otherwise.
 */
ZhuyinSymbol zhuyinSymbol_from_toneMark_id(guint toneMark_id);

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
