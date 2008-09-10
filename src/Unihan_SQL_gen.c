/** 
 * @file Unihan_SQL_gen.c
 * @brief SQL statement generation function and house keeping functions.
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

#include "config.h"
#include <stdio.h>
#include "Unihan.h"
#include "allocate.h"
#include "sqlite_functions.h"
#include "str_functions.h"
#include "verboseMsg.h"

#define MAX_BUFFER_SIZE 2000
static sqlite3 *unihanDb=NULL;

/**
 * UNIHAN_FIELD_NAMES.
 *
 *
 */
const char *UNIHAN_FIELD_NAMES[UNIHAN_FIELDS_COUNT+1]={
    "code",
    "kAccountingNumeric",
    "kBigFive",
    "kCangjie",
    "kCantonese",
    "kCCCII",
    "kCheungBauerIndex",
    "kCheungBauer",
    "kCihaiT",
    "kCNS1986",
    "kCNS1992",
    "kCompatibilityVariant",
    "kCowles",
    "kDaeJaweon",
    "kDefinition",
    "kEACC",
    "kFennIndex",
    "kFenn",
    "kFourCornerCode",
    "kFrequency",
    "kGB0",
    "kGB1",
    "kGB3",
    "kGB5",
    "kGB7",
    "kGB8",
    "kGradeLevel",
    "kGSR",
    "kHangul",
    "kHanYu",
    "kHanyuPinlu",
    "kHDZRadBreak",
    "kHKGlyph",
    "kHKSCS",
    "kIBMJapan",
    "kIICore",
    "kIRGDaeJaweon",
    "kIRGDaiKanwaZiten",
    "kIRGHanyuDaZidian",
    "kIRGKangXi",
    "kIRG_GSource",
    "kIRG_HSource",
    "kIRG_JSource",
    "kIRG_KPSource",
    "kIRG_KSource",
    "kIRG_TSource",
    "kIRG_USource",
    "kIRG_VSource",
    "kJapaneseKun",
    "kJapaneseOn",
    "kJIS0213",
    "kJis0",
    "kJis1",
    "kKangXi",
    "kKarlgren",
    "kKorean",
    "kKPS0",
    "kKPS1",
    "kKSC0",
    "kKSC1",
    "kLau",
    "kMainlandTelegraph",
    "kMandarin",
    "kMatthews",
    "kMeyerWempe",
    "kMorohashi",
    "kNelson",
    "kOtherNumeric",
    "kPhonetic",
    "kPrimaryNumeric",
    "kPseudoGB1",
    "kRSAdobe_Japan1_6",
    "kRSJapanese",
    "kRSKangXi",
    "kRSKanWa",
    "kRSKorean",
    "kRSUnicode",
    "kSBGY",
    "kSemanticVariant",
    "kSimplifiedVariant",
    "kSpecializedSemanticVariant",
    "kTaiwanTelegraph",
    "kTang",
    "kTotalStrokes",
    "kTraditionalVariant",
    "kVietnamese",
    "kXerox",
    "kXHC1983",
    "kZVariant",

    "utf8",

    "shortSourceName",
    "sourceMapping",

    "variantType",
    "variantCode",

    "fromDict",
    "semanticT",
    "semanticB",
    "semanticZ",

    "radicalIndex",
    "additionalStrokeCount",

    "adobeCID_CV",
    "adobeCID",
    "adobeCID_radicalStrokeCount",

    "kangXi_page",
    "kangXi_charNum",
    "kangXi_virtual",

    "freqRank",

    "pinyin",
    "pinyin_freq",

    "zVariantSource",
    NULL
};

const char *UNIHAN_TABLE_NAMES[]={
    "kAccountingNumericTable",
    "kBigFiveTable",
    "kCangjieTable",
    "kCantoneseTable",
    "kCCCIITable",
    "kCheungBauerIndexTable",
    "kCheungBauerTable",
    "kCihaiTTable",
    "kCNS1986Table",
    "kCNS1992Table",
    "kCompatibilityVariantTable",
    "kCowlesTable",
    "kDaeJaweonTable",
    "kDefinitionTable",
    "kEACCTable",
    "kFennIndexTable",
    "kFennTable",
    "kFourCornerCodeTable",
    "kFrequencyTable",
    "kGB0Table",
    "kGB1Table",
    "kGB3Table",
    "kGB5Table",
    "kGB7Table",
    "kGB8Table",
    "kGradeLevelTable",
    "kGSRTable",
    "kHangulTable",
    "kHanYuTable",
    "kHanyuPinluTable",
    "kHDZRadBreakTable",
    "kHKGlyphTable",
    "kHKSCSTable",
    "kIBMJapanTable",
    "kIICoreTable",
    "kIRGDaeJaweonTable",
    "kIRGDaiKanwaZitenTable",
    "kIRGHanyuDaZidianTable",
    "kIRGKangXiTable",
    "kJapaneseKunTable",
    "kJapaneseOnTable",
    "kJIS0213Table",
    "kJis0Table",
    "kJis1Table",
    "kKangXiTable",
    "kKarlgrenTable",
    "kKoreanTable",
    "kKPS0Table",
    "kKPS1Table",
    "kKSC0Table",
    "kKSC1Table",
    "kLauTable",
    "kMainlandTelegraphTable",
    "kMandarinTable",
    "kMatthewsTable",
    "kMeyerWempeTable",
    "kMorohashiTable",
    "kNelsonTable",
    "kOtherNumericTable",
    "kPhoneticTable",
    "kPrimaryNumericTable",
    "kPseudoGB1Table",
    "kRSAdobe_Japan1_6Table",
    "kRSJapaneseTable",
    "kRSKangXiTable",
    "kRSKanWaTable",
    "kRSKoreanTable",
    "kRSUnicodeTable",
    "kSBGYTable",
    "kSemanticVariantTable",
    "kSimplifiedVariantTable",
    "kSpecializedSemanticVariantTable",
    "kTaiwanTelegraphTable",
    "kTangTable",
    "kTotalStrokesTable",
    "kTraditionalVariantTable",
    "kVietnameseTable",
    "kXeroxTable",
    "kXHC1983Table",
    "kZVariantTable",

    "utf8Table",

    "IRG_SourceTable",

    "IRG_SourceMappingTable",

    "kSemanticVariantTableExtra",
    "kSpecializedSemanticVariantTableExtra",
    "kZVariantTableExtra",
    NULL
};



/**
 * Fields that holds integer.
 *
 * Note that 0-padded fields (such as UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT) are not treated as integer.
 */
const UnihanField UNIHAN_INTEGER_FIELDS[]={
    UNIHAN_FIELD_CODE,
    UNIHAN_FIELD_KACCOUNTINGNUMERIC,
    UNIHAN_FIELD_KCOMPATIBILITYVARIANT,
    UNIHAN_FIELD_KFREQUENCY,
    UNIHAN_FIELD_KGRADELEVEL,
    UNIHAN_FIELD_KOTHERNUMERIC,
    UNIHAN_FIELD_KPRIMARYNUMERIC,
    UNIHAN_FIELD_KSIMPLIFIEDVARIANT,

    UNIHAN_FIELD_KTOTALSTROKES,
    UNIHAN_FIELD_KTRADITIONALVARIANT,

    UNIHAN_FIELD_VARIANT_CODE,
    UNIHAN_FIELD_SEMANTIC_T,
    UNIHAN_FIELD_SEMANTIC_B,
    UNIHAN_FIELD_SEMANTIC_Z,

    UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT,

    UNIHAN_FIELD_KANGXI_VIRTUAL,
    UNIHAN_FIELD_FREQ_RANK,
    UNIHAN_FIELD_PINYIN_FREQ,
    UNIHAN_INVALID_FIELD
};


UnihanField UNIHAN_IRG_SOURCE_FIELDS[]={
    UNIHAN_FIELD_KIRG_GSOURCE,
    UNIHAN_FIELD_KIRG_HSOURCE,
    UNIHAN_FIELD_KIRG_JSOURCE,
    UNIHAN_FIELD_KIRG_KPSOURCE,
    UNIHAN_FIELD_KIRG_KSOURCE,
    UNIHAN_FIELD_KIRG_TSOURCE,
    UNIHAN_FIELD_KIRG_USOURCE,
    UNIHAN_FIELD_KIRG_VSOURCE,
    UNIHAN_INVALID_FIELD
};

