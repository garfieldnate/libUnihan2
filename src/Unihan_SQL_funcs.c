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
    "kCheungBauer",
    "kCheungBauerIndex",
    "kCihaiT",
    "kCNS1986",
    "kCNS1992",
    "kCompatibilityVariant",
    "kCowles",
    "kDaeJaweon",
    "kDefinition",
    "kEACC",
    "kFenn",
    "kFennIndex",
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

    "IRG_source_short_name",
    
    "IRG_source_mapping",

    "variant_type",
    "variant_code",

    "from_dict",
    "semantic_T",
    "semantic_B",
    "semantic_Z",

    "radical_index",
    "additional_stroke_count",

    "adobeCID_CV",
    "adobeCID",
    "adobeCID_radicalStrokeCount",

    "KangXi_page",
    "KangXi_charNum",
    "KangXi_virtual",

    "freq_rank",

    "pinYin",
    "pinyin_freq",

    "zVariant_source",

    "zhuYin",
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
    "kFennTable",
    "kFennIndexTable",
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
    UNIHAN_FIELD_kACCOUNTINGNUMERIC,
    UNIHAN_FIELD_kCOMPATIBILITYVARIANT,
    UNIHAN_FIELD_kFREQUENCY,
    UNIHAN_FIELD_kGRADELEVEL,
    UNIHAN_FIELD_kOTHERNUMERIC,
    UNIHAN_FIELD_kPRIMARYNUMERIC,
    UNIHAN_FIELD_kSIMPLIFIEDVARIANT,

    UNIHAN_FIELD_kTOTALSTROKES,
    UNIHAN_FIELD_kTRADITIONALVARIANT,

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
    UNIHAN_FIELD_kIRG_GSOURCE,
    UNIHAN_FIELD_kIRG_HSOURCE,
    UNIHAN_FIELD_kIRG_JSOURCE,
    UNIHAN_FIELD_kIRG_KPSOURCE,
    UNIHAN_FIELD_kIRG_KSOURCE,
    UNIHAN_FIELD_kIRG_TSOURCE,
    UNIHAN_FIELD_kIRG_USOURCE,
    UNIHAN_FIELD_kIRG_VSOURCE,
    UNIHAN_INVALID_FIELD
};

const UnihanField UNIHAN_KRS_FIELDS[]={
    UNIHAN_FIELD_kRSADOBE_JAPAN1_6,
    UNIHAN_FIELD_kRSJAPANESE,
    UNIHAN_FIELD_kRSKANGXI,
    UNIHAN_FIELD_kRSKANWA,
    UNIHAN_FIELD_kRSKOREAN,
    UNIHAN_FIELD_kRSUNICODE,
    UNIHAN_INVALID_FIELD
};

const UnihanField UNIHAN_KVARIANT_FIELDS[]={
    UNIHAN_FIELD_kCOMPATIBILITYVARIANT,
    UNIHAN_FIELD_kSEMANTICVARIANT,
    UNIHAN_FIELD_kSIMPLIFIEDVARIANT,
    UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, 
    UNIHAN_FIELD_kTRADITIONALVARIANT,
    UNIHAN_FIELD_kZVARIANT,
    UNIHAN_INVALID_FIELD
};


const UnihanField UNIHAN_UCS4_FIELDS[]={
    UNIHAN_FIELD_CODE,
    UNIHAN_FIELD_kCOMPATIBILITYVARIANT,
    UNIHAN_FIELD_kSEMANTICVARIANT,
    UNIHAN_FIELD_kSIMPLIFIEDVARIANT,
    UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, 
    UNIHAN_FIELD_kTRADITIONALVARIANT,
    UNIHAN_FIELD_kZVARIANT,
    UNIHAN_FIELD_VARIANT_CODE,
    UNIHAN_INVALID_FIELD
};

const UnihanField UNIHAN_MANDARIN_FIELDS[]={
    UNIHAN_FIELD_kMANDARIN,
    UNIHAN_FIELD_PINYIN,
    UNIHAN_FIELD_ZHUYIN,
    UNIHAN_INVALID_FIELD
};

