/** 
 * @file Unihan_phonetic.c
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

#include "allocate.h"
#include "str_functions.h"
#include "sqlite_functions.h"
#include "Unihan_phonetic.h"


const ZhuYin_Symbol ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_COUNT]={
    0x3105,   // "ㄅ"
    0x3106,   // "ㄆ"
    0x3107,   // "ㄇ"
    0x3108,   // "ㄈ"
    0x3109,   // "ㄉ"
    0x310A,   // "ㄊ"
    0x310B,   // "ㄋ"
    0x310C,   // "ㄌ"
    0x310D,   // "ㄍ"
    0x310E,   // "ㄎ"
    0x310F,   // "ㄏ"
    0x3110,   // "ㄐ"
    0x3111,   // "ㄑ"
    0x3112,   // "ㄒ"
    0x3113,   // "ㄓ"
    0x3114,   // "ㄔ"
    0x3115,   // "ㄕ"
    0x3116,   // "ㄖ"
    0x3117,   // "ㄗ"
    0x3118,   // "ㄘ"
    0x3119,   // "ㄙ"
    0x3127,   // "ㄧ"
    0x3128,   // "ㄨ"
    0x3129,   // "ㄩ"
    0x311A,   // "ㄚ"
    0x311B,   // "ㄛ"
    0x311C,   // "ㄜ"
    0x311D,   // "ㄝ"
    0x311E,   // "ㄞ"
    0x311F,   // "ㄟ"
    0x3120,   // "ㄠ"
    0x3121,   // "ㄡ"
    0x3122,   // "ㄢ"
    0x3123,   // "ㄣ"
    0x3124,   // "ㄤ"
    0x3125,   // "ㄥ"
    0x3126,   // "ㄦ"
    0x02C9,   // "ˉ"
    0x02CA,   // "ˊ"
    0x02C7,   // "ˇ"
    0x02CB,   // "ˋ"
    0x02D9,   // "˙"
};


#define PHONEME_FLAG_HAS_INITIAL   	1
#define PHONEME_FLAG_HAS_MEDIAL    	1 <<  1
#define PHONEME_FLAG_HAS_FINAL     	1 <<  2
#define PHONEME_FLAG_HAS_A         	1 <<  3 
#define PHONEME_FLAG_HAS_E         	1 <<  4
#define PHONEME_FLAG_HAS_I         	1 <<  5
#define PHONEME_FLAG_HAS_O         	1 <<  6 
#define PHONEME_FLAG_HAS_U         	1 <<  7
#define PHONEME_FLAG_HAS_U_DIAERESIS	1 <<  8
#define PHONEME_FLAG_HAS_E_CIRCUMFLEX   1 <<  9
#define PHONEME_FLAG_HAS_Y	   	1 << 10
#define PHONEME_FLAG_HAS_W	   	1 << 11
#define PHONEME_FLAG_HAS_LN        	1 << 12 // ㄋ, ㄌ
#define PHONEME_FLAG_HAS_JQX       	1 << 13 // ㄐ, ㄑ, ㄒ
#define PHONEME_FLAG_HAS_ZCSR      	1 << 14 // ㄓ, ㄔ, ㄕ, ㄖ, ㄗ, ㄘ, ㄙ
#define PHONEME_FLAG_HAS_FINAL_U   	1 << 15 // ㄡ
#define PHONEME_FLAG_HAS_FINAL_N   	1 << 16 // ㄢ, ㄣ, ㄤ, ㄥ
#define PHONEME_FLAG_HAS_FINAL_G   	1 << 17 // ㄤ, ㄥ
#define PHONEME_FLAG_HAS_TONEMARK  	1 << 18 // Includes ˉ, ˊ, ˇ, ˋ, and pinyin character with tonemark, but not numbers.
#define PHONEME_FLAG_HAS_NUMBER		1 << 19
#define PHONEME_FLAG_HAS_COLON		1 << 20
#define PHONEME_FLAG_HAS_WILDCHAR	1 << 21

typedef struct{
    ZhuYin_Symbol zhuYin_symbol;
    guint phonemeFlags;
} ZhuYin_Symbol_Properties;

const ZhuYin_Symbol_Properties ZHUYIN_SYMBOL_PROPERTIES[]={
    {0x3105, PHONEME_FLAG_HAS_INITIAL},   // "ㄅ"
    {0x3106, PHONEME_FLAG_HAS_INITIAL},   // "ㄆ"
    {0x3107, PHONEME_FLAG_HAS_INITIAL},   // "ㄇ"
    {0x3108, PHONEME_FLAG_HAS_INITIAL},   // "ㄈ"
    {0x3109, PHONEME_FLAG_HAS_INITIAL},   // "ㄉ"
    {0x310A, PHONEME_FLAG_HAS_INITIAL},   // "ㄊ"
    {0x310B, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_LN},   // "ㄋ"
    {0x310C, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_LN},   // "ㄌ"
    {0x310D, PHONEME_FLAG_HAS_INITIAL},   // "ㄍ"
    {0x310E, PHONEME_FLAG_HAS_INITIAL},   // "ㄎ"
    {0x310F, PHONEME_FLAG_HAS_INITIAL},   // "ㄏ"
    {0x3110, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_JQX},   // "ㄐ"
    {0x3111, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_JQX},   // "ㄑ"
    {0x3112, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_JQX},   // "ㄒ"
    {0x3113, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_ZCSR},   // "ㄓ"
    {0x3114, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_ZCSR},   // "ㄔ"
    {0x3115, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_ZCSR},   // "ㄕ"
    {0x3116, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_ZCSR},   // "ㄖ"
    {0x3117, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_ZCSR},   // "ㄗ"
    {0x3118, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_ZCSR},   // "ㄘ"
    {0x3119, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_ZCSR},   // "ㄙ"
    {0x3127, PHONEME_FLAG_HAS_MEDIAL  | PHONEME_FLAG_HAS_Y},   // "ㄧ"
    {0x3128, PHONEME_FLAG_HAS_MEDIAL  | PHONEME_FLAG_HAS_W},   // "ㄨ"
    {0x3129, PHONEME_FLAG_HAS_MEDIAL  | PHONEME_FLAG_HAS_U_DIAERESIS},   // "ㄩ"
    {0x311A, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_A},   // "ㄚ"
    {0x311B, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_O},   // "ㄛ"
    {0x311C, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_E},   // "ㄜ"
    {0x311D, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_E_CIRCUMFLEX},   // "ㄝ"
    {0x311E, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_I},   // "ㄞ"
    {0x311F, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_I},   // "ㄟ"
    {0x3120, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_O},   // "ㄠ"
    {0x3121, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_FINAL_U},   // "ㄡ"
    {0x3122, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_FINAL_N},   // "ㄢ"
    {0x3123, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_FINAL_N},   // "ㄣ"
    {0x3124, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_FINAL_N | PHONEME_FLAG_HAS_FINAL_G},   // "ㄤ"
    {0x3125, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_FINAL_N | PHONEME_FLAG_HAS_FINAL_G},   // "ㄥ"
    {0x3126, PHONEME_FLAG_HAS_FINAL   | PHONEME_FLAG_HAS_E},   // "ㄦ"
    {0x02C9, PHONEME_FLAG_HAS_TONEMARK},   // "ˉ"
    {0x02CA, PHONEME_FLAG_HAS_TONEMARK},   // "ˊ"
    {0x02C7, PHONEME_FLAG_HAS_TONEMARK},   // "ˇ"
    {0x02CB, PHONEME_FLAG_HAS_TONEMARK},   // "ˋ"
    {0x02D9, PHONEME_FLAG_HAS_TONEMARK},   // "˙"
    {0,0}
};


/**
 * Struct of PinYin-ZhuYin conversion rule.
 *
 * This struct shows a conversion rule between ZhuYin_Symbol
 * and PinYin Phoneme.
 *
 */