const UnihanField UNIHAN_KRS_FIELDS[]={
    UNIHAN_FIELD_KRSADOBE_JAPAN1_6,
    UNIHAN_FIELD_KRSJAPANESE,
    UNIHAN_FIELD_KRSKANGXI,
    UNIHAN_FIELD_KRSKANWA,
    UNIHAN_FIELD_KRSKOREAN,
    UNIHAN_FIELD_KRSUNICODE,
    UNIHAN_INVALID_FIELD
};

const UnihanField UNIHAN_KVARIANT_FIELDS[]={
    UNIHAN_FIELD_KCOMPATIBILITYVARIANT,
    UNIHAN_FIELD_KSEMANTICVARIANT,
    UNIHAN_FIELD_KSIMPLIFIEDVARIANT,
    UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT, 
    UNIHAN_FIELD_KTRADITIONALVARIANT,
    UNIHAN_FIELD_KZVARIANT,
    UNIHAN_INVALID_FIELD
};


const UnihanField UNIHAN_SCALAR_FIELDS[]={
    UNIHAN_FIELD_CODE,
    UNIHAN_FIELD_KCOMPATIBILITYVARIANT,
    UNIHAN_FIELD_KSEMANTICVARIANT,
    UNIHAN_FIELD_KSIMPLIFIEDVARIANT,
    UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT, 
    UNIHAN_FIELD_KTRADITIONALVARIANT,
    UNIHAN_FIELD_KZVARIANT,
    UNIHAN_FIELD_VARIANT_CODE,
    UNIHAN_INVALID_FIELD
};

/**
 * Fields that are functional dependent to code.
 *
 * 
 */
const UnihanField UNIHAN_SINGLETON_FIELDS[]={
    UNIHAN_FIELD_CODE,
    UNIHAN_FIELD_KACCOUNTINGNUMERIC,
    UNIHAN_FIELD_KBIGFIVE,
    UNIHAN_FIELD_KCCCII,
    UNIHAN_FIELD_KCHEUNGBAUER,
    UNIHAN_FIELD_KCNS1986,
    UNIHAN_FIELD_KCNS1992,
    UNIHAN_FIELD_KDEFINITION,
    UNIHAN_FIELD_KFOURCORNERCODE,
    UNIHAN_FIELD_KFREQUENCY,
    UNIHAN_FIELD_KGB0,
    UNIHAN_FIELD_KGB1,
    UNIHAN_FIELD_KGB3,
    UNIHAN_FIELD_KGB5,
    UNIHAN_FIELD_KGB7,
    UNIHAN_FIELD_KGB8,
    UNIHAN_FIELD_KGRADELEVEL,
    UNIHAN_FIELD_KHKSCS,
    UNIHAN_FIELD_KHKGLYPH,
    UNIHAN_FIELD_KIICORE,
    UNIHAN_FIELD_KIBMJAPAN,
    UNIHAN_FIELD_KJIS0213,
    UNIHAN_FIELD_KJIS0,	
    UNIHAN_FIELD_KJIS1,	
    UNIHAN_FIELD_KKPS0,
    UNIHAN_FIELD_KKPS1,
    UNIHAN_FIELD_KKSC0,
    UNIHAN_FIELD_KKSC1,
    UNIHAN_FIELD_KMAINLANDTELEGRAPH,
    UNIHAN_FIELD_KOTHERNUMERIC,
    UNIHAN_FIELD_KPRIMARYNUMERIC,
    UNIHAN_FIELD_KTAIWANTELEGRAPH,
    UNIHAN_FIELD_KTOTALSTROKES,
    UNIHAN_FIELD_KXEROX,
    UNIHAN_FIELD_UTF8,
    UNIHAN_INVALID_FIELD
};

UnihanIRG_SourceData UNIHAN_IRG_SOURCES[]={
    {"G0","GB2312-80"},
    {"G1","GB12345-90 with 58 Hong Kong and 92 Korean \"Idu\" characters"},
    {"G3","GB7589-87 unsimplified forms"},
    {"G5","GB7590-87 unsimplified forms"},
    {"G7","General Purpose Hanzi List for Modern Chinese Language, and General List of Simplified Hanzi"},
    {"GS","Singapore characters"},
    {"G8","GB8685-88"},
    {"GE","GB16500-95"},
    {"G9","GB18030-2000"},
    {"G4K","Siku Quanshu"},
    {"GBK","Chinese Encyclopedia"},
    {"GCH","The Ci Hai (PRC edition)"},
    {"GCY","The Ci Yuan "},
    {"GFZ","Founder Press System"},
    {"GFZ_BK","Founder Press System"},
    {"GHC","The Hanyu Da Cidian"},
    {"GHZ","The Hanyu Da Zidian"},
    {"GKX","The KangXi dictionary"},

    {"H","Hong Kong Supplementary Character Set"},
    {"J0","JIS X 0208:1990"},
    {"J1","JIS X 0212:1990"},
    {"JA","Unified Japanese IT Vendors Contemporary Ideographs, 1993"},
    {"J3","JIS X 0213:2000"},
    {"J3A","JIS X 0213:2004 level-3"},
    {"J4","JIS X 0213:2000"},

    {"KP0","KPS 9566-97"},
    {"KP1","KPS 10721-2000"},

    {"K0","KS C 5601-1987"},
    {"K1","KS C 5657-1991"},
    {"K2","PKS C 5700-1 1994"},
    {"K3","PKS C 5700-2 1994"},
    {"K4","PKS 5700-3:1998"},

    {"T1","CNS 11643-1992, plane 1"},
    {"T2","CNS 11643-1992, plane 2"},
    {"T3","CNS 11643-1992, plane 3 (with some additional characters)"},
    {"T4","CNS 11643-1992, plane 4"},
    {"T5","CNS 11643-1992, plane 5"},
    {"T6","CNS 11643-1992, plane 6"},
    {"T7","CNS 11643-1992, plane 7"},
    {"TF","CNS 11643-1992, plane 15"},

    {"U","Other sources which were used by the Unicode Consortium"},

    {"V0","TCVN 5773:1993"},
    {"V1","TCVN 6056:1995"},
    {"V2","VHN 01:1998"},
    {"V3","VHN 02:1998"},
    {NULL}
};

#define UNIHAN_NOINDEX_IRG_SOURCES_COUNT	9
const UnihanIRG_SourceId UNIHAN_NOINDEX_IRG_SOURCES[UNIHAN_NOINDEX_IRG_SOURCES_COUNT]={
    UNIHAN_SOURCE_G4K,
    UNIHAN_SOURCE_GBK,
    UNIHAN_SOURCE_GCH,
    UNIHAN_SOURCE_GCY,
    UNIHAN_SOURCE_GFZ,
    UNIHAN_SOURCE_GFZ_BK,
    UNIHAN_SOURCE_GHC,
    UNIHAN_SOURCE_GHZ,
    UNIHAN_SOURCE_GKX
};

const char UNIHAN_LOCALE_NAMES[UNIHAN_LOCALES_COUNT][6]={
    "ja_JP",  
    "ko_KP",  
    "ko_KR",
    "zh_CN",  
    "zh_HK",  
    "zh_SG",  
    "zh_TW",  
    "vi_VN",
};

const char *UNIHAN_RANGE_NAMES[UNIHAN_RANGES_COUNT]={
    "CJK Unified Ideographs Extension A",
    "CJK Unified Ideographs",
    "CJK Unified Ideographs (4.1)",
    "CJK Unified Ideographs (5.1)",
    "CJK Compatibility Ideographs (a)",
    "CJK Compatibility Ideographs (b)",
    "CJK Compatibility Ideographs (4.1)",
    "CJK Unified Ideographs Extension B",
    "CJK Compatibility Supplement"
};

/*=========================================================================
 * Value parsing/toString functions
 */

/*-----------------------------
 * Parse KangXi
 */

typedef enum{
    UNIHAN_KANGXI_STATE_PAGE,
    UNIHAN_KANGXI_STATE_CHARNUM,
} UnihanKangXiState;

#define STRING_BUFFER_KANGXI_PAGE_SIZE 6
#define STRING_BUFFER_KANGXI_CHARNUM_SIZE 4
#define STRING_BUFFER_KANGXI_SIZE STRING_BUFFER_KANGXI_PAGE_SIZE + 1 +STRING_BUFFER_KANGXI_CHARNUM_SIZE +1
typedef struct {
    char page[STRING_BUFFER_KANGXI_PAGE_SIZE];
    char charNum[STRING_BUFFER_KANGXI_PAGE_SIZE];
    gboolean virtual;
} KangXiRec;

