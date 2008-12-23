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
#include "verboseMsg.h"
#define MAX_STRING_BUFFER_SIZE	2000

const ZhuyinSymbol ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_COUNT]={
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

// neutral 
#define ZHUYIN_REGEX_LEADING_NEUTRAL "(˙)?" // 1
#define ZHUYIN_REGEX_INITIAL_OTHERS "((ㄅ)?(ㄆ)?(ㄇ)?(ㄈ)?(ㄉ)?(ㄊ)?(ㄋ)?(ㄌ)?(ㄍ)?(ㄎ)?(ㄏ)?" // 2-13
#define ZHUYIN_REGEX_INITIAL_JQX "((ㄐ)?(ㄑ)?(ㄒ)?)?"			// 14-17
#define ZHUYIN_REGEX_INITIAL_ZCSR "((ㄓ)?(ㄔ)?(ㄕ)?(ㄖ)?(ㄗ)?(ㄘ)?(ㄙ)?)?" // 18-25
#define ZHUYIN_REGEX_INITIAL  ZHUYIN_REGEX_INITIAL_OTHERS\
    ZHUYIN_REGEX_INITIAL_JQX ZHUYIN_REGEX_INITIAL_ZCSR ")?"   // 1-25
#define ZHUYIN_REGEX_MEDIAL "(((ㄧ)?(ㄩ)?)?(ㄨ)?)?"  // 26-30
#define ZHUYIN_REGEX_FINAL  "((ㄚ)?(ㄛ)?(ㄜ)?(ㄝ)?(ㄞ)?(ㄟ)?(ㄠ)?(ㄡ)?(ㄢ)?(ㄤ)?((ㄣ)?(ㄥ)?)?(ㄦ)?)?" // 31-45
#define ZHUYIN_REGEX_TONE  "((ˉ|1)?(ˊ|2)?(ˇ|3)?(ˋ|4)?(˙|5)?)?" // 46-51
#define ZHUYIN_REGEX	ZHUYIN_REGEX_LEADING_NEUTRAL ZHUYIN_REGEX_INITIAL ZHUYIN_REGEX_MEDIAL ZHUYIN_REGEX_FINAL ZHUYIN_REGEX_TONE

#define ZHUYIN_PINYIN_SUBSTITUTE_INITIAL_OTHERS "$N3{b}$N4{p}$N5{m}$N6{f}$N7{f}$N8{d}$N9{t}$N10{n}$N11{l}$N12{g}$N13{k}$N14{h}"
#define ZHUYIN_PINYIN_SUBSTITUTE_INITIAL_JQX "$N15{j}$N16{q}$N17{x}"
/*
 * $N18{$E26{$E30{i}}: if no medial or final, then an 'i' is appended.
 */
#define ZHUYIN_PINYIN_SUBSTITUTE_INITIAL_ZCSR "$N19{zh}$N20{ch}$N21{sh}$N22{r}$N23{z}$N24{c}$N25{s}$N18{$E26{$E31{i}}"
#define ZHUYIN_PINYIN_SUBSTITUTE_INITIAL ZHUYIN_PINYIN_SUBSTITUTE_INITIAL_OTHERS\
    ZHUYIN_PINYIN_SUBSTITUTE_INITIAL_JQX ZHUYIN_PINYIN_SUBSTITUTE_INITIAL_ZCSR

/*
 * $N27{$E2{y}}: prepend 'y' if no initial for 'ㄧ' or 'ㄩ'
 *
 * ㄧ: $N28{$N42{i}}: 
 *     append 'i' if ㄣ or ㄥ presents 
 *
 * ㄩ:$N29{$N44{$N14{io,o},v}: 
 *     if 'ㄥ' presents, 
 *         if jqx presents, then 'ㄩ' is translated as 'io',
 *         else 'ㄩ' is translated as 'o'
 *     else  'ㄩ' is translated as 'v'
 *
 * ㄨ:$N30{$E2{$E31{wu,$N42{we,w}},$N44{o,u}}}:
 *     if no initials
 *        if no final then translate to 'wu' 
 *        else if has ㄣ or ㄥ then translate to 'we'
 *             else translate to 'w'
 *     else if has  ㄥ then translate to 'o'
 *          else translate to 'u'
 *
 */
#define ZHUYIN_PINYIN_SUBSTITUTE_MEDIAL "$N27{$E2{y}}$N28{$N2{i}}$N29{$N44{$N14{io,o},v}$N30{$E2{$E31{wu,$N42{we,w}},$N44{o,u}}}"
/**
 * ㄟ: $N37{$N26{i,ei}}
 *     if medial present then translate to i
 *     else  translate to ei
 *
 * ㄡ: $N39{$N26{$N2{u,ou},ou}
 *     if medial present:
 *        if initial present then translate to 'u'
 *        else translate to 'ou'
 *     else  translate to 'ou'
 *
 * ㄣ: $N43{$N26{n,en}}
 *     if medial present then translate to 'n'
 *     else  translate to 'en'
 *         
 * ㄥ: $N44{$N26{ng,eng}}
 *     if medial present then translate to 'ng'
 *     else  translate to 'eug'
 * 
 */
#define ZHUYIN_PINYIN_SUBSTITUTE_FINAL "$N32{a}$N33{o}$N34{e}$N35{E}"\
    "$N36{ai}$N37{$N26{i,ei}}$N38{ao}$N39{$N26{$N2{u,ou},ou}"\
    "$N40{ang}$N41{an}$N43{$N26{n,en}}$N44{$N26{ng,eng}}$N45{er}"
#define ZHUYIN_PINYIN_SUBSTITUTE	ZHUYIN_PINYIN_SUBSTITUTE_INITIAL ZHUYIN_PINYIN_SUBSTITUTE_MEDIAL ZHUYIN_PINYIN_SUBSTITUTE_FINAL

#define ZHUYIN_SUBSTITUTE_TONE "$N1{5}$N47{1}$N48{2}$N49{3}$N50{4}$N51{5}"



#define PINYIN_REGEX_INITIAL_OTHERS "(b)?(p)?(m)?(f)?(d)?(t)?(n)?(l)?(g)?(k)?(h)?" 	// 2-12
#define PINYIN_REGEX_INITIAL_JQX "((j)?(q)?(x)?)?"					// 13-16
#define PINYIN_REGEX_INITIAL_ZCSR "((zh)?(ch)?(sh)?(r)?(z)?(c)?(s)?)?"			// 17-24

#define PINYIN_REGEX_INITIAL "(" PINYIN_REGEX_INITIAL_OTHERS\
    PINYIN_REGEX_INITIAL_JQX PINYIN_REGEX_INITIAL_ZCSR ")?"   // 1-24

/* 
 * yi: -> ^ㄧ
 * w:  -> ^ㄨ
 * yv: -> ^ㄩ
 * i: -> +ㄧ*
 * u: -> +ㄩ*
 *
 */
#define PINYIN_REGEX_MEDIAL "((yi?)?(w[eu]?)?(y?v)?(io)?((i)|(u))?)?"		// 25-32
#define PINYIN_REGEX_FINAL  "((ang)?(e?ng)?(e?n)?(er)?(ai)?(e?i)?(ao)?(o?u)?(an)?(a)?(o)?(e)?(E)?)?"  // 33

#define PINYIN_REGEX	PINYIN_REGEX_INITIAL PINYIN_REGEX_MEDIAL PINYIN_REGEX_FINAL

#define PINYIN_ZHUYIN_SUBSTITUTE_INITIAL_OTHERS "$N2{ㄅ}$N3{ㄆ}$N4{ㄇ}$N5{ㄈ}$N6{ㄉ}$N7{ㄊ}$N8{ㄋ}$N9{ㄌ}$N10{ㄍ}$N11{ㄎ}$N12{ㄏ}"
#define PINYIN_ZHUYIN_SUBSTITUTE_INITIAL_JQX "$N14{ㄐ}$N15{(ㄑ}$N16{ㄒ}"
#define PINYIN_ZHUYIN_SUBSTITUTE_INITIAL_ZCSR "$N18{ㄓ}$N19{ㄔ}$N20{ㄕ}$N21{ㄖ}$N22{ㄗ}$N23{ㄘ}$N24{ㄙ}"
#define PINYIN_ZHUYIN_SUBSTITUTE_INITIAL	PINYIN_ZHUYIN_SUBSTITUTE_INITIAL_OTHERS\
    PINYIN_ZHUYIN_SUBSTITUTE_INITIAL_JQX PINYIN_ZHUYIN_SUBSTITUTE_INITIAL_ZCSR
#define PINYIN_ZHUYIN_SUBSTITUTE_MEDIAL		"$N26{ㄧ}$N27{ㄨ}$N28{ㄩ}$N29{ㄩ}$N31{ㄧ}$N32{ㄨ}"
#define PINYIN_ZHUYIN_SUBSTITUTE_FINAL		"$N35{ㄤ}$N36{ㄥ}$N37{ㄣ}$N38{ㄦ}$N39{ㄞ}$N40{ㄟ}$N41{ㄠ}$N42{ㄡ}$N43{ㄢ}$N44{ㄚ}$N45{ㄛ}$N46{ㄜ}$N47{ㄝ}"

#define PINYIN_ZHUYIN_SUBSTITUTE PINYIN_ZHUYIN_SUBSTITUTE_INITIAL\
    PINYIN_ZHUYIN_SUBSTITUTE_MEDIAL PINYIN_ZHUYIN_SUBSTITUTE_FINAL

const gunichar PINYIN_COMBINING_TONED_ACCENTS[4]={
    0x0304,	// combining macron, 1st tone.
    0x0301,     // combining acute accent, 2nd tone.
    0x030C,	// combining caron, 3rd tone.
    0x0300,	// combining grave accent, 4th tone.
};

const gunichar ZHUYIN_TONED_SYMBOLS[5]={
    0x02C9,	// "ˉ", 1st tone.
    0x02CA,     // "ˊ", 2nd tone.
    0x02C7,	// "ˇ", 3rd tone.
    0x02CB,	// "ˋ", 4th tone.
    0x02D9,     // "˙", 5th tone
};

/*==========================================================
 * Syllable functions.
 */
static Pinyin *zhuyin_to_pinyin_normalized_toneless(Zhuyin *zhuyin){
    return zhuyin_regex_formatted_combine(zhuyin,ZHUYIN_PINYIN_SUBSTITUTE);
}

static Zhuyin *pinyin_normalized_to_zhuyin_toneless(Pinyin *pinyin){
    return pinyin_regex_formatted_combine(pinyin,PINYIN_ZHUYIN_SUBSTITUTE);
}

Syllable *syllable_new(){
    Syllable *syl=NEW_INSTANCE(Syllable);
    initString( syl->transcription);
    syl->tone=0;
    return syl;
}

Syllable *syllable_new_pinyin(const Pinyin *pinyin_str){
    Syllable *syl=syllable_new();
    guint tone=0;
    if (!isEmptyString(pinyin_str)){
	Pinyin *pinyin=g_utf8_normalize(pinyin_str,PINYIN_MAX_LENGTH,G_NORMALIZE_NFD);
	g_assert(pinyin);
	gchar *pinyin_tmp=pinyin_regex_import_formatted_combine(pinyin,PINYIN_SUBSTITUTE);
	gchar *toneStr=pinyin_regex_import_formatted_combine(pinyin,PINYIN_SUBSTITUTE_TONE);
	tone=atoi(toneStr);
	if (pinyin_tmp){
	    g_strlcpy(syl->transcription,pinyin_tmp,TRANSCRIPTION_MAX_LENGTH);
	    g_free(pinyin_tmp);
	}
	g_free(pinyin);
	g_free(toneStr);
    }
    syl->tone=tone;
    return syl;
}

Syllable *syllable_new_zhuyin(const Zhuyin *zhuyin_str){
    Syllable *syl=syllable_new();
    guint tone=0;
    if (!isEmptyString(zhuyin_str)){
	Zhuyin *zhuyin=zhuyin_new(zhuyin_str);
	tone=zhuyin_strip_tone(zhuyin);
	g_strlcpy(syl->transcription,zhuyin,TRANSCRIPTION_MAX_LENGTH);
	g_free(zhuyin);
    }
    syl->tone=tone;
    return syl;
}

Syllable *syllable_clone(Syllable *syl){
    Syllable *syl_new=syllable_new();
    g_strlcpy(syl_new->transcription,syl_new->transcription,TRANSCRIPTION_MAX_LENGTH);
    syl_new->tone=syl->tone;
    return syl_new;
}

Pinyin *syllable_to_pinyin(Syllable *syl,PinyinFormatFlags formatFlags){
    Pinyin *pinyin_tmp=NULL;
    Pinyin *pinyin_curr=NULL;
    Pinyin *pinyin=pinyin_new(NULL);
    gboolean canNFC=FALSE;
	
    if (syllable_is_zhuyin_fast(syl)){
	pinyin_tmp=zhuyin_to_pinyin_normalized_toneless(syl->transcription);
	pinyin_curr=pinyin_tmp;
    }else{
	pinyin_curr=syl->transcription;
    }
    int i,j=0;
    for(i=0;pinyin_curr[i]!='\0';i++){
	switch (pinyin_curr[i]){
	    case 'v':
		if (formatFlags & PINYIN_FORMAT_FLAG_STRIP_DIAERESIS){
		    pinyin[j++]='u';
		    break;
		}
		if (formatFlags & PINYIN_FORMAT_FLAG_STRIP_TRIVIAL_ACCENT){
		    if (i>0 && (pinyin_curr[0]!='l' && pinyin_curr[0]!='n' )){
			pinyin[j++]='u';
		    }
		    break;
		}else{
		    /* Do not remove trivial accent. */
		    /* or Non trivial v. */
		    if (formatFlags & PINYIN_FORMAT_FLAG_ASCII_ONLY){
			if (formatFlags & PINYIN_FORMAT_FLAG_NFD){
			    pinyin[j++]='u';
			    pinyin[j++]=':';
			}else{
			    pinyin[j++]='v';
			}
		    }else{
			/* Allow non-ascii, add diaeresis */
			pinyin[j++]='u';
			pinyin[j++]='\xCC';
			pinyin[j++]='\x88';
			canNFC=TRUE;
		    }
		}
		break;
	    case 'E':
		if (formatFlags & PINYIN_FORMAT_FLAG_STRIP_CIRCUMFLEX){
		    pinyin[j++]='e';
		    break;
 	        }
		
		if (formatFlags & PINYIN_FORMAT_FLAG_STRIP_TRIVIAL_ACCENT){
		    if (strlen(pinyin_curr)>1){
			pinyin[j++]='e';
			break;
		    }
		}
		/* Do not remove trivial accent. */
		/* or Non trivial E. */
		if (formatFlags & PINYIN_FORMAT_FLAG_ASCII_ONLY){
		    if (formatFlags & PINYIN_FORMAT_FLAG_NFD){
			pinyin[j++]='e';
			pinyin[j++]='^';
		    }else{
			pinyin[j++]='E';
		    }
		}else{
		    /* Allow non-ascii, add circumflex */
		    pinyin[j++]='e';
		    pinyin[j++]='\xCC';
		    pinyin[j++]='\x82';
		    canNFC=TRUE;
		}
		break;
	    default:
		pinyin[j++]=pinyin_curr[i];
		break;
	}
    }
    pinyin[j]='\0';
    pinyin_add_tone(pinyin,syl->tone,formatFlags);
    if (pinyin_tmp){
	g_free(pinyin_tmp);
    }	

    Pinyin* result=NULL;
    if (canNFC && !(formatFlags & PINYIN_FORMAT_FLAG_NFD)){
	result=g_utf8_normalize(pinyin,PINYIN_MAX_LENGTH,G_NORMALIZE_NFC);
	g_free(pinyin);
    }else{
	result=pinyin;
    }
    return result;
}

Zhuyin *syllable_to_zhuyin(Syllable *syl,ZhuyinFormatFlags formatFlags){
    Zhuyin *zhuyin_tmp=NULL;
    Zhuyin *zhuyin_curr=NULL;
    Zhuyin *zhuyin=zhuyin_new(NULL);

    if (!syllable_is_zhuyin_fast(syl)){
	zhuyin_tmp=pinyin_normalized_to_zhuyin_toneless(syl->transcription);
	zhuyin_curr=zhuyin_tmp;
    }else{
	zhuyin_curr=syl->transcription;
    }

    g_strlcpy(zhuyin,zhuyin_curr,ZHUYIN_MAX_LENGTH);
    zhuyin_add_tone(zhuyin,syl->tone,formatFlags);
    if (zhuyin_tmp){
	g_free(zhuyin_tmp);
    }
    return zhuyin;
}

gboolean syllable_is_zhuyin(Syllable *syl){
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(syl->transcription, -1 , &items_written);
    for(i=0;i<items_written;i++){
	if (zhuyinSymbol_get_id(uniStr[i])==ZHUYIN_INVALID_SYMBOL){
	    return FALSE;
	}
    }
    return TRUE;
}


gboolean syllable_is_zhuyin_fast(Syllable *syl){
    gunichar uniCh=g_utf8_get_char(syl->transcription);
    if (zhuyinSymbol_get_id(uniCh)==ZHUYIN_INVALID_SYMBOL){
	return FALSE;
    }
    return TRUE;
}

void syllable_free(Syllable *syl){
    g_free(syl->transcription);
    g_free(syl);
}

/*----------------------------------------------------------
 * Syllable regex functions.
 */

regex_t pinyin_import_regex_t;
regex_t pinyin_regex_t;
regex_t zhuyin_regex_t;
gboolean syllable_regex_t_initialized=FALSE;

int syllabel_regex_t_init(){
    int ret=0;
    gchar buf[MAX_STRING_BUFFER_SIZE];
    if (!syllable_regex_t_initialized){
	ret=regcomp(&pinyin_import_regex_t, PINYIN_REGEX_IMPORT, REG_EXTENDED);
	if (ret){
	    regerror(ret, &pinyin_import_regex_t, buf, MAX_STRING_BUFFER_SIZE);
	    verboseMsg_print(VERBOSE_MSG_ERROR,"[Error] syllable_regex_init(): ");
	    verboseMsg_print(VERBOSE_MSG_ERROR,"cannot compile pinyin_import_regex_t:  %s\n",buf);
	    return ret;
	}

	ret=regcomp(&pinyin_regex_t, PINYIN_REGEX, REG_EXTENDED);
	if (ret){
	    regerror(ret, &pinyin_regex_t, buf, MAX_STRING_BUFFER_SIZE);
	    verboseMsg_print(VERBOSE_MSG_ERROR,"[Error] syllable_regex_init(): ");
	    verboseMsg_print(VERBOSE_MSG_ERROR,"cannot compile pinyin_regex_t:  %s\n",buf);
	    return ret;
	}

	ret=regcomp(&zhuyin_regex_t, ZHUYIN_REGEX, REG_EXTENDED);
	if (ret){
	    regerror(ret, &zhuyin_regex_t, buf, MAX_STRING_BUFFER_SIZE);
	    verboseMsg_print(VERBOSE_MSG_ERROR,"[Error] syllable_regex_init(): ");
	    verboseMsg_print(VERBOSE_MSG_ERROR,"cannot compile zhuyin_regex_t:  %s\n",buf);
	    return ret;
	}
	syllable_regex_t_initialized=TRUE;

    }
    return ret;
}

/*==========================================================
 * Pinyin <=> Zhuyin functions.
 */

static PinyinFormatFlags pinyinAccentFormat_to_pinyinFormatFlags(
	PinyinAccentFormat toFormat, gboolean useTrailNumber){
    PinyinFormatFlags formatFlags=(useTrailNumber)? 0 : PINYIN_FORMAT_FLAG_TONE_AS_ACCENT;
    switch(toFormat){
	case PINYIN_ACCENT_ALWAYS:
	    break;
	case PINYIN_ACCENT_ORIGINAL:
	    formatFlags |= PINYIN_FORMAT_FLAG_STRIP_TRIVIAL_ACCENT;
	    break;
	case PINYIN_ACCENT_UNIHAN:
	    formatFlags |= PINYIN_FORMAT_FLAG_STRIP_TRIVIAL_ACCENT | PINYIN_FORMAT_FLAG_STRIP_CIRCUMFLEX;
	    break;
	case PINYIN_ACCENT_TRAILING:
	    formatFlags |= PINYIN_FORMAT_FLAG_STRIP_TRIVIAL_ACCENT | PINYIN_FORMAT_FLAG_STRIP_CIRCUMFLEX 
		| PINYIN_FORMAT_FLAG_NFD | PINYIN_FORMAT_FLAG_ASCII_ONLY;
	    break;
	case PINYIN_ACCENT_INPUT_METHOD:
	    formatFlags |= PINYIN_FORMAT_FLAG_STRIP_TRIVIAL_ACCENT | PINYIN_FORMAT_FLAG_STRIP_CIRCUMFLEX 
		| PINYIN_FORMAT_FLAG_ASCII_ONLY;
	    break;
	case PINYIN_ACCENT_NONE:
	    formatFlags |= PINYIN_FORMAT_FLAG_STRIP_CIRCUMFLEX | PINYIN_FORMAT_FLAG_STRIP_DIAERESIS ;
	    break;
	case PINYIN_ACCENT_INTERNAL:
	    formatFlags |= PINYIN_FORMAT_FLAG_ASCII_ONLY;
	    break;
    }
    return formatFlags;
}

static ZhuyinFormatFlags zhuyinToneMarkFormat_to_zhuyinFormatFlags(
	ZhuyinToneMarkFormat toFormat){
    ZhuyinFormatFlags formatFlags=0;
    switch(toFormat){
	case ZHUYIN_TONEMARK_ALWAYS:
	    break;
	case ZHUYIN_TONEMARK_ORIGINAL:
	    formatFlags |= ZHUYIN_FORMAT_FLAG_FRONT_5TH_TONE;
	    break;
	case ZHUYIN_TONEMARK_INPUT_METHOD:
	    formatFlags |= ZHUYIN_FORMAT_FLAG_STRIP_1ST_TONE;
	    break;
	case ZHUYIN_TONEMARK_NUMERICAL:
	    formatFlags |= ZHUYIN_FORMAT_FLAG_NUMERICAL_TONE;
	    break;
    }
    return formatFlags;
}


/*==========================================================
 * Pinyin functions.
 */

	

Pinyin *pinyin_new(const char *pinyin_str){
    Pinyin *pinyin;
    if (isEmptyString(pinyin_str)){
	pinyin=NEW_ARRAY_INSTANCE(PINYIN_MAX_LENGTH,char);
	initString(pinyin);
    }else{
	pinyin=g_strndup(pinyin_str,PINYIN_MAX_LENGTH);
    }
    return pinyin;
}


static guint uniChar_get_tone(gunichar uniChar){
    int i;
    if (uniChar>='1' && uniChar<='9'){
	return uniChar-'0';
    }
    for(i=0;i<4;i++){
	if (PINYIN_COMBINING_TONED_ACCENTS[i]==uniChar){
	    return i+1;
	}
    }
    for(i=0;i<5;i++){
	if (ZHUYIN_TONED_SYMBOLS[i]==uniChar){
	    return i+1;
	}
    }
    return 0;
}

gboolean pinyin_has_tone(const Pinyin* pinyin){
    if (pinyin_get_tone(pinyin)){
	return TRUE;
    }
    return FALSE;
}

guint pinyin_get_tone(const Pinyin* pinyin){
    Pinyin* pinyin_norm=g_utf8_normalize(pinyin,PINYIN_MAX_LENGTH,G_NORMALIZE_NFD);
    guint tone=0;
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinyin_norm, -1 , &items_written);
    for (i=0;i<items_written;i++){
	tone =uniChar_get_tone(uniStr[i]);
	if (tone){
	   break;
	}
    }
    g_free(pinyin_norm);
    g_free(uniStr);
    return tone;
}