typedef struct {
    const char  *pinYin_phoneme; //<! PinYin phoneme.
    ZhuYin_Symbol zhuYin_symbol;   //<! ZhuYin.
    guint mask;             //<! The bits to be compare. (with AND)
    guint match;            //<! The masked bits should be exactly the same with match, or the rule will not be applied.
    guint location;
} P_Z_Rule;



const P_Z_Rule P_Z_RULES[]={
    {"ZHI",  0x3113, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, // "ㄓ"
    {"CHI",  0x3114, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, // "ㄔ"
    {"SHI",  0x3115, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, // "ㄕ"
    {"RI",   0x3116, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, // "ㄖ"
    {"ZI",   0x3117, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, // "ㄗ"
    {"CI",   0x3118, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, // "ㄘ"
    {"SI",   0x3119, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, // "ㄙ"
    {"B",    0x3105, 0, 0}, // "ㄅ" 
    {"P",    0x3106, 0, 0}, // "ㄆ"
    {"M",    0x3107, 0, 0}, // "ㄇ"
    {"F",    0x3108, 0, 0}, // "ㄈ"
    {"D",    0x3109, 0, 0}, // "ㄉ"
    {"T",    0x310A, 0, 0}, // "ㄊ"
    {"N",    0x310B, 0, 0}, // "ㄋ"
    {"L",    0x310C, 0, 0}, // "ㄌ"
    {"G",    0x310D, 0, 0}, // "ㄍ"
    {"K",    0x310E, 0, 0}, // "ㄎ"
    {"H",    0x310F, 0, 0}, // "ㄏ"
    {"J",    0x3110, 0, 0}, // "ㄐ"
    {"Q",    0x3111, 0, 0}, // "ㄑ"
    {"X",    0x3112, 0, 0}, // "ㄒ"
    {"ZH",   0x3113, 0, 0}, // "ㄓ" 
    {"CH",   0x3114, 0, 0}, // "ㄔ"
    {"SH",   0x3115, 0, 0}, // "ㄕ"
    {"R",    0x3116, 0, 0}, // "ㄖ"
    {"Z",    0x3117, 0, 0}, // "ㄗ"
    {"C",    0x3118, 0, 0}, // "ㄘ"
    {"S",    0x3119, 0, 0}, // "ㄙ"
    {"YI",   0x3127, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_FINAL, 0}, // "ㄧ"
    /* For ^ㄧㄣ & ^ㄧㄥ */
    {"YI",   0x3127, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_FINAL_N, PHONEME_FLAG_HAS_FINAL_N}, // "ㄧ"
    {"WU",   0x3128, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_FINAL, 0}, // "ㄨ"
    {"YÜ",   0x3129, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_FINAL_G, 0 }, // "ㄩ"
    {"YO",   0x3129, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_FINAL_G, PHONEME_FLAG_HAS_FINAL_G },  // "ㄩ"
    {"Y",    0x3127, PHONEME_FLAG_HAS_INITIAL, 0}, // "ㄧ"
    /* For *ㄩㄥ */
    {"IO",    0x3129, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_JQX | PHONEME_FLAG_HAS_A |
	PHONEME_FLAG_HAS_FINAL_G, 
	PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_JQX | PHONEME_FLAG_HAS_FINAL_G}, // "ㄩ"
    {"I",    0x3127, PHONEME_FLAG_HAS_INITIAL, PHONEME_FLAG_HAS_INITIAL}, // "ㄧ"
    {"W",    0x3128, PHONEME_FLAG_HAS_INITIAL, 0}, // "ㄨ"
    /* For *ㄨㄥ */
    {"O",    0x3128, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_JQX | PHONEME_FLAG_HAS_A |
	PHONEME_FLAG_HAS_FINAL_G, 
	PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_FINAL_G}, // "ㄨ"
    {"U",    0x3128, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_Y, PHONEME_FLAG_HAS_INITIAL}, // "ㄨ"
    {"Ü",    0x3129, PHONEME_FLAG_HAS_INITIAL, PHONEME_FLAG_HAS_INITIAL},  // "ㄩ"
    /* For *ㄨㄥ */
    {"ENG",  0x3125, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_W, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_W }, // "ㄥ"
    {"ENG",  0x3125, PHONEME_FLAG_HAS_MEDIAL, 0}, // "ㄥ"
    /* For *ㄨㄣ */
    {"EN",   0x3123, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_W, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_W }, // "ㄣ"
    {"EN",   0x3123, PHONEME_FLAG_HAS_MEDIAL, 0}, // "ㄣ"
    {"EI",   0x311F, PHONEME_FLAG_HAS_MEDIAL, 0}, // "ㄟ"
    {"EI",   0x311F, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL, PHONEME_FLAG_HAS_MEDIAL}, // "ㄟ"
    /* For ^ㄧㄡ */
    {"OU",   0x3121, PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_Y, PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_Y}, // "ㄡ"
    {"OU",   0x3121, PHONEME_FLAG_HAS_MEDIAL, 0}, // "ㄡ"
    {"NG",   0x3125, PHONEME_FLAG_HAS_MEDIAL, PHONEME_FLAG_HAS_MEDIAL}, // "ㄥ"
    {"NG",   0x3125, PHONEME_FLAG_HAS_FINAL_N, PHONEME_FLAG_HAS_FINAL_N}, // "ㄥ"
    {"N",    0x3123, PHONEME_FLAG_HAS_MEDIAL, PHONEME_FLAG_HAS_MEDIAL}, // "ㄣ"
    {"N",    0x3123, PHONEME_FLAG_HAS_FINAL_N, PHONEME_FLAG_HAS_FINAL_N}, // "ㄣ"
    {"I",    0x311F, PHONEME_FLAG_HAS_MEDIAL, PHONEME_FLAG_HAS_MEDIAL}, // "ㄟ"
    {"U",    0x3121,  PHONEME_FLAG_HAS_FINAL_U, PHONEME_FLAG_HAS_FINAL_U}, // "ㄡ"
    {"ANG",  0x3124, 0, 0}, // "ㄤ" 
    {"AI",   0x311E, 0, 0}, // "ㄞ"
    {"AO",   0x3120, 0, 0}, // "ㄠ"
    {"AN",   0x3122, 0, 0}, // "ㄢ"
    {"A",    0x311A, 0, 0}, // "ㄚ"   
    {"O",    0x311B, 0, 0}, // "ㄛ"
    {"ER",   0x3126, 0, 0}, // "ㄦ"
    {"E",    0x311C, 0, 0}, // "ㄜ"
    {"Ê",    0x311D, 0, 0}, // "ㄝ"

    {"1",    0x02C9, 0, 0}, // "ˉ"
    {"2",    0x02CA, 0, 0}, // "ˊ"
    {"3",    0x02C7, 0, 0}, // "ˇ"
    {"4",    0x02CB, 0, 0}, // "ˋ"
    {"5",    0x02D9, 0, 0}, // "˙"
    /* Pass SQL wild characters */
    {"_",    0x005F, 0, 0}, // "_"
    {"%",    0x0025, 0, 0}, // "%"
    {NULL, 0, 0, 0}
};


const gunichar A_TONEMARKS[5]={
    0x0100,  // "Ā"
    0x00C1,  // "Á"
    0x01CD,  // "Ǎ",
    0x00C0,  // "À",
    0x0041,  // "A"
};

const gunichar E_TONEMARKS[5]={
    0x0112,  // "Ē",
    0x00C9,  // "É",
    0x011A,  // "Ě",
    0x00C8,  // "È",
    0x0045,  // "E"
};

const gunichar I_TONEMARKS[5]={
    0x012A,  // "Ī",
    0x00CD,  // "Ì",
    0x012C,  // "Ǐ",
    0x00CC,  // "Í",
    0x0049,  // "I"
};

const gunichar O_TONEMARKS[5]={
    0x014C,  // "Ō",
    0x00D3,  // "Ó",
    0x01D1,  // "Ǒ",
    0x00D2,  // "Ò",
    0x004F,  // "O"
};

const gunichar U_TONEMARKS[5]={
    0x016A,  // "Ū",
    0x00DA,  // "Ú",
    0x01D3,  // "Ǔ",
    0x00D9,  // "Ù",
    0x0055,  // "U"
};


const gunichar U_DIAERESIS_TONEMARKS[5]={
    0x01D5,  // "Ǖ",
    0x01D7,  // "Ǜ",
    0x01D9,  // "Ǚ",
    0x01DB,  // "Ǘ",
    0x00DC,  // "Ü"
};

const gunichar *PINYIN_TONEMARKS[6]={
    A_TONEMARKS,
    E_TONEMARKS,
    I_TONEMARKS,
    O_TONEMARKS,
    U_TONEMARKS,
    U_DIAERESIS_TONEMARKS
};


PinYin *pinYin_new(const char *pinYin_str){
    PinYin *pinYin;
    if (isEmptyString(pinYin_str)){
	pinYin=NEW_ARRAY_INSTANCE(PINYIN_MAX_LENGTH,char);
	initString(pinYin);
    }else{
	pinYin=g_utf8_strup(pinYin_str,PINYIN_MAX_LENGTH);
    }
    return pinYin;
}

static gboolean uniChar_tone_mark_lookup(gunichar uniChar, int *i, int *j, int depth){
    for (*i=0;*i<6;(*i)++){
	for (*j=0;*j<depth;(*j)++){
	    if (PINYIN_TONEMARKS[*i][*j]==uniChar){
		return TRUE;
	    }
	}
    }
    *i=-1;
    *j=-1;
    return FALSE;
}

static gboolean uniChar_is_vowel(gunichar uniChar, int *i, int *j){
    return uniChar_tone_mark_lookup(uniChar, i, j, 5);

}

static gboolean uniChar_has_toneMark(gunichar uniChar, int *i, int *j){
    return uniChar_tone_mark_lookup(uniChar, i, j, 4);
}

static gboolean uniChar_is_SQL_wildchar(gunichar uniChar){
    switch(uniChar){
	case '_':
	case '%':
	    return TRUE;
	default:
	    break;
    }
    return FALSE;
}



static  gboolean flags_are_suitable(guint flags, guint mask, guint match){
    if ((flags & mask) ^ match)
        return FALSE;
    return TRUE;
}



static guint pinYin_scan_fingerPrint(gunichar *uniStr){
    int i,j,k;
    guint flags=0;
    for (i=0;uniStr[i]!=0;i++){
	if (uniChar_is_vowel(uniStr[i],&j,&k)){
	    switch(j){
		case 0:
		    flags |= PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_FINAL;
		    break;
		case 1:
		    flags |= PHONEME_FLAG_HAS_E | PHONEME_FLAG_HAS_FINAL;
		    break;
		case 2:
		    if (flags & PHONEME_FLAG_HAS_ZCSR){
		    }else if (flags & PHONEME_FLAG_HAS_MEDIAL){
			if (!(flags & PHONEME_FLAG_HAS_Y)){
			    flags |= PHONEME_FLAG_HAS_FINAL | PHONEME_FLAG_HAS_I;
			}
		    }else if (flags & PHONEME_FLAG_HAS_FINAL){
			flags |= PHONEME_FLAG_HAS_I ;
		    }else {
			flags |= PHONEME_FLAG_HAS_MEDIAL;
		    }
		    break;
		case 3:
		    flags |= PHONEME_FLAG_HAS_O | PHONEME_FLAG_HAS_FINAL;
		    break;
		case 4:
		    if (flags & PHONEME_FLAG_HAS_MEDIAL){
			if (flags & PHONEME_FLAG_HAS_W){
			    flags |= PHONEME_FLAG_HAS_U;
			}else{
			    flags |= PHONEME_FLAG_HAS_FINAL | PHONEME_FLAG_HAS_FINAL_U;
			}
		    }else if (flags & PHONEME_FLAG_HAS_O){
			flags |= PHONEME_FLAG_HAS_FINAL_U; // 'ㄡ'
		    }else if (flags & PHONEME_FLAG_HAS_INITIAL){
			flags |= PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_U;
		    }else{
			g_error("Un-handled U!");
		    }
		    break;
		case 5:
		    flags |= PHONEME_FLAG_HAS_U_DIAERESIS |  PHONEME_FLAG_HAS_MEDIAL;
		    break;
		default:
		    break;
	    }
	    if (k<4){
		flags |= PHONEME_FLAG_HAS_TONEMARK;
	    }
	    continue;
	}
	switch(uniStr[i]){
	    case 'W':
		flags |= PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_W;
		break;
	    case 'V':
		flags |= PHONEME_FLAG_HAS_U_DIAERESIS | PHONEME_FLAG_HAS_MEDIAL;
		break;
	    case 0xCA:  // 'Ê'
		flags |= PHONEME_FLAG_HAS_E_CIRCUMFLEX | PHONEME_FLAG_HAS_FINAL;
		break;
	    case 'Y':
		flags |= PHONEME_FLAG_HAS_Y | PHONEME_FLAG_HAS_MEDIAL;
		break;
	    case 'L':
		flags |= PHONEME_FLAG_HAS_LN | PHONEME_FLAG_HAS_INITIAL;
		break;
	    case 'N':
		if (i>0)
		    flags |= PHONEME_FLAG_HAS_FINAL_N | PHONEME_FLAG_HAS_FINAL;
		else 
		    flags |= PHONEME_FLAG_HAS_LN | PHONEME_FLAG_HAS_INITIAL;
		break;
	    case 'J':
	    case 'Q':
	    case 'X':
		flags |= PHONEME_FLAG_HAS_JQX | PHONEME_FLAG_HAS_INITIAL;
		break;
	    case 'Z':
	    case 'C':
	    case 'S':
	    case 'R':
		if (i==0)
		    flags |= PHONEME_FLAG_HAS_ZCSR | PHONEME_FLAG_HAS_INITIAL;
		break;
	    case 'H':
		if (i==0)
		    flags |= PHONEME_FLAG_HAS_INITIAL;
		break;
	    case 'G':
		if (i>0)
		    /* HAS_FINAL already */
		    flags |= PHONEME_FLAG_HAS_FINAL_G;
		else
		    flags |= PHONEME_FLAG_HAS_INITIAL;
		break;
	    case ':':
		flags |= PHONEME_FLAG_HAS_COLON;
		break;
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
		flags |= PHONEME_FLAG_HAS_NUMBER;
		break;
	    case 'B':
	    case 'D':
	    case 'F':
	    case 'K':
	    case 'M':
	    case 'P':
	    case 'T':
		flags |= PHONEME_FLAG_HAS_INITIAL;
	    default:
		if (uniChar_is_SQL_wildchar(uniStr[i])){
		    flags |= PHONEME_FLAG_HAS_WILDCHAR;
		}
		break;
	}
    }
    return flags;
}


/*
 * @param uniStr string in gunichar array.
 * @param index the pointer to index.
 * @param accentRequired gboolean value stores whether the accent mark is required.
 * @return TRUE if uniStr[*index] is diaeresis u; FALSE otherwise.
 */
static gboolean is_diaeresis_u(gunichar *uniStr, glong *index, gboolean *accentRequired){
    *accentRequired=TRUE;
    switch(uniStr[*index]){
	case 'V':
	    return TRUE;
	case 0xDC: // 'Ü'
	    /* It is possible that accent mark is not required (can be omitted). */
	    if (*index==0){
		return TRUE;
	    }
	case 'U':
	    /* Decide later */
	    break;
	default:
	    return FALSE;
    }
    if (*index>0){
	switch(uniStr[*index-1]){
	    case 'J':
	    case 'Q':
	    case 'X':
	    case 'Y':
		*accentRequired=FALSE;
		return TRUE;
	    default:
		break;
	}
    }
    if (uniStr[*index+1]!=0){
	switch(uniStr[*index+1]){
	    case ':':
		(*index)++;
		return TRUE;
	    case 0xCA:  // 'Ê'
	    case 'E':
		return TRUE;
	    default:
		break;
	}
    }
    if (uniStr[*index]==0xDC){ // 'Ü'
	return TRUE;
    }
    *accentRequired=FALSE;
    return FALSE;
}

/*
 * @param uniStr string in gunichar array.
 * @param index the pointer to index.
 * @param accentRequired gboolean value stores whether the accent mark is required.
 * @return TRUE if uniStr[*index] is diaeresis u; FALSE otherwise.
 */
gboolean is_circumflex_e(gunichar *uniStr, glong *index, gboolean *accentRequired){
    *accentRequired=TRUE;
    switch(uniStr[*index]){
	case 0xCA:  // 'Ê'
	    if (*index==0){
		return TRUE;
	    }
	case 'E':
	    break;
	default:
	    return FALSE;
    }
    if (index>0){
	switch(uniStr[*index-1]){
	    case 'I':
	    case 'Y':
	    case 'U':
	    case 'V':
	    case ':':  // 'U:'
	    case 0xDC: // 'Ü'
		*accentRequired=FALSE;
		return TRUE;
	    default:
		break;
	}
    }
    if (uniStr[*index]==0xCA){ // 'Ê'
	return TRUE;
    }
    *accentRequired=FALSE;
    return FALSE;
}

gboolean pinYin_has_tone(const PinYin* pinYin){
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
    gboolean result=FALSE;
    int j,k;
    for (i=0;i<items_written;i++){
	if (uniChar_has_toneMark(uniStr[i],&j,&k)){
	    result=TRUE;
	    break;
	}
	if (g_unichar_isdigit(uniStr[i])){
	    result=TRUE;
	    break;
	}
    }
    g_free(uniStr);
    return result;
}

guint pinYin_get_tone(const PinYin* pinYin){
    guint tone=0;
    glong i,items_written;
    int j,k;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
    for (i=0;i<items_written;i++){
	if (uniChar_has_toneMark(uniStr[i],&j,&k)){
	    tone=k+1;
	    break;
	}else if (g_unichar_isdigit(uniStr[i])){
	    tone=uniStr[i]-'0';
	    break;
	}
    }
    g_free(uniStr);
    return tone;
}

guint pinYin_strip_tone(PinYin* pinYin){
    guint tone=0;
    glong i,items_written;
    int j,k;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
    initString(pinYin);
    for (i=0;i<items_written;i++){
	if (uniChar_has_toneMark(uniStr[i],&j,&k)){
	    utf8_concat_ucs4(pinYin,PINYIN_TONEMARKS[j][4]);
	    tone=k+1;
	    continue;
	}else if (g_unichar_isdigit(uniStr[i])){
	    tone=uniStr[i]-'0';
	}else{
	    utf8_concat_ucs4(pinYin,uniStr[i]);
	}
    }
    g_free(uniStr);
    return tone;
}


void pinYin_add_tone(PinYin* pinYin, guint tone, gboolean useTrailNumber){
    glong i,items_written;
    int j,k;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
    guint flags=pinYin_scan_fingerPrint(uniStr);
    char pinYin_tmp[PINYIN_MAX_LENGTH];
    initString(pinYin_tmp);

    for (i=0;i<items_written;i++){
	if (uniChar_is_vowel(uniStr[i],&j,&k)){
	    if (useTrailNumber || tone<=0){
		utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][4]);
	    }else {
		switch(j){
		    case 0: // A
			/* Tone mark on A if there is A. */
			utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][tone-1]);
			break;
		    case 1: // E
		    case 3: // O
			if (!(flags &  PHONEME_FLAG_HAS_A)){
			    utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][tone-1]);
			}else{
			    utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][4]);
			}
			break;
		    case 2: // I
			if (!(flags &  ( PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_E | PHONEME_FLAG_HAS_O))){
			    if ((i>items_written-2) || (uniStr[i+1]!='U') || (uniStr[i+1]!=0xDC) ){
				utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][tone-1]);
				break;
			    }
			}
			utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][4]);
			break;			
		    case 4: // U
			if (!(flags &  ( PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_E | PHONEME_FLAG_HAS_O))){
			    if ((i>items_written-2) || (uniStr[i+1]!='I') ){
				utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][tone-1]);
				break;
			    }
			}
			utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][4]);
			break;			
		    case 5: // Ü
			if (!(flags &  ( PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_E | PHONEME_FLAG_HAS_O))){
			    if ((i>items_written-2) || (uniStr[i+1]!='I') ){
				utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][tone-1]);
				break;
			    }
			}
			utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][4]);
			break;			
		    default:
			break;
		}
	    }
	}else if (g_unichar_isdigit(uniStr[i])){
	}else{
	    utf8_concat_ucs4(pinYin_tmp,uniStr[i]);
	}
    }
    if (useTrailNumber){
	if (tone!=0){
	    utf8_concat_ucs4(pinYin_tmp,tone+'0');
	}
    }
    g_free(uniStr);
    g_strlcpy(pinYin,pinYin_tmp,PINYIN_MAX_LENGTH);
}