static GArray *kangXiRec_parse(const char *composite_value){
    GArray *gArray=g_array_new(FALSE,TRUE,sizeof(KangXiRec));
    char **subFieldArray=g_strsplit_set(composite_value," .",-1);
    int i;
    int currIndex=0;
    KangXiRec *currRec=NULL;
    UnihanKangXiState state=UNIHAN_KANGXI_STATE_PAGE;


    for(i=0;subFieldArray[i]!=NULL;i++){
	switch(state){
	    case UNIHAN_KANGXI_STATE_PAGE:
		state=UNIHAN_KANGXI_STATE_CHARNUM;
		break;
	    case UNIHAN_KANGXI_STATE_CHARNUM:
		g_assert(i>0);
		currIndex=gArray->len;
		g_array_set_size(gArray,currIndex+1);
		currRec=&g_array_index(gArray,KangXiRec,currIndex);
		g_strlcpy(currRec->page,subFieldArray[i-1],6);
		currRec->charNum[0]=subFieldArray[i][0];
		currRec->charNum[1]=subFieldArray[i][1];
		currRec->charNum[2]='\0';
		currRec->virtual=(subFieldArray[i][2]=='1') ? TRUE : FALSE;
		state=UNIHAN_KANGXI_STATE_PAGE;
		break;
	}
    }
    g_strfreev(subFieldArray);
    return gArray;
}

static void kangXiRec_parse_SQLite_value
(KangXiRec *rec, sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==3);
    if (sqlite3_value_type(argv[0])==SQLITE_TEXT){
	sqlite_value_signed_text_buffer(rec->page,argv[0]);
    }

    if (sqlite3_value_type(argv[1])==SQLITE_TEXT){
	sqlite_value_signed_text_buffer(rec->charNum,argv[1]);
    }

    int virtual=sqlite3_value_int(argv[2]);
    rec->virtual=(virtual) ? TRUE: FALSE;
}

static void kangXiRec_to_string(char* const buf, KangXiRec *rec){
    g_snprintf(buf,STRING_BUFFER_KANGXI_SIZE,"%s.%s%d",rec->page,rec->charNum,(rec->virtual)? 1:0);
}

/*-----------------------------
 * Parse pinyin freq (PinLu)
 */

typedef enum{
    UNIHAN_PINYIN_FREQ_STATE_PINYIN,
    UNIHAN_PINYIN_FREQ_STATE_FREQ,
    UNIHAN_PINYIN_FREQ_STATE_SEPARATER
} UnihanPinyinFreqState;


#define STRING_BUFFER_PINYIN_SIZE 8
#define STRING_BUFFER_FREQ_SIZE 6
#define STRING_BUFFER_PINYIN_FREQ_SIZE STRING_BUFFER_PINYIN_SIZE+ STRING_BUFFER_FREQ_SIZE +3
typedef struct {
    char pinyin[7];
    int freq;
} PinyinFreqRec;

static GArray *pinyinFreqRec_parse(const char *composite_value){
    GArray *gArray=g_array_new(FALSE,TRUE,sizeof(PinyinFreqRec));
    char **subFieldArray=g_strsplit_set(composite_value," ()",-1);
    int i;
    int currIndex=0;
    int freq;
    PinyinFreqRec *currRec=NULL;
    UnihanPinyinFreqState state=UNIHAN_PINYIN_FREQ_STATE_PINYIN;

    for(i=0;subFieldArray[i]!=NULL;i++){
	switch(state){
	    case UNIHAN_PINYIN_FREQ_STATE_PINYIN:
		state=UNIHAN_PINYIN_FREQ_STATE_FREQ;
		break;
	    case UNIHAN_PINYIN_FREQ_STATE_FREQ:
		g_assert(i>0);
		currIndex=gArray->len;
		g_array_set_size(gArray,currIndex+1);
		currRec=&g_array_index(gArray,PinyinFreqRec,currIndex);
		g_strlcpy(currRec->pinyin,subFieldArray[i-1],STRING_BUFFER_PINYIN_SIZE);
		freq=atoi(subFieldArray[i]);
		g_assert(freq);
		currRec->freq=freq;
		state=UNIHAN_PINYIN_FREQ_STATE_SEPARATER;
		break;
	    case UNIHAN_PINYIN_FREQ_STATE_SEPARATER:
		state=UNIHAN_PINYIN_FREQ_STATE_PINYIN;
		break;
	}
    }
    g_strfreev(subFieldArray);
    return gArray;
}

static void pinyinFreqRec_parse_SQLite_value
(PinyinFreqRec *rec, sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==2);
    if (sqlite3_value_type(argv[0])==SQLITE_TEXT){
	sqlite_value_signed_text_buffer(rec->pinyin,argv[0]);
    }
    rec->freq=sqlite3_value_int(argv[1]);
}

static void pinyinFreqRec_to_string(char* const buf, PinyinFreqRec *rec){
    g_snprintf(buf,STRING_BUFFER_PINYIN_FREQ_SIZE,"%s(%d)",rec->pinyin,rec->freq);
}



/*-----------------------------
 * Parse semantic variant
 */

typedef enum{
    UNIHAN_SEMANTIC_VARIANT_STATE_INIT=-1,
    UNIHAN_SEMANTIC_VARIANT_STATE_CODE,
    UNIHAN_SEMANTIC_VARIANT_STATE_DICT,
    UNIHAN_SEMANTIC_VARIANT_STATE_REL
} UnihanSemanticVariantState;

typedef struct {
    gunichar variantCode;
    char fromDict[40];
    gboolean T;
    gboolean B;
    gboolean Z;
} SemanticDictRec;

static GArray *semanticDictRec_parse(const char *composite_value){
    GArray *gArray=g_array_new(FALSE,TRUE,sizeof(SemanticDictRec));

    char **subFieldArray=g_strsplit_set(composite_value," <,:",-1);
    int i,j;
    int currIndex=0;
    SemanticDictRec *currRec=NULL;
    UnihanSemanticVariantState state=UNIHAN_SEMANTIC_VARIANT_STATE_CODE,
			       lastState=UNIHAN_SEMANTIC_VARIANT_STATE_INIT;
    gunichar variantCode=0;
    int len;
    for(i=0;subFieldArray[i]!=NULL;i++){
	switch(subFieldArray[i][0]){
	    case 'U':
		state=UNIHAN_SEMANTIC_VARIANT_STATE_CODE;
		variantCode=0;
		break;
	    case 'k':
		state=UNIHAN_SEMANTIC_VARIANT_STATE_DICT;
		break;
	    default:
		state=UNIHAN_SEMANTIC_VARIANT_STATE_REL;
		break;
	}
	switch(state){
	    case UNIHAN_SEMANTIC_VARIANT_STATE_CODE:
		variantCode=unihanChar_parse(subFieldArray[i]);
		currIndex=gArray->len;
		g_array_set_size(gArray,currIndex+1);
		currRec=&g_array_index(gArray,SemanticDictRec,currIndex);
		currRec->variantCode=variantCode;
		break;
	    case UNIHAN_SEMANTIC_VARIANT_STATE_DICT:
		g_assert(variantCode!=0);
		if (lastState!=UNIHAN_SEMANTIC_VARIANT_STATE_CODE){
		    currIndex=gArray->len;
		    g_array_set_size(gArray,currIndex+1);
		    currRec=&g_array_index(gArray,SemanticDictRec,currIndex);
		    currRec->variantCode=variantCode;
		}
		g_strlcpy(currRec->fromDict,subFieldArray[i],40);
		break;
	    case UNIHAN_SEMANTIC_VARIANT_STATE_REL:
		len=strlen(subFieldArray[i]);
		for(j=0;j<len;j++){
		    switch (subFieldArray[i][j]){
			case 'T':
			    currRec->T=TRUE;
			    break;
			case 'B':
			    currRec->B=TRUE;
			    break;
			case 'Z':
			    currRec->Z=TRUE;
			    break;
			default:
			    g_error("Unihan.c:semanticDictRec_parse(): Invalid relation character %c i=%d j=%d %s!\n"
				    ,subFieldArray[i][j],i,j,subFieldArray[i]);
			    break;
		    }
		}
		break;
	    default:
		break;
	}
	lastState=state;
    }
    g_strfreev(subFieldArray);
    return gArray;
}



/*=========================================================================
 * Sqlite non-aggregate custom functions
 */

