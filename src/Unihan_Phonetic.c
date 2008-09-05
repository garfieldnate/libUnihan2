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
#include "Unihan_Phonetic.h"


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
    {"YING",    "ㄧㄥ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YIN",    "ㄧㄣ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YI",    "ㄧ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"WU",   "ㄨ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {NULL}
};

const P_Z_Properties PHONEMES_LIST_SPECIAL[]={
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

const P_Z_Properties PHONEMES_LIST_FINAL_ONLY[]={
    {"Ê",   "ㄝ",PINYIN_PHONEME_TYPE_FINAL_ONLY},
    {NULL}
};

const P_Z_Properties PHONEMES_LIST_FINAL_WITH_MEDIAL[]={
    {"NG", "ㄥ",PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL},
    {"N",  "ㄣ",PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL},
    {"E",  "ㄝ",PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL},
    {NULL}
};


const P_Z_Properties PHONEMES_LIST_FINAL_WITHOUT_MEDIAL[]={
    {"ENG", "ㄥ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"EN",  "ㄣ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"E",   "ㄜ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {NULL}
};



const P_Z_Properties PHONEMES_LIST_FINAL[]={
    {"ANG", "ㄤ",PINYIN_PHONEME_TYPE_FINAL},
    {"AI",  "ㄞ",PINYIN_PHONEME_TYPE_FINAL},
    {"AO",  "ㄠ",PINYIN_PHONEME_TYPE_FINAL},
    {"AN",  "ㄢ",PINYIN_PHONEME_TYPE_FINAL},
    {"EI",  "ㄟ",PINYIN_PHONEME_TYPE_FINAL},
    {"ER",  "ㄦ",PINYIN_PHONEME_TYPE_FINAL},
    {"OU",  "ㄡ",PINYIN_PHONEME_TYPE_FINAL},
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

    PHONEMES_LIST_FINAL_ONLY,        
    PHONEMES_LIST_FINAL_WITH_MEDIAL, 
    PHONEMES_LIST_FINAL_WITHOUT_MEDIAL, 
    PHONEMES_LIST_FINAL,             

    PHONEMES_LIST_TONEMARK,
    NULL
};



PinYin *pinYin_new(const char *pinYin_str){
    PinYin *pinYin;
    if (isEmptyString(pinYin_str)){
	pinYin=NEW_ARRAY_INSTANCE(PINYIN_MAX_LENGTH,char);
    }else{
	pinYin=g_utf8_strup(pinYin_str,PINYIN_MAX_LENGTH);
    }
    return pinYin;
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
	case 0xDC: // 'Ü'
	    return TRUE;
	case 'U':
	    break;
	default:
	    return FALSE;
    }
    if (g_unichar_isdefined(uniStr[*index+1])){
	if ((uniStr[*index]=='U') && (uniStr[*index+1]==':')){
	    (*index)++;
	    return TRUE;
	}
    }
    if (index>0){
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
	    return TRUE;
	default:
	    break;
    }
    if (index>0){
	switch(uniStr[*index-1]){
	    case 'I':
	    case 'U':
	    case 0xDC: // 'Ü'
		*accentRequired=FALSE;
		return TRUE;
	    default:
		break;
	}
    }
    return FALSE;
}


gboolean pinYin_has_diaeresis_u(const PinYin *pinYin){
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
    gboolean result=FALSE;
    gboolean accentRequire=FALSE;
    for(i=0;i<items_written;i++){
	if (is_diaeresis_u(uniStr,&i,&accentRequire)){
	    result=TRUE;
	    break;
	}
    }
    g_free(uniStr);
    return result;
}

gboolean pinYin_has_circumflex_e(const PinYin *pinYin){
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
    gboolean result=FALSE;
    gboolean accentRequire=FALSE;
    for(i=0;i<items_written;i++){
	if (is_circumflex_e(uniStr,&i,&accentRequire)){
	    result=TRUE;
	    break;
	}
    }
    g_free(uniStr);
    return result;
}

gboolean pinYin_has_toneMark(const PinYin* pinYin){
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
    gboolean result=FALSE;
    for (i=0;i<items_written;i++){
	if (!g_unichar_isalpha(uniStr[i]) && !g_unichar_isdigit(uniStr[i])){
	    result=TRUE;
	    break;
	}
    }
    g_free(uniStr);
    return result;
}


PinYin *pinYin_convert_accent_format(const PinYin* pinYin, PinYin_Accent_Format toFormat,gboolean useToneMark){
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);

    GString *strBuf=g_string_sized_new(PINYIN_MAX_LENGTH);

    gboolean accentRequired;
    for(i=0;i<items_written;i++){
	if (is_diaeresis_u(uniStr,&i,&accentRequired)){
	    g_debug("is_diaeresis_u=TRUE");
	    if (accentRequired){
		switch(toFormat){
		    case PINYIN_ACCENT_ALWAYS:
		    case PINYIN_ACCENT_ORIGINAL:
		    case PINYIN_ACCENT_UNIHAN:
			g_string_append(strBuf,"Ü");
			break;
		    case PINYIN_ACCENT_TRAILING:
			g_string_append(strBuf,"U:");
			break;
		    case PINYIN_ACCENT_INPUT_METHOD:
			g_string_append(strBuf,"V");
			break;
		    case PINYIN_ACCENT_NONE:
			g_string_append(strBuf,"U");
			break;
		}
	    }else{
		if (toFormat==PINYIN_ACCENT_ALWAYS){
		    g_string_append(strBuf,"Ü");
		}else{
		    g_string_append(strBuf,"U");
		}
	    }
	}else if(is_circumflex_e(uniStr,&i,&accentRequired)){
	    g_debug("is_circumflex_e=TRUE");
	    if (accentRequired){
		switch(toFormat){
		    case PINYIN_ACCENT_ALWAYS:
		    case PINYIN_ACCENT_ORIGINAL:
			g_string_append(strBuf,"Ê");
			break;
		    case PINYIN_ACCENT_UNIHAN:
		    case PINYIN_ACCENT_TRAILING:
		    case PINYIN_ACCENT_INPUT_METHOD:
		    case PINYIN_ACCENT_NONE:
			g_string_append(strBuf,"E");
			break;
		}
	    }else{
		if (toFormat==PINYIN_ACCENT_ALWAYS){
		    g_string_append(strBuf,"Ê");
		}else{
		    g_string_append(strBuf,"E");
		}
	    }
	}else{
	    g_debug("is_eu=FALSE");
	    g_string_append_unichar(strBuf,uniStr[i]);
	}
    }
    return g_string_free(strBuf,FALSE);
}

