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


const PinYin_ZhuYin_Properties PHONEMES_INITIAL_ONLY[]={
    {"ZHI",  "ㄓ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"CHI",  "ㄔ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"SHI",  "ㄕ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"RI",   "ㄖ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"ZI",   "ㄗ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"CI",   "ㄘ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    {"SI",   "ㄙ", PINYIN_PHONEME_TYPE_INITIAL_ONLY},
    NULL
}

const PinYin_ZhuYin_Properties PHONEMES_INITIAL[]={
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
    NULL
};

const PinYin_ZhuYin_Properties PHONEMES_SPECIAL_NO_INITIAL[]={
    {"YING",   "ㄧㄥ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YIN",    "ㄧㄣ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"WENG",   "ㄨㄥ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"WEN",    "ㄨㄣ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YUN",   "ㄩㄣ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YONG",   "ㄩㄥ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"YI",    "ㄧ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    {"WU",   "ㄨ",PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL},
    NULL
};

const PinYin_ZhuYin_Properties PHONEMES_SPECIAL[]={
    {"ING",   "ㄧㄥ",PINYIN_PHONEME_TYPE_SPECIAL},
    {"IN",    "ㄧㄣ",PINYIN_PHONEME_TYPE_SPECIAL},
    {"EN",    "ㄨㄣ",PINYIN_PHONEME_TYPE_SPECIAL},
    {"ONG",   "ㄨㄥ",PINYIN_PHONEME_TYPE_SPECIAL},
    {"UN",     "ㄩㄣ",PINYIN_PHONEME_TYPE_SPECIAL},
    {"IONG",   "ㄩㄥ",PINYIN_PHONEME_TYPE_SPECIAL},
    NULL
};

const PinYin_ZhuYin_Properties PHONEMES_MEDIAL_NO_INITIAL[]={
    {"YU",   "ㄩ",PINYIN_PHONEME_TYPE_FINAL_SPECIAL_NO_INITIAL},
    {"Y",   "ㄧ",PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL},
    {"W",   "ㄨ",PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL},
    NULL
};

const PinYin_ZhuYin_Properties PHONEMES_MEDIAL[]={
    {"IO",   "ㄩ",PINYIN_PHONEME_TYPE_MEDIAL},
    {"I",  "ㄧ",PINYIN_PHONEME_TYPE_MEDIAL},
    {"U",   "ㄨ",PINYIN_PHONEME_TYPE_MEDIAL},
    NULL
};

const PinYin_ZhuYin_Properties PHONEMES_FINAL_ONLY[]={
    {"Ê",   "ㄝ",PINYIN_PHONEME_FINAL_ONLY},
    NULL
};

const PinYin_ZhuYin_Properties PHONEMES_FINAL_WITH_MEDIAL[]={
    {"NG", "ㄥ",PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL},
    {"N",  "ㄣ",PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL},
    {"E",  "ㄝ",PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL},
    NULL
};


const PinYin_ZhuYin_Properties PHONEMES_FINAL_WITHOUT_MEDIAL[]={
    {"ENG", "ㄥ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"EN",  "ㄣ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    {"E",   "ㄜ",PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL},
    NULL
};



const PinYin_ZhuYin_Properties PHONEMES_FINAL[]={
    {"ANG", "ㄤ",PINYIN_PHONEME_TYPE_FINAL},
    {"AI",  "ㄞ",PINYIN_PHONEME_TYPE_FINAL},
    {"AO",  "ㄠ",PINYIN_PHONEME_TYPE_FINAL},
    {"AN",  "ㄢ",PINYIN_PHONEME_TYPE_FINAL},
    {"EI",  "ㄟ",PINYIN_PHONEME_TYPE_FINAL},
    {"ER",  "ㄦ",PINYIN_PHONEME_TYPE_FINAL},
    {"OU",  "ㄡ",PINYIN_PHONEME_TYPE_FINAL},
    {"A",   "ㄚ",PINYIN_PHONEME_TYPE_FINAL},   
    {"O",   "ㄛ",PINYIN_PHONEME_TYPE_FINAL},
    NULL
};

const PinYin_ZhuYin_Properties PHONEMES_TONEMARK[]={
    {"1",   "ˉ",PINYIN_PHONEME_TYPE_TONEMARK},
    {"2",   "ˊ",PINYIN_PHONEME_TYPE_TONEMARK},
    {"3",   "ˇ",PINYIN_PHONEME_TYPE_TONEMARK},
    {"4",   "ˋ",PINYIN_PHONEME_TYPE_TONEMARK},
    {"5",   "˙",PINYIN_PHONEME_TYPE_TONEMARK},
    NULL
};

const PinYin_ZhuYin_Properties POHNEMES[PINYIN_PHONEME_TYPES_COUNT][]={
    PHONEME_TYPE_INITIAL_ONLY, 
    PHONEME_TYPE_INITIAL,      

    PHONEME_TYPE_SPECIAL_NO_INITIAL, 
    PHONEME_TYPE_SPECIAL,            

    PHONEME_TYPE_MEDIAL_NO_INITIAL, 
    PHONEME_TYPE_MEDIAL,            

    PHONEME_TYPE_FINAL_ONLY,        
    PHONEME_TYPE_FINAL_WITH_MEDIAL, 
    PHONEME_TYPE_FINAL_WITHOUT_MEDIAL, 
    PHONEME_TYPE_FINAL,             

    PHONEME_TYPE_TONEMARK,
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
static gboolean is_diaeresis_u(gunichar *uniStr, guint *index, gboolean *accentRequired){
    *accentRequired=TRUE;
    switch(uniStr[*index]){
	case 'Ü':
	    return TRUE;
	default:
	    break;
    }
    if (g_unichar_isdefined(uniStr[*index+1])){
	if ((uniStr[*index]=='U') && (uniStr[*index+]==':')){
	    *index++;
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
gboolean is_circumflex_e(gunichar *uniStr, guint *index, gboolean *accentRequired){
    *accentRequired=TRUE;
    switch(uniStr[*index]){
	case 'Ê':
	    return TRUE;
	default:
	    break;
    }
    if (index>0){
	switch(uniStr[*index-1]){
	    case 'I':
	    case 'U':
	    case 'Ü':
		*accentRequired=FALSE;
		return TRUE;
	    default:
		break;
	}
    }
}


gboolean pinYin_has_diaeresis_u(const PinYin *pinYin){
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
    gboolean result=FALSE;
    for(i=0;i<items_written;i++){
	if (is_diaeresis_u(uniStr,&i)){
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
    for(i=0;i<items_written;i++){
	if (is_circumflex_e(uniStr,&i)){
	    result=TRUE;
	    break;
	}
    }
    g_free(uniStr);
    return result;
}

gboolean pinYin_has_toneMark(const PinYin* pinYin){
    glong i,items_read,items_written;
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

PinYin *pinYin_convert_accent(const PinYin* pinYin, PinYin_Accent_Mode toMode,gboolean toneMark){
    PinYin *outBuf=pinYin_new(NULL);
    pinYin_convert_accent_buffer(pinYin, toMode, outBuf,NULL);
    return outBuf;
}


glong pinYin_convert_accent_buffer(const PinYin *pinYin, PinYin_Accent_Mode toMode, gboolean toneMark, PinYin *outBuf,GError **error){
    glong i=0,toIndex=0,srcLen=0;
    gchar *p=pinYin;
    gunichar srcChar;
    glong items_read,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);

    GArray *outputArray=g_array_new(TRUE, FALSE, sizeof(gunichar));
    gboolean accentRequired;
    for(i=0;i<items_written;i++){
	if (is_diaeresis_u(uniStr,&i,&accentRequired)){
	    if (accentRequired){
		switch(toMode){
		    case PINYIN_ACCENT_ALWAYS:
		    case PINYIN_ACCENT_ORIGINAL:
		    case PINYIN_ACCENT_UNIHAN:
			g_array_append_val(outputArray,'Ü');
			break;
		    case PINYIN_ACCENT_TRAILING:
			g_array_append_val(outputArray,'U');
			g_array_append_val(outputArray,':');
			break;
		    case PINYIN_ACCENT_INPUT_METHOD:
			g_array_append_val(outputArray,'V');
			break;
		    case PINYIN_ACCENT_NONE:
			g_array_append_val(outputArray,'U');
			break;
		}
	    }else{
		if (toMode==PINYIN_ACCENT_ALWAYS){
		    g_array_append_val(outputArray,'Ü');
		}else{
		    g_array_append_val(outputArray,'U');
		}
	    }
	}else if(is_circumflex_e(uniStr,&i,&accentRequired)){
	    if (accentRequired){
		switch(toMode){
		    case PINYIN_ACCENT_ALWAYS:
		    case PINYIN_ACCENT_ORIGINAL:
			g_array_append_val(outputArray,'Ê');
			break;
		    case PINYIN_ACCENT_UNIHAN:
		    case PINYIN_ACCENT_TRAILING:
		    case PINYIN_ACCENT_INPUT_METHOD:
		    case PINYIN_ACCENT_NONE:
			g_array_append_val(outputArray,'E');
			break;
		}
	    }else{
		if (toMode==PINYIN_ACCENT_ALWAYS){
		    g_array_append_val(outputArray,'Ê');
		}else{
		    g_array_append_val(outputArray,'E');
		}
	    }
	}else{
	    g_array_append_val(outputArray,uniStr[i]);
	}
    }
    GError **error;
    gchar* tempStr=g_ucs4_to_utf8 (outputArray->data,outputArray->len,&items_read,&items_written,error);
    g_strlcpy(outBuf,tempStr, PINYIN_MAX_LENGTH);
    g_free(tempStr);
    g_array_free(outputArray,TRUE);
    return items_read;
}


static const PinYin_ZhuYin_Properties *pinYin_determine_properties(char *pinYin_str, PinYin_Phoneme_Type prev){
    PinYin_ZhuYin_Properties *prop=NULL;

    switch(prev){
	case PHONEME_INVALID_TYPE:
	    // Start of pinYin
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_INITIAL_ONLY))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_INITIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_SPECIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_ONLY))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_INVALID_TYPE");

	case PINYIN_PHONEME_TYPE_INITIAL_ONLY:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_INITIAL_ONLY");

	case PINYIN_PHONEME_TYPE_INITIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_SPECIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_INITIAL");

	case PINYIN_PHONEME_TYPE_SPECIAL_NO_INITIAL:
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_SPECIAL_NO_INITIAL");

	case PINYIN_PHONEME_TYPE_SPECIAL:
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_SPECIAL");

	case PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_MEDIAL_NO_INITIAL");

	case PINYIN_PHONEME_TYPE_MEDIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_MEDIAL");

	case PINYIN_PHONEME_TYPE_FINAL_ONLY:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_ONLY");

	case PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_WITH_MEDIAL");

	case PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		 break;
    	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_WITHOUT_MEDIAL");

	case PINYIN_PHONEME_TYPE_FINAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL");

	case PINYIN_PHONEME_TYPE_TONEMARK:
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_TONEMARK");

    }
    return prop;
}

ZhuYin *pinYin_to_zhuYin(const PinYin* pinYin){
    PinYin *aPinYin=pinYin_convert_accent(pinYin, PINYIN_ACCENT_ORIGINAL,FALSE);
    ZhuYin *zhuYin=zhuYin_new(NULL);
    guint counter,j;
    char *p=aPinYin;
    PinYin_Phoneme_Type pType=PINYIN_PHONEME_INVALID_TYPE;
    PinYin_ZhuYin_Properties *prop=NULL;
    while (*p!='\0'){
	if (*p=='1'){
	    break;
	}
	prop=pinYin_determine_properties(p,pType);
	g_assert(prop);
	pType=prop->pType;
	g_strlcat(zhuYin,prop->zhuYin,ZHUYIN_MAX_LENGTH);

	for (j=ZHUYIN_SYMBOL_COUNT-1;j>=0;j--){
	    if (!g_str_has_prefix(p,PINYIN_PHONEME_LIST[j])){
		continue;
	    }
	    g_strlcat(zhuYin,PINYIN_PHONEME_LIST[j],ZHUYIN_MAX_LENGTH);
	    p+=strlen(prop->pinYin_phoneme);
	}
    }
    g_free(aPinYin);
    return zhuYin;
}

const PinYin *pinYin_phoneme_from_id(ZhuYin_Symbol_Id id){
    if (id<0 || id >= ZHUYIN_SYMBOL_COUNT )
	return NULL;
    return PINYIN_PHONEME_LIST[j];
}

ZhuYin_Symbol_Id pinYin_phoneme_get_id(const PinYin *pinYin){
    PinYin *pS=pinYin_convert_accent(pinYin, PINYIN_ACCENT_ALWAYS);
    int j;
    for (j=ZHUYIN_SYMBOL_COUNT-1;j>=0;j--){
	if (strcmp(p,PINYIN_PHONEME_LIST[j])==0){
	    g_free(pS);
	    return j;
	}
    }
    g_free(pS);
    return ZHUYIN_INVALID_SYMBOL;
}


/*========================================
 * ZhuYin functions.
 */
ZhuYin *zhuYin_new(char *zhuYin_str){
    ZhuYin *zhuYin;
    if (isEmptyString(zhuYin_str)){
	zhuYin=NEW_ARRAY_INSTANCE(ZHUYIN_MAX_LENGTH,char);
    }else{
	zhuYin=g_utf8_strup(zhuYin_str,ZHUYIN_MAX_LENGTH);
    }
    return zhuYin;
}


#define PHONEME_FLAG_HAS_INITIAL   0x1
#define PHONEME_FLAG_HAS_MEDIAL    0x2
#define PHONEME_FLAG_HAS_FINAL     0x4
#define PHONEME_FLAG_HAS_TONEMARK  0x8


PinYin *zhuYin_to_pinYin(ZhuYin* zhuYin){
    PinYin_ZhuYin_Properties *prop=NULL;
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuYin, -1 , &items_written);

    PinYin *pinYin=pinYin_new(NULL);
    guint phonemeFlags=0;
    for(i=0;i<items_written;i++){
	if (zhuYin_Symbol_is_initial(uniStr[i])){
	    if ((prop=pzProperties_from_zhuyin_symbol(uniStr[i],PINYIN_PHONEME_TYPE_INITIAL))==NULL){
		g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
	    }
	    g_strlcat(pinYin,prop->pinYin_phoneme,PINYIN_MAX_LENGTH);
	    phonemeFlags |= PHONEME_FLAG_HAS_INITIAL;
	    
	}else if (zhuYin_Symbol_is_medial(uniStr[i])){
	    if (phonemeFlags & PHONEME_FLAG_HAS_INITIAL){
		if ((prop=pzProperties_from_zhuyin_symbol(uniStr[i],PINYIN_PHONEME_TYPE_MEDIAL))==NULL){
		    g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
		}
		g_strlcat(pinYin,prop->pinYin_phoneme,PINYIN_MAX_LENGTH);
	    }else{
		if ((prop=pzProperties_from_zhuyin_symbol(uniStr[i],PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL))==NULL){
		    g_error("zhuYin_to_pinYin(%s): Symbol not found.",zhuYin);
		}
		g_strlcat(pinYin,prop->pinYin_phoneme,PINYIN_MAX_LENGTH);
	    }
	    phonemeFlags |= PHONEME_FLAG_HAS_MEDIAL;
	}

    }

    if (phoneme_flags & PHONEME_FLAG_HAS_INVALID)
	return NULL;

    if (phoneme_flags & PHONEME_FLAG_HAS_INITIAL){
	if (phoneme_flags & PHONEME_FLAG_HAS_INITIAL
    }



    if ((prop=zhuYin_get_phoneme_flags(pinYin,PINYIN_PHONEME_TYPE_INITIAL))!=NULL){
	phomeme_flags|=PHONEME_FLAG_HAS_INITIAL;
    }
    if ((prop=zhuYin_find_phoneme_prefix_in_type(pinYin,PINYIN_PHONEME_TYPE_INI))!=NULL){
	phomeme_flags|=PHONEME_FLAG_HAS_INITIAL;
    }

}

static const PinYin_ZhuYin_Properties *zhuYin_determine_properties(char *zhuYin, PinYin_Phoneme_Type prev){
    PinYin_ZhuYin_Properties *prop=NULL;

    switch(prev){
	case PHONEME_INVALID_TYPE:
	    // Start of pinYin
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_INITIAL_ONLY))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_INITIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_ONLY))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_INVALID_TYPE");

	case PINYIN_PHONEME_TYPE_INITIAL_ONLY:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_INITIAL_ONLY");

	case PINYIN_PHONEME_TYPE_INITIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_INITIAL");
	case PINYIN_PHONEME_TYPE_MEDIAL_NO_INITIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_MEDIAL_NO_INITIAL");

	case PINYIN_PHONEME_TYPE_MEDIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_FINAL))!=NULL)
		break;
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_MEDIAL");

	case PINYIN_PHONEME_TYPE_FINAL_ONLY:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_ONLY");

	case PINYIN_PHONEME_TYPE_FINAL_WITH_MEDIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_WITH_MEDIAL");

	case PINYIN_PHONEME_TYPE_FINAL_WITHOUT_MEDIAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL_WITHOUT_MEDIAL");

	case PINYIN_PHONEME_TYPE_FINAL:
	    if ((prop=pzProperties_from_pinyin_prefix(pinYin,PINYIN_PHONEME_TYPE_TONEMARK))!=NULL)
		break;
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_FINAL");

	case PINYIN_PHONEME_TYPE_TONEMARK:
	    g_error("pinYin_determine_properties: Not suitable property found when prev=PHONEME_TYPE_TONEMARK");

    }
    return prop;
}