static void adobeRadicalStroke_value_concat_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==5);
    char buf[20];
    char CV_buf[5];
    const char *CV=sqlite_value_signed_text_buffer(CV_buf,argv[0]);

    char cid_buf[5];
    const char *cid=sqlite_value_signed_text_buffer(cid_buf,argv[1]);

    char radical_buf[10];
    const char *radical=sqlite_value_signed_text_buffer(radical_buf,argv[2]);

    char radicalStroke_buf[10];
    const char *radical_stroke=sqlite_value_signed_text_buffer(radicalStroke_buf,argv[3]);

    char stroke_buf[10];
    const char *stroke=sqlite_value_signed_text_buffer(stroke_buf,argv[4]);

    g_snprintf(buf,20,"%s+%s+%s.%s.%s",CV,cid,radical,radical_stroke,stroke);
    char *pStr=g_strdup(buf);
    sqlite3_result_text(context,pStr,-1,g_free);
}

static void hanYu_pinLu_value_concat_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    PinyinFreqRec rec;
    char *pStr=NEW_ARRAY_INSTANCE(STRING_BUFFER_PINYIN_FREQ_SIZE,char);
    pinyinFreqRec_parse_SQLite_value(&rec, context, argc, argv);

    pinyinFreqRec_to_string(pStr,&rec);
    sqlite3_result_text(context,pStr,-1,g_free);
}

static void irg_source_value_concat_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==2);
    char buf[20];
    char shortName_buf[10];
    initString(shortName_buf);
    const char *shortName=(sqlite3_value_type(argv[0])==SQLITE_TEXT) ? 
	sqlite_value_signed_text_buffer(shortName_buf,argv[0]):NULL;
    
    char sourceMapping_buf[20];
    initString(sourceMapping_buf);
    const char *sourceMapping=(sqlite3_value_type(argv[1])==SQLITE_TEXT) ? 
       	sqlite_value_signed_text_buffer(sourceMapping_buf,argv[1]): NULL;
    char *pStr=NULL;

    UnihanIRG_SourceId source=unihanIRG_SourceId_parse(shortName);
    switch(source){
	case UNIHAN_SOURCE_H:
	case UNIHAN_SOURCE_U:
	    pStr=g_strdup(sourceMapping);
	    break;
	case UNIHAN_SOURCE_KP0:
	case UNIHAN_SOURCE_KP1:
	    g_snprintf(buf,20,"%s-%s",shortName,sourceMapping);
	    pStr=g_strdup(buf);
	    break;
	default:
	    subString(buf,shortName,1,strlen(shortName));
	    if (sourceMapping){
		g_strlcat(buf,"-",20);
		g_strlcat(buf,sourceMapping,20);
	    }
	    pStr=g_strdup(buf);
	    break;
    }
    sqlite3_result_text(context,pStr,-1,g_free);
}

static void kangXi_value_concat_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    KangXiRec rec;
    char *pStr=NEW_ARRAY_INSTANCE(STRING_BUFFER_KANGXI_SIZE,char);
    kangXiRec_parse_SQLite_value(&rec, context, argc, argv);

    kangXiRec_to_string(pStr,&rec);
    sqlite3_result_text(context,pStr,-1,g_free);
}

static void radicalStroke_value_concat_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==2);
    char buf[20];
    char radical_buf[10];
    const char *radical=sqlite_value_signed_text_buffer(radical_buf,argv[0]);
    char stroke_buf[10];
    const char *stroke=sqlite_value_signed_text_buffer(stroke_buf,argv[1]);

    g_snprintf(buf,20,"%s.%s",radical,stroke);
    char *pStr=g_strdup(buf);
    sqlite3_result_text(context,pStr,-1,g_free);
}

static void to_scalar_string_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==1);
    gunichar code= (sqlite3_value_type(argv[0])==SQLITE_INTEGER) ? sqlite3_value_int64(argv[0]): 0;
    char *pStr=unihanChar_to_scalar_string(code);
    sqlite3_result_text(context,pStr,-1,g_free);
}

static void zVariant_value_concat_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==2);
    char keyBuf[100];
    initString(keyBuf);
    long code=sqlite3_value_int64(argv[0]);
    GString *strBuf=g_string_new(NULL);
    g_string_printf(strBuf,"U+%lX",code);
    if (sqlite3_value_type(argv[1])==SQLITE_TEXT){
       sqlite_value_signed_text_buffer(keyBuf,argv[1]);
    }
    if (!isEmptyString(keyBuf)){
        g_string_append_printf(strBuf,":%s",keyBuf);
       
    }
    char *pStr=g_string_free(strBuf,FALSE);
    sqlite3_result_text(context,pStr,-1,g_free);
} 

typedef struct scalarFuncStru{
    const char* funcName;
    void (*func)(sqlite3_context *context, int argc, sqlite3_value **argv);
    int argc;
} ScalarFuncStru;


#define UNIHAN_SCALAR_FUNCS_COUNT 7
const ScalarFuncStru scalarFuncs[UNIHAN_SCALAR_FUNCS_COUNT]={
    {"ADOBE_RADICAL_STROKE_VALUE_CONCAT",adobeRadicalStroke_value_concat_Func,5},
    {"HANYU_PINLU_VALUE_CONCAT",hanYu_pinLu_value_concat_Func,2},
    {"IRG_SOURCE_VALUE_CONCAT",irg_source_value_concat_Func,2},
    {"KANGXI_VALUE_CONCAT",kangXi_value_concat_Func,3},
    {"RADICAL_STROKE_VALUE_CONCAT",radicalStroke_value_concat_Func,2},
    {"TO_SCALAR_STRING",to_scalar_string_Func,1},
    {"Z_VARIANT_VALUE_CONCAT",zVariant_value_concat_Func,2}
};


/*=========================================================================
 * Sqlite aggregation custom functions
 */

typedef struct {
    int rowCount;
    gunichar lastCode;
    GString *strBuf;
} ConcatStru;


static void semantic_value_concat_step_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==5);
    ConcatStru *cStru = (ConcatStru *) sqlite3_aggregate_context(context, sizeof(*cStru));

    if (cStru->rowCount==0){
	    cStru->strBuf=g_string_new(NULL);
    }
    gunichar code=(gunichar) sqlite3_value_int64(argv[0]);
    gboolean hasColon=FALSE;

    char fromDict_buf[20];
    initString(fromDict_buf);

    const char *fromDict=(sqlite3_value_type(argv[1])==SQLITE_TEXT) ? sqlite_value_signed_text_buffer(fromDict_buf,argv[1]): NULL;
    int T= (sqlite3_value_type(argv[2])==SQLITE_INTEGER) ? sqlite3_value_int(argv[2]): 0;
    int B= (sqlite3_value_type(argv[3])==SQLITE_INTEGER) ? sqlite3_value_int(argv[3]): 0;
    int Z= (sqlite3_value_type(argv[4])==SQLITE_INTEGER) ? sqlite3_value_int(argv[4]): 0;
    if (cStru->lastCode!=code){
	if (cStru->rowCount>0){
	    g_string_append(cStru->strBuf," ");
	}
	g_string_append_printf(cStru->strBuf,"U+%X",code);
    }
    if (fromDict){
	if (cStru->lastCode!=code){
	    g_string_append(cStru->strBuf,"<");
	}else{
	    g_string_append(cStru->strBuf,",");
	}
	g_string_append(cStru->strBuf,fromDict);
	if (T){
	    if (!hasColon){
		g_string_append(cStru->strBuf,":");
		hasColon=TRUE;
	    }
	    g_string_append(cStru->strBuf,"T");
	}
	if (B){
	    if (!hasColon){
		g_string_append(cStru->strBuf,":");
		hasColon=TRUE;
	    }
	    g_string_append(cStru->strBuf,"B");
	}
	if (Z){
	    if (!hasColon){
		g_string_append(cStru->strBuf,":");
		hasColon=TRUE;
	    }
	    g_string_append(cStru->strBuf,"Z");
	}
    }
    cStru->lastCode=code;
    cStru->rowCount++;
}

static void semantic_value_concat_finalized_Func(sqlite3_context *context){
    ConcatStru *cStru = (ConcatStru *) sqlite3_aggregate_context(context, sizeof(*cStru));

    if (cStru->rowCount>0){
	char *buf=g_string_free(cStru->strBuf,FALSE);
	sqlite3_result_text(context,buf,-1,g_free);
    }
}

/*=================================
 * Select generating functions.
 */
