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
    'ㄅ',
    'ㄆ',
    'ㄇ',
    'ㄈ',
    'ㄉ',
    'ㄊ',
    'ㄋ',
    'ㄌ',
    'ㄍ',
    'ㄎ',
    'ㄏ',
    'ㄐ',
    'ㄑ',
    'ㄒ',
    'ㄓ',
    'ㄔ',
    'ㄕ',
    'ㄖ',
    'ㄗ',
    'ㄘ',
    'ㄙ',
    'ㄧ',
    'ㄨ',
    'ㄩ',
    'ㄚ',
    'ㄛ',
    'ㄜ',
    'ㄝ',
    'ㄞ',
    'ㄟ',
    'ㄠ',
    'ㄡ',
    'ㄢ',
    'ㄣ',
    'ㄤ',
    'ㄥ',
    'ㄦ',
    'ˊ',
    'ˇ',
    'ˋ',
    '˙'
};

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

PinYin *pinYin_convert_accent(const PinYin* pinYin, PinYin_Accent_Mode toMode){
    PinYin *outBuf=pinYin_new(NULL);
    pinYin_convert_accent_buffer(pinYin, toMode, outBuf,NULL);
    return outBuf;
}


glong pinYin_convert_accent_buffer(const PinYin *pinYin, PinYin_Accent_Mode toMode, PinYin *outBuf,GError **error){
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
	if (strcmp(p,PINYIN_PHONEME_LIST[j])!=0){
	    continue;
	}
	return j;
    }
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