guint pinyin_strip_tone_normalized(Pinyin* pinyin){
    glong i,items_written;
    Pinyin* pinyin_norm=g_utf8_normalize(pinyin,PINYIN_MAX_LENGTH,G_NORMALIZE_NFD);
    guint tone=0;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinyin_norm, -1 , &items_written);
    Pinyin *pinyin_tmp=pinyin_new(NULL);

    for (i=0;i<items_written;i++){
	tone =uniChar_get_tone(uniStr[i]);
	if (tone){
	    continue;
	}else{
	    utf8_concat_ucs4(pinyin_tmp,uniStr[i]);
	}
    }
    g_strlcpy(pinyin,pinyin_tmp,PINYIN_MAX_LENGTH);
    g_free(pinyin_tmp);
    g_free(pinyin_norm);
    g_free(uniStr);
    return tone;
}

guint pinyin_strip_tone(Pinyin* pinyin){
    gboolean isDecomposed=string_is_decomposed_fast(pinyin);
    guint tone=pinyin_strip_tone_normalized(pinyin);
    if (!isDecomposed){
	gchar *pinyin_tmp=g_utf8_normalize(pinyin,PINYIN_MAX_LENGTH,G_NORMALIZE_NFC);
	g_strlcpy(pinyin,pinyin_tmp,PINYIN_MAX_LENGTH);
    }
    return tone;
}

