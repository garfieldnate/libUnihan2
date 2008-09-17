/** 
 * @file Unihan_Phonetic.c
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

#define PHONEME_FLAG_HAS_INITIAL   0x001
#define PHONEME_FLAG_HAS_MEDIAL    0x002
#define PHONEME_FLAG_HAS_FINAL     0x004
#define PHONEME_FLAG_HAS_JQX       0x008 // ㄐ, ㄑ, ㄒ
#define PHONEME_FLAG_HAS_ZCSR      0x010 // ㄓ, ㄔ, ㄕ, ㄖ, ㄗ, ㄘ, ㄙ
#define PHONEME_FLAG_HAS_A         0x020 
#define PHONEME_FLAG_HAS_FINAL_N   0x040 // ㄢ, ㄣ, ㄤ, ㄥ
#define PHONEME_FLAG_HAS_FINAL_G   0x080 //ㄤ, ㄥ
#define PHONEME_FLAG_HAS_TONEMARK  0x100



const P_Z_Rules PHONEMES_LIST[]={
    {"ZHI",  "ㄓ", PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0},
    {"CHI",  "ㄔ", PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, 
    {"SHI",  "ㄕ", PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0},
    {"RI",   "ㄖ", PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, 
    {"ZI",   "ㄗ", PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, 
    {"CI",   "ㄘ", PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, 
    {"SI",   "ㄙ", PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL, 0}, 
    {"YI",   "ㄧ", PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_FINAL, 0}, 
    /* For ㄧㄣ & ㄧㄥ */
    {"YI",  "ㄧ", PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_A | PHONEME_FLAG_HAS_FINAL_N, PHONEME_FLAG_HAS_FINAL_N},
    {"WU",  "ㄨ", PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_FINAL, 0}, 
    {"YÜ",  "ㄩ", PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_FINAL_G, 0 }, 
    {"YO",  "ㄩ", PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_FINAL_G, PHONEME_FLAG_HAS_FINAL_G }, 
    {"I",   "ㄧ", PHONEME_FLAG_HAS_INITIAL, PHONEME_FLAG_HAS_INITIAL},
    {"Y",   "ㄧ", PHONEME_FLAG_HAS_INITIAL, 0},
    {"W",   "ㄨ", PHONEME_FLAG_HAS_INITIAL, 0},
    {"Ü",   "ㄩ", PHONEME_FLAG_HAS_INITIAL, PHONEME_FLAGS_HAS_INITIAL},
    {"ENG", "ㄥ", PHONEME_FLAG_HAS_MEDIAL, 0},
    {"EN",  "ㄣ", PHONEME_FLAG_HAS_MEDIAL, 0},
    {"EI",  "ㄟ", PHONEME_FLAG_HAS_MEDIAL, 0},
    {"E",   "ㄜ", PHONEME_FLAG_HAS_MEDIAL, 0},
    {"OU",  "ㄡ", PHONEME_FLAG_HAS_MEDIAL, 0},
    {"NG",  "ㄥ", PHONEME_FLAG_HAS_MEDIAL, PHONEME_FLAG_HAS_MEDIAL},
    {"N",   "ㄣ", PHONEME_FLAG_HAS_MEDIAL, PHONEME_FLAG_HAS_MEDIAL},
    {"I",   "ㄟ", PHONEME_FLAG_HAS_MEDIAL, PHONEME_FLAG_HAS_MEDIAL},
    {"U",   "ㄡ", PHONEME_FLAG_HAS_MEDIAL, PHONEME_FLAG_HAS_MEDIAL},
    /* Unconditional matched. */
    {"B",   "ㄅ", 0, 0},
    {"P",   "ㄆ", 0, 0},
    {"M",   "ㄇ", 0, 0},
    {"F",   "ㄈ", 0, 0},
    {"D",   "ㄉ", 0, 0},
    {"T",   "ㄊ", 0, 0},
    {"N",   "ㄋ", 0, 0},
    {"L",   "ㄌ", 0, 0},
    {"G",   "ㄍ", 0, 0},
    {"K",   "ㄎ", 0, 0},
    {"H",   "ㄏ", 0, 0},
    {"J",   "ㄐ", 0, 0},
    {"Q",   "ㄑ", 0, 0},
    {"X",   "ㄒ", 0, 0},
    {"ZH",  "ㄓ", 0, 0},
    {"CH",  "ㄔ", 0, 0},
    {"SH",  "ㄕ", 0, 0},
    {"R",   "ㄖ", 0, 0},
    {"Z",   "ㄗ", 0, 0},
    {"C",   "ㄘ", 0, 0},
    {"S",   "ㄙ", 0, 0},
    {"ANG", "ㄤ", 0, 0},
    {"AI",  "ㄞ", 0, 0},
    {"AO",  "ㄠ", 0, 0},
    {"AN",  "ㄢ", 0, 0},
    {"Ê",   "ㄝ", 0, 0},
    {"A",   "ㄚ", 0, 0},   
    {"O",   "ㄛ", 0, 0},
    {"ER",  "ㄦ", 0, 0},
    {"1",   "ˉ", 0, 0},
    {"2",   "ˊ", 0, 0},
    {"3",   "ˇ", 0, 0},
    {"4",   "ˋ", 0, 0},
    {"5",   "˙", 0, 0},
    {NULL}
}

