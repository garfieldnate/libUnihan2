/** 
 * @file Unihan_builtin_def.c
 * @brief Data structures  for builtin tables and fields only.
 * 
 * This file contains the data structures 
 *  which only deal for builtin tables and fields.
 */

/**
 * UNIHAN_FIELDS.
 *
 *
 */

const FieldProperties UNIHAN_FIELD_PROPERTIES[]={
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
    {"kHanyuPinlu", UNIHAN_FIELDFLAG_LOWERCASE},
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

    {NULL,0}
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


typedef struct{
    UnihanField field;
    gchar *value;
} UnihanFieldValuePair;


/*
 * UNIHAN_FIELD_CODE is omitted, as it exists in every table
 */
const UnihanFieldTablePair REALFIELD_TABLES[]={
    {UNIHAN_FIELD_kACCOUNTINGNUMERIC,	UNIHAN_TABLE_kACCOUNTINGNUMERIC},
    {UNIHAN_FIELD_kBIGFIVE,		UNIHAN_TABLE_kBIGFIVE},
    {UNIHAN_FIELD_kCANGJIE,		UNIHAN_TABLE_kCANGJIE},
    {UNIHAN_FIELD_kCANTONESE,		UNIHAN_TABLE_kCANTONESE},
    {UNIHAN_FIELD_kCCCII,		UNIHAN_TABLE_kCCCII},
    {UNIHAN_FIELD_kCHEUNGBAUER,		UNIHAN_TABLE_kCHEUNGBAUER},
    {UNIHAN_FIELD_kCHEUNGBAUERINDEX,	UNIHAN_TABLE_kCHEUNGBAUERINDEX},
    {UNIHAN_FIELD_kCIHAIT,		UNIHAN_TABLE_kCIHAIT},
    {UNIHAN_FIELD_kCNS1986,		UNIHAN_TABLE_kCNS1986},
    {UNIHAN_FIELD_kCNS1992,		UNIHAN_TABLE_kCNS1992},
    {UNIHAN_FIELD_kCOMPATIBILITYVARIANT,		UNIHAN_TABLE_kCOMPATIBILITYVARIANT},
    {UNIHAN_FIELD_kCOWLES,		UNIHAN_TABLE_kCOWLES},
    {UNIHAN_FIELD_kDAEJAWEON,		UNIHAN_TABLE_kDAEJAWEON},
    {UNIHAN_FIELD_kDEFINITION,		UNIHAN_TABLE_kDEFINITION},
    {UNIHAN_FIELD_kEACC,		UNIHAN_TABLE_kEACC},
    {UNIHAN_FIELD_kFENN,		UNIHAN_TABLE_kFENN},
    {UNIHAN_FIELD_kFENNINDEX,		UNIHAN_TABLE_kFENNINDEX},
    {UNIHAN_FIELD_kFOURCORNERCODE,	UNIHAN_TABLE_kFOURCORNERCODE},
    {UNIHAN_FIELD_kFREQUENCY,		UNIHAN_TABLE_kFREQUENCY},
    {UNIHAN_FIELD_kGB0,			UNIHAN_TABLE_kGB0},
    {UNIHAN_FIELD_kGB1,			UNIHAN_TABLE_kGB1},
    {UNIHAN_FIELD_kGB3,			UNIHAN_TABLE_kGB3},
    {UNIHAN_FIELD_kGB5,			UNIHAN_TABLE_kGB5},
    {UNIHAN_FIELD_kGB7,			UNIHAN_TABLE_kGB7},
    {UNIHAN_FIELD_kGB8,			UNIHAN_TABLE_kGB8},
    {UNIHAN_FIELD_kGRADELEVEL,		UNIHAN_TABLE_kGRADELEVEL},
    {UNIHAN_FIELD_kGSR,			UNIHAN_TABLE_kGSR},
    {UNIHAN_FIELD_kHANGUL,		UNIHAN_TABLE_kHANGUL},
    {UNIHAN_FIELD_kHANYU,		UNIHAN_TABLE_kHANYU},

    {UNIHAN_FIELD_PINYIN_BASE,		UNIHAN_TABLE_kHANYUPINLU},
    {UNIHAN_FIELD_PINYIN_TONE,		UNIHAN_TABLE_kHANYUPINLU},
    {UNIHAN_FIELD_PINYIN_FREQ,		UNIHAN_TABLE_kHANYUPINLU},

    {UNIHAN_FIELD_kHDZRADBREAK,		UNIHAN_TABLE_kHDZRADBREAK},
    {UNIHAN_FIELD_kHKGLYPH,		UNIHAN_TABLE_kHKGLYPH},
    {UNIHAN_FIELD_kHKSCS,		UNIHAN_TABLE_kHKSCS},
    {UNIHAN_FIELD_kIBMJAPAN,		UNIHAN_TABLE_kIBMJAPAN},
    {UNIHAN_FIELD_kIICORE,		UNIHAN_TABLE_kIICORE},

    {UNIHAN_FIELD_IRG_GSOURCE,		UNIHAN_TABLE_IRG_GSOURCE},
    {UNIHAN_FIELD_IRG_GSOURCE,		UNIHAN_TABLE_IRG_GSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,	UNIHAN_TABLE_IRG_GSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_HSOURCE,		UNIHAN_TABLE_IRG_HSOURCE},
    {UNIHAN_FIELD_IRG_HSOURCE,		UNIHAN_TABLE_IRG_HSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,	UNIHAN_TABLE_IRG_HSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_JSOURCE,		UNIHAN_TABLE_IRG_JSOURCE},
    {UNIHAN_FIELD_IRG_JSOURCE,		UNIHAN_TABLE_IRG_JSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,	UNIHAN_TABLE_IRG_JSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_KPSOURCE,		UNIHAN_TABLE_IRG_KPSOURCE},
    {UNIHAN_FIELD_IRG_KPSOURCE,		UNIHAN_TABLE_IRG_KPSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,	UNIHAN_TABLE_IRG_KPSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_KSOURCE,		UNIHAN_TABLE_IRG_KSOURCE},
    {UNIHAN_FIELD_IRG_KSOURCE,		NIHAN_TABLE_IRG_KSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,	UNIHAN_TABLE_IRG_KSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_TSOURCE,		UNIHAN_TABLE_IRG_TSOURCE},
    {UNIHAN_FIELD_IRG_TSOURCE,		UNIHAN_TABLE_IRG_TSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,	UNIHAN_TABLE_IRG_TSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_USOURCE,		UNIHAN_TABLE_IRG_USOURCE},
    {UNIHAN_FIELD_IRG_USOURCE,		UNIHAN_TABLE_IRG_USOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,	UNIHAN_TABLE_IRG_USOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_VSOURCE,		UNIHAN_TABLE_IRG_VSOURCE},
    {UNIHAN_FIELD_IRG_VSOURCE,		UNIHAN_TABLE_IRG_VSOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,	UNIHAN_TABLE_IRG_VSOURCE_EXTRA},

    {UNIHAN_FIELD_kIRGDAEJAWEON,	UNIHAN_TABLE_kIRGDAEJAWEON},
    {UNIHAN_FIELD_kIRGDAIKANWAZITEN,	UNIHAN_TABLE_kIRGDAIKANWAZITEN},
    {UNIHAN_FIELD_kIRGHANYUDAZIDIAN,	UNIHAN_TABLE_kIRGHANYUDAZIDIAN},

    {UNIHAN_FIELD_DICT_PAGE,		UNIHAN_TABLE_kIRGKANGXI},
    {UNIHAN_FIELD_DICT_POSITION,	UNIHAN_TABLE_kIRGKANGXI},
    {UNIHAN_FIELD_DICT_VIRTUAL,		UNIHAN_TABLE_kIRGKANGXI},

    {UNIHAN_FIELD_kJAPANESEKUN,		UNIHAN_TABLE_kJAPANESEKUN},
    {UNIHAN_FIELD_kJAPANESEON,		UNIHAN_TABLE_kJAPANESEON},
    {UNIHAN_FIELD_kJIS0213,		UNIHAN_TABLE_kJIS0213},
    {UNIHAN_FIELD_kJIS0,		UNIHAN_TABLE_kJIS0},
    {UNIHAN_FIELD_kJIS1,		UNIHAN_TABLE_kJIS1},

    {UNIHAN_FIELD_DICT_PAGE,		UNIHAN_TABLE_kKANGXI},
    {UNIHAN_FIELD_DICT_POSITION,	UNIHAN_TABLE_kKANGXI},
    {UNIHAN_FIELD_DICT_VIRTUAL,		UNIHAN_TABLE_kKANGXI},

    {UNIHAN_FIELD_kKARLGREN,		UNIHAN_TABLE_kKARLGREN},
    {UNIHAN_FIELD_kKOREAN,		UNIHAN_TABLE_kKOREAN},
    {UNIHAN_FIELD_kKPS0,		UNIHAN_TABLE_kKPS0},
    {UNIHAN_FIELD_kKPS1,		UNIHAN_TABLE_kKPS1},
    {UNIHAN_FIELD_kKSC0,		UNIHAN_TABLE_kKSC0},
    {UNIHAN_FIELD_kKSC1,		UNIHAN_TABLE_kKSC1},
    {UNIHAN_FIELD_kLAU,			UNIHAN_TABLE_kLAU},
    {UNIHAN_FIELD_kMAINLANDTELEGRAPH,	UNIHAN_TABLE_kMAINLANDTELEGRAPH},

    {UNIHAN_FIELD_PINYIN_BASE,		UNIHAN_TABLE_kMANDARIN},
    {UNIHAN_FIELD_PINYIN_TONE,		UNIHAN_TABLE_kMANDARIN},
    {UNIHAN_FIELD_FREQ_RANK,		UNIHAN_TABLE_kMANDARIN},

    {UNIHAN_FIELD_kMATTHEWS,		UNIHAN_TABLE_kMATTHEWS},
    {UNIHAN_FIELD_kMEYERWEMPE,		UNIHAN_TABLE_kMEYERWEMPE},
    {UNIHAN_FIELD_kMOROHASHI,		UNIHAN_TABLE_kMOROHASHI},
    {UNIHAN_FIELD_kNELSON,		UNIHAN_TABLE_kNELSON},
    {UNIHAN_FIELD_kOTHERNUMERIC,	UNIHAN_TABLE_kOTHERNUMERIC},
    {UNIHAN_FIELD_kPHONETIC,		UNIHAN_TABLE_kPHONETIC},
    {UNIHAN_FIELD_kPRIMARYNUMERIC,	UNIHAN_TABLE_kPRIMARYNUMERIC},
    {UNIHAN_FIELD_kPSEUDOGB1,		UNIHAN_TABLE_kPSEUDOGB1},

    {UNIHAN_FIELD_ADOBE_CID_CV, 	UNIHAN_TABLE_kRSADOBE_JAPAN1_6},
    {UNIHAN_FIELD_ADOBE_CID, 		UNIHAN_TABLE_kRSADOBE_JAPAN1_6},
    {UNIHAN_FIELD_RADICAL_INDEX, 	UNIHAN_TABLE_kRSADOBE_JAPAN1_6},
    {UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT,	UNIHAN_TABLE_kRSADOBE_JAPAN1_6},
    {UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,	UNIHAN_TABLE_kRSADOBE_JAPAN1_6},

    {UNIHAN_FIELD_RADICAL_INDEX, 	UNIHAN_TABLE_kRSJAPANESE},
    {UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,	UNIHAN_TABLE_kRSJAPANESE},
    {UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED, UNIHAN_TABLE_kRSJAPANESE},

    {UNIHAN_FIELD_RADICAL_INDEX, 	UNIHAN_TABLE_kRSKANGXI},
    {UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,	UNIHAN_TABLE_kRSKANGXI},
    {UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,	UNIHAN_TABLE_kRSKANGXI},

    {UNIHAN_FIELD_RADICAL_INDEX, 	UNIHAN_TABLE_kRSKANWA},
    {UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,	UNIHAN_TABLE_kRSKANWA},
    {UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,	UNIHAN_TABLE_kRSKANWA},

    {UNIHAN_FIELD_RADICAL_INDEX, 	UNIHAN_TABLE_kRSKOREAN},
    {UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,	UNIHAN_TABLE_kRSKOREAN},
    {UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,	UNIHAN_TABLE_kRSKOREAN},

    {UNIHAN_FIELD_RADICAL_INDEX, 	UNIHAN_TABLE_kRSUNICODE},
    {UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,	UNIHAN_TABLE_kRSUNICODE},
    {UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED, 	UNIHAN_TABLE_kRSUNICODE},

    {UNIHAN_FIELD_SEMANTICVARIANT,		UNIHAN_TABLE_kSEMANTICVARIANT},
    {UNIHAN_FIELD_SEMANTICVARIANT,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SERIAL_NO_JOIN,	UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_FROM_DICT,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_T,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_B,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_Z,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},

    {UNIHAN_FIELD_kSIMPIFIEDVARIANT,	UNIHAN_TABLE_kSIMPLIFIEDVARIANT},

    {UNIHAN_FIELD_SPECIALIZEDVARIANT,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT},
    {UNIHAN_FIELD_SPECIALIZEDVARIANT,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SERIAL_NO_JOIN,	UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_FROM_DICT,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_T,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_B,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_Z,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},

    {UNIHAN_FIELD_kTAIWANTELEGRAPH,	UNIHAN_TABLE_kTAIWANTELEGRAPH},
    {UNIHAN_FIELD_kTANG,		UNIHAN_TABLE_kTANG},
    {UNIHAN_FIELD_kTOTALSTROKES,	UNIHAN_TABLE_kTOTALSTROKES},

    {UNIHAN_FIELD_kTRADITIONALVARIANT,	UNIHAN_TABLE_kTRADITIONALVARIANT},

    {UNIHAN_FIELD_kVIETNAMESE,		UNIHAN_TABLE_kVIETNAMESE},
    {UNIHAN_FIELD_kXEROX,		UNIHAN_TABLE_kXEROX},

    {UNIHAN_FIELD_DICT_PAGE,			UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_DICT_POSITION,		UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_DICT_VARIANT_SERIAL,		UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_DICT_UNENCODED,		UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_DICT_SERIAL_NO_JOIN,		UNIHAN_TABLE_kXHC1983},

    {UNIHAN_FIELD_DICT_PINYIN_BASE,		UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_DICT_PINYIN_TONE,		UNIHAN_TABLE_kXHC1983},

    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kZVARIANT},
    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kZVARIANT_EXTRA},
    {UNIHAN_FIELD_ZVARIANT_SOURCE,	UNIHAN_TABLE_kZVARIANT_EXTRA},

    {UNIHAN_INVALID_FIELD,  UNIHAN_INVALID_TABLE},
};

