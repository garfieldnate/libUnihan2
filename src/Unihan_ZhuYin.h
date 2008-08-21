/** 
 * @file Unihan_ZhuYin.h
 * @brief ZhuYin (BoPoMoFo) processing functions.
 * 
 * This header file list the ZhuYin processing functions,
 * such as HanYu pinyin conversion C functions, and
 * corresponding SQL scalar functions.
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

#ifndef UNIHAN_ZHUYIN_H_
#define UNIHAN_ZHUYIN_H_

/**
 * Maximum space that pinyin requires.
 * 
 */
#define PINYIN_MAX_LENGTH_MAX 9

/**
 * Maximum space that pinyin requires.
 * 
 */

#define ZHUYIN_MAX_LENGTH_MAX 9

/**
 * ZhuYin symbol.
 */
typedef gunichar  ZhuYin_Symbol;


/**
 * Pronunciation in ZhuYin UTF-8 string.
 */
typedef char[ZHUYIN_MAX_LENGTH_MAX] ZhuYin;

/**
 * Pronunciation in PinYin UTF-8 string.
 */
typedef char[PINYIN_MAX_LENGTH_MAX] PinYin;

/**
 * ID of ZhuYin symbol.
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
    ZHUYIN_SYMBOL_V,        //!< ZhuYin symbol 'ㄩ'
    ZHUYIN_SYMBOL_A,         //!< ZhuYin symbol 'ㄚ'
    ZHUYIN_SYMBOL_O,         //!< ZhuYin symbol 'ㄛ'
    ZHUYIN_SYMBOL_E,         //!< ZhuYin symbol 'ㄜ'
    ZHUYIN_SYMBOL_E_HAT,     //!< ZhuYin symbol 'ㄝ'
    ZHUYIN_SYMBOL_AI,        //!< ZhuYin symbol 'ㄞ'
    ZHUYIN_SYMBOL_EI,        //!< ZhuYin symbol 'ㄟ'
    ZHUYIN_SYMBOL_AO,        //!< ZhuYin symbol 'ㄠ'
    ZHUYIN_SYMBOL_OU,        //!< ZhuYin symbol 'ㄡ'
    ZHUYIN_SYMBOL_AN,        //!< ZhuYin symbol 'ㄢ'
    ZHUYIN_SYMBOL_EN,        //!< ZhuYin symbol 'ㄣ'
    ZHUYIN_SYMBOL_ANG,       //!< ZhuYin symbol 'ㄤ'
    ZHUYIN_SYMBOL_ENG,       //!< ZhuYin symbol 'ㄥ'
    ZHUYIN_SYMBOL_ER,        //!< ZhuYin symbol 'ㄦ'
    ZHUYIN_SYMBOL_2,         //!< ZhuYin 2nd tone mark 'ˊ'
    ZHUYIN_SYMBOL_3,         //!< ZhuYin 3rd tone mark 'ˇ'
    ZHUYIN_SYMBOL_4,         //!< ZhuYin 4th tone mark 'ˋ'
    ZHUYIN_SYMBOL_NETURAL,   //!< ZhuYin neutral (5th) tone mark '˙'
} ZhuYin_Symbol_Id;
#define ZHUYIN_SYMBOL_COUNT 37 + 4 

/**
 * Enumeration of PinYin accent (not tone mark) handling modes.
 *
 * There are two PinYin symbols with accents, Umlaut U (ü), and E hat ê .
 * Original form, ü and ê are suitable for pronunciation learning.
 * However, these symbols cannot be typed intuitively with popular (US-American)
 * keyboard layout, so ü is often substituted with u or v, and ê is substituted by e.
 *
 * Note the accent-like tone marks are not discussed here.
 * In libUnihan, tone marks are always represented as trailing number.
 */
typedef enum{
    PINYIN_ACCENT_ORIGINAL, //!< ü is represented as ü, ê is represented as ê.
    PINYIN_ACCENT_TRAILING, //!< ü is represented as U:, ê is represented as E.
    PINYIN_ACCENT_CONVERT,  //!< ü is represented as V, ê is represented as E.
    PINYIN_ACCENT_NONE      //!< ü is represented as U, ê is represented as E.
} PinYin_Accent_Mode;

/**
 * An array of ZhuYin symbols.
 */
extern const ZhuYin_Symbol ZHUYIN_SYMBOL_LIST[];

/**
 * An array of PinYin phoneme.
 */
extern const PinYin  PINYIN_PHONEME_LIST[];

/**
 * New a PinYin instance.
 *
 * @return new PinYin instances.
 */
PinYin *pinYin_new();

/**
 * Convert PinYin accents and return a newly allocated converted PinYin.
 *
 * @param pinYin the PinYin to be converted.
 * @param toMode the PinYin accent mode to be converted to.
 * @return a newly located PinYin instance.
 */
PinYin *pinYin_convert_accent(PinYin *pinYin, PinYin_Accent_Mode toMode);

/**
 * Convert PinYin accents and put the output to a given buffer.
 *
 * @param pinYin the PinYin to be converted.
 * @param toMode the PinYin accent mode to be converted to.
 * @param outBuf the buffer that hold the converted PinYin.
 */
void pinYin_convert_accent_buffer(PinYin *pinYin, PinYin_Accent_Mode toMode, PinYin *outBuf);

/**
 * PinYin to ZhuYin
 *
 * @param pinYin the PinYin to be converted.
 * @return a newly located ZhuYin instance.
 */
ZhuYin *pinYin_to_zhuYin(PinYin* pinYin);


/**
 * PinYin to ZhuYin
 *
 * @param pinYin the PinYin to be converted.
 * @param zhuYin the resulting ZhuYin.
 */
ZhuYin *pinYin_to_zhuYin_buffer(PinYin *pinYin, ZhuYin *zhuYin);


/*----------------------------------------
 * PinYin phoneme functions.
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
ZhuYin_Symbol_Id zhuYin_Symbol_to_id(ZhuYin_Symbol zSym);

/*========================================
 * ZhuYin functions.
 */

/**
 * New a ZhuYin instance.
 *
 * @return new ZhuYin instances.
 */
ZhuYin *zhuYin_new();


/**
 * ZhuYin to PinYin
 *
 * @param zhuYin the ZhuYin to be converted.
 * @return a newly located PinYin instance.
 */
PinYin *zhuYin_to_pinYin(ZhuYin* zhuYin);


/**
 * ZhuYin to PinYin
 *
 * @param zhuYin the ZhuYin to be converted.
 * @param pinYin the resulting PinYin.
 */
PinYin *zhuYin_to_pinYin_buffer(ZhuYin* zhuYin, PinYin *pinYin);


/*----------------------------------------
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
ZhuYin_Symbol_Id zhuYin_Symbol_to_id(ZhuYin_Symbol zSym);

#endif /* UNIHANZHUYIN_H_ */