const P_Z_Properties PHONEMES_LIST_INITIAL_ONLY[]={
    {"ZHI",  "ㄓ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"CHI",  "ㄔ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"SHI",  "ㄕ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"RI",   "ㄖ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"ZI",   "ㄗ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"CI",   "ㄘ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"SI",   "ㄙ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {NULL}
};

const P_Z_Properties PHONEMES_LIST_INITIAL[]={
    {"B",   "ㄅ",PINYIN_PHONEME_TYPE_INITIAL},
    {"P",   "ㄆ",PINYIN_PHONEME_TYPE_INITIAL},
    {"M",   "ㄇ",PINYIN_PHONEME_TYPE_INITIAL},
    {"F",   "ㄈ",PINYIN_PHONEME_TYPE_INITIAL},
    {"D",   "ㄉ",PINYIN_PHONEME_TYPE_INITIAL},
    {"T",   "ㄊ",PINYIN_PHONEME_TYPE_INITIAL},
    {"N",   "ㄋ",PINYIN_PHONEME_TYPE_INITIAL},
    {"L",   "ㄌ",PINYIN_PHONEME_TYPE_INITIAL},
    {"G",   "ㄍ",PINYIN_PHONEME_TYPE_INITIAL},
    {"K",   "ㄎ",PINYIN_PHONEME_TYPE_INITIAL},
    {"H",   "ㄏ",PINYIN_PHONEME_TYPE_INITIAL},
    {"J",   "ㄐ",PINYIN_PHONEME_TYPE_INITIAL},
    {"Q",   "ㄑ",PINYIN_PHONEME_TYPE_INITIAL},
    {"X",   "ㄒ",PINYIN_PHONEME_TYPE_INITIAL},
    {"ZH",  "ㄓ",PINYIN_PHONEME_TYPE_INITIAL},
    {"CH",  "ㄔ",PINYIN_PHONEME_TYPE_INITIAL},
    {"SH",  "ㄕ",PINYIN_PHONEME_TYPE_INITIAL},
    {"R",   "ㄖ",PINYIN_PHONEME_TYPE_INITIAL},
    {"Z",   "ㄗ",PINYIN_PHONEME_TYPE_INITIAL},
    {"C",   "ㄘ",PINYIN_PHONEME_TYPE_INITIAL},
    {"S",   "ㄙ",PINYIN_PHONEME_TYPE_INITIAL},
    {NULL}
};

const P_Z_Properties PHONEMES_LIST_SPECIAL_NO_INITIAL[]={
    {"WENG",   "ㄨㄥ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"WEN",    "ㄨㄣ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YÜN",   "ㄩㄣ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YONG",   "ㄩㄥ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YOU",    "ㄧㄡ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YING",    "ㄧㄥ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YIN",    "ㄧㄣ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YI",    "ㄧ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"WU",   "ㄨ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {NULL}
};

const P_Z_Properties PHONEMES_LIST_SPECIAL[]={
    {"IU",    "ㄧㄡ",PINYIN_PHONEME_TYPE_SPECIAL},
    {"UN",    "ㄨㄣ",PINYIN_PHONEME_TYPE_SPECIAL},
    {"ONG",   "ㄨㄥ",PINYIN_PHONEME_TYPE_SPECIAL},
    {"ÜN",     "ㄩㄣ",PINYIN_PHONEME_TYPE_SPECIAL},
    {"IONG",   "ㄩㄥ",PINYIN_PHONEME_TYPE_SPECIAL},
    {NULL}
};

const P_Z_Properties PHONEMES_LIST_MEDIAL_NO_INITIAL[]={
    {"YÜ",   "ㄩ",PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL},
    {"Y",   "ㄧ",PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL},
    {"W",   "ㄨ",PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL},
    {NULL}
};

const P_Z_Properties PHONEMES_LIST_MEDIAL[]={
    {"I",  "ㄧ",PINYIN_PHONEME_TYPE_MEDIAL},
    {"U",   "ㄨ",PINYIN_PHONEME_TYPE_MEDIAL},
    {"Ü",   "ㄩ",PINYIN_PHONEME_TYPE_MEDIAL},
    {NULL}
};


const P_Z_Properties PHONEMES_LIST_FINAL_WITH_MEDIAL[]={
    {"NG", "ㄥ",PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL},
    {"N",  "ㄣ",PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL},
    {"I",  "ㄟ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"U",  "ㄡ",PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL},
    {NULL}
};


const P_Z_Properties PHONEMES_LIST_FINAL_WITHOUT_MEDIAL[]={
    {"ENG", "ㄥ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"EN",  "ㄣ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"EI",  "ㄟ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"ER",  "ㄦ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"E",   "ㄜ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"OU",  "ㄡ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {NULL}
};



const P_Z_Properties PHONEMES_LIST_FINAL[]={
    {"ANG", "ㄤ",PINYIN_PHONEME_TYPE_FINAL},
    {"AI",  "ㄞ",PINYIN_PHONEME_TYPE_FINAL},
    {"AO",  "ㄠ",PINYIN_PHONEME_TYPE_FINAL},
    {"AN",  "ㄢ",PINYIN_PHONEME_TYPE_FINAL},
    {"Ê",   "ㄝ",PINYIN_PHONEME_TYPE_FINAL},
    {"A",   "ㄚ",PINYIN_PHONEME_TYPE_FINAL},   
    {"O",   "ㄛ",PINYIN_PHONEME_TYPE_FINAL},
    {NULL}
};

const P_Z_Properties PHONEMES_LIST_TONEMARK[]={
    {"1",   "ˉ",PINYIN_PHONEME_TYPE_TONEMARK},
    {"2",   "ˊ",PINYIN_PHONEME_TYPE_TONEMARK},
    {"3",   "ˇ",PINYIN_PHONEME_TYPE_TONEMARK},
    {"4",   "ˋ",PINYIN_PHONEME_TYPE_TONEMARK},
    {"5",   "˙",PINYIN_PHONEME_TYPE_TONEMARK},
    {NULL}
};

const P_Z_Properties *PHONEMES_LIST[]={
    PHONEMES_LIST_INITIAL_ONLY, 
    PHONEMES_LIST_INITIAL,      

    PHONEMES_LIST_SPECIAL_NO_INITIAL, 
    PHONEMES_LIST_SPECIAL,            

    PHONEMES_LIST_MEDIAL_NO_INITIAL, 
    PHONEMES_LIST_MEDIAL,            

    PHONEMES_LIST_FINAL_WITH_MEDIAL, 
    PHONEMES_LIST_FINAL_WITHOUT_MEDIAL, 
    PHONEMES_LIST_FINAL,             

    PHONEMES_LIST_TONEMARK,
    NULL
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
    0x00DC,  // "Ǖ"
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

static gboolean uniChar_has_toneMark(gunichar uniChar, int *i, int *j){
    for (*i=0;*i<6;(*i)++){
	for (*j=0;*j<5;(*j)++){
	    if (PINYIN_TONEMARKS[*i][*j]==uniChar){
		return TRUE;
	    }
	}
    }
    *i=-1;
    *j=-1;
    return FALSE;
}


#define PINYIN_HAS_A		0x1
#define PINYIN_HAS_E		0x2
#define PINYIN_HAS_I		0x4
#define PINYIN_HAS_O		0x8
#define PINYIN_HAS_U		0x10
#define PINYIN_HAS_U_DIAERESIS	0x20
#define PINYIN_HAS_E_CIRCUMFLEX	0x40
#define PINYIN_HAS_Y		0x80
#define PINYIN_HAS_LN		0x100
#define PINYIN_HAS_JQX		0x200
#define PINYIN_HAS_ZCSR		0x400   // ㄓ, ㄔ, ㄕ, ㄖ, ㄗ, ㄘ, ㄙ
#define PINYIN_HAS_N_FINAL	0x800   // ㄢ, ㄣ, ㄤ, ㄥ
#define PINYIN_HAS_G_FINAL	0x1000   //ㄤ, ㄥ
#define PINYIN_HAS_INITIAL_OTHER 0x2000
#define PINYIN_HAS_NUMBER	0x4000
#define PINYIN_HAS_COLON	0x8000


static guint uniStr_scan_pinYin_fingerPrint(gunichar *uniStr){
    int i,j,k;
    guint flags=0;
    for (i=0;uniStr[i]!=0;i++){
	if (uniChar_has_toneMark(uniStr[i],&j,&k)){
	    flags |= 1 << (j+1);
	    continue;
	}
	switch(uniStr[i]){
	    case 'W':
		flags |= PINYIN_HAS_U;
		break;
	    case 'V':
		flags |= PINYIN_HAS_U_DIAERESIS;
		break;
	    case 0xCA:  // 'Ê'
		flags |= PINYIN_HAS_E_CIRCUMFLEX;
		break;
	    case 'Y':
		flags |= PINYIN_HAS_Y;
		break;
	    case 'L':
	    case 'N':
		flags |= PINYIN_HAS_LN;
		break;
	    case 'J':
	    case 'Q':
	    case 'X':
		flags |= PINYIN_HAS_JQX;
		break;
	    case 'Z':
	    case 'C':
	    case 'S':
	    case 'R':
		if (i==0)
		    flags |= PINYIN_HAS_ZCSR;
		break;
	    case 'H':
		if (i==0)
		    flags |= PINYIN_HAS_INITIAL_OTHER;
		break;
	    case 'N':
		if (i>0)
		    flags |= PINYIN_HAS_N_FINAL;
		else
		    flags |= PINYIN_HAS_INITIAL_OTHER;
		break;
	    case 'G':
		if (i>0)
		    flags |= PINYIN_HAS_G_FINAL;
		else
		    flags |= PINYIN_HAS_INITIAL_OTHER;
		break;
	    case ':':
		flags |= PINYIN_HAS_COLON;
		break;
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
		flags |= PINYIN_HAS_COLON;
		break;


	    default:

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

gboolean pinYin_has_toneMark(const PinYin* pinYin){
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

guint pinYin_strip_toneMark(PinYin* pinYin){
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



void pinYin_add_toneMark(PinYin* pinYin, guint tone, gboolean useTrailNumber){
    glong i,items_written;
    int j,k;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
    guint flags=uniStr_scan_pinYin_fingerPrint(uniStr);
    char pinYin_tmp[PINYIN_MAX_LENGTH];
    initString(pinYin_tmp);

    for (i=0;i<items_written;i++){
	if (uniChar_has_toneMark(uniStr[i],&j,&k)){
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
			if (!(flags &  PINYIN_HAS_A)){
			    utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][tone-1]);
			}else{
			    utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][4]);
			}
			break;
		    case 2: // I
			if (!(flags &  ( PINYIN_HAS_A | PINYIN_HAS_E | PINYIN_HAS_O))){
			    if ((i>items_written-2) || (uniStr[i+1]!='U') || (uniStr[i+1]!=0xDC) ){
				utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][tone-1]);
				break;
			    }
			}
			utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][4]);
			break;			
		    case 4: // U
			if (!(flags &  ( PINYIN_HAS_A | PINYIN_HAS_E | PINYIN_HAS_O))){
			    if ((i>items_written-2) || (uniStr[i+1]!='I') ){
				utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][tone-1]);
				break;
			    }
			}
			utf8_concat_ucs4(pinYin_tmp,PINYIN_TONEMARKS[j][4]);
			break;			
		    case 5: // Ü
			if (!(flags &  ( PINYIN_HAS_A | PINYIN_HAS_E | PINYIN_HAS_O))){
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
	    if (useTrailNumber){
		utf8_concat_ucs4(pinYin_tmp,tone+'0');
	    }
	}else{
	    utf8_concat_ucs4(pinYin_tmp,uniStr[i]);
	}
    }
    g_free(uniStr);
    g_strlcpy(pinYin,pinYin_tmp,PINYIN_MAX_LENGTH);
}

PinYin *pinYin_convert_accent_format(const PinYin* pinYin, PinYin_Accent_Format toFormat, gboolean useTrailNumber){
    glong i,items_written;
    PinYin *pinYin_result=pinYin_new(pinYin);
    guint tone=pinYin_strip_toneMark(pinYin_result);
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin_result, -1 , &items_written);
    initString(pinYin_result);

    gboolean accentRequired;
    for(i=0;i<items_written;i++){
//	g_debug("uniStr[%d]=%x\n",i,uniStr[i]);
	if (is_diaeresis_u(uniStr,&i,&accentRequired)){
//	    g_debug("is_diaeresis_u=TRUE i=%d accentRequired=%d\n",i,accentRequired);
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
//	    g_debug("is_circumflex_e=TRUE");
	    if (accentRequired){
//		g_debug("accentRequire=TRUE");
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
//		g_debug("accentRequire=FALSE");
		if (toFormat==PINYIN_ACCENT_ALWAYS){
		    g_strlcat(pinYin_result,"Ê",PINYIN_MAX_LENGTH);
		}else{
		    g_strlcat(pinYin_result,"E",PINYIN_MAX_LENGTH);
		}
	    }
	}else{
//	    g_debug("is_eu=FALSE");
//
	    utf8_concat_ucs4(pinYin_result,uniStr[i]);
	}
    }
    pinYin_add_toneMark(pinYin_result, tone, useTrailNumber);
    return pinYin_result;
}

