/** 
 * @file Unihan_builtin.c
 * @brief Data structures and functions for builtin tables and fields only.
 * 
 * This file contains the data structures and functions 
 *  which only deal for builtin tables and fields.
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

#include <glib.h>
#include <sqlite3.h>
#include "Unihan.h"

#define MAX_BUFFER_SIZE 2000
#define UNIHAN_FIELD_ARRAY_MAX_LEN 200
#define UNIHAN_TABLE_ARRAY_MAX_LEN 800


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

    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kSEMANTICVARIANT},
    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kSIMPLIFIEDVARIANT},
    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT},

    {UNIHAN_FIELD_kTAIWANTELEGRAPH,	UNIHAN_TABLE_kTAIWANTELEGRAPH},
    {UNIHAN_FIELD_kTANG,		UNIHAN_TABLE_kTANG},
    {UNIHAN_FIELD_kTOTALSTROKES,	UNIHAN_TABLE_kTOTALSTROKES},

    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kTRADITIONALVARIANT},

    {UNIHAN_FIELD_kVIETNAMESE,		UNIHAN_TABLE_kVIETNAMESE},
    {UNIHAN_FIELD_kXEROX,		UNIHAN_TABLE_kXEROX},
    {UNIHAN_FIELD_kXHC1983,		UNIHAN_TABLE_kXHC1983},
    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kZVARIANT},

    {UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,	UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,	UNIHAN_TABLE_IRG_SOURCE_EXTRA},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,		UNIHAN_TABLE_IRG_SOURCE_EXTRA},


    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kSIMPLIFIEDVARIANT_EXTRA},
    {UNIHAN_FIELD_FROM_DICT,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_T,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_B,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SEMANTIC_Z,		UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA},

    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_FROM_DICT,		UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SPECIALIZEDSEMANTIC_T,	UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SPECIALIZEDSEMANTIC_B,	UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},
    {UNIHAN_FIELD_SPECIALIZEDSEMANTIC_Z,	UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA},


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
    {UNIHAN_FIELD_kIRG_GSOURCE,		UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_HSOURCE,		UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_JSOURCE,		UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_KPSOURCE,	UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_KSOURCE,		UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_TSOURCE,		UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_USOURCE,		UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_kIRG_VSOURCE,		UNIHAN_TABLE_IRG_SOURCE},
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

    {UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,	UNIHAN_TABLE_IRG_SOURCE},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,		UNIHAN_TABLE_IRG_SOURCE_EXTRA},

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

    {UNIHAN_FIELD_VARIANT_CODE,		UNIHAN_TABLE_kSEMANTICVARIANT},

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
    UnihanTable refTable;
    UnihanField refField;
} UnihanReferenceTableField;


const UnihanReferenceTableField PSEUDOFIELDS_REQUIRED[]={
    {UNIHAN_FIELD_kHANYUPINLU, UNIHAN_TABLE_kHANYUPINLU, UNIHAN_FIELD_PINYIN_BASE},
    {UNIHAN_FIELD_kHANYUPINLU, UNIHAN_TABLE_kHANYUPINLU, UNIHAN_FIELD_PINYIN_TONE},
    {UNIHAN_FIELD_kHANYUPINLU, UNIHAN_TABLE_kHANYUPINLU, UNIHAN_FIELD_PINYIN_FREQ},

    {UNIHAN_FIELD_kIRG_GSOURCE, UNIHAN_TABLE_IRG_SOURCE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME },
    {UNIHAN_FIELD_kIRG_GSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME},
    {UNIHAN_FIELD_kIRG_GSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_HSOURCE, UNIHAN_TABLE_IRG_SOURCE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME },
    {UNIHAN_FIELD_kIRG_HSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME},
    {UNIHAN_FIELD_kIRG_HSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_JSOURCE, UNIHAN_TABLE_IRG_SOURCE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME },
    {UNIHAN_FIELD_kIRG_JSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME},
    {UNIHAN_FIELD_kIRG_JSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_KPSOURCE,  UNIHAN_TABLE_IRG_SOURCE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME },
    {UNIHAN_FIELD_kIRG_KPSOURCE,  UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME},
    {UNIHAN_FIELD_kIRG_KPSOURCE,  UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_KSOURCE, UNIHAN_TABLE_IRG_SOURCE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME },
    {UNIHAN_FIELD_kIRG_KSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME},
    {UNIHAN_FIELD_kIRG_KSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_TSOURCE, UNIHAN_TABLE_IRG_SOURCE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME },
    {UNIHAN_FIELD_kIRG_TSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME},
    {UNIHAN_FIELD_kIRG_TSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_USOURCE, UNIHAN_TABLE_IRG_SOURCE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME },
    {UNIHAN_FIELD_kIRG_USOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME},
    {UNIHAN_FIELD_kIRG_USOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_MAPPING},
    {UNIHAN_FIELD_kIRG_VSOURCE, UNIHAN_TABLE_IRG_SOURCE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME },
    {UNIHAN_FIELD_kIRG_VSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME},
    {UNIHAN_FIELD_kIRG_VSOURCE, UNIHAN_TABLE_IRG_SOURCE_EXTRA, UNIHAN_FIELD_IRG_SOURCE_MAPPING},

    {UNIHAN_FIELD_kIRGKANGXI, UNIHAN_TABLE_kIRGKANGXI, UNIHAN_FIELD_DICT_PAGE},
    {UNIHAN_FIELD_kIRGKANGXI, UNIHAN_TABLE_kIRGKANGXI, UNIHAN_FIELD_DICT_POSITION},
    {UNIHAN_FIELD_kIRGKANGXI, UNIHAN_TABLE_kIRGKANGXI, UNIHAN_FIELD_DICT_VIRTUAL},

    {UNIHAN_FIELD_kKANGXI, UNIHAN_TABLE_kKANGXI, UNIHAN_FIELD_DICT_PAGE},
    {UNIHAN_FIELD_kKANGXI, UNIHAN_TABLE_kKANGXI, UNIHAN_FIELD_DICT_POSITION},
    {UNIHAN_FIELD_kKANGXI, UNIHAN_TABLE_kKANGXI, UNIHAN_FIELD_DICT_VIRTUAL},

    {UNIHAN_FIELD_kMANDARIN,	UNIHAN_TABLE_kMANDARIN, UNIHAN_FIELD_PINYIN_BASE},
    {UNIHAN_FIELD_kMANDARIN,	UNIHAN_TABLE_kMANDARIN, UNIHAN_FIELD_PINYIN_TONE},

    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6, UNIHAN_TABLE_kRSADOBE_JAPAN1_6, UNIHAN_FIELD_ADOBE_CID_CV},
    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6, UNIHAN_TABLE_kRSADOBE_JAPAN1_6, UNIHAN_FIELD_ADOBE_CID},
    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6, UNIHAN_TABLE_kRSADOBE_JAPAN1_6, UNIHAN_FIELD_RADICAL_INDEX},
    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6, UNIHAN_TABLE_kRSADOBE_JAPAN1_6, UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT},
    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6, UNIHAN_TABLE_kRSADOBE_JAPAN1_6, UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT},
    {UNIHAN_FIELD_kRSJAPANESE, UNIHAN_TABLE_kRSJAPANESE, UNIHAN_FIELD_RADICAL_INDEX},
    {UNIHAN_FIELD_kRSJAPANESE, UNIHAN_TABLE_kRSJAPANESE, UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT},
    {UNIHAN_FIELD_kRSJAPANESE, UNIHAN_TABLE_kRSJAPANESE, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED},
    {UNIHAN_FIELD_kRSKANGXI, UNIHAN_TABLE_kRSKANGXI, UNIHAN_FIELD_RADICAL_INDEX},
    {UNIHAN_FIELD_kRSKANGXI, UNIHAN_TABLE_kRSKANGXI, UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT},
    {UNIHAN_FIELD_kRSKANGXI, UNIHAN_TABLE_kRSKANGXI, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED},
    {UNIHAN_FIELD_kRSKANWA, UNIHAN_TABLE_kRSKANWA, UNIHAN_FIELD_RADICAL_INDEX},
    {UNIHAN_FIELD_kRSKANWA, UNIHAN_TABLE_kRSKANWA, UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT},
    {UNIHAN_FIELD_kRSKANWA, UNIHAN_TABLE_kRSKANWA, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED},
    {UNIHAN_FIELD_kRSKOREAN, UNIHAN_TABLE_kRSKOREAN, UNIHAN_FIELD_RADICAL_INDEX},
    {UNIHAN_FIELD_kRSKOREAN, UNIHAN_TABLE_kRSKOREAN, UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT},
    {UNIHAN_FIELD_kRSKOREAN, UNIHAN_TABLE_kRSKOREAN, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED},
    {UNIHAN_FIELD_kRSUNICODE, UNIHAN_TABLE_kRSUNICODE, UNIHAN_FIELD_RADICAL_INDEX},
    {UNIHAN_FIELD_kRSUNICODE, UNIHAN_TABLE_kRSUNICODE, UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT},
    {UNIHAN_FIELD_kRSUNICODE, UNIHAN_TABLE_kRSUNICODE, UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED},

    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT, UNIHAN_FIELD_VARIANT_CODE},
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_VARIANT_CODE},
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_FROM_DICT},
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_SEMANTIC_T},
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_SEMANTIC_B},
    {UNIHAN_FIELD_kSEMANTICVARIANT, UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_SEMANTIC_Z},

    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_FIELD_VARIANT_CODE},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_VARIANT_CODE},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_FROM_DICT},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_SPECIALIZEDSEMANTIC_T},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_SPECIALIZEDSEMANTIC_B},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA, UNIHAN_FIELD_SPECIALIZEDSEMANTIC_Z},

    {UNIHAN_FIELD_kZVARIANT, UNIHAN_TABLE_kZVARIANT, UNIHAN_FIELD_VARIANT_CODE},
    {UNIHAN_FIELD_kZVARIANT, UNIHAN_TABLE_kZVARIANT_EXTRA, UNIHAN_FIELD_VARIANT_CODE},
    {UNIHAN_FIELD_kZVARIANT, UNIHAN_TABLE_kZVARIANT_EXTRA, UNIHAN_FIELD_ZVARIANT_SOURCE},

    
    {UNIHAN_FIELD_PINYIN,  UNIHAN_TABLE_kMANDARIN, UNIHAN_FIELD_PINYIN_BASE},
    {UNIHAN_FIELD_PINYIN,  UNIHAN_TABLE_kMANDARIN, UNIHAN_FIELD_PINYIN_TONE},
    {UNIHAN_FIELD_ZHUYIN,  UNIHAN_TABLE_kMANDARIN, UNIHAN_FIELD_PINYIN_BASE},
    {UNIHAN_FIELD_ZHUYIN,  UNIHAN_TABLE_kMANDARIN, UNIHAN_FIELD_PINYIN_TONE},

    {UNIHAN_FIELD_SCALAR_VALUE,    UNIHAN_TABLE_CODE, UNIHAN_FIELD_CODE},
    {UNIHAN_FIELD_UTF8,    UNIHAN_TABLE_CODE, UNIHAN_FIELD_CODE},


    {UNIHAN_INVALID_FIELD,  UNIHAN_INVALID_TABLE, UNIHAN_INVALID_FIELD},
};

const UNIHAN_NOINDEX_FIELDS[]={
    UNIHAN_FIELD_kACCOUNTINGNUMERIC,
    UNIHAN_FIELD_kDEFINITION,
    UNIHAN_FIELD_kOTHERNUMERIC,
    UNIHAN_FIELD_kPRIMARYNUMERIC,
    UNIHAN_FIELD_DICT_POSITION,
    UNIHAN_FIELD_DICT_VIRTUAL,

    UNIHAN_INVALID_FIELD
};


/*=========================================================
 * Functions
 */