const UnihanFieldTablePair FIELD_PREFERRED_TABLES[]={
    {UNIHAN_FIELD_CODE,			UNIHAN_TABLE_CODE},
    {UNIHAN_FIELD_kACCOUNTINGNUMERIC,	UNIHAN_TABLE_kACCOUNTINGNUMERIC},
    {UNIHAN_FIELD_kBIGFIVE,		UNIHAN_TABLE_kBIGFIVE},
    {UNIHAN_FIELD_kCANGJIE,		UNIHAN_TABLE_kCANGJIE},
    {UNIHAN_FIELD_kCANTONESE,		UNIHAN_TABLE_kCANTONESE},
    {UNIHAN_FIELD_kCCCII,		UNIHAN_TABLE_kCCCII},
    {UNIHAN_FIELD_kCHEUNGBAUER,		UNIHAN_TABLE_kCHEUNGBAUER},
    {UNIHAN_FIELD_kCHEUNGBAUERINDEX,	UNIHAN_TABLE_kCHEUNGBAUERINDEX},
    {UNIHAN_FIELD_kCIHAIT,		UNIHAN_TABLE_kCIHAIT},
    {UNIHAN_FIELD_kCNS1986,		UNIHAN_TABLE_kCNS1986},
    {UNIHAN_FIELD_kCNS1992,		UNIHAN_TABLE_kCNS1992},
    {UNIHAN_FIELD_kCOMPATIBILITYVARIANT,		UNIHAN_TABLE_kCOMPATIBILITYVARIANT},
    {UNIHAN_FIELD_kCOWLES,		UNIHAN_TABLE_kCOWLES},
    {UNIHAN_FIELD_kDAEJAWEON,		UNIHAN_TABLE_kDAEJAWEON},
    {UNIHAN_FIELD_kDEFINITION,		UNIHAN_TABLE_kDEFINITION},
    {UNIHAN_FIELD_kEACC,		UNIHAN_TABLE_kEACC},
    {UNIHAN_FIELD_kFENN,		UNIHAN_TABLE_kFENN},
    {UNIHAN_FIELD_kFENNINDEX,		UNIHAN_TABLE_kFENNINDEX},
    {UNIHAN_FIELD_kFOURCORNERCODE,	UNIHAN_TABLE_kFOURCORNERCODE},
    {UNIHAN_FIELD_kFREQUENCY,		UNIHAN_TABLE_kFREQUENCY},
    {UNIHAN_FIELD_kGB0,			UNIHAN_TABLE_kGB0},
    {UNIHAN_FIELD_kGB1,			UNIHAN_TABLE_kGB1},
    {UNIHAN_FIELD_kGB3,			UNIHAN_TABLE_kGB3},
    {UNIHAN_FIELD_kGB5,			UNIHAN_TABLE_kGB5},
    {UNIHAN_FIELD_kGB7,			UNIHAN_TABLE_kGB7},
    {UNIHAN_FIELD_kGB8,			UNIHAN_TABLE_kGB8},
    {UNIHAN_FIELD_kGRADELEVEL,		UNIHAN_TABLE_kGRADELEVEL},
    {UNIHAN_FIELD_kGSR,			UNIHAN_TABLE_kGSR},
    {UNIHAN_FIELD_kHANGUL,		UNIHAN_TABLE_kHANGUL},
    {UNIHAN_FIELD_kHANYU,		UNIHAN_TABLE_kHANYU},
    {UNIHAN_FIELD_kHANYUPINLU,		UNIHAN_TABLE_kHANYUPINLU},
    {UNIHAN_FIELD_kHDZRADBREAK,		UNIHAN_TABLE_kHDZRADBREAK},
    {UNIHAN_FIELD_kHKGLYPH,		UNIHAN_TABLE_kHKGLYPH},
    {UNIHAN_FIELD_kHKSCS,		UNIHAN_TABLE_kHKSCS},
    {UNIHAN_FIELD_kIBMJAPAN,		UNIHAN_TABLE_kIBMJAPAN},
    {UNIHAN_FIELD_kIICORE,		UNIHAN_TABLE_kIICORE},
    {UNIHAN_FIELD_kIRGDAEJAWEON,	UNIHAN_TABLE_kIRGDAEJAWEON},
    {UNIHAN_FIELD_kIRGDAIKANWAZITEN,	UNIHAN_TABLE_kIRGDAIKANWAZITEN},
    {UNIHAN_FIELD_kIRGHANYUDAZIDIAN,	UNIHAN_TABLE_kIRGHANYUDAZIDIAN},
    {UNIHAN_FIELD_kIRGKANGXI,		UNIHAN_TABLE_kIRGKANGXI},
    {UNIHAN_FIELD_kIRG_GSOURCE,		UNIHAN_TABLE_IRG_GSOURCE},
    {UNIHAN_FIELD_kIRG_HSOURCE,		UNIHAN_TABLE_IRG_HSOURCE},
    {UNIHAN_FIELD_kIRG_JSOURCE,		UNIHAN_TABLE_IRG_JGSOURCE},
    {UNIHAN_FIELD_kIRG_KPSOURCE,	UNIHAN_TABLE_IRG_KPSOURCE},
    {UNIHAN_FIELD_kIRG_KSOURCE,		UNIHAN_TABLE_IRG_KSOURCE},
    {UNIHAN_FIELD_kIRG_TSOURCE,		UNIHAN_TABLE_IRG_TSOURCE},
    {UNIHAN_FIELD_kIRG_USOURCE,		UNIHAN_TABLE_IRG_USOURCE},
    {UNIHAN_FIELD_kIRG_VSOURCE,		UNIHAN_TABLE_IRG_VSOURCE},
    {UNIHAN_FIELD_kJAPANESEKUN,		UNIHAN_TABLE_kJAPANESEKUN},
    {UNIHAN_FIELD_kJAPANESEON,		UNIHAN_TABLE_kJAPANESEON},
    {UNIHAN_FIELD_kJIS0213,		UNIHAN_TABLE_kJIS0213},
    {UNIHAN_FIELD_kJIS0,		UNIHAN_TABLE_kJIS0},
    {UNIHAN_FIELD_kJIS1,		UNIHAN_TABLE_kJIS1},
    {UNIHAN_FIELD_kKANGXI,		UNIHAN_TABLE_kKANGXI},
    {UNIHAN_FIELD_kKARLGREN,		UNIHAN_TABLE_kKARLGREN},
    {UNIHAN_FIELD_kKOREAN,		UNIHAN_TABLE_kKOREAN},
    {UNIHAN_FIELD_kKPS0,		UNIHAN_TABLE_kKPS0},
    {UNIHAN_FIELD_kKPS1,		UNIHAN_TABLE_kKPS1},
    {UNIHAN_FIELD_kKSC0,		UNIHAN_TABLE_kKSC0},
    {UNIHAN_FIELD_kKSC1,		UNIHAN_TABLE_kKSC1},
    {UNIHAN_FIELD_kLAU,			UNIHAN_TABLE_kLAU},
    {UNIHAN_FIELD_kMAINLANDTELEGRAPH,	UNIHAN_TABLE_kMAINLANDTELEGRAPH},
    {UNIHAN_FIELD_kMANDARIN,		UNIHAN_TABLE_kMANDARIN},
    {UNIHAN_FIELD_kMATTHEWS,		UNIHAN_TABLE_kMATTHEWS},
    {UNIHAN_FIELD_kMEYERWEMPE,		UNIHAN_TABLE_kMEYERWEMPE},
    {UNIHAN_FIELD_kMOROHASHI,		UNIHAN_TABLE_kMOROHASHI},
    {UNIHAN_FIELD_kNELSON,		UNIHAN_TABLE_kNELSON},
    {UNIHAN_FIELD_kOTHERNUMERIC,	UNIHAN_TABLE_kOTHERNUMERIC},
    {UNIHAN_FIELD_kPHONETIC,		UNIHAN_TABLE_kPHONETIC},
    {UNIHAN_FIELD_kPRIMARYNUMERIC,	UNIHAN_TABLE_kPRIMARYNUMERIC},
    {UNIHAN_FIELD_kPSEUDOGB1,		UNIHAN_TABLE_kPSEUDOGB1},
    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6,	UNIHAN_TABLE_kRSADOBE_JAPAN1_6},
    {UNIHAN_FIELD_kRSJAPANESE,		UNIHAN_TABLE_kRSJAPANESE},
    {UNIHAN_FIELD_kRSKANGXI,		UNIHAN_TABLE_kRSKANGXI},
    {UNIHAN_FIELD_kRSKANWA,		UNIHAN_TABLE_kRSKANWA},
    {UNIHAN_FIELD_kRSKOREAN,		UNIHAN_TABLE_kRSKOREAN},
    {UNIHAN_FIELD_kRSUNICODE,		UNIHAN_TABLE_kRSUNICODE},
    {UNIHAN_FIELD_kSBGY,		UNIHAN_TABLE_kSBGY},
    {UNIHAN_FIELD_kSEMANTICVARIANT,	UNIHAN_TABLE_kSEMANTICVARIANT},
    {UNIHAN_FIELD_kSIMPLIFIEDVARIANT,	UNIHAN_TABLE_kSIMPLIFIEDVARIANT},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT},
    {UNIHAN_FIELD_kTAIWANTELEGRAPH,	UNIHAN_TABLE_kTAIWANTELEGRAPH},
    {UNIHAN_FIELD_kTANG,		UNIHAN_TABLE_kTANG},
    {UNIHAN_FIELD_kTOTALSTROKES,	UNIHAN_TABLE_kTOTALSTROKES},
    {UNIHAN_FIELD_kTRADITIONALVARIANT,	UNIHAN_TABLE_kTRADITIONALVARIANT},
    {UNIHAN_FIELD_kVIETNAMESE,		UNIHAN_TABLE_kVIETNAMESE},
    {UNIHAN_FIELD_kXEROX,		UNIHAN_TABLE_kXEROX},
    {UNIHAN_FIELD_kXHC1983,		UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_kZVARIANT,		UNIHAN_TABLE_kZVARIANT},

    {UNIHAN_FIELD_DICT_PAGE,		UNIHAN_TABLE_kKANGXI},
    {UNIHAN_FIELD_DICT_POSITION,	UNIHAN_TABLE_kKANGXI},
    {UNIHAN_FIELD_DICT_VIRTUAL,	UNIHAN_TABLE_kKANGXI},


    {UNIHAN_FIELD_PINYIN,		UNIHAN_TABLE_kMANDARIN},
    {UNIHAN_FIELD_PINYIN_BASE,		UNIHAN_TABLE_kMANDARIN},
    {UNIHAN_FIELD_PINYIN_TONE,		UNIHAN_TABLE_kMANDARIN},
    {UNIHAN_FIELD_PINYIN_FREQ,		UNIHAN_TABLE_kHANYUPINLU},
    {UNIHAN_FIELD_ZHUYIN,		UNIHAN_TABLE_kMANDARIN},

    {UNIHAN_FIELD_ADOBE_CID_CV,		UNIHAN_TABLE_kRSADOBE_JAPAN1_6},
    {UNIHAN_FIELD_ADOBE_CID,		UNIHAN_TABLE_kRSADOBE_JAPAN1_6},
    {UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT,	UNIHAN_TABLE_kRSADOBE_JAPAN1_6},

    {UNIHAN_FIELD_RADICAL_INDEX,		UNIHAN_TABLE_kRSUNICODE},
    {UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,	UNIHAN_TABLE_kRSUNICODE},
    {UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,	UNIHAN_TABLE_kRSUNICODE},

    {UNIHAN_FIELD_FROM_DICT,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_T,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_B,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_Z,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_ZVARIANT_SOURCE,	UNIHAN_TABLE_kZVARIANT_EXTRA},

    {UNIHAN_FIELD_FREQ_RANK,		UNIHAN_TABLE_kMANDARIN},
    {UNIHAN_FIELD_SCALAR_VALUE,		UNIHAN_TABLE_kMANDARIN},
    {UNIHAN_FIELD_UTF8,			UNIHAN_TABLE_kMANDARIN},


    {UNIHAN_INVALID_FIELD,  UNIHAN_INVALID_TABLE},
};