static const P_Z_Properties *pinYin_determine_properties(const char *pinYin_str, PinYin_Phoneme_Type prev){
    const P_Z_Properties *prop=NULL;

    switch(prev){
	case PINYIN_PHONEME_INVALID_TYPE:
	    // Start of pinYin
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_INITIAL_ONLY))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_INITIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_SPECIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL))!=NULL)
		break;
//            if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL_ONLY))!=NULL)
//                break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_INVALID_TYPE");

	case PINYIN_PHONEME_TYPE_INITIAL_ONLY:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_INITIAL_ONLY");

	case PINYIN_PHONEME_TYPE_INITIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_SPECIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_INITIAL");

	case PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL:
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_SPECIAL_NO_INITIAL");

	case PINYIN_PHONEME_TYPE_SPECIAL:
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_SPECIAL");

	case PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_MEDIAL_NO_INITIAL");

	case PINYIN_PHONEME_TYPE_MEDIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_MEDIAL");

//        case PINYIN_PHONEME_TYPE_FINAL_ONLY:
//            if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
//                break;
//            g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_ONLY");

	case PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_WITH_MEDIAL");

	case PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		 break;
    	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_WITHOUT_MEDIAL");

	case PINYIN_PHONEME_TYPE_FINAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL");

	case PINYIN_PHONEME_TYPE_TONEMARK:
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_TONEMARK");

    }
    return prop;
}