UnihanTable unihanField_get_builtin_preferred_table(UnihanField field){
    int i;
    for(i=0;FIELD_PREFERRED_TABLES[i].field!=UNIHAN_INVALID_FIELD;i++){
	if (FIELD_PREFERRED_TABLES[i].field==field){
	    return FIELD_PREFERRED_TABLES[i].table;
	}
    }
    return UNIHAN_INVAILD_TABLE;
}

UnihanTable *unihanField_get_builtin_required_tables(UnihanField field){
    int i,counter=0;
    UnihanTable *tables=NEW_ARRAY_INSTANCES(UNIHAN_TABLE_ARRAY_MAX_LEN, UnihanTable);
    for(i=0;PSEUDOFIELD_REQUIRED_TABLES[i].field!=UNIHAN_INVALID_FIELD;i++){
	if (PSEUDOFIELD_REQUIRED_TABLES[i].field==field){
	    tables[counter++]=PSEUDOFIELD_REQUIRED_TABLES[i].refTable;
	}
    }
    if (counter==0){
	/* Maybe a real field */
	tables[counter++]=unihanField_get_builtin_preferred_table(field);
    }
    tables[counter]=UNIHAN_INVALID_TABLE;
    return tables;
}

UnihanTable *unihanField_get_all_builtin_tables(UnihanField field){
    UnihanTable *tables=unihanField_get_builtin_required_table(field);
    if (tables[0]==UNIHAN_INVALID_TABLE){
	int i,counter=0;
	g_free(tables);
	tables=NEW_ARRAY_INSTANCES(UNIHAN_TABLE_ARRAY_MAX_LEN, UnihanTable);
	for(i=0;FIELD_TABLES[i].field!=UNIHAN_INVALID_FIELD;i++){
	    if (FIELD_TABLES[i].field==field){
		tables[counter++]=FIELD_TABLES[i].table;
	    }
	}
	tables[counter]=UNIHAN_INVALID_TABLE;
    }
    return tables;
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
    StringList *sList=NULL;

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
	sList=stringList_new();
	sRec=&g_array_index(gArray,SemanticDictRec,i);

	g_snprintf(variantBuf,20,"%d",sRec->variantCode);
	/* Insert to k*SementicVariantTable */
	stringList_insert(sList,codeBuf);
	stringList_insert(sList,variantBuf);

	newResult=unihan_insert_no_duplicate(table,sList);
	result=latest_db_result(result,newResult);
	stringList_free(sList);

	if (isEmptyString(sRec->fromDict)){
	    continue;
	}

	sList=stringList_new();
	/* Insert to SemanticDictTable */
	stringList_insert(sList,codeBuf);
	stringList_insert(sList,variantBuf);
	stringList_insert(sList,sRec->fromDict);
	stringList_insert(sList,(sRec->T)? oneStr: zeroStr);
	stringList_insert(sList,(sRec->B)? oneStr: zeroStr);
	stringList_insert(sList,(sRec->Z)? oneStr: zeroStr);

	newResult=unihan_insert_no_duplicate(extraTable,sList);
	result=latest_db_result(result,newResult);
	stringList_free(sList);
    }

    g_array_free(gArray,TRUE);
    return result;
}