PinYin *pinYin_convert_accent_format(const PinYin* pinYin, PinYin_Accent_Format toFormat, gboolean useTrailNumber){
    glong i,items_written;
    PinYin *pinYin_result=pinYin_new(pinYin);
    guint tone=pinYin_strip_tone(pinYin_result);
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin_result, -1 , &items_written);
    initString(pinYin_result);
    gboolean hasWildChar=FALSE;

    gboolean accentRequired;
    for(i=0;i<items_written;i++){
	if (uniChar_is_SQL_wildchar(uniStr[i])){
	    hasWildChar=TRUE;
	    utf8_concat_ucs4(pinYin_result,uniStr[i]);
	} else	if (is_diaeresis_u(uniStr,&i,&accentRequired)){
	    if (accentRequired){
		switch(toFormat){
		    case PINYIN_ACCENT_ALWAYS:
		    case PINYIN_ACCENT_ORIGINAL:
		    case PINYIN_ACCENT_UNIHAN:
			g_strlcat(pinYin_result,"Ü",PINYIN_MAX_LENGTH);
			break;
		    case PINYIN_ACCENT_TRAILING:
			g_strlcat(pinYin_result,"U:",PINYIN_MAX_LENGTH);
			break;
		    case PINYIN_ACCENT_INPUT_METHOD:
			g_strlcat(pinYin_result,"V",PINYIN_MAX_LENGTH);
			break;
		    case PINYIN_ACCENT_NONE:
			g_strlcat(pinYin_result,"U",PINYIN_MAX_LENGTH);
			break;
		}
	    }else{
		if (toFormat==PINYIN_ACCENT_ALWAYS){
		    g_strlcat(pinYin_result,"Ü",PINYIN_MAX_LENGTH);
		}else{
		    g_strlcat(pinYin_result,"U",PINYIN_MAX_LENGTH);
		}
	    }
	}else if(is_circumflex_e(uniStr,&i,&accentRequired)){
//	    printf("is_circumflex_e=TRUE, accent=%d\n",accentRequired);
	    if (accentRequired){
		switch(toFormat){
		    case PINYIN_ACCENT_ALWAYS:
		    case PINYIN_ACCENT_ORIGINAL:
			g_strlcat(pinYin_result,"Ê",PINYIN_MAX_LENGTH);
			break;
		    case PINYIN_ACCENT_UNIHAN:
		    case PINYIN_ACCENT_TRAILING:
		    case PINYIN_ACCENT_INPUT_METHOD:
		    case PINYIN_ACCENT_NONE:
			g_strlcat(pinYin_result,"E",PINYIN_MAX_LENGTH);
			break;
		}
	    }else{
		if (toFormat==PINYIN_ACCENT_ALWAYS){
		    g_strlcat(pinYin_result,"Ê",PINYIN_MAX_LENGTH);
		}else{
		    g_strlcat(pinYin_result,"E",PINYIN_MAX_LENGTH);
		}
	    }
	}else{
	    utf8_concat_ucs4(pinYin_result,uniStr[i]);
	}
    }
    if (!hasWildChar && tone==0){
	pinYin_add_tone(pinYin_result, 5, useTrailNumber);
    }else{
	pinYin_add_tone(pinYin_result, tone, useTrailNumber);
    }
    return pinYin_result;
}