ZhuYin *pinYin_to_zhuYin(const PinYin* pinYin, ZhuYin_ToneMark_Format toFormat){
    PinYin *pinYinTmp=pinYin_convert_accent_format(pinYin, PINYIN_ACCENT_ALWAYS,FALSE);
//    g_debug("pinYin=%s pinYinTmp=%s|\n",pinYin,pinYinTmp);
    ZhuYin *zhuYinTmp=zhuYin_new(NULL);
    char *p=pinYinTmp;
    PinYin_Phoneme_Type pType=PINYIN_PHONEME_INVALID_TYPE;
    const P_Z_Properties *prop=NULL;
    while (*p!='\0'){
//	printf("p=%s| *p=%d\n",p,*p);
	if (*p=='1'){
	    break;
	}
	prop=pinYin_determine_properties(p,pType);
	g_assert(prop);
	pType=prop->pType;
	g_strlcat(zhuYinTmp,prop->zhuYin,ZHUYIN_MAX_LENGTH);
//	printf("  prop->pType=%d prop->pinYin_phoneme=%s prop->zhuYin=%s zhuYinTmp=%s\n",
//		prop->pType, prop->pinYin_phoneme, prop->zhuYin, zhuYinTmp);
	p+=strlen(prop->pinYin_phoneme);
    }
    ZhuYin *zhuYin=zhuYin_convert_toneMark_format(zhuYinTmp,toFormat);
    g_free(pinYinTmp);
    g_free(zhuYinTmp);
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


guint zhuYin_strip_toneMark(ZhuYin* zhuYin){
    guint tone=1,toneTmp;
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
    return tone;
}

void zhuYin_add_toneMark(ZhuYin* zhuYin, guint tone, ZhuYin_ToneMark_Format toFormat){
    ZhuYin zhuYin_tmp[ZHUYIN_MAX_LENGTH];
    if (tone==5 && toFormat==ZHUYIN_TONEMARK_ORIGINAL){
	utf8_concat_ucs4(zhuYin_tmp,ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_NEUTRAL]);
    }else{
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

ZhuYin *zhuYin_convert_toneMark_format(const ZhuYin* zhuYin, ZhuYin_ToneMark_Format toFormat){
    ZhuYin *zhuYin_result=zhuYin_new(zhuYin);
    guint tone=zhuYin_strip_toneMark(zhuYin_result);
    zhuYin_add_toneMark(zhuYin_result,tone,toFormat);
    return zhuYin_result;
}

static guint uniStr_scan_zhuYin_fingerPrint(gunichar *uniStr){
    guint phonemeFlags=0;
    int i;
    for(i=0;uniStr[i]!=0;i++){
	if (uniStr[i]>=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_B] && 
		uniStr[i]<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_S]){
	    phonemeFlags |= PHONEME_FLAG_HAS_INITIAL;

	}else if (uniStr[i]>=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_I] &&
	       	uniStr[i]<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_U_DIAERESIS]){
	    phonemeFlags |= PHONEME_FLAG_HAS_MEDIAL;

	}else if (uniStr[i]>=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_A] && 
		uniStr[i]<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_ER]){
	    phonemeFlags |= PHONEME_FLAG_HAS_FINAL;

	}else if (uniStr[i]>=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_1] && 
		uniStr[i]<= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_NEUTRAL]){
    	    phonemeFlags |= PHONEME_FLAG_HAS_TONEMARK;

	}else if (uniStr[i]>='1' && uniStr[i]<='5'){
	    phonemeFlags |= PHONEME_FLAG_HAS_TONEMARK;
	}
    }
    return phonemeFlags;
}


