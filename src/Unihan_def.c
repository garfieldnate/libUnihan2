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
 * UNIHAN_FIELDS.
 *
 *
 */
const FieldProperties *UNIHAN_FIELD_PROPERTIES[UNIHAN_FIELDS_COUNT+1]={
    {"code", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_UCS4 },
    {"kAccountingNumeric", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_NO_INDEX | UNIHAN_FIELDFLAG_SINGLETON},
    {"kBigFive", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kCangjie", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kCantonese", UNIHAN_FIELDFLAG_LOWERCASE},
    {"kCCCII",  UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"kCheungBauer",  UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"kCheungBauerIndex", 0},
    {"kCihaiT", 0},
    {"kCNS1986", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"kCNS1992", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"kCompatibilityVariant", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_UCS4 },
    {"kCowles", 0},
    {"kDaeJaweon", 0},
    {"kDefinition", UNIHAN_FIELDFLAG_NO_INDEX | UNIHAN_FIELDFLAG_SINGLETON},
    {"kEACC", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16},
    {"kFenn", 0},
    {"kFennIndex", 0},
    {"kFourCornerCode", UNIHAN_FIELDFLAG_SINGLETON},
    {"kFrequency", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_SINGLETON},
    {"kGB0",  UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kGB1",  UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kGB3",  UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kGB5",  UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kGB7",  UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kGB8",  UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kGradeLevel",  UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_SINGLETON},
    {"kGSR", UNIHAN_FIELDFLAG_LOWERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"kHangul", 0},
    {"kHanYu", 0},
    {"kHanyuPinlu", UNIHAN_FIELDFLAG_PSEUDO | UNIHAN_FIELDFLAG_LOWERCASE},
    {"kHDZRadBreak", 0},
    {"kHKGlyph", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kHKSCS", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kIBMJapan", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kIICore", UNIHAN_FIELDFLAG_SINGLETON},
    {"kIRGDaeJaweon", 0},
    {"kIRGDaiKanwaZiten", 0},
    {"kIRGHanyuDaZidian", 0},
    {"kIRGKangXi", 0},
    {"kIRG_GSource", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kIRG_HSource", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kIRG_JSource", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kIRG_KPSource", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kIRG_KSource", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kIRG_TSource", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kIRG_USource", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kIRG_VSource", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kJapaneseKun", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kJapaneseOn", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kJIS0213", 0},
    {"kJis0", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kJis1", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kKangXi", 0},
    {"kKarlgren", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kKorean", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kKPS0", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kKPS1", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kKSC0", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kKSC1", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kLau", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16},
    {"kMainlandTelegraph", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kMandarin", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kMatthews", UNIHAN_FIELDFLAG_LOWERCASE},
    {"kMeyerWempe", UNIHAN_FIELDFLAG_LOWERCASE},
    {"kMorohashi", UNIHAN_FIELDFLAG_LOWERCASE},
    {"kNelson", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4},
    {"kOtherNumeric", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_NO_INDEX | UNIHAN_FIELDFLAG_SINGLETON},
    {"kPhonetic", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kPrimaryNumeric", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_NO_INDEX | UNIHAN_FIELDFLAG_SINGLETON},
    {"kPseudoGB1", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_HEXDECIMAL_16 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kRSAdobe_Japan1_6", UNIHAN_FIELDFLAG_UPPERCASE},
    {"kRSJapanese", 0},
    {"kRSKangXi", 0},
    {"kRSKanWa", 0},
    {"kRSKorean", 0},
    {"kRSUnicode", 0},
    {"kSBGY", 0},
    {"kSemanticVariant", 0},
    {"kSimplifiedVariant", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_UCS4},
    {"kSpecializedSemanticVariant", 0},
    {"kTaiwanTelegraph", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4 | UNIHAN_FIELDFLAG_SINGLETON},
    {"kTang", 0},
    {"kTotalStrokes", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_SINGLETON},
    {"kTraditionalVariant", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_UCS4},
    {"kVietnamese", 0},
    {"kXerox",  UNIHAN_FIELDFLAG_SINGLETON},
    {"kXHC1983", UNIHAN_FIELDFLAG_LOWERCASE},
    {"kZVariant", 0},

    {"dict_page", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_NO_INDEX},
    {"dict_page_0_padded_4", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_4  | UNIHAN_FIELDFLAG_NO_INDEX | UNIHAN_FIELDFLAG_NO_PRIMARYKEY},
    {"dict_position", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_NO_INDEX | UNIHAN_FIELDFLAG_NO_PRIMARYKEY},
    {"dict_virtual", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_NO_INDEX  | UNIHAN_FIELDFLAG_NO_PRIMARYKEY},
    {"dict_variant_serial", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_0_PADDED_2  | UNIHAN_FIELDFLAG_NO_INDEX  | UNIHAN_FIELDFLAG_NO_PRIMARYKEY},
    {"dict_unencoded", UNIHAN_FIELDFLAG_INTEGER  | UNIHAN_FIELDFLAG_NO_PRIMARYKEY},

    {"IRG_GSource", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"IRG_HSource", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"IRG_JSource", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"IRG_KPSource", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"IRG_KSource", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"IRG_TSource", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"IRG_USource", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"IRG_VSource", UNIHAN_FIELDFLAG_UPPERCASE | UNIHAN_FIELDFLAG_SINGLETON},
    {"IRG_source_mapping", UNIHAN_FIELDFLAG_NO_INDEX | UNIHAN_FIELDFLAG_NO_PRIMARYKEY},

    {"pinyin", UNIHAN_FIELDFLAG_LOWERCASE},
    {"pinyin_base", UNIHAN_FIELDFLAG_LOWERCASE},
    {"pinyin_tone", UNIHAN_FIELDFLAG_INTEGER},
    {"pinyin_freq", UNIHAN_FIELDFLAG_INTEGER},
    {"zhuyin", 0},


    {"adobeCID_CV", UNIHAN_FIELDFLAG_UPPERCASE},
    {"adobeCID", 0},
    {"adobeCID_radicalStrokeCount", UNIHAN_FIELDFLAG_INTEGER},
    {"radical_index", UNIHAN_FIELDFLAG_INTEGER},
    {"additional_stroke_count", UNIHAN_FIELDFLAG_INTEGER},
    {"radical_is_simplified", UNIHAN_FIELDFLAG_INTEGER},


    {"semantic_variant", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_UCS4},
    {"specializedsemantic_variant", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_UCS4},

    {"from_dict", 0},
    {"semantic_T", UNIHAN_FIELDFLAG_INTEGER},
    {"semantic_B", UNIHAN_FIELDFLAG_INTEGER},
    {"semantic_Z", UNIHAN_FIELDFLAG_INTEGER},

    {"z_variant", UNIHAN_FIELDFLAG_INTEGER | UNIHAN_FIELDFLAG_UCS4},
    {"zVariant_source", 0},

    {"freq_rank", UNIHAN_FIELDFLAG_INTEGER},

    {"scalar_value", 0},

    {"serial", UNIHAN_FIELDFLAG_INTEGER},
    {"serial_no_join", UNIHAN_FIELDFLAG_INTEGER},

    {"utf8", 0},

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
    "kSemanticVariantTableExtra",
    "kSimplifiedVariantTable",
    "kSpecializedSemanticVariantTable",
    "kSpecializedSemanticVariantTableExtra",
    "kTaiwanTelegraphTable",
    "kTangTable",
    "kTotalStrokesTable",
    "kTraditionalVariantTable",
    "kVietnameseTable",
    "kXeroxTable",
    "kXHC1983Table",
    "kZVariantTable",
    "kZVariantTableExtra",

    "codeTable",
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