ZhuYin_Symbol zhuYin_Symbol_from_id(ZhuYin_Symbol_Id id){
    if (id<0 || id >= ZHUYIN_SYMBOL_COUNT )
	return 0;
    return ZHUYIN_SYMBOL_LIST[j];
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
}

gboolean zhuYin_Symbol_is_medial(ZhuYin_Symbol zSym){
    if ((zSym>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_I]) &&
	    (zSym<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_U_DIAERESIS])){
	return TRUE;
    }
}

gboolean zhuYin_Symbol_is_final(ZhuYin_Symbol zSym){
    if ((zSym>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_A]) &&
	(zSym<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_ER])){
	return TRUE;
    }
}

gboolean zhuYin_Symbol_is_tonemark(ZhuYin_Symbol zSym){
    if ((zSym>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_1]) &&
	    (zSym<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_NEUTRAL])){
	return TRUE;
    }
}


guint zhuYin_get_phoneme_flags(ZhuYin *zhuYin){
    guint result=0;
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuYin, -1 , &items_written);
    for(i=0;i<items_written;i++){
	if ((uniStr[i]>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_B]) &&
	       	(uniStr[i]<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_S])){
	    result |=PHONEME_FLAG_HAS_INITIAL;
	}else if ((uniStr[i]>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_I]) &&
		(uniStr[i]<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_U_DIAERESIS])){
	    result |=PHONEME_FLAG_HAS_MEDIAL;
	}else if ((uniStr[i]>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_A]) &&
		(uniStr[i]<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_ER])){
	    result |=PHONEME_FLAG_HAS_FINAL;
	}else if ((uniStr[i]>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_1]) &&
		(uniStr[i]<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_NEUTRAL])){
	    result |=PHONEME_FLAG_HAS_TONEMARK;
	}else{
	    result |=PHONEME_FLAG_HAS_INVALID;
	}
    }
    g_free(uniStr);
    return result;

}