#define HAS_A			0x01
#define HAS_E			0x02
#define HAS_I			0x04
#define HAS_O			0x08
#define HAS_U			0x10

void pinyin_add_tone_formatFlags(Pinyin* pinyin, guint tone, PinyinFormatFlags formatFlags){
    if (tone==0){
	return;
    }
    int index=-1;
    pinyin_strip_tone_normalized(pinyin);
    if (!(formatFlags & PINYIN_FORMAT_FLAG_TONE_AS_ACCENT)){
	/* Numeric tone */
	string_append_c(pinyin,'0'+tone,PINYIN_MAX_LENGTH);
	return;
    }
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(pinyin, -1 , &items_written);
    guint hasVowel=0;
    for(i=0;i<items_written;i++){
	switch(uniStr[i]){
	    case 'a':
		index=i+1;
		hasVowel |= HAS_A;
		break;
	    case 0x302: // combining circumflex accent
	    case 'e':
		hasVowel |= HAS_E;
		index=i+1;
		break;
	    case 'o':
		index=i+1;
		hasVowel |= HAS_O;
	    case 'i':
		hasVowel |= HAS_I;
		if (hasVowel & ~ (HAS_A| HAS_E| HAS_O)){
		    index=i+1;
		}
		break;
	    case 0x308: // combining diaeresis
	    case 'u':
		hasVowel |= HAS_U;
		if (hasVowel & ~ (HAS_A| HAS_E| HAS_O)){
		    index=i+1;
		}
		break;
	    default:
		break;
	}
	if (hasVowel & HAS_A){
	    break;
	}
    }
    initString(pinyin);
    for(i=0;i<items_written+1;i++){
	if (i==index){
	    if (tone<5){
		utf8_concat_ucs4(pinyin,PINYIN_COMBINING_TONED_ACCENTS[tone-1]);
	    }
	}
	if (i>=items_written){
	    break;
	}
	utf8_concat_ucs4(pinyin,uniStr[i]);
    }
    if (!(formatFlags & PINYIN_FORMAT_FLAG_NFD)){
	/* Need NFC */
	gchar *pinyin_tmp=g_utf8_normalize(pinyin,PINYIN_MAX_LENGTH,G_NORMALIZE_NFC);
	g_strlcpy(pinyin,pinyin_tmp,PINYIN_MAX_LENGTH);
	g_free(pinyin_tmp);
    }
    g_free(uniStr);
}