static char *unihan_generate_select_clause(UnihanField field,gboolean showScalarString){
    GString *strBuf=g_string_new(NULL);
    UnihanTable fromTable=unihanField_get_table(field);
    switch(field){
	case UNIHAN_FIELD_CODE:
	    if (showScalarString){
		g_string_printf(strBuf,"TO_SCALAR_STRING(%s) AS CodePoint",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_CODE]);
	    }else{
		g_string_printf(strBuf,"%s",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_CODE]);
	    }
	    break;
	case UNIHAN_FIELD_KCOMPATIBILITYVARIANT:
	case UNIHAN_FIELD_KSIMPLIFIEDVARIANT:
	case UNIHAN_FIELD_KTRADITIONALVARIANT:

	case UNIHAN_FIELD_VARIANT_CODE:
	    if (showScalarString){
		g_string_printf(strBuf,"TO_SCALAR_STRING(%s.%s) AS VariantCodePoint",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
	    }else{
		g_string_printf(strBuf,"%s.%s",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
	    }
	    break;
	case UNIHAN_FIELD_KIRG_HSOURCE:
	case UNIHAN_FIELD_KIRG_USOURCE:
	    g_string_printf(strBuf,"%s.%s",
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_MAPPING]);
	    break;
	case UNIHAN_FIELD_KIRG_GSOURCE:
	case UNIHAN_FIELD_KIRG_JSOURCE:
	case UNIHAN_FIELD_KIRG_KPSOURCE:
	case UNIHAN_FIELD_KIRG_KSOURCE:
	case UNIHAN_FIELD_KIRG_TSOURCE:
	case UNIHAN_FIELD_KIRG_VSOURCE:
	    g_string_printf(strBuf,"IRG_SOURCE_VALUE_CONCAT(%s.%s,%s.%s)",
		    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_MAPPING]);
	    break;
	case UNIHAN_FIELD_KIRGKANGXI:
	case UNIHAN_FIELD_KKANGXI:
	    g_string_printf(strBuf,"KANGXI_VALUE_CONCAT(%s, %s, %s)",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_PAGE],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_CHARNUM],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_VIRTUAL]);
	    break;
	case UNIHAN_FIELD_KHANYUPINLU:
	    g_string_printf(strBuf,"HANYU_PINLU_VALUE_CONCAT(%s, %s)",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN_FREQ]);
	    break;
	case UNIHAN_FIELD_KRSADOBE_JAPAN1_6:
	    g_string_printf(strBuf,"ADOBE_RADICAL_STROKE_VALUE_CONCAT(%s, %s, %s, %s, %s)",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_CV],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT]);
	    break;
	case UNIHAN_FIELD_KRSJAPANESE:
	case UNIHAN_FIELD_KRSKANGXI:
	case UNIHAN_FIELD_KRSKANWA:
	case UNIHAN_FIELD_KRSKOREAN:
	case UNIHAN_FIELD_KRSUNICODE:
	    g_string_printf(strBuf,"RADICAL_STROKE_VALUE_CONCAT(%s, %s)",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT]);
	    break;
	case UNIHAN_FIELD_KSEMANTICVARIANT:
	case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
	    g_string_printf(strBuf,"SEMANTIC_VARIANT_VALUE_CONCAT(%s.%s, %s, %s, %s, %s)",
		    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_FROM_DICT],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_SEMANTIC_T],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_SEMANTIC_B],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_SEMANTIC_Z]);
	    break;
	case UNIHAN_FIELD_KZVARIANT:
	    g_string_printf(strBuf,"Z_VARIANT_VALUE_CONCAT(%s.%s, %s)",
	    	    UNIHAN_TABLE_NAMES[fromTable],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ZVARIANT_SOURCE]);
	    break;

	default:
	    g_string_printf(strBuf,"%s.%s",UNIHAN_TABLE_NAMES[fromTable],UNIHAN_FIELD_NAMES[field]);
	    break;  
    }    
    return g_string_free(strBuf,FALSE);
}

/*=================================
 * FROM generating functions.
 */
static char *unihan_generate_from_clause(UnihanField givenField,UnihanField queryField){
    GString *strBuf=g_string_new(NULL);
    UnihanTable table,extraTable;
    gboolean first=TRUE;

    if (queryField!=UNIHAN_FIELD_CODE ){
	table=unihanField_get_table(queryField);
	g_string_append(strBuf,UNIHAN_TABLE_NAMES[table]);
	if (unihanField_is_IRG_Source(queryField)){
	    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[table],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[table],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME]);
	}else{
	    switch(queryField){
		case UNIHAN_FIELD_KSEMANTICVARIANT:
		case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		    extraTable=unihanField_get_extra_table(queryField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s ",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]
			    );
		    break;
                case UNIHAN_FIELD_KZVARIANT:
		    extraTable=unihanField_get_extra_table(queryField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
                    break;
		default:
		    break;
	    }
	}
	first=FALSE;
    }
    if (givenField!=UNIHAN_FIELD_CODE ){
	if (!first){
	    g_string_append_c(strBuf,',');
	}

	table=unihanField_get_table(givenField);
	g_string_append(strBuf,UNIHAN_TABLE_NAMES[table]);
	if (unihanField_is_IRG_Source(givenField)){
	    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[table],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_TABLE_NAMES[table],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE_MAPPING],
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME]);
	}else{
	    switch(givenField){
		case UNIHAN_FIELD_KSEMANTICVARIANT:
		case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		    extraTable=unihanField_get_extra_table(givenField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]
			    );
		    break;
		case UNIHAN_FIELD_KZVARIANT:
		    extraTable=unihanField_get_extra_table(givenField);
		    g_string_append_printf(strBuf," LEFT JOIN %s ON %s.code=%s.code AND %s.%s=%s.%s",
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_TABLE_NAMES[table],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			    UNIHAN_TABLE_NAMES[extraTable],
			    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
		    break;
		default:
		    break;
	    }
	}
    }
    g_string_append_c(strBuf,' ');
    return g_string_free(strBuf,FALSE);
}

/*=================================
 * WHERE generating functions.
 */

static char *unihan_append_radical_stroke_where_clause(GString *strBuf, UnihanField field, const char *value){
    int i=0,len=strlen(value);
    g_string_append_printf(strBuf,"%s=\"",
	    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX]);

    while (i<len && value[i]!='.'){
	g_string_append_c(strBuf,value[i]);
	i++;
    }

    if (value[i]=='.'){
	/* additional strokes count   */
	g_string_append_printf(strBuf,"\" AND %s=\"",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	return NULL;
    }
    while (i<len){
	g_string_append_c(strBuf,value[i]);
	i++;
    }
    g_string_append(strBuf,"\" ") ;

    return strBuf->str;
}

static char *unihan_append_adobe_japan1_6_where_clause(GString *strBuf ,const char *value){
    int i=0,len=strlen(value);
    if (value[i]=='C'){
	g_string_append_printf(strBuf," %s=\"C\"",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_CV]);
	i++;
    }
    if (value[i]=='V'){
	g_string_append_printf(strBuf," %s=\"V\"",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_CV]);
	i++;
    }
    if (value[i]=='+'){
	/* CID field */
	g_string_append_printf(strBuf," AND %s=\"",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	g_string_free(strBuf,TRUE);
	return NULL;
    }

    while (i<len && value[i]!='+'){
	g_string_append_c(strBuf,value[i]);
	i++;
    }
    if (value[i]=='+'){
	/* Radical field  */
	g_string_append_printf(strBuf,"\" AND %s=\"",
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_RADICAL_INDEX]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	g_string_free(strBuf,TRUE);
	exit(-1);
	return NULL;
    }

    while (i<len && value[i]!='.'){
	g_string_append_c(strBuf,value[i]);
	i++;
    }

    if (value[i]=='.'){
	/* Radical strokes count   */
	g_string_append_printf(strBuf,"\" AND %s=\"",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	g_string_free(strBuf,TRUE);
	return NULL;
    }

    while (i<len && value[i]!='.'){
	g_string_append_c(strBuf,value[i]);
	i++;
    }

    if (value[i]=='.'){
	/* additional strokes count   */
	g_string_append_printf(strBuf,"\" AND %s=\"",UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT]);
	i++;
    }else{
	verboseMsg_print(VERBOSE_MSG_ERROR,"Invalid format!");
	return NULL;
    }
    while (i<len){
	g_string_append_c(strBuf,value[i]);
	i++;
    }

    g_string_append_printf(strBuf,"\" ");
    return strBuf->str;
}