const UnihanField UNIHAN_CASE_NO_CHANGE_FIELDS[]={
    UNIHAN_FIELD_UTF8,
    UNIHAN_FIELD_kCHEUNGBAUER,
    UNIHAN_FIELD_kCHEUNGBAUERINDEX,
    UNIHAN_FIELD_kCIHAIT,
    UNIHAN_FIELD_kCOWLES,
    UNIHAN_FIELD_kDAEJAWEON,
    UNIHAN_FIELD_kDEFINITION,
    UNIHAN_FIELD_kFENNINDEX,
    UNIHAN_FIELD_kFOURCORNERCODE,
    UNIHAN_FIELD_kHANYU,
    UNIHAN_FIELD_kIICORE,
    UNIHAN_FIELD_kIRGDAIKANWAZITEN,
    UNIHAN_FIELD_kIRGKANGXI,
    UNIHAN_FIELD_kJIS0213,
    UNIHAN_FIELD_kJIS0,
    UNIHAN_FIELD_kJIS1,
    UNIHAN_FIELD_kKANGXI,
    UNIHAN_FIELD_kKSC0,
    UNIHAN_FIELD_kKSC1,
    UNIHAN_FIELD_kLAU,
    UNIHAN_FIELD_kMAINLANDTELEGRAPH,
    UNIHAN_FIELD_kMOROHASHI,
    UNIHAN_FIELD_kNELSON,
    UNIHAN_FIELD_kPSEUDOGB1,
    UNIHAN_FIELD_kRSJAPANESE,
    UNIHAN_FIELD_kRSKANGXI,
    UNIHAN_FIELD_kRSKANWA,
    UNIHAN_FIELD_kRSKOREAN,
    UNIHAN_FIELD_kRSUNICODE,
    UNIHAN_FIELD_kSBGY,
    UNIHAN_FIELD_kSEMANTICVARIANT,
    UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT,
    UNIHAN_FIELD_kTAIWANTELEGRAPH,
    UNIHAN_FIELD_kTANG,
    UNIHAN_FIELD_kVIETNAMESE,
    UNIHAN_FIELD_kXEROX,

    UNIHAN_INVALID_FIELD
};


const UnihanField UNIHAN_LOWERCASE_FIELDS[]={
    UNIHAN_FIELD_kCANTONESE,
    UNIHAN_FIELD_kHANYUPINLU,
    UNIHAN_FIELD_kGSR,
    UNIHAN_FIELD_kMATTHEWS,
    UNIHAN_FIELD_kMEYERWEMPE,
    UNIHAN_FIELD_kXHC1983,
    UNIHAN_INVALID_FIELD
};

/**
 * Fields that are functional dependent to code.
 *
 * 
 */