static const P_Z_Properties *pinYin_determine_properties(char *pinYin_str, PinYin_Phoneme_Type prev){
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
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_FINAL_ONLY))!=NULL)
		break;
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

	case PINYIN_PHONEME_TYPE_FINAL_ONLY:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin_str,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_ONLY");

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
    ZhuYin *zhuYinTmp=zhuYin_new(NULL);
    char *p=pinYinTmp;
    PinYin_Phoneme_Type pType=PINYIN_PHONEME_INVALID_TYPE;
    const P_Z_Properties *prop=NULL;
    while (*p!='\0'){
	if (*p=='1'){
	    break;
	}
	prop=pinYin_determine_properties(p,pType);
	g_assert(prop);
	pType=prop->pType;
	g_strlcat(zhuYinTmp,prop->zhuYin,ZHUYIN_MAX_LENGTH);
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
    }else{
	zhuYin=g_utf8_strup(zhuYin_str,ZHUYIN_MAX_LENGTH);
    }
    return zhuYin;
}

ZhuYin *zhuYin_convert_toneMark_format(const ZhuYin* zhuYin, ZhuYin_ToneMark_Format toFormat){
    guint tone=1,toneTmp;
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuYin, -1 , &items_written);
    for (i=0;i<items_written;i++){
	toneTmp=zhuYin_Symbol_to_toneMark_id(uniStr[i]);
	if (toneTmp){
	    tone=toneTmp;
	    break;
	}
    }

    GString *strBuf=g_string_sized_new(PINYIN_MAX_LENGTH);
    gboolean toneMark_treated=FALSE;

    if (tone==5 && toFormat==ZHUYIN_TONEMARK_ORIGINAL){
	g_string_append_unichar(strBuf,ZHUYIN_SYMBOL_NEUTRAL);
	toneMark_treated=TRUE;
    }

    for (i=0;i<items_written;i++){
	toneTmp=zhuYin_Symbol_to_toneMark_id(uniStr[i]);
	if (toneTmp){
	    if (toneMark_treated){
		continue;
	    }
	    switch (toFormat){
		case ZHUYIN_TONEMARK_ALWAYS:
		    g_string_append_unichar(strBuf,zhuYin_Symbol_from_toneMark_id(toneTmp));
		    toneMark_treated=TRUE;
		    continue;
		case ZHUYIN_TONEMARK_ORIGINAL:
		case ZHUYIN_TONEMARK_INPUT_METHOD:
		    if (toneTmp!=1){
			g_string_append_unichar(strBuf,zhuYin_Symbol_from_toneMark_id(toneTmp));
		    }else{
			/* 1st tone omitted */
		    }
		    toneMark_treated=TRUE;
		    continue;
		case ZHUYIN_TONEMARK_NUMERICAL:
		    g_string_append_c(strBuf,toneTmp);
		    toneMark_treated=TRUE;
		    continue;
	    }
	}else{
	    g_string_append_unichar(strBuf,uniStr[i]);
	}
    }

    if (!toneMark_treated){
	/* Append back the missing 1st tone */
	g_assert(tone==1);
	switch (toFormat){
	    case ZHUYIN_TONEMARK_ALWAYS:
		g_string_append_unichar(strBuf,zhuYin_Symbol_from_toneMark_id(tone));
		toneMark_treated=TRUE;
		break;
	    case ZHUYIN_TONEMARK_NUMERICAL:
		g_string_append_c(strBuf,toneTmp);
		toneMark_treated=TRUE;
		break;
	    default:
		g_error("zhuYin_convert_toneMark_format(%s,%d): bug encountered. Tone mark not treated!",zhuYin,toFormat);
	}
    }

    return g_string_free(strBuf,FALSE);
}

