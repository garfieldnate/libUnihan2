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
   "V",      
   "A",      
   "O",      
   "E",      
   "E",  
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

PinYin *pinYin_new(){
    return NEW_ARRAY_INSTANCE(PINYIN_MAX_LENGTH_MAX,char);
}

PinYin *pinYin_convert_accent(PinYin* pinYin, PinYin_Accent_Mode toMode){
    PinYin *outBuf=pinYin_new();
    pinYin_convert_accent_buffer(pinYin, toMode, outBuf);
    return outBuf;
}

void pinYin_convert_accent_buffer(PinYin *pinYin, PinYin_Accent_Mode toMode, PinYin *outBuf){
    glong i=0,toIndex=0,srcLen=0;
    gchar *p=pinYin;
    gunichar srcChar;
    gunichar *ucs4str=g_utf8_to_ucs4_fast(pinYin, -1, &srcLen);
    while ((srcChar=g_utf8_next_char(pinYin))g_unichar_isdefined(g_
    for(i=0;i<srcLen;i++){
	gunichar srcChar=ucs4str[i];

	switch(toMode){
	    case PINYIN_ACCENT_ORIGINAL:
		break;
	    case PINYIN_ACCENT_TRAILING:
		break;
	    case PINYIN_ACCENT_CONVERT:
		break;
	    case PINYIN_ACCENT_NONE:
		break;
	}    
    }

}