static void unihan_append_IRG_sources_query_where_clause(GString *strBuf, UnihanIRG_Source source){
    g_string_append_printf(strBuf," AND %s.%s LIKE ",
	    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE],
	    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME]);
    switch(source){
	case UNIHAN_IRG_SOURCE_G:
	    g_string_append(strBuf,"'G%%'");
	    break;
	case UNIHAN_IRG_SOURCE_H:
	    g_string_append(strBuf,"'H'");
	    break;
	case UNIHAN_IRG_SOURCE_J:
	    g_string_append(strBuf,"'J%%'");
	    break;
	case UNIHAN_IRG_SOURCE_KP:
	    g_string_append(strBuf,"'KP_'");
	    break;
	case UNIHAN_IRG_SOURCE_K:
	    g_string_append(strBuf,"'K_'");
	    break;
	case UNIHAN_IRG_SOURCE_T:
	    g_string_append(strBuf,"'T%%'");
	    break;
	case UNIHAN_IRG_SOURCE_U:
	    g_string_append(strBuf,"'U'");
	    break;
	case UNIHAN_IRG_SOURCE_V:
	    g_string_append(strBuf,"'V_'");
	    break;
	default:
	    break;
    }
}

static void unihan_append_kangXi_where_clause(GString *strBuf, UnihanField field,const char* composite_value){
    UnihanTable table=unihanField_get_table(field);
    GArray *gArray=kangXiRec_parse(composite_value);
    int i=0;
    KangXiRec *rec=NULL;
    g_assert(table>=0);

    if (gArray->len>0){
	rec=&g_array_index(gArray,KangXiRec,i);
	g_string_append_printf(strBuf," %s.%s=\"%s\"",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_PAGE],
		rec->page);
	g_string_append_printf(strBuf," AND %s.%s=\"%s\"",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_CHARNUM],
		rec->charNum);
	g_string_append_printf(strBuf," AND %s.%s=%d",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_KANGXI_VIRTUAL],
		rec->virtual);
    }
    g_array_free(gArray,TRUE);
}

static void unihan_append_pinyinFreq_where_clause(GString *strBuf, UnihanField field,const char* composite_value){
    UnihanTable table=unihanField_get_table(field);
    GArray *gArray=pinyinFreqRec_parse(composite_value);
    int i=0;
    PinyinFreqRec *rec=NULL;
    g_assert(table>=0);

    if (gArray->len>0){
	rec=&g_array_index(gArray,PinyinFreqRec,i);
	g_string_append_printf(strBuf," %s.%s=\"%s\"",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN],
		rec->pinyin);
	g_string_append_printf(strBuf," AND %s.%s=%d",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_PINYIN_FREQ],
		rec->freq);
    }
    g_array_free(gArray,TRUE);
}

static void unihan_append_semantic_where_clause(GString *strBuf, UnihanField field, const char* composite_value){
    GArray *gArray=semanticDictRec_parse(composite_value);
    int i=0;
    SemanticDictRec *rec=NULL;
    UnihanTable table=unihanField_get_table(field);
    g_assert(table>=0);

    if (gArray->len>0){
	rec=&g_array_index(gArray,SemanticDictRec,i);
	g_string_append_printf(strBuf," %s.%s=%d",
		UNIHAN_TABLE_NAMES[table],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
		rec->variantCode);
	if (!isEmptyString(rec->fromDict)){
	    g_string_append_printf(strBuf," AND %s=\"%s\"",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_FROM_DICT],
		    rec->fromDict);
	    g_string_append_printf(strBuf," AND semanticT=%d AND semanticB=%d AND semanticZ=%d",
		    rec->T,rec->B,rec->Z);
	}
    }
    g_array_free(gArray,TRUE);
}

static void unihan_append_zvariant_where_clause(GString *strBuf, UnihanField field, const char* composite_value){
    char **subFieldArray=g_strsplit(composite_value,":",-1);
    g_assert(subFieldArray[0]);
    gunichar variantCode=unihanChar_parse(subFieldArray[0]);
    g_string_append_printf(strBuf," %s.%s=%d",
	    UNIHAN_TABLE_NAMES[UNIHAN_TABLE_KZVARIANT],
	    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
	    variantCode);
    if (!isEmptyString(subFieldArray[1])){
	g_string_append_printf(strBuf," AND %s=\"%s\"",
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_ZVARIANT_SOURCE],
		subFieldArray[1]);
    }
    g_strfreev(subFieldArray);
}

static void unihan_append_where_clause_join_table(GString *strBuf, 
	UnihanField givenField, UnihanField queryField){

    UnihanTable givenTable,queryTable;

    if (givenField==UNIHAN_FIELD_CODE ){
	return;
    }else if (queryField==UNIHAN_FIELD_CODE){
	return;
    }else{
	queryTable=unihanField_get_table(queryField);
	givenTable=unihanField_get_table(givenField);
	g_string_append_printf(strBuf, " AND %s.code=%s.code",
		UNIHAN_TABLE_NAMES[queryTable],
		UNIHAN_TABLE_NAMES[givenTable]);
    }
}

static char *unihan_generate_where_clause(UnihanField givenField, const char *value, 
	UnihanTable fromTable,
	UnihanField queryField,
       	gboolean likeMode){
    GString *strBuf=g_string_new(NULL);
    UnihanIRG_SourceRec *rec=NULL;
    if (unihanField_is_IRG_Source(givenField)){
	rec=unihanIRG_SourceRec_parse(givenField,value);
    }
    char *relStr=(likeMode)? "LIKE": "=";

    if (rec!=NULL){
	g_string_append_printf(strBuf,"%s.%s=\"%s\"",
		UNIHAN_TABLE_NAMES[UNIHAN_TABLE_IRG_SOURCE],
		UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME],
		UNIHAN_IRG_SOURCES[rec->sourceId].name);
	if (!unihanIRG_Source_has_no_mapping(rec->sourceId)){
	    g_string_append_printf(strBuf," AND %s %s \"%s\"",
		    UNIHAN_FIELD_NAMES[UNIHAN_FIELD_IRG_SOURCE_MAPPING],
		    relStr,
		    rec->sourceMapping);
	}
	unihanIRG_SourceRec_free(rec);
    }else{
	switch(givenField){
	    case UNIHAN_FIELD_KIRGKANGXI:
	    case UNIHAN_FIELD_KKANGXI:
		unihan_append_kangXi_where_clause(strBuf,givenField,value);
		break;
	    case UNIHAN_FIELD_KHANYUPINLU:
		unihan_append_pinyinFreq_where_clause(strBuf,givenField,value);
		break;
	    case UNIHAN_FIELD_KRSADOBE_JAPAN1_6:
		unihan_append_adobe_japan1_6_where_clause(strBuf,value);
		break;
	    case UNIHAN_FIELD_KRSJAPANESE:
	    case UNIHAN_FIELD_KRSKANGXI:
	    case UNIHAN_FIELD_KRSKANWA:
	    case UNIHAN_FIELD_KRSKOREAN:
	    case UNIHAN_FIELD_KRSUNICODE:
		unihan_append_radical_stroke_where_clause(strBuf, givenField, value);
		break;
	    case UNIHAN_FIELD_KSEMANTICVARIANT:
	    case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		unihan_append_semantic_where_clause(strBuf, givenField, value);
		break;
	    case UNIHAN_FIELD_KCOMPATIBILITYVARIANT:
	    case UNIHAN_FIELD_KSIMPLIFIEDVARIANT:
	    case UNIHAN_FIELD_KTRADITIONALVARIANT:
		g_string_append_printf(strBuf,"%s.%s=\"%s\"",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE],
			value);
		break;
	    case UNIHAN_FIELD_KZVARIANT:
		unihan_append_zvariant_where_clause(strBuf, givenField, value);
		break;

	    default:
		g_string_append_printf(strBuf,"%s.%s %s \"%s\"",
			UNIHAN_TABLE_NAMES[fromTable],
			UNIHAN_FIELD_NAMES[givenField],
			relStr,value);
		break;
	}
    }

    unihan_append_where_clause_join_table(strBuf, givenField, queryField);

    /* Below is needed if queryField is pseudo */
    UnihanIRG_Source source=unihanField_get_IRG_source(queryField);
    if (source>=0){
	unihan_append_IRG_sources_query_where_clause(strBuf, source);
    }else{
//        switch(queryField){
//            case UNIHAN_FIELD_KRSJAPANESE:
//            case UNIHAN_FIELD_KRSKANGXI:
//            case UNIHAN_FIELD_KRSKANWA:
//            case UNIHAN_FIELD_KRSKOREAN:
//            case UNIHAN_FIELD_KRSUNICODE:
//                g_string_append(strBuf," AND ");
//                unihan_append_radical_stroke_query_where_clause(strBuf, queryField);
//                break;
//            case UNIHAN_FIELD_KSEMANTICVARIANT:
//            case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
//                g_string_append_printf(strBuf," AND %s.code=%s.code",
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_VARIANT],
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_SEMANTIC_DICT]);
//                g_string_append_printf(strBuf," AND %s.variantCode=%s.variantCode",
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_VARIANT],
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_SEMANTIC_DICT]);
//            case UNIHAN_FIELD_KCOMPATIBILITYVARIANT:
//            case UNIHAN_FIELD_KSIMPLIFIEDVARIANT:
//            case UNIHAN_FIELD_KTRADITIONALVARIANT:
//            case UNIHAN_FIELD_KZVARIANT:
//                g_string_append_printf(strBuf," AND %s.%s=\"%s\"",
//                        UNIHAN_TABLE_NAMES[UNIHAN_TABLE_VARIANT],
//                        UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_TYPE],
//                        UNIHAN_FIELD_NAMES[queryField]);
//                break;
//            default:
//                break;
//        }
    }

    return g_string_free(strBuf,FALSE);
}