#define PHONEME_FLAG_HAS_INITIAL   0x1
#define PHONEME_FLAG_HAS_MEDIAL    0x2
#define PHONEME_FLAG_HAS_FINAL     0x4
#define PHONEME_FLAG_HAS_TONEMARK  0x8


PinYin *zhuYin_to_pinYin(const ZhuYin* zhuYin, PinYin_Accent_Format toFormat,gboolean useToneMark){
    const P_Z_Properties *prop=NULL;
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuYin, -1 , &items_written);
    const char* p=zhuYin;

    PinYin *pinYinTmp=pinYin_new(NULL);
    guint phonemeFlags=0;
    for(i=0;i<items_written;i++){
	prop=NULL;
	if (zhuYin_Symbol_is_initial(uniStr[i])){
	    if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_INITIAL))!=NULL){
	    }else{
		g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
	    }
	    phonemeFlags |= PHONEME_FLAG_HAS_INITIAL;
	    
	}else if (zhuYin_Symbol_is_medial(uniStr[i])){
	    if (phonemeFlags & PHONEME_FLAG_HAS_INITIAL){
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_SPECIAL))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_MEDIAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
		}

	    }else{
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL))==NULL){
		}else {
		    g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
		}
	    }
	    phonemeFlags |= PHONEME_FLAG_HAS_MEDIAL;
	}else if (zhuYin_Symbol_is_final(uniStr[i])){
	    if (phonemeFlags & PHONEME_FLAG_HAS_MEDIAL){
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
		}
	    }else if (phonemeFlags & PHONEME_FLAG_HAS_INITIAL){	
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
		}
	    }else{
		// Only the final.
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL_ONLY))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_FINAL))!=NULL){
		}else{
		    g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
		}
		if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL))!=NULL){
		}else if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL))==NULL){
		}else {
		    g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
		}
	    }
	    phonemeFlags |= PHONEME_FLAG_HAS_FINAL;
	}else if (zhuYin_Symbol_is_toneMark(uniStr[i])){
	    if ((prop=pzProperties_from_zhuyin_prefix(p,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL){
	    }else{
		g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
	    }
	    phonemeFlags |= PHONEME_FLAG_HAS_TONEMARK;
	}else{
	    g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
	}
	if (prop){
	    g_strlcat(pinYinTmp,prop->pinYin_phoneme,PINYIN_MAX_LENGTH);
	    p+=strlen(prop->zhuYin);
	}
    }
    PinYin *pinYin=pinYin_convert_accent_format(pinYinTmp,toFormat,useToneMark);
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

    while(prop!=NULL){
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

    while(prop!=NULL){
	if (g_str_has_prefix(zhuYin_str,prop->zhuYin)){
	    return prop;
	}
	prop=&PHONEMES_LIST[pType][++i];
    }
    return NULL;
}