const UnihanField UNIHAN_SINGLETON_FIELDS[]={
    UNIHAN_FIELD_CODE,
    UNIHAN_FIELD_kACCOUNTINGNUMERIC,
    UNIHAN_FIELD_kBIGFIVE,
    UNIHAN_FIELD_kCCCII,
    UNIHAN_FIELD_kCHEUNGBAUER,
    UNIHAN_FIELD_kCNS1986,
    UNIHAN_FIELD_kCNS1992,
    UNIHAN_FIELD_kDEFINITION,
    UNIHAN_FIELD_kFOURCORNERCODE,
    UNIHAN_FIELD_kFREQUENCY,
    UNIHAN_FIELD_kGB0,
    UNIHAN_FIELD_kGB1,
    UNIHAN_FIELD_kGB3,
    UNIHAN_FIELD_kGB5,
    UNIHAN_FIELD_kGB7,
    UNIHAN_FIELD_kGB8,
    UNIHAN_FIELD_kGRADELEVEL,
    UNIHAN_FIELD_kHKSCS,
    UNIHAN_FIELD_kHKGLYPH,
    UNIHAN_FIELD_kIICORE,
    UNIHAN_FIELD_kIBMJAPAN,
    UNIHAN_FIELD_kJIS0213,
    UNIHAN_FIELD_kJIS0,	
    UNIHAN_FIELD_kJIS1,	
    UNIHAN_FIELD_kKPS0,
    UNIHAN_FIELD_kKPS1,
    UNIHAN_FIELD_kKSC0,
    UNIHAN_FIELD_kKSC1,
    UNIHAN_FIELD_kMAINLANDTELEGRAPH,
    UNIHAN_FIELD_kOTHERNUMERIC,
    UNIHAN_FIELD_kPRIMARYNUMERIC,
    UNIHAN_FIELD_kTAIWANTELEGRAPH,
    UNIHAN_FIELD_kTOTALSTROKES,
    UNIHAN_FIELD_kXEROX,
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
 * Parse pinYin freq (PinLu)
 */

typedef enum{
    UNIHAN_PINYIN_FREQ_STATE_PINYIN,
    UNIHAN_PINYIN_FREQ_STATE_FREQ,
    UNIHAN_PINYIN_FREQ_STATE_SEPARATER
} UnihanPinYinFreqState;


#define STRING_BUFFER_PINYIN_SIZE 8
#define STRING_BUFFER_FREQ_SIZE 6
#define STRING_BUFFER_PINYIN_FREQ_SIZE STRING_BUFFER_PINYIN_SIZE+ STRING_BUFFER_FREQ_SIZE +3
typedef struct {
    char pinYin[7];
    int freq;
} PinYinFreqRec;

static GArray *pinYinFreqRec_parse(const char *composite_value){
    GArray *gArray=g_array_new(FALSE,TRUE,sizeof(PinYinFreqRec));
    char **subFieldArray=g_strsplit_set(composite_value," ()",-1);
    int i;
    int currIndex=0;
    int freq;
    PinYinFreqRec *currRec=NULL;
    UnihanPinYinFreqState state=UNIHAN_PINYIN_FREQ_STATE_PINYIN;

    for(i=0;subFieldArray[i]!=NULL;i++){
	switch(state){
	    case UNIHAN_PINYIN_FREQ_STATE_PINYIN:
		state=UNIHAN_PINYIN_FREQ_STATE_FREQ;
		break;
	    case UNIHAN_PINYIN_FREQ_STATE_FREQ:
		g_assert(i>0);
		currIndex=gArray->len;
		g_array_set_size(gArray,currIndex+1);
		currRec=&g_array_index(gArray,PinYinFreqRec,currIndex);
		g_strlcpy(currRec->pinYin,subFieldArray[i-1],STRING_BUFFER_PINYIN_SIZE);
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

static void pinYinFreqRec_parse_SQLite_value
(PinYinFreqRec *rec, sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==3);
    if (sqlite3_value_type(argv[0])==SQLITE_TEXT){
	sqlite_value_signed_text_buffer(rec->pinYin,argv[0]);
    }
    rec->freq=sqlite3_value_int(argv[1]);
}

static void pinYinFreqRec_to_string(char* const buf, PinYinFreqRec *rec, UnihanQueryOption qOption){
    PinYin *pinYin=NULL;
    ZhuYin *zhuYin=NULL;

    if (qOption & UNIHAN_QUERY_OPTION_ZHUYIN_FORCE_DISPLAY){
	zhuYin=pinYin_to_zhuYin(rec->pinYin,UNIHAN_QUERY_OPTION_GET_ZHUYIN_FORMAT(qOption));
	g_snprintf(buf,STRING_BUFFER_PINYIN_FREQ_SIZE,"%s(%d)",zhuYin,rec->freq);
	g_free(zhuYin);
    }else{
	pinYin=pinYin_convert_accent_format(rec->pinYin,UNIHAN_QUERY_OPTION_GET_PINYIN_FORMAT(qOption),
		((qOption & UNIHAN_QUERY_OPTION_PINYIN_TONE_ACCENT) ? 0: 1));
	g_snprintf(buf,STRING_BUFFER_PINYIN_FREQ_SIZE,"%s(%d)",pinYin,rec->freq);
	g_free(pinYin);
    }
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
	    case 'u':
	    case 'U':
		state=UNIHAN_SEMANTIC_VARIANT_STATE_CODE;
		variantCode=0;
		break;
	    case 'k':
	    case 'K':
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
    PinYinFreqRec rec;
    g_assert(argc==3);
    char *pStr=NEW_ARRAY_INSTANCE(STRING_BUFFER_PINYIN_FREQ_SIZE,char);
    pinYinFreqRec_parse_SQLite_value(&rec, context, argc, argv);
    UnihanQueryOption qOption=UNIHAN_QUERY_OPTION_DEFAULT;
    if (sqlite3_value_type(argv[2])==SQLITE_INTEGER){
	qOption= sqlite3_value_int64(argv[2]); 
    }
    pinYinFreqRec_to_string(pStr,&rec,qOption);
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

static void scalar_string_parse_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==1);
    char *pStr=NEW_ARRAY_INSTANCE(20,char);
    char *value=sqlite_value_signed_text(argv[0]);
    if (value && value[0]=='U'){
	gunichar uniChar=unihanChar_parse(value);
	g_snprintf(pStr,20,"%u",uniChar);
    }else{
	g_strlcpy(pStr,value,20);
    }
    g_free(value);
    sqlite3_result_text(context,pStr,-1,g_free);
}



static void to_lowercase_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==1);
    char *str=sqlite_value_signed_text(argv[0]);
    char *pStr=g_utf8_strdown(str,-1);
    g_free(str);
    sqlite3_result_text(context,pStr,-1,g_free);
}

