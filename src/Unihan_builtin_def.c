/** 
 * @file Unihan_builtin_def.c
 * @brief Data structures  for builtin tables and fields only.
 * 
 * This file contains the data structures 
 *  which only deal for builtin tables and fields.
 */

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

    {UNIHAN_FIELD_DICT_PAGE_0_PADDED_4,		UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_DICT_POSITION,		UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_DICT_VARIANT_SERIAL,		UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_DICT_UNENCODED,		UNIHAN_TABLE_kXHC1983},

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
    UnihanField field,
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
	"([^[:digit:]]*)([[:digit:]])\(([[:digit:]]*)\)"},
        {UNIHAN_FIELD_PINYIN_BASE, UNIHAN_FIELD_PINYIN_TONE, UNIHAN_FIELD_PINYIN_FREQ,
	    UNIHAN_INVALID_FIELD},
	{"$1", "$2", "$3", NULL}
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
	"([[:digit:]]*)\\.([[:digit:]])*([01])",
	{UNIHAN_FIELD_DICT_PAGE, UNIHAN_FIELD_DICT_POSITION, UNIHAN_FIELD_DICT_VIRTUAL
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$3", NULL}
    },
    {UNIHAN_FIELD_kKANGXI, UNIHAN_TABLE_kKANGXI,
	"([[:digit:]]*)\\.([[:digit:]])*([01])",
	{UNIHAN_FIELD_DICT_PAGE, UNIHAN_FIELD_DICT_POSITION, UNIHAN_FIELD_DICT_VIRTUAL
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$3", NULL}
    },

    {UNIHAN_FIELD_kMANDARIN,	UNIHAN_TABLE_kMANDARIN,
	"([^[:digit:]]*)([1-5])",
	{UNIHAN_FIELD_PINYIN_BASE, UNIHAN_FIELD_PINYIN_TONE, UNIHAN_FIELD_FREQ_RANK,
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$+", NULL}
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
	{"$1","$2","$3", NULL}
    },
    {UNIHAN_FIELD_kRSKANGXI, UNIHAN_TABLE_kRSKANGXI,
	"([[:digit:]]+)('?)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_RADICAL_INDEX, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$3", NULL}
    },
    {UNIHAN_FIELD_kRSKANWA, UNIHAN_TABLE_kRSKANWA, 
	"([[:digit:]]+)('?)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_RADICAL_INDEX, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$3", NULL}
    },
    {UNIHAN_FIELD_kRSKOREAN, UNIHAN_TABLE_kRSKOREAN, 
	"([[:digit:]]+)('?)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_RADICAL_INDEX, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$3", NULL}
    },
    {UNIHAN_FIELD_kRSUNICODE, UNIHAN_TABLE_kRSUNICODE, 
	"([[:digit:]]+)('?)\\.([[:digit:]]+)",
	{UNIHAN_FIELD_RADICAL_INDEX, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT, 
	    UNIHAN_INVALID_FIELD},
	{"$1","$2","$3", NULL}
    },
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT, 
	"U+[[:xdigit:]]*",
	{UNIHAN_FIELD_VARIANT_CODE,  UNIHAN_INVALID_FIELD},
	{"$0", NULL}
    },
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA,
	"(U+[[:xdigit:]]*)<(k[[:alpha:]]*):(T?)(B?)(Z?)",
	{UNIHAN_FIELD_VARIANT_CODE, UNIHAN_FIELD_SERIAL_NO_JOIN, UNIHAN_FIELD_FROM_DICT,
	    UNIHAN_FIELD_SEMANTIC_T, UNIHAN_FIELD_SEMANTIC_B, UNIHAN_FIELD_SEMANTIC_Z,
	    UNIHAN_INVALID_FIELD},
	{"$1", "$+", "$2","$3","$4","$5", NULL}
    },

    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT, 
	"U+[[:xdigit:]]*",
	{UNIHAN_FIELD_VARIANT_CODE,  UNIHAN_INVALID_FIELD},
	{"$0", NULL}
    },
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA,
	"(U+[[:xdigit:]]*)<(k[[:alpha:]]*):(T?)(B?)(Z?)",
	{UNIHAN_FIELD_VARIANT_CODE, UNIHAN_FIELD_SERIAL_NO_JOIN, UNIHAN_FIELD_FROM_DICT,
	    UNIHAN_FIELD_SEMANTIC_T, UNIHAN_FIELD_SEMANTIC_B, UNIHAN_FIELD_SEMANTIC_Z,
	    UNIHAN_INVALID_FIELD},
	{"$1", "$+", "$2","$3","$4","$5", NULL}
    },
    {UNIHAN_FIELD_kXHC1983, UNIHAN_TABLE_kZVARIANT, 
    	"U+[[:xdigit:]]*",
    	{UNIHAN_FIELD_VARIANT_CODE,  UNIHAN_INVALID_FIELD},
    	{"$0", NULL}
    },

    {UNIHAN_FIELD_kZVARIANT, UNIHAN_TABLE_kZVARIANT, 
	"U+[[:xdigit:]]*",
	{UNIHAN_FIELD_VARIANT_CODE,  UNIHAN_INVALID_FIELD},
	{"$0", NULL}
    },
    {UNIHAN_FIELD_kZVARIANT, UNIHAN_TABLE_kZVARIANT_EXTRA, 
	"(U+[[:xdigit:]]*):(k[[:alpha:]]*)",
	{UNIHAN_FIELD_VARIANT_CODE, UNIHAN_FIELD_ZVARIANT_SOURCE, UNIHAN_INVALID_FIELD},
	{"$1","$2", NULL}
    },

    {UNIHAN_INVALID_FIELD,  UNIHAN_INVALID_TABLE ,
	"",
	{NULL},
	{NULL}
    }
};

typedef struct{
    UnihanField field;
    UnihanTable refTable;
    UnihanField refField;
} UnihanFieldTableReferenceTableField;


typedef struct{
    UnihanField field;
    UnihanTable refTable;
    UnihanField refField;
} UnihanReferenceTableField;


const UnihanReferenceTableField PSEUDOFIELDS_REQUIRED[]={
}


const UNIHAN_NOINDEX_FIELDS[]={
    UNIHAN_FIELD_kACCOUNTINGNUMERIC,
    UNIHAN_FIELD_kDEFINITION,
    UNIHAN_FIELD_kOTHERNUMERIC,
    UNIHAN_FIELD_kPRIMARYNUMERIC,
    UNIHAN_FIELD_DICT_POSITION,
    UNIHAN_FIELD_DICT_VIRTUAL,

    UNIHAN_INVALID_FIELD
};