void pinyin_add_tone(Pinyin* pinyin, guint tone, gboolean useTrailNumber){
    PinyinFormatFlags formatFlags=(useTrailNumber)? 0 : PINYIN_FORMAT_FLAG_TONE_AS_ACCENT;
    if (string_is_decomposed_fast(pinyin)){
	formatFlags |= PINYIN_FORMAT_FLAG_NFD;
    }
    pinyin_add_tone_formatFlags(pinyin,tone,formatFlags);
}


Pinyin *pinyin_convert_formatFlags(const Pinyin *pinyin, PinyinFormatFlags formatFlags){
    Syllable *syl=syllable_new_pinyin(pinyin);
    return syllable_to_pinyin(syl, formatFlags);
}

Pinyin *pinyin_convert_accent_format(const Pinyin* pinyin, PinyinAccentFormat toFormat, gboolean useTrailNumber){
    return pinyin_convert_formatFlags(pinyin, pinyinAccentFormat_to_pinyinFormatFlags(toFormat,useTrailNumber));
}

Zhuyin *pinyin_to_zhuyin_formatFlags(const Pinyin* pinyin, ZhuyinFormatFlags formatFlags){
    Syllable *syl=syllable_new_pinyin(pinyin);
    return syllable_to_zhuyin(syl, formatFlags);
}