static const P_Z_Rule *pinYin_find_rule(const char *pinYin_str,guint phonemeFlags, guint pos){
    int i=0;
    const P_Z_Rule *rule=&P_Z_RULES[i];
    while(rule!=NULL && rule->pinYin_phoneme!=NULL){
	if (flags_are_suitable(phonemeFlags, rule->mask, rule->match)){
//	    printf(" rule->pinYin_phoneme=%s, rule->zhuYin_symbol=%X\n", rule->pinYin_phoneme,  rule->zhuYin_symbol);
	    if (g_str_has_prefix(pinYin_str,rule->pinYin_phoneme)){
		if ((pos & PHONEME_FLAG_HAS_INITIAL) && zhuYin_Symbol_is_initial(rule->zhuYin_symbol)){
		    return rule;
		}else if ((pos & PHONEME_FLAG_HAS_MEDIAL) && zhuYin_Symbol_is_medial(rule->zhuYin_symbol)){
		    return rule;
		}else if ((pos & PHONEME_FLAG_HAS_FINAL) && zhuYin_Symbol_is_final(rule->zhuYin_symbol)){
		    return rule;
		}else if ( zhuYin_Symbol_is_tone(rule->zhuYin_symbol)){
		    return rule;
		}
	    }
	}
	rule=&P_Z_RULES[++i];
    }
    return NULL;
}