typedef struct{
    UnihanField field;
    gchar *value;
} UnihanFieldValuePair;



const UnihanFieldValuePair FIELD_DEFAULT_VALUES[]={
    {UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,"0"},
    {UNIHAN_FIELD_SEMANTIC_T,"0"},
    {UNIHAN_FIELD_SEMANTIC_B,"0"},
    {UNIHAN_FIELD_SEMANTIC_Z,"0"},
    {UNIHAN_INVALID_FIELD,NULL}
};

const UnihanFieldValuePair FIELD_BOOLEAN_TRUE_DISPLAY_VALUES[]={
    {UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,"'"},
    {UNIHAN_FIELD_SEMANTIC_T,"T"},
    {UNIHAN_FIELD_SEMANTIC_B,"B"},
    {UNIHAN_FIELD_SEMANTIC_Z,"Z"},
    {UNIHAN_INVALID_FIELD,NULL}
};


typedef struct{
    UnihanField pseudoField;
    UnihanTable table;
    gchar *importPattern;
    UnihanField *fields;
    gchar **storeFormats;
} UnihanImportData;

/*
 * Most of the Unihan tag value can be import using this.
 * Exceptions:
 * 1. kSementicVariant
 *    Need to use search/replace pattern s/(U\+[[:xdigit:]]*)<([^,]*)(.*)/$1$3/ 
 *    until nothing match.
 * 2. kSpecializedSemanticVariant
 *    Same as kSementicVariant
 * 3. kXHC1983
 *    Convert the pinyin tone to trailing number.
 */