PinYin *zhuYin_to_pinYin(const ZhuYin* zhuYin, PinYin_Accent_Format toFormat,gboolean useTrailNumber){
    const P_Z_Properties *prop=NULL;
    glong i,items_written;
    ZhuYin *zhuYinTmp=zhuYin_convert_toneMark_format(zhuYin,ZHUYIN_TONEMARK_ALWAYS);
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuYinTmp, -1 , &items_written);
    const char* p=zhuYinTmp;
    glong prop_zhuYin_len;

    PinYin *pinYinTmp=pinYin_new(NULL);
    guint phonemeFlags=uniStr_scan_zhuYin_fingerPrint(uniStr);
    g_debug("phonemeFlags=%X\n",phonemeFlags);
    for(i=0;i<items_written;i++){
	prop=NULL;
	if (zhuYin_Symbol_is_initial(uniStr[i])){
	    if (phonemeFlags & (PHONEME_FLAG_HAS_MEDIAL | PHONEME_FLAG_HAS_FINAL)){
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_INITIAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): Initial symbol not found.",zhuYinTmp);
		}
	    }else{
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_INITIAL_ONLY))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_INITIAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): Initial symbol not found.",zhuYinTmp);
		}
	    }
	    
	}else if (zhuYin_Symbol_is_medial(uniStr[i])){
	    if (phonemeFlags & PHONEME_FLAG_HAS_INITIAL){
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_SPECIAL))!=NULL){
		    prop_zhuYin_len=g_utf8_strlen(prop->zhuYin,-1);
		    i+=prop_zhuYin_len-1;
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_MEDIAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): p=%s Special/Medial symbol not found.",zhuYinTmp,p);
		}

	    }else{
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL))!=NULL){
		    prop_zhuYin_len=g_utf8_strlen(prop->zhuYin,-1);
		    i+=prop_zhuYin_len-1;
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL))!=NULL){
		}else {
		    g_error("zhuYin_to_pinYin(%s): p=%s Non-initialed Special/Medial Symbol not found.",zhuYinTmp,p);
		}
	    }
	}else if (zhuYin_Symbol_is_final(uniStr[i])){
	    if (phonemeFlags & PHONEME_FLAG_HAS_MEDIAL){
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): p=%s Non-medialed Final Symbol not found.",zhuYinTmp,p);
		}
	    }else if (phonemeFlags & PHONEME_FLAG_HAS_INITIAL){	
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): p=%s  Final Symbol not found.",zhuYinTmp,p);
		}
	    }else{
		// Only the final.
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): p=%s  Final-Only Symbol not found.",zhuYinTmp,p);
		}
	    }
	}else if (zhuYin_Symbol_is_toneMark(uniStr[i])){
	    if ((phonemeFlags & (PHONEME_FLAG_HAS_INITIAL | PHONEME_FLAG_HAS_MEDIAL  | PHONEME_FLAG_HAS_FINAL))==1){
		// Initial Only
		g_strlcat(pinYinTmp,"I",PINYIN_MAX_LENGTH);
	    }
	    if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL){
	    }else{
		g_error("zhuYin_to_pinYin(%s): p=%s Tone mark not found.",zhuYinTmp,p);
	    }
	}else{
	    g_error("zhuYin_to_pinYin(%s): Not Zhuyin symbols.",zhuYinTmp);
	}
	if (prop){
	    printf("prop->pinYin_phoneme=%s prop->zhuYin=%s\n",prop->pinYin_phoneme,prop->zhuYin);
	    g_strlcat(pinYinTmp,prop->pinYin_phoneme,PINYIN_MAX_LENGTH);
	    p+=strlen(prop->zhuYin);
	}
    }
    PinYin *pinYin=pinYin_convert_accent_format(pinYinTmp,toFormat,useTrailNumber);
    g_free(zhuYinTmp);
    g_free(pinYinTmp);
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