ZhuYin *pinYin_to_zhuYin(const PinYin* pinYin, ZhuYin_ToneMark_Format toFormat){
    PinYin *pinYinTmp=pinYin_convert_accent_format(pinYin, PINYIN_ACCENT_ALWAYS,TRUE);
    ZhuYin zhuYinTmp[ZHUYIN_MAX_LENGTH];
    initString(zhuYinTmp);
    glong items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYinTmp, -1 , &items_written);
    guint flags=pinYin_scan_fingerPrint(uniStr);
    char *p=pinYinTmp;
    guint pos =  PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL;

    const P_Z_Rule *rule=NULL;
    while (*p!='\0'){
        // printf("p=%s| *p=%d\n",p,*p);
	rule=pinYin_find_rule(p,flags,pos);
	g_assert(rule);
	if (zhuYin_Symbol_is_initial(rule->zhuYin_symbol)){
	    pos &= ~PHONEME_FLAG_HAS_INITIAL;
	}else if (zhuYin_Symbol_is_medial(rule->zhuYin_symbol)){
	    pos &= ~(PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL);
	}else if (zhuYin_Symbol_is_final(rule->zhuYin_symbol)){
	    pos &= ~(PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL);
	}
	utf8_concat_ucs4(zhuYinTmp,rule->zhuYin_symbol);
	p+=strlen(rule->pinYin_phoneme);
    }
    ZhuYin *zhuYin=zhuYin_convert_toneMark_format(zhuYinTmp,toFormat);
    g_free(pinYinTmp);
    g_free(uniStr);
    return zhuYin;
}