Zhuyin *pinyin_to_zhuyin(const Pinyin* pinyin, ZhuyinToneMarkFormat toFormat){
    return pinyin_to_zhuyin_formatFlags(pinyin, zhuyinToneMarkFormat_to_zhuyinFormatFlags(toFormat));
}


/*----------------------------------------
 * Pinyin regex functions.
 */

gchar *pinyin_regex_import_formatted_combine(const gchar *str, const gchar *format){
    int ret=syllabel_regex_t_init();
    if (ret)
	return NULL;
    return string_regex_formatted_combine_regex_t(str, &pinyin_import_regex_t, format, 0, NULL);
}

gchar *pinyin_regex_formatted_combine(const gchar *str, const gchar *format){
    int ret=syllabel_regex_t_init();
    if (ret)
	return NULL;
    return string_regex_formatted_combine_regex_t(str, &pinyin_regex_t, format, 0, NULL);
}


/*========================================
 * Zhuyin functions.
 */
Zhuyin *zhuyin_new(const char *zhuyin_str){
    Zhuyin *zhuyin=NULL;
    if (isEmptyString(zhuyin_str)){
	zhuyin=NEW_ARRAY_INSTANCE(ZHUYIN_MAX_LENGTH,char);
	initString(zhuyin);
    }else{
	zhuyin=g_utf8_strup(zhuyin_str,ZHUYIN_MAX_LENGTH);
    }
    return zhuyin;
}