SQL_Result *unihan_find_all_matched(UnihanField givenField, char *givenValue, 
	UnihanField queryField,	char **errMsg_ptr, int *execResult_ptr, 
	gboolean likeMode,gboolean showScalarString){
    char *selectStr=NULL;
    char *fromStr=NULL;
    char *whereStr=NULL;
    int i;
    GString *strBuf=g_string_new(NULL);

    UnihanTable table;
    UnihanTable *tableArray=(givenField!=UNIHAN_FIELD_CODE) ? 
	    unihanField_get_all_tables(givenField): unihanField_get_all_tables(queryField);
    for(i=0;tableArray[i]>=0;i++){
	if (i>0){
	    g_string_append(strBuf," UNION ");
	}
	selectStr=unihan_generate_select_clause(queryField,showScalarString);
	fromStr=unihan_generate_from_clause(givenField,queryField);
	whereStr=unihan_generate_where_clause(givenField,givenValue,tableArray[i],queryField,likeMode);

	g_string_append_printf(strBuf,"SELECT %s FROM %s WHERE %s",selectStr,fromStr, whereStr);

	/* Group by */
	switch(queryField){
	    case UNIHAN_FIELD_KSEMANTICVARIANT:
	    case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		table=unihanField_get_table(queryField);
		g_string_append_printf(strBuf," GROUP BY %s.%s",
			UNIHAN_TABLE_NAMES[table],
			UNIHAN_FIELD_NAMES[UNIHAN_FIELD_VARIANT_CODE]);
		break;
	    default:
		break;

	}
    }

    g_string_append(strBuf,";");
    verboseMsg_print(VERBOSE_MSG_INFO1,"%s\n",strBuf->str);
    
    SQL_Result *sResult=unihanSql_get_sql_result(strBuf->str, errMsg_ptr, execResult_ptr);
    g_free(selectStr);
    g_free(fromStr);
    g_free(whereStr);
    g_string_free(strBuf,TRUE);
    g_free(tableArray);
    return sResult;
}

char* unihan_find_first_matched(UnihanField givenField, char* givenValue, 
	UnihanField queryField,gboolean likeMode,gboolean showScalarString){
    int nrow, ncolumn;
    char **results;
    char *errmsg=NULL;

    int ret=unihan_find_all_matched(givenField,givenValue, queryField, &results,
	    &nrow, &ncolumn, &errmsg,likeMode,showScalarString);
    if (ret){
	verboseMsg_print(VERBOSE_MSG_ERROR,"Database error: %s\n", errmsg);
	return NULL;
    }
    if (nrow<=0){
	return NULL;
    }
    char *result=g_strdup(results[ncolumn]);
    sqlite3_free_table(results);
    return result;
}


int unihan_count_matched_record(UnihanTable table, char** valueArray){
    int i;
    if (table<0){
	return FALSE;
    }
    UnihanField* fields=unihanTable_get_fields(table);
    GString *strBuf=g_string_new("SELECT * FROM");
    g_string_append_printf(strBuf," %s WHERE", UNIHAN_TABLE_NAMES[table]);

    for(i=0;fields[i]>=0;i++){
	if (valueArray[i]==NULL){
	    g_error("Unihan.c:unihan_count_matched_record(): Table %s: valueArray is shorter than number of fields!\n",
		    UNIHAN_TABLE_NAMES[table]);
	}
	if (i>0){
	    g_string_append(strBuf," AND");
	}
	if (unihanField_is_integer(fields[i])){
	    g_string_append_printf(strBuf," %s=%s",UNIHAN_FIELD_NAMES[fields[i]],valueArray[i]);
	}else{
	    g_string_append_printf(strBuf," %s=\"%s\"",UNIHAN_FIELD_NAMES[fields[i]],valueArray[i]);
	}
    }
    g_string_append(strBuf,";");
    verboseMsg_print(VERBOSE_MSG_INFO2,"unihan_count_matched_record(): %s\n",strBuf->str);
    int ret=unihanSql_count_matches(strBuf->str);
    verboseMsg_print(VERBOSE_MSG_INFO2,"unihan_count_matched_record(): %d records founds\n",ret);
    g_string_free(strBuf,TRUE);
    g_free(fields);
    return ret;
}

static int latest_db_result(int result,int newResult){
    if ((result<=0) && (newResult>0)){
	/* newResult overrides result, indicates there is database error */
	result=newResult;
    }else if ((result==0) && (newResult<0)){
	/* newResult overrides result, indicates at least one insert instruction is skipped. */
	result=newResult;
    }else{
	/* no need to change result */
    }
    return result;
}

static int insert_semanticVariant(gunichar code, UnihanField field, const char *composite_value){
    GStringChunk *sChunk=NULL;
    GPtrArray *pArray=g_ptr_array_new();

    GArray *gArray=semanticDictRec_parse(composite_value);
    SemanticDictRec *sRec=NULL;
    int i;
    char codeBuf[20], variantBuf[20];
    const char oneStr[]="1", zeroStr[]="0";
    int result=0,newResult=0;
    UnihanTable table=unihanField_get_table(field),
		extraTable=unihanField_get_extra_table(field);



    g_snprintf(codeBuf,20,"%d",code);
    for(i=0;i<gArray->len;i++){
	sRec=&g_array_index(gArray,SemanticDictRec,i);
	sChunk=g_string_chunk_new(1000);

	g_snprintf(variantBuf,20,"%d",sRec->variantCode);
	/* Insert to k*SementicVariantTable */
	g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,codeBuf));
	g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,variantBuf));

	newResult=unihan_insert_no_duplicate(table,(char **) pArray->pdata);
	result=latest_db_result(result,newResult);
	/* We cannot use g_string_chunk_clear without glib>=2.14 */
	g_string_chunk_free(sChunk);
	g_ptr_array_set_size(pArray,0);

	if (isEmptyString(sRec->fromDict)){
	    continue;
	}

	/* Insert to SemanticDictTable */
	sChunk=g_string_chunk_new(1000);

	g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,codeBuf));
	g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,variantBuf));
	g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,sRec->fromDict));
	if (sRec->T){
	    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,oneStr));
	}else{
	    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,zeroStr));
	}

	if (sRec->B){
	    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,oneStr));
	}else{
	    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,zeroStr));
	}

	if (sRec->Z){
	    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,oneStr));
	}else{
	    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,zeroStr));
	}

	newResult=unihan_insert_no_duplicate(extraTable,(char **) pArray->pdata);
	result=latest_db_result(result,newResult);
	/* We cannot use g_string_chunk_clear without glib>=2.14 */
	g_string_chunk_free(sChunk);
	g_ptr_array_set_size(pArray,0);

    }

    g_ptr_array_free(pArray,TRUE);
    g_array_free(gArray,TRUE);
    return result;
}

static int insert_zVariant(gunichar code, UnihanField field, const char *composite_value){
    char **subFieldArray=g_strsplit(composite_value,":",-1);
    g_assert(subFieldArray[0]);
    gunichar variantCode=unihanChar_parse(subFieldArray[0]);
    GStringChunk *sChunk=g_string_chunk_new(1000);
    GPtrArray *pArray=g_ptr_array_new();
    char codeBuf[20], variantBuf[20];

    int result=0,newResult=0;
    UnihanTable table=unihanField_get_table(field),
		extraTable=unihanField_get_extra_table(field);

    g_snprintf(codeBuf,20,"%d",code);
    g_snprintf(variantBuf,20,"%d",variantCode);

    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,codeBuf));
    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,variantBuf));
    newResult=unihan_insert_no_duplicate(table,(char **) pArray->pdata);
    result=latest_db_result(result,newResult);
    /* We cannot use g_string_chunk_clear without glib>=2.14 */
    g_string_chunk_free(sChunk);
    g_ptr_array_set_size(pArray,0);

    if (!isEmptyString(subFieldArray[1])){
	sChunk=g_string_chunk_new(1000);
	g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,codeBuf));
	g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,variantBuf));
	g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,subFieldArray[1]));

	newResult=unihan_insert_no_duplicate(extraTable,(char **) pArray->pdata);
	result=latest_db_result(result,newResult);
	/* We cannot use g_string_chunk_clear without glib>=2.14 */
	g_string_chunk_free(sChunk);

    }
    g_ptr_array_free(pArray,TRUE);
    g_strfreev(subFieldArray);
    return result;
}