/*========================================
 * ZhuYin functions.
 */
ZhuYin *zhuYin_new(const char *zhuYin_str){
    ZhuYin *zhuYin=NULL;
    if (isEmptyString(zhuYin_str)){
	zhuYin=NEW_ARRAY_INSTANCE(ZHUYIN_MAX_LENGTH,char);
	initString(zhuYin);
    }else{
	zhuYin=g_utf8_strup(zhuYin_str,ZHUYIN_MAX_LENGTH);
    }
    return zhuYin;
}

guint zhuYin_get_tone(const ZhuYin* zhuYin){
    guint tone=0,toneTmp;
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuYin, -1 , &items_written);
    for (i=0;i<items_written;i++){
	toneTmp=zhuYin_Symbol_to_toneMark_id(uniStr[i]);
	if (toneTmp){
	    tone=toneTmp;
	}
    }
    g_free(uniStr);
    return tone;
}

guint zhuYin_strip_tone(ZhuYin* zhuYin){
    guint tone=0,toneTmp;
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuYin, -1 , &items_written);
    initString(zhuYin);
    for (i=0;i<items_written;i++){
	toneTmp=zhuYin_Symbol_to_toneMark_id(uniStr[i]);
	if (toneTmp){
	    tone=toneTmp;
	}else{
	    utf8_concat_ucs4(zhuYin,uniStr[i]);
	}
    }
    g_free(uniStr);
    return tone;
}