guint zhuyin_get_tone(const Zhuyin* zhuyin){
    guint tone=0,toneTmp;
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuyin, -1 , &items_written);
    for (i=0;i<items_written;i++){
	toneTmp=zhuyinSymbol_to_toneMark_id(uniStr[i]);
	if (toneTmp){
	    tone=toneTmp;
	}
    }
    g_free(uniStr);
    return tone;
}

guint zhuyin_strip_tone(Zhuyin* zhuyin){
    guint tone=0,toneTmp;
    glong i,items_written;
    gunichar *uniStr=g_utf8_to_ucs4_fast(zhuyin, -1 , &items_written);
    initString(zhuyin);
    for (i=0;i<items_written;i++){
	toneTmp=zhuyinSymbol_to_toneMark_id(uniStr[i]);
	if (toneTmp){
	    tone=toneTmp;
	}else{
	    utf8_concat_ucs4(zhuyin,uniStr[i]);
	}
    }
    g_free(uniStr);
    return tone;
}

void zhuyin_add_tone_formatFlags(Zhuyin* zhuyin, guint tone, ZhuyinFormatFlags formatFlags){
    if (tone==0){
	return;
    }
    if (tone==1 && formatFlags & ZHUYIN_FORMAT_FLAG_STRIP_1ST_TONE){
	return;
    }
    Zhuyin zhuyin_tmp[ZHUYIN_MAX_LENGTH];
    initString(zhuyin_tmp);
    if (tone==5 && formatFlags & ZHUYIN_FORMAT_FLAG_FRONT_5TH_TONE){
	utf8_concat_ucs4(zhuyin_tmp,ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_NEUTRAL]);
	g_strlcat(zhuyin_tmp,zhuyin,ZHUYIN_MAX_LENGTH);
    }else{
	g_strlcat(zhuyin_tmp,zhuyin,ZHUYIN_MAX_LENGTH);
	if (formatFlags & ZHUYIN_FORMAT_FLAG_NUMERICAL_TONE){
	    string_append_c(zhuyin_tmp,tone+'0',ZHUYIN_MAX_LENGTH);
	}else{
	    utf8_concat_ucs4(zhuyin_tmp,zhuyinSymbol_from_toneMark_id(tone));
	}
    }
    g_strlcpy(zhuyin,zhuyin_tmp,ZHUYIN_MAX_LENGTH);

}