PinYin_ZhuYin_Properties pzProperties_from_pinyin_phoneme
const pinYin_ZhuYin_Properties *pzProperties_from_pinyin_prefix(const char *pinYin_str, PinYin_Phoneme_Type pType){
    int i;
    g_assert(pType>=0);
    for(i=0; PHONEMES[pType][i]!=NULL;i++){
	if (g_str_has_prefix(pinYin_str,PHONEMES[pType][i].pinYin_phoneme)){
	    return &PHONEMES[pType][i];
	}
    }
    return NULL;
}

const pinYin_ZhuYin_Properties *pzProperties_from_zhuyin_prefix(const char *zhuYin_str, PinYin_Phoneme_Type pType){
    int i;
    g_assert(pType>=0);
    for(i=0; PHONEMES[pType][i]!=NULL;i++){
	if (g_str_has_prefix(zhuYin_str,PHONEMES[pType][i].zhuYin)){
	    return &PHONEMES[pType][i];
	}
    }
    return NULL;

}

const pinYin_ZhuYin_Properties *pzProperties_from_zhuyin_symbol(ZhuYin_Symbol zSym, PinYin_Phoneme_Type pType){
    char *utf8Str=ucs4_to_utf8(zSym);
    pinYin_ZhuYin_Properties *prop=pzProperties_from_zhuyin_prefix(utf8Str,pType);
    g_free(utf8Str);
    return prop;
}