void zhuYin_add_tone(ZhuYin* zhuYin, guint tone, ZhuYin_ToneMark_Format toFormat){
    ZhuYin zhuYin_tmp[ZHUYIN_MAX_LENGTH];
    initString(zhuYin_tmp);
    if (tone==5 && toFormat==ZHUYIN_TONEMARK_ORIGINAL){
	utf8_concat_ucs4(zhuYin_tmp,ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_NEUTRAL]);
	g_strlcat(zhuYin_tmp,zhuYin,ZHUYIN_MAX_LENGTH);
    }else{
	g_strlcat(zhuYin_tmp,zhuYin,ZHUYIN_MAX_LENGTH);
	if (tone>0){
	    switch (toFormat){
		case ZHUYIN_TONEMARK_ALWAYS:
		    utf8_concat_ucs4(zhuYin_tmp,zhuYin_Symbol_from_toneMark_id(tone));
		    break;
		case ZHUYIN_TONEMARK_ORIGINAL:
		case ZHUYIN_TONEMARK_INPUT_METHOD:
		    if (tone!=1){
			utf8_concat_ucs4(zhuYin_tmp,zhuYin_Symbol_from_toneMark_id(tone));
		    }else{
			/* 1st tone omitted */
		    }
		    break;
		case ZHUYIN_TONEMARK_NUMERICAL:
		    utf8_concat_ucs4(zhuYin_tmp,'0'+tone);
		    break;
	    }
	}
    }
    g_strlcpy(zhuYin,zhuYin_tmp,ZHUYIN_MAX_LENGTH);
}

ZhuYin *zhuYin_convert_toneMark_format(const ZhuYin* zhuYin, ZhuYin_ToneMark_Format toFormat){
    ZhuYin *zhuYin_result=zhuYin_new(zhuYin);
    guint tone=zhuYin_strip_tone(zhuYin_result);
    int i;
    gboolean hasWildChar=FALSE;
    for(i=0;zhuYin_result[i]!='\0';i++){
	if (uniChar_is_SQL_wildchar(zhuYin_result[i])){
	    hasWildChar=TRUE;
	}
    }

    if (!hasWildChar && tone==0){
	zhuYin_add_tone(zhuYin_result,1,toFormat);
    }else{
	zhuYin_add_tone(zhuYin_result,tone,toFormat);
    }
    return zhuYin_result;
}

static guint zhuYin_scan_fingerPrint(gunichar *uniStr){
    guint phonemeFlags=0;
    int i;
    ZhuYin_Symbol_Id zuId;
    
    for(i=0;uniStr[i]!=0;i++){
	if (uniChar_is_SQL_wildchar(uniStr[i])){
	    phonemeFlags |= PHONEME_FLAG_HAS_WILDCHAR;
	}else{
	    zuId=zhuYin_Symbol_get_id(uniStr[i]);
	    phonemeFlags |=ZHUYIN_SYMBOL_PROPERTIES[zuId].phonemeFlags;
	}
    }
    return phonemeFlags;
}

static const P_Z_Rule *zhuYin_find_rule(ZhuYin_Symbol zSym,guint phonemeFlags,guint pos){
    int i=0;
    const P_Z_Rule *rule=&P_Z_RULES[i];
    while(rule!=NULL && rule->pinYin_phoneme!=NULL){
	if (flags_are_suitable(phonemeFlags, rule->mask, rule->match)){
	    if (zSym==rule->zhuYin_symbol){
//                printf(" rule->pinYin_phoneme=%s, rule->zhuYin_symbol=%X\n", rule->pinYin_phoneme,  rule->zhuYin_symbol);
		if ((pos & PHONEME_FLAG_HAS_INITIAL) && zhuYin_Symbol_is_initial(zSym)){
		    return rule;
		}else if ((pos & PHONEME_FLAG_HAS_MEDIAL) && zhuYin_Symbol_is_medial(zSym)){
		    return rule;
		}else if ((pos & PHONEME_FLAG_HAS_FINAL) && zhuYin_Symbol_is_final(zSym)){
		    return rule;
		}else if (zhuYin_Symbol_is_tone(zSym)){
		    return rule;
		}else if (uniChar_is_SQL_wildchar(zSym)){
		    return rule;
		}

	    }
	}
	rule=&P_Z_RULES[++i];
    }
    return NULL;
}