void zhuyin_add_tone(Zhuyin* zhuyin, guint tone, ZhuyinToneMarkFormat toFormat){
    zhuyin_add_tone_formatFlags(zhuyin,tone,zhuyinToneMarkFormat_to_zhuyinFormatFlags(toFormat));
}

Zhuyin *zhuyin_convert_formatFlags(const Zhuyin *zhuyin, PinyinFormatFlags formatFlags){
    Syllable *syl=syllable_new_zhuyin(zhuyin);
    return syllable_to_zhuyin(syl, formatFlags);
}

Zhuyin *zhuyin_convert_toneMark_format(const Zhuyin* zhuyin, ZhuyinToneMarkFormat toFormat){
    return zhuyin_convert_formatFlags(zhuyin,zhuyinToneMarkFormat_to_zhuyinFormatFlags(toFormat));
}


Pinyin *zhuyin_to_pinyin_formatFlags(const Zhuyin* zhuyin, PinyinFormatFlags formatFlags){
    Syllable *syl=syllable_new_zhuyin(zhuyin);
    return syllable_to_pinyin(syl,formatFlags);
}

Pinyin *zhuyin_to_pinyin(const Zhuyin* zhuyin, PinyinAccentFormat toFormat,gboolean useTrailNumber){
    return zhuyin_to_pinyin_formatFlags(zhuyin,pinyinAccentFormat_to_pinyinFormatFlags(toFormat,useTrailNumber));
}