const UnihanImportData PSEUDOFIELD_IMPORT_DATA[]={
    {UNIHAN_FIELD_kHANYUPINLU, UNIHAN_TABLE_kHANYUPINLU, 
	PINYIN_REGEX "\(([[:digit:]]*)\)"},
        {UNIHAN_FIELD_PINYIN_BASE, UNIHAN_FIELD_PINYIN_TONE, UNIHAN_FIELD_PINYIN_FREQ,
	    UNIHAN_INVALID_FIELD},
	{PINYIN_PATTERN_SUBSTITUTE, PINYIN_TONE_PATTERN_SUBSTITUTE, "$15", NULL}
    },

    {UNIHAN_FIELD_kIRG_GSOURCE, UNIHAN_TABLE_IRG_GSOURCE,
	"[[:alnum:]]*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,  UNIHAN_INVALID_FIELD},
	{"G$0", NULL}
    },
    {UNIHAN_FIELD_kIRG_GSOURCE, UNIHAN_TABLE_IRG_GSOURCE_EXTRA,
	"([[:alnum:]]*)-(.*)",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME, UNIHAN_FIELD_IRG_SOURCE_MAPPING, UNIHAN_INVALID_FIELD},
	{"G$1","$2", NULL}
    },
    {UNIHAN_FIELD_kIRG_HSOURCE, UNIHAN_TABLE_IRG_HSOURCE,
	".*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,  UNIHAN_INVALID_FIELD},
	{"H", NULL}
    },
    {UNIHAN_FIELD_kIRG_HSOURCE, UNIHAN_TABLE_IRG_HSOURCE_EXTRA,
	".*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME, UNIHAN_FIELD_IRG_SOURCE_MAPPING, UNIHAN_INVALID_FIELD},
	{"H","$0", NULL}
    },
    {UNIHAN_FIELD_kIRG_JSOURCE, UNIHAN_TABLE_IRG_JSOURCE,
	"[[:alnum:]]*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,  UNIHAN_INVALID_FIELD},
	{"J$0", NULL}
    },
    {UNIHAN_FIELD_kIRG_JSOURCE, UNIHAN_TABLE_IRG_JSOURCE_EXTRA,
	"([[:alnum:]]*)-(.*)",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME, UNIHAN_FIELD_IRG_SOURCE_MAPPING, UNIHAN_INVALID_FIELD},
	{"J$1","$2", NULL}
    },
    {UNIHAN_FIELD_kIRG_KPSOURCE, UNIHAN_TABLE_IRG_KPSOURCE,
	"[[:alnum:]]*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,  UNIHAN_INVALID_FIELD},
	{"$0", NULL}
    },
    {UNIHAN_FIELD_kIRG_KPSOURCE, UNIHAN_TABLE_IRG_KPSOURCE_EXTRA,
	"([[:alnum:]]*)-(.*)",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME, UNIHAN_FIELD_IRG_SOURCE_MAPPING, UNIHAN_INVALID_FIELD},
	{"$1","$2", NULL}
    },
    {UNIHAN_FIELD_kIRG_KSOURCE, UNIHAN_TABLE_IRG_KSOURCE,
	"[[:alnum:]]*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,  UNIHAN_INVALID_FIELD},
	{"K$0", NULL}
    },
    {UNIHAN_FIELD_kIRG_KSOURCE, UNIHAN_TABLE_IRG_KSOURCE_EXTRA,
	"([[:alnum:]]*)-(.*)",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME, UNIHAN_FIELD_IRG_SOURCE_MAPPING, UNIHAN_INVALID_FIELD},
	{"K$1","$2", NULL}
    },
    {UNIHAN_FIELD_kIRG_TSOURCE, UNIHAN_TABLE_IRG_TSOURCE,
	"[[:alnum:]]*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,  UNIHAN_INVALID_FIELD},
	{"T$0", NULL}
    },
    {UNIHAN_FIELD_kIRG_TSOURCE, UNIHAN_TABLE_IRG_TSOURCE_EXTRA,
	"([[:alnum:]]*)-(.*)",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME, UNIHAN_FIELD_IRG_SOURCE_MAPPING, UNIHAN_INVALID_FIELD},
	{"T$1","$2", NULL}
    },
    {UNIHAN_FIELD_kIRG_USOURCE, UNIHAN_TABLE_IRG_USOURCE,
	".*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,  UNIHAN_INVALID_FIELD},
	{"U", NULL}
    },
    {UNIHAN_FIELD_kIRG_USOURCE, UNIHAN_TABLE_IRG_USOURCE_EXTRA,
	".*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME, UNIHAN_FIELD_IRG_SOURCE_MAPPING, UNIHAN_INVALID_FIELD},
	{"U","$0", NULL}
    },
    {UNIHAN_FIELD_kIRG_VSOURCE, UNIHAN_TABLE_IRG_VSOURCE,
	"[[:alnum:]]*",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,  UNIHAN_INVALID_FIELD},
	{"V", NULL}
    },
    {UNIHAN_FIELD_kIRG_VSOURCE, UNIHAN_TABLE_IRG_VSOURCE_EXTRA,
	"([[:alnum:]]*)-(.*)",
	{UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME, UNIHAN_FIELD_IRG_SOURCE_MAPPING, UNIHAN_INVALID_FIELD},
	{"V$1","$2", NULL}
    },

    {UNIHAN_FIELD_kIRGKANGXI, UNIHAN_TABLE_kIRGKANGXI,
	"([[:digit:]]*)\\.([[:digit:]]*)([01])",
	{UNIHAN_FIELD_DICT_PAGE, UNIHAN_FIELD_DICT_POSITION, UNIHAN_FIELD_DICT_VIRTUAL
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$3", NULL}
    },
    {UNIHAN_FIELD_kKANGXI, UNIHAN_TABLE_kKANGXI,
	"([[:digit:]]*)\\.([[:digit:]]*)([01])",
	{UNIHAN_FIELD_DICT_PAGE, UNIHAN_FIELD_DICT_POSITION, UNIHAN_FIELD_DICT_VIRTUAL
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$3", NULL}
    },

    {UNIHAN_FIELD_kMANDARIN,	UNIHAN_TABLE_kMANDARIN,
	PINYIN_REGEX,
	{UNIHAN_FIELD_PINYIN_BASE, UNIHAN_FIELD_PINYIN_TONE, UNIHAN_FIELD_FREQ_RANK,
	    UNIHAN_INVALID_FIELD},
	{PINYIN_PATTERN_SUBSTITUTE, PINYIN_TONE_PATTERN_SUBSTITUTE,"$+0", NULL}
    },

    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6, UNIHAN_TABLE_kRSADOBE_JAPAN1_6,
	"([CV])\\+([[:digit:]]+)\\+([[:digit:]]+)\\.([[:digit:]]+)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_ADOBE_CID_CV, UNIHAN_FIELD_ADOBE_CID, UNIHAN_FIELD_RADICAL_INDEX,
	    UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT, UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, UNIHAN_INVALID_FIELD},
	{"$1","$2","$3", "$4", "$5", NULL}
    },
    {UNIHAN_FIELD_kRSJAPANESE, UNIHAN_TABLE_kRSJAPANESE,
	"([[:digit:]]+)('?)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_RADICAL_INDEX, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$N2{1,0}","$3", NULL}
    },
    {UNIHAN_FIELD_kRSKANGXI, UNIHAN_TABLE_kRSKANGXI,
	"([[:digit:]]+)('?)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_RADICAL_INDEX, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$N2{1,0}","$3", NULL}
    },
    {UNIHAN_FIELD_kRSKANWA, UNIHAN_TABLE_kRSKANWA, 
	"([[:digit:]]+)('?)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_RADICAL_INDEX, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$N2{1,0}","$3", NULL}
    },
    {UNIHAN_FIELD_kRSKOREAN, UNIHAN_TABLE_kRSKOREAN, 
	"([[:digit:]]+)('?)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_RADICAL_INDEX, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$N2{1,0}","$3", NULL}
    },
    {UNIHAN_FIELD_kRSUNICODE, UNIHAN_TABLE_kRSUNICODE, 
	"([[:digit:]]+)('?)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_RADICAL_INDEX, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$N2{1,0}","$3", NULL}
    },
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT, 
	"U\\+[[:xdigit:]]*",
	{UNIHAN_FIELD_VARIANT_CODE,  UNIHAN_INVALID_FIELD},
	{"$0", NULL}
    },
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA,
	"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*):(T?)(B?)(Z?)",
	{UNIHAN_FIELD_VARIANT_CODE, UNIHAN_FIELD_SERIAL_NO_JOIN, UNIHAN_FIELD_FROM_DICT,
	    UNIHAN_FIELD_SEMANTIC_T, UNIHAN_FIELD_SEMANTIC_B, UNIHAN_FIELD_SEMANTIC_Z,
	    UNIHAN_INVALID_FIELD},
	{"$1", "$+0", "$2","$N3{1,0}","$N4{1,0}","$N5{1,0}", NULL}
    },

    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT, 
	"U\\+[[:xdigit:]]*",
	{UNIHAN_FIELD_VARIANT_CODE,  UNIHAN_INVALID_FIELD},
	{"$0", NULL}
    },
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA,
	"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*):(T?)(B?)(Z?)",
	{UNIHAN_FIELD_VARIANT_CODE, UNIHAN_FIELD_SERIAL_NO_JOIN, UNIHAN_FIELD_FROM_DICT,
	    UNIHAN_FIELD_SEMANTIC_T, UNIHAN_FIELD_SEMANTIC_B, UNIHAN_FIELD_SEMANTIC_Z,
	    UNIHAN_INVALID_FIELD},
	{"$1", "$+0", "$2","$N3{1,0}","$N4{1,0}","$N5{1,0}", NULL}
    },
    {UNIHAN_FIELD_kXHC1983, UNIHAN_TABLE_kXHC1983, 
	"([[:digit:]]{4})\\.([[:digit:]]{2})([[:digit:]])(\*)?[^[:space:]]*:" PINYIN_REGEX,
	{UNIHAN_FIELD_DICT_PAGE, UNIHAN_FIELD_DICT_POSITION, UNIHAN_FIELD_DICT_VARIANT_SERIAL,
	    UNIHAN_FIELD_DICT_UNENCODED, UNIHAN_FIELD_DICT_SERIAL_NO_JOIN,
	    UNIHAN_FIELD_PINYIN_BASE, UNIHAN_FIELD_PINYIN_TONE, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$3","$N4{1,0}", "$+0", 
	    "$N14{1}$N15{2}$N16{3}$N17{4}$E13{5}" NULL}
    },

    {UNIHAN_FIELD_kZVARIANT, UNIHAN_TABLE_kZVARIANT, 
	"U\\+[[:xdigit:]]*",
	{UNIHAN_FIELD_VARIANT_CODE,  UNIHAN_INVALID_FIELD},
	{"$0", NULL}
    },
    {UNIHAN_FIELD_kZVARIANT, UNIHAN_TABLE_kZVARIANT_EXTRA, 
	"(U\\+[[:xdigit:]]*):(k[[:alpha:]]*)",
	{UNIHAN_FIELD_VARIANT_CODE, UNIHAN_FIELD_ZVARIANT_SOURCE, UNIHAN_INVALID_FIELD},
	{"$1","$2", NULL}
    },

    {UNIHAN_INVALID_FIELD,  UNIHAN_INVALID_TABLE ,
	NULL,
	{NULL},
	{NULL}
    }
};

typedef struct{
    UnihanField field;
    UnihanTable table;
    gchar *regex_pattern;
    gchar *eval_str;
} UnihanImportData_Post;

UnihanImportData_Post PSEUDOFIELD_IMPORT_DATA_POST[]={
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA,
	"(U\+[[:xdigit:]]*)<(k[[:alpha:]]*:?T?B?Z?),(.*)", "$1<$3"},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA,
	"(U\+[[:xdigit:]]*)<(k[[:alpha:]]*:?T?B?Z?),(.*)", "$1<$3"},
    {UNIHAN_FIELD_kXHC1983, UNIHAN_TABLE_kXHC1983,
	"([[:digit:]\.]{8}),([^:]*):(.*)", "$2<$3"},
    {UNIHAN_INVALID_FIELD, UNIHAN_INVALID_TABLE,
	NULL,NULL},
};