PinYin *zhuYin_to_pinYin(const ZhuYin* zhuYin, PinYin_Accent_Format toFormat,gboolean useTrailNumber){
    const P_Z_Rule *rule=NULL;
    glong i,items_written;
    ZhuYin *zhuYinTmp=zhuYin_convert_toneMark_format(zhuYin,ZHUYIN_TONEMARK_ALWAYS);
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuYinTmp, -1 , &items_written);
    guint pos =  PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL;

    PinYin pinYinTmp[PINYIN_MAX_LENGTH];
    initString(pinYinTmp);
    guint phonemeFlags=zhuYin_scan_fingerPrint(uniStr);
    for(i=0;i<items_written;i++){
//	printf(" phonemeFlags=%X, pos %X uniStr[%d]=%X\n", phonemeFlags, pos,i,uniStr[i]);
	rule=zhuYin_find_rule(uniStr[i],phonemeFlags,pos);
	g_assert(rule);
	if (zhuYin_Symbol_is_initial(rule->zhuYin_symbol)){
	    pos &= ~PHONEME_FLAG_HAS_INITIAL;
	}else if (zhuYin_Symbol_is_medial(rule->zhuYin_symbol)){
	    pos &= ~(PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL);
	}else if (zhuYin_Symbol_is_final(rule->zhuYin_symbol)){
	    pos &= ~(PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL);
	}
	g_strlcat(pinYinTmp,rule->pinYin_phoneme,PINYIN_MAX_LENGTH);
    }
    PinYin *pinYin=pinYin_convert_accent_format(pinYinTmp,toFormat,useTrailNumber);
    g_free(zhuYinTmp);
    return pinYin;
}


ZhuYin_Symbol zhuYin_Symbol_from_id(ZhuYin_Symbol_Id id){
    if (id<0 || id >= ZHUYIN_SYMBOL_COUNT )
	return 0;
    return ZHUYIN_SYMBOL_LIST[id];
}

ZhuYin_Symbol_Id zhuYin_Symbol_get_id(ZhuYin_Symbol zSym){
    int j;
    for (j=ZHUYIN_SYMBOL_COUNT-1;j>=0;j--){
	if (ZHUYIN_SYMBOL_LIST[j]==zSym){
	    return j;
	}
    }
    return ZHUYIN_INVALID_SYMBOL;
}

gboolean zhuYin_Symbol_is_initial(ZhuYin_Symbol zSym){
    if ((zSym>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_B]) &&
	    (zSym<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_S])){
	return TRUE;
    }
    return FALSE;
}

gboolean zhuYin_Symbol_is_medial(ZhuYin_Symbol zSym){
    if ((zSym>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_I]) &&
	    (zSym<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_U_DIAERESIS])){
	return TRUE;
    }
    return FALSE;
}

gboolean zhuYin_Symbol_is_final(ZhuYin_Symbol zSym){
    if ((zSym>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_A]) &&
	(zSym<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_ER])){
	return TRUE;
    }
    return FALSE;
}


gboolean zhuYin_Symbol_is_tone(ZhuYin_Symbol zSym){
    return (zhuYin_Symbol_to_toneMark_id(zSym)==0) ? FALSE : TRUE;
}

guint zhuYin_Symbol_to_toneMark_id(ZhuYin_Symbol zSym){
    switch (zSym){
	case  '1':
	case  0x02C9:   // "ˉ"
	    return 1;
	case  '2':
	case  0x02CA:   // "ˊ"
	    return 2;
	case  '3':
	case  0x02C7:   // "ˇ"
	    return 3;
	case  '4':
	case  0x02CB:   // "ˋ"
	    return 4;
	case  '5':
	case 0x02D9:   // "˙"
	    return 5;
	default:
	    break;
    }
    return 0;
}

ZhuYin_Symbol zhuYin_Symbol_from_toneMark_id(guint toneMark_id){
    switch (toneMark_id){
	case 1:
	    return ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_1];
	case 2:
	    return ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_2];
	case 3:
	    return ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_3];
	case 4:
	    return ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_4];
	case 5:
	    return ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_NEUTRAL];
    }
    return 0;
}

/*========================================
 * ZhuYin database conversion functions.
 */

void pinYin_convert_accent_format_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==3);
    char pinYinTmp[PINYIN_MAX_LENGTH];
    const char *pinYin=sqlite_value_signed_text_buffer(pinYinTmp,argv[0]);
    int toFormat= (sqlite3_value_type(argv[1])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[1]): 0;
    gboolean useTrailNumber= 
	(((sqlite3_value_type(argv[2])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[2]): 0)==0)? FALSE: TRUE;
    char *pStr=pinYin_convert_accent_format(pinYin,toFormat,useTrailNumber);
    sqlite3_result_text(context,pStr,-1,g_free);
}

void pinYin_to_zhuYin_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==2);
    char pinYinTmp[PINYIN_MAX_LENGTH];
    const char *pinYin=sqlite_value_signed_text_buffer(pinYinTmp,argv[0]);
    int toFormat= (sqlite3_value_type(argv[1])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[1]): 0;
    char *pStr=pinYin_to_zhuYin(pinYin,toFormat);
    sqlite3_result_text(context,pStr,-1,g_free);
}

void zhuYin_convert_toneMark_format_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==2);
    char zhuYinTmp[ZHUYIN_MAX_LENGTH];
    const char *zhuYin=sqlite_value_signed_text_buffer(zhuYinTmp,argv[0]);
    int toFormat= (sqlite3_value_type(argv[1])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[1]): 0;
    char *pStr=zhuYin_convert_toneMark_format(zhuYin,toFormat);
    sqlite3_result_text(context,pStr,-1,g_free);
}

void zhuYin_to_pinYin_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==3);
    char zhuYinTmp[ZHUYIN_MAX_LENGTH];
    const char *zhuYin=sqlite_value_signed_text_buffer(zhuYinTmp,argv[0]);
    int toFormat= (sqlite3_value_type(argv[1])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[1]): 0;
    gboolean useTrailNumber= 
	(((sqlite3_value_type(argv[2])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[2]): 0)==0)? FALSE: TRUE;
    char *pStr=zhuYin_to_pinYin(zhuYin,toFormat,useTrailNumber);
    sqlite3_result_text(context,pStr,-1,g_free);
}




