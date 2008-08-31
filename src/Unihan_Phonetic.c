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



typedef struct {
    char  pinYin_phoneme[5];
    char  pinYin_phoneme[5];
    ZhuYin_Symbol  zSym;
} Phoneme_Record;

const ZhuYin_Record INITIAL_PHONEMES[]={
    {"B",   "ㄅ"},
    {"P",   "ㄆ"},
    {"M",   "ㄇ"},
    {"F",   "ㄈ"},
    {"D",   "ㄉ"},
    {"T",   "ㄊ"},
    {"N",   "ㄋ"},
    {"L",   "ㄌ"},
    {"G",   "ㄍ"},
    {"K",   "ㄎ"},
    {"H",   "ㄏ"},
    {"J",   "ㄐ"},
    {"Q",   "ㄑ"},
    {"X",   "ㄒ"},
    {"ZH",  "ㄓ"},
    {"CH",  "ㄔ"},
    {"SH",  "ㄕ"},
    {"R",   "ㄖ"},
    {"Z",   "ㄗ"},
    {"C",   "ㄘ"},
    {"S",   "ㄙ"},
    NULL
};

const ZhuYin_Record MEDIAL_PHONEMES[]={
    {"IO",   "ㄩ"},
    {"I",  "ㄧ"},
    {"U",   "ㄨ"},
    NULL
};

const ZhuYin_Record MEDIAL_PHONEMES_NO_INITIAL[]={
    {"YI",  "ㄧ"},
    {"WU",   "ㄨ"},
    {"YU",   "ㄩ"},
    {"YO",   "ㄩ"},
    {"Y",  "ㄧ"},
    {"W",   "ㄨ"},
    NULL
};

const ZhuYin_Record FINAL_PHONEMES_NORMAL[]={
    {"ANG", "ㄤ"},
    {"AI",  "ㄞ"},
    {"AO",  "ㄠ"},
    {"AN",  "ㄢ"},
    {"EI",  "ㄟ"},
    {"ER",  "ㄦ"},
    {"OU",  "ㄡ"},
    {"A",   "ㄚ"},   
    {"O",   "ㄛ"},
    {"Ê",   "ㄝ"},
    NULL
}

const ZhuYin_Record FINAL_PHONEMES_WITHOUT_MEDIAL[]={
    {"ENG", "ㄥ"},
    {"EN",  "ㄣ"},
    {"E",   "ㄜ"},
    {"I", ""},
    NULL
}

const ZhuYin_Record FINAL_PHONEMES_WITH_MEDIAL[]={
    {"NG", "ㄥ"},
    {"N",  "ㄣ"},
    {"E",   "ㄝ"},
    NULL
}


const PinYin PINYIN_PHONEME_LIST[ZHUYIN_SYMBOL_COUNT]={
   "B",       
   "P",      
   "M",      
   "F",      
   "D",      
   "T",      
   "N",      
   "L",      
   "G",      
   "K",      
   "H",      
   "J",      
   "Q",      
   "X",      
   "ZH",     
   "CH",     
   "SH",     
   "R",      
   "Z",      
   "C",      
   "S",      
   "I",      
   "U",      
   "Ü",      
   "A",      
   "O",      
   "E",      
   "Ê",  
   "AI",     
   "EI",     
   "AO",     
   "OU",     
   "AN",     
   "EN",     
   "ANG",    
   "ENG",    
   "ER",     
   "2",      
   "3",      
   "4",      
   "5"
};

PinYin *pinYin_new(const char *pinYinStr){
    PinYin *pinYin;
    if (isEmptyString(pinYinStr)){
	pinYin=NEW_ARRAY_INSTANCE(PINYIN_MAX_LENGTH,char);
    }else{
	pinYin=g_utf8_strup(pinYinStr,PINYIN_MAX_LENGTH);
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

ZhuYin *pinYin_to_zhuYin(const PinYin* pinYin){
    PinYin *aPinYin=pinYin_convert_accent(pinYin, PINYIN_ACCENT_ALWAYS);
    ZhuYin *zhuYin=zhuYin_new(NULL);
    guint counter,j;
    char *p=aPinYin;
    while (*p!='\0'){
	if (*p=='1'){
	    break;
	}
	for (j=ZHUYIN_SYMBOL_COUNT-1;j>=0;j--){
	    if (!g_str_has_prefix(p,PINYIN_PHONEME_LIST[j])){
		continue;
	    }
	    g_strlcat(zhuYin,PINYIN_PHONEME_LIST[j],ZHUYIN_MAX_LENGTH);
	    p+=strlen(PINYIN_PHONEME_LIST[j]);
	}
    }
    return zhuYin;
}

const PinYin *pinYin_phoneme_from_id(ZhuYin_Symbol_Id id){
    if (id<0 || id >= ZHUYIN_SYMBOL_COUNT )
	return NULL;
    return PINYIN_PHONEME_LIST[j];
}

ZhuYin_Symbol_Id pinYin_phoneme_get_id(const PinYin *pSym){
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
ZhuYin *zhuYin_new(char *zhuYinStr){
    ZhuYin *zhuYin;
    if (isEmptyString(zhuYinStr)){
	zhuYin=NEW_ARRAY_INSTANCE(ZHUYIN_MAX_LENGTH,char);
    }else{
	zhuYin=g_utf8_strup(zhuYinStr,ZHUYIN_MAX_LENGTH);
    }
    return zhuYin;
}

PinYin *zhuYin_to_pinYin(ZhuYin* zhuYin){

    
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