static int insert_zVariant(gunichar code, UnihanField field, const char *composite_value){
    char **subFieldArray=g_strsplit(composite_value,":",-1);
    g_assert(subFieldArray[0]);
    gunichar variantCode=unihanChar_parse(subFieldArray[0]);
    char codeBuf[20], variantBuf[20];
    StringList *sList=stringList_new();

    int result=0,newResult=0;
    UnihanTable table=unihanField_get_table(field),
		extraTable=unihanField_get_extra_table(field);

    g_snprintf(codeBuf,20,"%d",code);
    g_snprintf(variantBuf,20,"%d",variantCode);

    stringList_insert(sList,codeBuf);
    stringList_insert(sList,variantBuf);
    newResult=unihan_insert_no_duplicate(table, sList);
    result=latest_db_result(result,newResult);

    if (!isEmptyString(subFieldArray[1])){
	stringList_clear(sList);
	stringList_insert(sList,codeBuf);
	stringList_insert(sList,variantBuf);
	stringList_insert(sList,subFieldArray[1]);

	newResult=unihan_insert_no_duplicate(extraTable,sList);
	result=latest_db_result(result,newResult);

    }
    stringList_free(sList);
    g_strfreev(subFieldArray);
    return result;
}

int unihan_insert(UnihanTable table, StringList *valueList){
    int i;
    char *errmsg=NULL;
    if (table<0){
	return -1;
    }
    UnihanField* fields=unihanTable_get_fields(table);
    GString *strBuf=g_string_new("INSERT INTO");
    g_string_append_printf(strBuf," %s VALUES (", UNIHAN_TABLE_NAMES[table]);

    for(i=0;i<valueList->len;i++){
	if (fields[i]<0){
	    g_error("unihan_insert(): too many values!  %d value required, but %d are given!\n",i,valueList->len);
	}
	if (i>0){
	    g_string_append_c(strBuf,',');
	}
	if (unihanField_is_integer(fields[i])){
	    g_string_append_printf(strBuf," %s",stringList_index(valueList,i));
	}else{
	    g_string_append_printf(strBuf," \"%s\"",stringList_index(valueList,i));
	}
    }
    while(fields[i]>=0){
	i++;
    }
    if (i!=valueList->len){
	g_error("unihan_insert(): too few values!  %d value required, but %d are given!\n",i,valueList->len);
    }
    g_string_append(strBuf,");");
    verboseMsg_print(VERBOSE_MSG_INFO1,"%s\n",strBuf->str);
    int ret=unihanSql_exec(strBuf->str,NULL,NULL,&errmsg);
    if (ret) {
	verboseMsg_print(VERBOSE_MSG_ERROR, "unihan_insert(): Cannot insert. :%s\n", errmsg);
    }
    g_string_free(strBuf,TRUE);
    g_free(fields);
    return ret;
}