int unihan_insert(UnihanTable table, char** valueArray){
    int i;
    char *errmsg=NULL;
    if (table<0){
	return FALSE;
    }
    UnihanField* fields=unihanTable_get_fields(table);
    GString *strBuf=g_string_new("INSERT INTO");
    g_string_append_printf(strBuf," %s VALUES (", UNIHAN_TABLE_NAMES[table]);

    for(i=0;fields[i]>=0;i++){
	if (valueArray[i]==NULL){
	    g_error("Unihan.c:unihan_insert(): valueArray is shorter than number of fields!\n");
	}
	if (i>0){
	    g_string_append_c(strBuf,',');
	}
	if (unihanField_is_integer(fields[i])){
	    g_string_append_printf(strBuf," %s",valueArray[i]);
	}else{
	    g_string_append_printf(strBuf," \"%s\"",valueArray[i]);
	}
    }
    g_string_append(strBuf,");");
    verboseMsg_print(VERBOSE_MSG_INFO1,"%s\n",strBuf->str);
    int ret=unihanSql_exec(strBuf->str,NULL,NULL,&errmsg);
    if (ret) {
	verboseMsg_print(VERBOSE_MSG_ERROR, "unihan_insert(): Cannot %s, errmsg:%s\n", errmsg);
    }
    g_string_free(strBuf,TRUE);
    g_free(fields);
    return ret;
}


int unihan_insert_value(gunichar code, UnihanField field, const char *value){
    char buf[20];
    GStringChunk *sChunk=g_string_chunk_new(1000);
    UnihanTable table=unihanField_get_table(field);
    GPtrArray *pArray=g_ptr_array_new();
    char **subFieldArray=NULL;
    gunichar variantCode;
    static gunichar lastCode=0;
    int result=0,newResult=0;
    static int freqRank=1;
    

    UnihanIRG_SourceRec *rec=NULL;
    if (unihanField_is_IRG_Source(field)){
	rec=unihanIRG_SourceRec_parse(field,value);
    }

    if (rec!=NULL){
	const UnihanIRG_SourceData *srcData=unihanIRG_SourceData_get(rec->sourceId);
	if (srcData==NULL){
	    g_error("Unknown source!");
	}
	g_snprintf(buf,20,"%d",code);

	if (!unihanIRG_Source_has_no_mapping(rec->sourceId)){
	    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,buf));
	    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,srcData->name));
	    g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,rec->sourceMapping));
	    newResult=unihan_insert_no_duplicate(UNIHAN_TABLE_IRG_SOURCE_MAPPING,(char **) pArray->pdata);
	    result=latest_db_result(result,newResult);
	    /* We cannot use g_string_chunk_clear without glib>=2.14 */
	    g_string_chunk_free(sChunk);
	    sChunk=g_string_chunk_new(1000);
	    g_ptr_array_set_size(pArray,0);
	}

	g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,buf));
	g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,srcData->name));
	unihanIRG_SourceRec_free(rec);
    }else if (unihanField_array_index(field,UNIHAN_KVARIANT_FIELDS)>=0){
	switch(field){
	    case UNIHAN_FIELD_KSEMANTICVARIANT:
	    case UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT:
		return insert_semanticVariant(code, field, value);
	    case UNIHAN_FIELD_KZVARIANT:
		return insert_zVariant(code, field, value);
	    default:
		variantCode=unihanChar_parse(value);
		g_snprintf(buf,20,"%d",code);
		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,buf));
		g_snprintf(buf,20,"%d",variantCode);
		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,buf));
		break;
	}
    }else  if (unihanField_array_index(field,UNIHAN_KRS_FIELDS)>=0){
	switch(field){
	    case UNIHAN_FIELD_KRSADOBE_JAPAN1_6:
		subFieldArray=g_strsplit_set(value,".+",-1);
		g_snprintf(buf,20,"%d",code);

		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,buf));
		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,subFieldArray[0]));
		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,subFieldArray[1]));
		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,subFieldArray[2]));
		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,subFieldArray[3]));
		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,subFieldArray[4]));

		break;
	    default:
		subFieldArray=g_strsplit(value,".",-1);
		g_snprintf(buf,20,"%d",code);
		g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,buf));
		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,subFieldArray[0]));
		g_ptr_array_add(pArray,g_string_chunk_insert (sChunk,subFieldArray[1]));
		break;
	}
	g_assert(subFieldArray);
	g_free(subFieldArray);
    }else if (field==UNIHAN_FIELD_KMANDARIN){
	if (lastCode!=code){
	    freqRank=1;
	}
	g_snprintf(buf,20,"%d",code);
	g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,buf));
	g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,value));
	g_snprintf(buf,20,"%d",freqRank);
	g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,buf));
	freqRank++;
    }else if (field==UNIHAN_FIELD_KHANYUPINLU){
	g_snprintf(buf,20,"%d",code);
	g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,buf));
	GArray *pfArray=pinyinFreqRec_parse(value);
	if (pfArray->len>0){
	    PinyinFreqRec *rec=&g_array_index(pfArray,PinyinFreqRec,0);
	    g_ptr_array_add(pArray, g_string_chunk_insert (sChunk,rec->pinyin));
	    g_snprintf(buf,20,"%d",rec->freq);
	    g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,buf));
	}
	g_array_free(pfArray,TRUE);
    }else if (field==UNIHAN_FIELD_KIRGKANGXI || field==UNIHAN_FIELD_KKANGXI){
	g_snprintf(buf,20,"%d",code);
	g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,buf));
	GArray *kArray=kangXiRec_parse(value);
	if (kArray->len>0){
	    KangXiRec *rec=&g_array_index(kArray,KangXiRec,0);
	    g_ptr_array_add(pArray, g_string_chunk_insert (sChunk,rec->page));
	    g_ptr_array_add(pArray, g_string_chunk_insert (sChunk,rec->charNum));
	    g_snprintf(buf,20,"%d",(rec->virtual)? 1:0);
	    g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,buf));
	}
	g_array_free(kArray,TRUE);

    }else{
	g_snprintf(buf,20,"%d",code);
	g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,buf));
	g_ptr_array_add(pArray,	g_string_chunk_insert (sChunk,value));
    }
    newResult=unihan_insert_no_duplicate(table,(char **) pArray->pdata);
    result=latest_db_result(result,newResult);
    lastCode=code;
    g_ptr_array_free(pArray,TRUE);
    g_string_chunk_free(sChunk);
    return result;
}

int unihan_insert_no_duplicate(UnihanTable table, char** valueArray){
    if (unihan_count_matched_record(table,valueArray)>0){
	if (table==UNIHAN_TABLE_KSEMANTICVARIANT || table == UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT){
	    verboseMsg_print(VERBOSE_MSG_WARNING,"code %s is already inserted in table %s, no need to insert again.\n",
		    valueArray[0],UNIHAN_TABLE_NAMES[table]);
	}else{
	    verboseMsg_print(VERBOSE_MSG_WARNING,"Record duplicate in table %s on code=%s, skip!\n",
		    UNIHAN_TABLE_NAMES[table],valueArray[0]);
	}
	return -1;
    }
    int ret=unihan_insert(table,valueArray);
    if (ret>0){
	return ret;
    }
    return 0;
}

/*=================================
 * SQL wrapper functions.
 */

int unihanSql_exec(char *sqlClause, UnihanCallback callback, 
	void *callbackOption,  char **errmsg){
    return sqlite3_exec(unihanDb, sqlClause, callback, callbackOption, errmsg);
}

int unihanSql_count_matches(const char * sqlClause){
    char *zErrMsg = NULL;
    int ret=sqlite_count_matches(unihanDb,sqlClause,&zErrMsg);
    if (ret<0){
	verboseMsg_print(VERBOSE_MSG_ERROR, "Database error: %s\n", sqlite3_errmsg(unihanDb));
    }
    return ret;
}

SQL_Result *unihanSql_get_sql_result(const char *sqlClause, char **errMsg_ptr, int *execResult_ptr){
    return sqlite_get_sql_result(unihanDb, sqlClause, errMsg_ptr, execResult_ptr);
}