static void to_uppercase_Func(sqlite3_context *context, int argc, sqlite3_value **argv){
    g_assert(argc==1);
    char *str=sqlite_value_signed_text(argv[0]);
    char *pStr=g_utf8_strup(str,-1);
    g_free(str);
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


/*=========================================================================
 * Sqlite database functions
 */

const DatabaseFuncStru DATABASE_FUNCS[]={
    {"ADOBE_RADICAL_STROKE_VALUE_CONCAT",5,adobeRadicalStroke_value_concat_Func,NULL,NULL},
    {"HANYU_PINLU_VALUE_CONCAT",3,hanYu_pinLu_value_concat_Func,NULL,NULL},
    {"IRG_SOURCE_VALUE_CONCAT",2,irg_source_value_concat_Func,NULL,NULL},
    {"KANGXI_VALUE_CONCAT",3,kangXi_value_concat_Func,NULL,NULL},
    {"PINYIN_CONVERT_ACCENT_FORMAT",3,pinYin_convert_accent_format_scalar_func,NULL,NULL},
    {"PINYIN_TO_ZHUYIN",2,pinYin_to_zhuYin_scalar_func,NULL,NULL},
    {"RADICAL_STROKE_VALUE_CONCAT",2,radicalStroke_value_concat_Func,NULL,NULL},
    {"SCALAR_STRING_PARSE",1, scalar_string_parse_Func,NULL,NULL},
    {"SEMANTIC_VARIANT_VALUE_CONCAT",5,NULL,semantic_value_concat_step_Func,semantic_value_concat_finalized_Func},
    {"TO_SCALAR_STRING",1,to_scalar_string_Func,NULL,NULL,},
    {"TO_LOWERCASE",1,to_lowercase_Func,NULL,NULL},
    {"TO_UPPERCASE",1,to_uppercase_Func,NULL,NULL},
    {"Z_VARIANT_VALUE_CONCAT",2,zVariant_value_concat_Func,NULL,NULL},
    {"ZHUYIN_CONVERT_TONEMARK_FORMAT",2,zhuYin_convert_toneMark_format_scalar_func,NULL,NULL},
    {"ZHUYIN_TO_PINYIN",3,zhuYin_to_pinYin_scalar_func,NULL,NULL},
    {NULL,0,NULL,NULL,NULL},
};


/**
 * Data structure of database supporting functions.
 *
 */
typedef struct pseudoFieldStru{
    UnihanField pseudoField;             //!< Pseudo fields.
    const char *funcName;                //!< Associated Function name.
} PseudoFieldStru;

const PseudoFieldStru PSEUDO_FIELDS[]={
    {UNIHAN_FIELD_kIRG_GSOURCE,  "IRG_SOURCE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kIRG_HSOURCE,  "IRG_SOURCE_VALUE_CONCAT"}, 
    {UNIHAN_FIELD_kIRG_JSOURCE,   "IRG_SOURCE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kIRG_KPSOURCE,  "IRG_SOURCE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kIRG_KSOURCE,   "IRG_SOURCE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kIRG_TSOURCE,   "IRG_SOURCE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kIRG_USOURCE,   "IRG_SOURCE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kIRG_VSOURCE,   "IRG_SOURCE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kSEMANTICVARIANT, "SEMANTIC_VARIANT_VALUE_CONCAT"},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT,  "SEMANTIC_VARIANT_VALUE_CONCAT"},
    {UNIHAN_FIELD_kZVARIANT,"Z_VARIANT_VALUE_CONCAT"},
    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6,"ADOBE_RADICAL_STROKE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kRSJAPANESE, "RADICAL_STROKE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kRSKANGXI, "RADICAL_STROKE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kRSKANWA, "RADICAL_STROKE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kRSKOREAN, "RADICAL_STROKE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kRSUNICODE, "RADICAL_STROKE_VALUE_CONCAT"},
    {UNIHAN_FIELD_kHANYUPINLU, "HANYU_PINLU_VALUE_CONCAT"},
    {UNIHAN_FIELD_kIRGKANGXI, "KANGXI_VALUE_CONCAT"},
    {UNIHAN_FIELD_kKANGXI, "KANGXI_VALUE_CONCAT"},
    {UNIHAN_FIELD_ZHUYIN,  "PINYIN_ZHUYIN"},
    {UNIHAN_INVALID_FIELD,  NULL},
};

typedef struct pseudoFieldRequireTablesStru{
    UnihanField pseudoField;             //!< Pseudo fields.
    UnihanTable requiredTable; 
} PseudoFieldRequireTablesStru;

const PseudoFieldRequireTablesStru PSEUDO_FIELDS_REQUIRED_TABLES[]={
    {UNIHAN_FIELD_kIRG_GSOURCE,  UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_GSOURCE,  UNIHAN_TABLE_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_HSOURCE,  UNIHAN_TABLE_IRG_SOURCE}, 
    {UNIHAN_FIELD_kIRG_HSOURCE,  UNIHAN_TABLE_IRG_SOURCE_MAPPING}, 
    {UNIHAN_FIELD_kIRG_JSOURCE,  UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_JSOURCE,  UNIHAN_TABLE_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_KPSOURCE, UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_KPSOURCE, UNIHAN_TABLE_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_KSOURCE,  UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_KSOURCE,  UNIHAN_TABLE_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_TSOURCE,  UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_TSOURCE,  UNIHAN_TABLE_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_USOURCE,  UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_USOURCE,  UNIHAN_TABLE_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_VSOURCE,  UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_VSOURCE,  UNIHAN_TABLE_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT},
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT,  UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT,  UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_kZVARIANT, UNIHAN_TABLE_kZVARIANT},
    {UNIHAN_FIELD_kZVARIANT, UNIHAN_TABLE_kZVARIANT_EXTRA},
    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6, UNIHAN_TABLE_kRSADOBE_JAPAN1_6},
    {UNIHAN_FIELD_kRSJAPANESE, UNIHAN_TABLE_kRSJAPANESE},
    {UNIHAN_FIELD_kRSKANGXI, UNIHAN_TABLE_kRSKANGXI},
    {UNIHAN_FIELD_kRSKANWA, UNIHAN_TABLE_kRSKANWA},
    {UNIHAN_FIELD_kRSKOREAN, UNIHAN_TABLE_kRSKOREAN},
    {UNIHAN_FIELD_kRSUNICODE, UNIHAN_TABLE_kRSUNICODE},
    {UNIHAN_FIELD_kHANYUPINLU, UNIHAN_TABLE_kHANYUPINLU},
    {UNIHAN_FIELD_kIRGKANGXI, UNIHAN_TABLE_kIRGKANGXI},
    {UNIHAN_FIELD_kKANGXI, UNIHAN_TABLE_kKANGXI},
    {UNIHAN_FIELD_ZHUYIN,  UNIHAN_TABLE_kMANDARIN},
    {UNIHAN_FIELD_UTF8,    UNIHAN_TABLE_CODE},
    {UNIHAN_INVALID_FIELD,  UNIHAN_INVALID_TABLE},
};