int unihan_insert_tagValue_builtin_table(gunichar code, UnihanField field, const char *tagValue){
    char buf[20];
    UnihanTable *tables=unihanField_get_builtin_required_tables(field);
    gchar **values=NULL;
    gchar **fieldArray=NULL;
    gunichar variantCode;
    if (!unihanField_is_singleton(field)){
	values=g_strsplit_set(value," ",-1);
    }else{
	
    }
    



    UnihanTable *tables=unihanField_get_builtin
    StringList *sList=stringList_new();
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

	if (!unihanIRG_Source_has_no_mapping(rec->sourceId)){/
	    stringList_insert(sList,buf);
	    stringList_insert(sList,srcData->name);
	    stringList_insert(sList,rec->sourceMapping);
	    newResult=unihan_insert_no_duplicate(UNIHAN_TABLE_IRG_SOURCE_EXTRA,sList);
	    result=latest_db_result(result,newResult);
	    stringList_clear(sList);
	}
	stringList_insert(sList,buf);
	stringList_insert(sList,srcData->name);
	unihanIRG_SourceRec_free(rec);
    }else if (unihanField_array_index(field,UNIHAN_KVARIANT_FIELDS)>=0){
	switch(field){
	    case UNIHAN_FIELD_kSEMANTICVARIANT:
	    case UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT:
		return insert_semanticVariant(code, field, value);
	    case UNIHAN_FIELD_kZVARIANT:
		return insert_zVariant(code, field, value);
	    default:
		variantCode=unihanChar_parse(value);
		g_snprintf(buf,20,"%d",code);
		stringList_insert(sList,buf);
		g_snprintf(buf,20,"%d",variantCode);
		stringList_insert(sList,buf);
		break;
	}
    }else  if (unihanField_array_index(field,UNIHAN_KRS_FIELDS)>=0){
	switch(field){
	    case UNIHAN_FIELD_kRSADOBE_JAPAN1_6:
		subFieldArray=g_strsplit_set(value,".+",-1);
		g_snprintf(buf,20,"%d",code);

		stringList_insert(sList,buf);
		stringList_insert(sList,subFieldArray[0]);
		stringList_insert(sList,subFieldArray[1]);
		stringList_insert(sList,subFieldArray[2]);
		stringList_insert(sList,subFieldArray[3]);
		stringList_insert(sList,subFieldArray[4]);

		break;
	    default:
		subFieldArray=g_strsplit(value,".",-1);
		g_snprintf(buf,20,"%d",code);
		stringList_insert(sList,buf);
		stringList_insert(sList,subFieldArray[0]);
		stringList_insert(sList,subFieldArray[1]);
		break;
	}
	g_assert(subFieldArray);
	g_free(subFieldArray);
    }else if (field==UNIHAN_FIELD_kMANDARIN){
	if (lastCode!=code){
	    freqRank=1;
	    lastCode=code;
	}
	g_snprintf(buf,20,"%d",code);
	stringList_insert(sList,buf);
	stringList_insert(sList,value);
	g_snprintf(buf,20,"%d",freqRank);
	stringList_insert(sList,buf);
	freqRank++;
    }else if (field==UNIHAN_FIELD_kHANYUPINLU){
	g_snprintf(buf,20,"%d",code);
	stringList_insert(sList,buf);
	GArray *pfArray=pinyinFreqRec_parse(value);
	if (pfArray->len>0){
	    PinyinFreqRec *rec=&g_array_index(pfArray,PinyinFreqRec,0);
	    stringList_insert(sList,rec->pinyin);
	    g_snprintf(buf,20,"%d",rec->freq);
	    stringList_insert(sList,buf);
	}
	g_array_free(pfArray,TRUE);
    }else if (field==UNIHAN_FIELD_kIRGKANGXI || field==UNIHAN_FIELD_kKANGXI){
	g_snprintf(buf,20,"%d",code);
	stringList_insert(sList,buf);
	GArray *kArray=kangXiRec_parse(value);
	if (kArray->len>0){
	    KangXiRec *rec=&g_array_index(kArray,KangXiRec,0);
	    stringList_insert(sList,rec->page);
	    stringList_insert(sList,rec->charNum);
	    g_snprintf(buf,20,"%d",(rec->virtual)? 1:0);
	    stringList_insert(sList,buf);
	}
	g_array_free(kArray,TRUE);

    }else{
	g_snprintf(buf,20,"%d",code);
	stringList_insert(sList,buf);
	stringList_insert(sList,value);
    }
    newResult=unihan_insert_no_duplicate(table,sList);
    result=latest_db_result(result,newResult);
    stringList_free(sList);
    return result;
}

int unihan_insert_no_duplicate(UnihanTable table, StringList *valueList){
    if (unihan_count_matched_record(table,valueList)>0){
	if (table==UNIHAN_TABLE_kSEMANTICVARIANT || table == UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT){
	    verboseMsg_print(VERBOSE_MSG_WARNING,"code %s is already inserted in table %s, no need to insert again.\n",
		    stringList_index(valueList,0),UNIHAN_TABLE_NAMES[table]);
	}else{
	    verboseMsg_print(VERBOSE_MSG_WARNING,"Record duplicate in table %s on code=%s, skip!\n",
		    UNIHAN_TABLE_NAMES[table],stringList_index(valueList,0));
	}
	return -1;
    }
    int ret=unihan_insert(table,valueList);
    if (ret>0){
	return ret;
    }
    return 0;
}

