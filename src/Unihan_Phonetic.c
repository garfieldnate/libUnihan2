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

PinYin *pinYin_new(char *pinYinStr){
    PinYin *pinYin=NEW_ARRAY_INSTANCE(PINYIN_MAX_LENGTH,char);
    if (!isEmptyString(pinYinStr)){
	glong i,items_written;
	gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);
	for(i=0;i<items_written;i++){
	    
	}

    }
    return pinYin;
}

PinYin *pinYin_convert_accent(PinYin* pinYin, PinYin_Accent_Mode toMode,GError **error){
    PinYin *outBuf=pinYin_new(NULL);
    pinYin_convert_accent_buffer(pinYin, toMode, outBuf,error);
    return outBuf;
}

static gboolean is_diaeresis_u(gunichar *uniStr, guint *index){
    switch(uniStr[*index]){
	case 'Ü':
	case 'Ü':
	    return TRUE;
	default:
	    break;
    }
    if (g_unichar_isdefined(uniStr[*index+1])){
	if ((uniStr[*index]=='U') && (uniStr[*index+]==':')){
	    return TRUE;
	}
    }
    if (index>0){
	switch(uniStr[*index-1]){
	    case 'J':
	    case 'j':
	    case 'Q':
	    case 'q':
	    case 'X':
	    case 'x':
	    case 'Y':
	    case 'y':
		return TRUE;
	    default:
		break;
	}
    }
    return FALSE;
}

static gboolean is_circumflex_e(gunichar *uniStr, guint *index){
    switch(uniStr[*index]){
	case 'Ê':
	    return TRUE;
	default:
	    break;
    }
    if (index>0){
	switch(uniStr[*index-1]){
	    case 'I':
	    case 'i':
	    case 'U':
	    case 'u':
	    case 'Ü':
	    case 'ü':
		return TRUE;
	    default:
		break;
	}
    }

}

glong pinYin_convert_accent_buffer(PinYin *pinYin, PinYin_Accent_Mode toMode, PinYin *outBuf,GError **error){
    glong i=0,toIndex=0,srcLen=0;
    gchar *p=pinYin;
    gunichar srcChar;
    glong items_read,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinYin, -1 , &items_written);

    GArray *outputArray=g_array_new(TRUE, FALSE, sizeof(gunichar));
    for(i=0;i<items_written;i++){
	if (is_diaeresis_u(uniStr,&i)){
	    switch(toMode){
		case PINYIN_ACCENT_ORIGINAL:
		    g_array_append_val(outputArray,'Ü');
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
	}else if(is_circumflex_e(uniStr,&i)){
	    switch(toMode){
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

ZhuYin *pinYin_to_zhuYin(PinYin* pinYin){
}