/*----------------------------------------
 * Zhuyin regex functions.
 */
gchar *zhuyin_regex_formatted_combine(const gchar *str, const gchar *format){
    int ret=syllabel_regex_t_init();
    if (ret)
	return NULL;
    return string_regex_formatted_combine_regex_t(str, &zhuyin_regex_t, format, 0, NULL);
}



/*----------------------------------------------------------
 * ZhuyinSymbol functions.
 */


ZhuyinSymbol zhuyinSymbol_from_id(ZhuyinSymbolId id){
    if (id<0 || id >= ZHUYIN_SYMBOL_COUNT )
	return 0;
    return ZHUYIN_SYMBOL_LIST[id];
}

ZhuyinSymbolId zhuyinSymbol_get_id(ZhuyinSymbol zSym){
    int j;
    for (j=ZHUYIN_SYMBOL_COUNT-1;j>=0;j--){
	if (ZHUYIN_SYMBOL_LIST[j]==zSym){
	    return j;
	}
    }
    return ZHUYIN_INVALID_SYMBOL;
}

gboolean zhuyinSymbol_is_initial(ZhuyinSymbol zSym){
    if ((zSym>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_B]) &&
	    (zSym<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_S])){
	return TRUE;
    }
    return FALSE;
}

gboolean zhuyinSymbol_is_medial(ZhuyinSymbol zSym){
    if ((zSym>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_I]) &&
	    (zSym<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_U_DIAERESIS])){
	return TRUE;
    }
    return FALSE;
}

gboolean zhuyinSymbol_is_final(ZhuyinSymbol zSym){
    if ((zSym>= ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_A]) &&
	(zSym<=ZHUYIN_SYMBOL_LIST[ZHUYIN_SYMBOL_ER])){
	return TRUE;
    }
    return FALSE;
}


gboolean zhuyinSymbol_is_tone(ZhuyinSymbol zSym){
    return (zhuyinSymbol_to_toneMark_id(zSym)==0) ? FALSE : TRUE;
}

guint zhuyinSymbol_to_toneMark_id(ZhuyinSymbol zSym){
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

ZhuyinSymbol zhuyinSymbol_from_toneMark_id(guint toneMark_id){
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
 * Zhuyin database conversion functions.
 */

void pinyin_convert_accent_format_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==3);
    char pinyinTmp[PINYIN_MAX_LENGTH];
    const char *pinyin=sqlite_value_signed_text_buffer(pinyinTmp,argv[0]);
    int toFormat= (sqlite3_value_type(argv[1])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[1]): 0;
    gboolean useTrailNumber= 
	(((sqlite3_value_type(argv[2])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[2]): 0)==0)? FALSE: TRUE;
    char *pStr=pinyin_convert_accent_format(pinyin,toFormat,useTrailNumber);
    sqlite3_result_text(context,pStr,-1,g_free);
}

void pinyin_to_zhuyin_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==2);
    char pinyinTmp[PINYIN_MAX_LENGTH];
    const char *pinyin=sqlite_value_signed_text_buffer(pinyinTmp,argv[0]);
    int toFormat= (sqlite3_value_type(argv[1])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[1]): 0;
    char *pStr=pinyin_to_zhuyin(pinyin,toFormat);
    sqlite3_result_text(context,pStr,-1,g_free);
}

void zhuyin_convert_toneMark_format_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==2);
    char zhuyinTmp[ZHUYIN_MAX_LENGTH];
    const char *zhuyin=sqlite_value_signed_text_buffer(zhuyinTmp,argv[0]);
    int toFormat= (sqlite3_value_type(argv[1])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[1]): 0;
    char *pStr=zhuyin_convert_toneMark_format(zhuyin,toFormat);
    sqlite3_result_text(context,pStr,-1,g_free);
}

void zhuyin_to_pinyin_scalar_func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==3);
    char zhuyinTmp[ZHUYIN_MAX_LENGTH];
    const char *zhuyin=sqlite_value_signed_text_buffer(zhuyinTmp,argv[0]);
    int toFormat= (sqlite3_value_type(argv[1])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[1]): 0;
    gboolean useTrailNumber= 
	(((sqlite3_value_type(argv[2])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[2]): 0)==0)? FALSE: TRUE;
    char *pStr=zhuyin_to_pinyin(zhuyin,toFormat,useTrailNumber);
    sqlite3_result_text(context,pStr,-1,g_free);
}