gboolean zhuYin_Symbol_is_toneMark(ZhuYin_Symbol zSym){
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


const P_Z_Properties *pzProperties_from_pinyin_prefix(const char *pinYin_str, PinYin_Phoneme_Type pType){
    int i=0;
    g_assert(pType>=0);
    const P_Z_Properties *prop=&PHONEMES_LIST[pType][i];

    while(prop!=NULL && prop->pinYin_phoneme!=NULL){
	if (g_str_has_prefix(pinYin_str,prop->pinYin_phoneme)){
	    return prop;
	}
	prop=&PHONEMES_LIST[pType][++i];
    }
    return NULL;
}

const P_Z_Properties *pzProperties_from_zhuyin_prefix(const char *zhuYin_str, PinYin_Phoneme_Type pType){
    int i=0;
    g_assert(pType>=0);
    const P_Z_Properties *prop=&PHONEMES_LIST[pType][i];
    const char *p=NULL;

    while(prop!=NULL && prop->zhuYin!=NULL){
	if (g_str_has_prefix(zhuYin_str,prop->zhuYin)){
	    printf("pzProperties_from_zhuyin_prefix(): zhuYin_str=%s prop->zhuYin=%s\n",zhuYin_str,prop->zhuYin);
	    switch (pType){
		case PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL:
		case PINYIN_PHONEME_TYPE_SPECIAL:
		    /* SPECIAL should be till the end. */
		    p=zhuYin_str+strlen(prop->zhuYin);
		    if (p!=NULL)
		    printf("pzProperties_from_zhuyin_prefix(): p=%s p.len=%d\n",p,strlen(p));
		    if (*p=='\0'){
			return prop;
		    }else if (zhuYin_Symbol_is_toneMark(g_utf8_get_char(p))){
			return prop;
		    }
		    return NULL;
		default:
		    return prop;
	    }
	}
	prop=&PHONEMES_LIST[pType][++i];
    }
    return NULL;
}



