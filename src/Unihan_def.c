/** 
 * @file Unihan_def.c
 * @brief This file consist definition and constants.
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

    "dict_page",
    "dict_charNum",
    "dict_virtual",

    "IRG_source_short_name",
    "IRG_source_mapping",

    "pinyin",
    "pinyin_base",
    "pinyin_tone",
    "pinyin_freq",
    "zhuyin",


    "adobeCID_CV",
    "adobeCID",
    "adobeCID_radicalStrokeCount",
    "radical_index",
    "additional_stroke_count",
    "radical_is_simplified",


    "variant_code",

    "from_dict",
    "semantic_T",
    "semantic_B",
    "semantic_Z",
    "zVariant_source",


    "freq_rank",

    "scalar_value",

    "serial",
    "serial_no_join",

    "utf8",


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
    
    "kIRG_GSourceTable",
    "kIRG_GSourceTableExtra",
    "kIRG_HSourceTable",
    "kIRG_HSourceTableExtra",
    "kIRG_JSourceTable",
    "kIRG_JSourceTableExtra",
    "kIRG_KPSourceTable",
    "kIRG_KPSourceTableExtra",
    "kIRG_KSourceTable",
    "kIRG_KSourceTableExtra",
    "kIRG_TSourceTable",
    "kIRG_TSourceTableExtra",
    "kIRG_USourceTable",
    "kIRG_USourceTableExtra",
    "kIRG_VSourceTable",
    "kIRG_VSourceTableExtra",

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


    "kSemanticVariantTableExtra",
    "kSpecializedSemanticVariantTableExtra",
    "kZVariantTableExtra",
    NULL
};



/**
 * Fields that holds integer.
 *
 * This includes UCS4 fields but exclude other fields that use Hexdecimal.
 *
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

    UNIHAN_FIELD_DICT_VIRTUAL,

    UNIHAN_FIELD_PINYIN_TONE,
    UNIHAN_FIELD_PINYIN_FREQ,

    UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT,
    UNIHAN_FIELD_RADICAL_INDEX,
    UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,
    UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,

    UNIHAN_FIELD_VARIANT_CODE,
    UNIHAN_FIELD_SEMANTIC_T,
    UNIHAN_FIELD_SEMANTIC_B,
    UNIHAN_FIELD_SEMANTIC_Z,

    UNIHAN_FIELD_FREQ_RANK,
    UNIHAN_FIELD_KEEP_SEQUAL,
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


const UnihanField UNIHAN_UPPERCASE_FIELDS[]={
    UNIHAN_FIELD_kBIGFIVE, 		
    UNIHAN_FIELD_kCANGJIE,		
    UNIHAN_FIELD_kCCCII,   		
    UNIHAN_FIELD_kCNS1986, 		
    UNIHAN_FIELD_kCNS1992, 		
    UNIHAN_FIELD_kCOMPATIBILITYVARIANT, 
    UNIHAN_FIELD_kEACC,			
    UNIHAN_FIELD_kFENN,			
    UNIHAN_FIELD_kGB0,			
    UNIHAN_FIELD_kGB1,			
    UNIHAN_FIELD_kGB3,			
    UNIHAN_FIELD_kGB5,			
    UNIHAN_FIELD_kGB7,			
    UNIHAN_FIELD_kGB8, 			
    
    UNIHAN_FIELD_kHDZRADBREAK,		
    UNIHAN_FIELD_kHKSCS,   		
    UNIHAN_FIELD_kIBMJAPAN,		
    UNIHAN_FIELD_kIRG_GSOURCE, 	
    UNIHAN_FIELD_kIRG_HSOURCE, 	
    UNIHAN_FIELD_kIRG_JSOURCE, 	
    UNIHAN_FIELD_kIRG_KPSOURCE, 	
    UNIHAN_FIELD_kIRG_KSOURCE, 		
    UNIHAN_FIELD_kIRG_TSOURCE, 		
    UNIHAN_FIELD_kIRG_USOURCE, 		
    UNIHAN_FIELD_kIRG_VSOURCE, 		
    UNIHAN_FIELD_kJAPANESEKUN,		
    UNIHAN_FIELD_kJAPANESEON,		
    UNIHAN_FIELD_kKARLGREN,		
    UNIHAN_FIELD_kKOREAN,		
    UNIHAN_FIELD_kKPS0,		
    UNIHAN_FIELD_kKPS1,		
    UNIHAN_FIELD_kMANDARIN,		
    UNIHAN_FIELD_kPHONETIC,		
    UNIHAN_FIELD_kVIETNAMESE,		

    UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,
    UNIHAN_FIELD_IRG_SOURCE_MAPPING,
    
    UNIHAN_FIELD_ADOBE_CID_CV,
    UNIHAN_FIELD_SCALAR_VALUE,

    UNIHAN_INVALID_FIELD
};



const UnihanField UNIHAN_LOWERCASE_FIELDS[]={
    UNIHAN_FIELD_kCANTONESE,
    UNIHAN_FIELD_kGSR,
    UNIHAN_FIELD_kHANYUPINLU,
    UNIHAN_FIELD_kMATTHEWS,
    UNIHAN_FIELD_kMEYERWEMPE,
    UNIHAN_FIELD_kXHC1983,
    UNIHAN_FIELD_PINYIN,
    UNIHAN_FIELD_PINYIN_BASE,

    UNIHAN_INVALID_FIELD
};

/**
 * Fields that are functional dependent to code.
 * Which means each character has at most one value per each fields.
 * But inverse does not always true.
 * Such as UNIHAN_FIELD_kGRADELEVEL, and UNIHAN_FIELD_kOTHERNUMERIC.
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




