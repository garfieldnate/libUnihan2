/** 
 * @file Unihan_enum.h
 * @brief Enumeration and defintion used in libUnihan.
 * 
 * This header file consists enumeration and definite used in libUnihan.
 * It is included in Unihan.h, so no need to include it directly.
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

#ifndef UNIHAN_ENUM_H_
#define UNIHAN_ENUM_H_
#include <glib.h>
#include <sqlite3.h>

/**
 * Enumeration of Unihan fields.
 *
 * This enumeration lists all fields of libUnihan. 
 * Fields are vital cores of libUnihan. Field are needed to perform queries and other operation.
 * For example, to get the pronunciation of "說",
 * fields \c utf8 and \c kMandarin should be specified in \c unihan_query.
 *
 * There are many types of fields.
 * In terms of database scheme, there are <b>real fields</b> and <b>pseudo fields</b>.
 * Real fields represent columns in  database tables; while pseudo fields on the other hand,
 * are derived from database functions and views.
 *
 * In terms of the origin, there are <b>original fields</b> and <b>supporting fields</b>.
 * Original fields directly come from Unicode's original data -- Unihan.txt;
 * while supporting fields do not exist in Unihan.txt, 
 * they either hold parts of the value from original Unihan tags, or provide convenient 
 * aliases for complex statements.
 *
 * Frequently used fields:
 * 
 *    -# \c UNIHAN_FIELD_CODE: Unicode point of this character in integer.
 *    -# \c UNIHAN_FIELD_UTF8: UTF8 representation of the character. Useful for showing the character.
 *    -# \c UNIHAN_FIELD_kDEFINITION: An English definition of the character, convenient for dictionaries.
 *    -# De facto standards:
 *    
 *       -# \c UNIHAN_FIELD_kBIGFIVE: Big5
 *       -# \c UNIHAN_FIELD_kGB0: GB 2312-80
 *       -# \c UNIHAN_FIELD_kJIS0: GB 0208-1990
 *       -# \c UNIHAN_FIELD_kKSC0: KS X 1001:1992
 *       .
 *    -# Pronunciations:
 *        -# \c UNIHAN_FIELD_kCANTONESE: Cantonese pronunciation
 *        -# \c UNIHAN_FIELD_kJAPANESEKUN: Japanese pronunciation
 *        -# \c UNIHAN_FIELD_kMANDARIN: Mandarin pronunciation in Hanyu  Pinyin
 *        -# \c UNIHAN_FIELD_ZHUYIN: Mandarin pronunciation as in Zhuyin
 *        .
 *    -# \c UNIHAN_FIELD_NOT_INSTALLED: The field name is recognized, but not installed in this system.
 *    -# \c UNIHAN_INVALID_FIELD: For error output of end of Unihan field array.
 *    .
 *   
 *  From 0.6, a new value  \c UNIHAN_FIELD_3RD_PARTY is used for third-party fields (fields which are 
 *  from third party database) handling.
 *  A UnihanField is greater than or equal to \c UNIHAN_FIELD_3RD_PARTY if and only if 
 *  it is a third party field.
 */
typedef enum{
    UNIHAN_FIELD_NOT_INSTALLED=-2,	//!< The field have not been installed.
    UNIHAN_INVALID_FIELD=-1,		//!< End of an Unihan Field array or indicate invalid field.
    UNIHAN_FIELD_CODE,			//!< Unicode code point in integer.
    UNIHAN_FIELD_kACCOUNTINGNUMERIC,	//!< Character when used in the writing of accounting numerals.
    UNIHAN_FIELD_kBIGFIVE, 		//!< Big5 Encoding
    UNIHAN_FIELD_kCANGJIE,		//!< Cangjie input code.
    UNIHAN_FIELD_kCANTONESE,		//!< Cantonese pronunciation(s) using the jyutping romanization.
    UNIHAN_FIELD_kCCCII,   		//!< Chinese Character Code for Information Interchange
    UNIHAN_FIELD_kCHEUNGBAUER,		//!< Data regarding the Cheung and Bauer, The Representation of Cantonese with Chinese Characters
    UNIHAN_FIELD_kCHEUNGBAUERINDEX,	//!< The position of the character in Cheung and Bauer, "The Representation of Cantonese with Chinese Characters".
    UNIHAN_FIELD_kCIHAIT,		//!< The position of this character in the Cihai (辭海) dictionary.
    UNIHAN_FIELD_kCNS1986, 		//!< CNS 11643-1986
    UNIHAN_FIELD_kCNS1992, 		//!< CNS 11643-1992
    UNIHAN_FIELD_kCOMPATIBILITYVARIANT, //!< The compatibility decomposition for this ideograph.
    UNIHAN_FIELD_kCOWLES,		//!< in Cowles, "A Pocket Dictionary of Cantonese".
    UNIHAN_FIELD_kDAEJAWEON,		//!< in the Dae Jaweon (Korean) dictionary.
    UNIHAN_FIELD_kDEFINITION,		//!< An English definition for this character.
    UNIHAN_FIELD_kEACC,			//!< EACC mapping for this character in hex.
    UNIHAN_FIELD_kFENN,			//!< from Fenn's Chinese-English Pocket Dictionary.
    UNIHAN_FIELD_kFENNINDEX,		//!< The position in Fenn's Chinese-English Pocket Dictionary by Courtenay.
    UNIHAN_FIELD_kFOURCORNERCODE,	//!< The four-corner code(s) for the character.  
    UNIHAN_FIELD_kFREQUENCY,		//!< A rough frequency measurement for the character based on analysis of traditional Chinese USENET postings.
    UNIHAN_FIELD_kGB0,			//!< GB 2312-80
    UNIHAN_FIELD_kGB1,			//!< GB 12345-90
    UNIHAN_FIELD_kGB3,			//!< GB 7589-87
    UNIHAN_FIELD_kGB5,			//!< GB 7590-87
    UNIHAN_FIELD_kGB7,			//!< General Purpose Hanzi List for Modern Chinese Language, and General List of Simplified Hanzi
    UNIHAN_FIELD_kGB8, 			//!< GB 8565-89
    //    UNIHAN_FIELD_kGB9, 		//!< GB18030-2000
    UNIHAN_FIELD_kGRADELEVEL,		//!< The primary grade in the Hong Kong school system by which a student is expected to know the character.
    UNIHAN_FIELD_kGSR,			//!< in Bernhard Karlgren's Grammata Serica Recensa.
    UNIHAN_FIELD_kHANGUL,		//!< modern Korean pronunciation(s)  in Hangul.
    UNIHAN_FIELD_kHANYU,		//!< in Hanyu Da Zidian (HDZ) Chinese character dictionary.
    UNIHAN_FIELD_kHANYUPINLU,		//!< in Xiandai Hanyu Pinlu Cidian  [Modern Standard Beijing Chinese Frequency Dictionary].
    UNIHAN_FIELD_kHDZRADBREAK,		//!< Indicates that 《漢語大字典》 Hanyu Da Zidian has a radical break beginning at this character's position.
    UNIHAN_FIELD_kHKGLYPH,		//!< The index of the character in 常用字字形表 (二零零零年修訂本),香港: 香港教育學院
    UNIHAN_FIELD_kHKSCS,   		//!< Big5 extended code points for the HK Supplementary Character Set.
    UNIHAN_FIELD_kIBMJAPAN,		//!< IBM Japanese mapping for this character in hexadecimal.
    UNIHAN_FIELD_kIICORE,		//!< IICore, the IRG-produced minimal set of required ideographs for East Asian use.
    UNIHAN_FIELD_kIRGDAEJAWEON,		//!< in Dae Jaweon (Korean) dictionary  used in the four-dictionary sorting algorithm.
    UNIHAN_FIELD_kIRGDAIKANWAZITEN,	//!< in Dai Kanwa Ziten, aka Morohashi dictionary (Japanese)  used in the four-dictionary sorting algorithm.   
    UNIHAN_FIELD_kIRGHANYUDAZIDIAN,	//!< in Hanyu Da Zidian (PRC) used in the four-dictionary sorting algorithm.
    UNIHAN_FIELD_kIRGKANGXI,		//!< in KangXi dictionary.
    UNIHAN_FIELD_kIRG_GSOURCE, 		//!< PRC/Singapore sources, including mapping information.
    UNIHAN_FIELD_kIRG_HSOURCE, 		//!< Hong Kong sources , including mapping information.
    UNIHAN_FIELD_kIRG_JSOURCE, 		//!< Japanese sources, including mapping information.
    UNIHAN_FIELD_kIRG_KPSOURCE, 	//!< North Korean sources, including mapping information.
    UNIHAN_FIELD_kIRG_KSOURCE, 		//!< South Korean sources, including mapping information.
    UNIHAN_FIELD_kIRG_TSOURCE, 		//!< Taiwan sources, including mapping information.
    UNIHAN_FIELD_kIRG_USOURCE, 		//!< Unicode/USA sources, including mapping information.
    UNIHAN_FIELD_kIRG_VSOURCE, 		//!< Vietname sources, including mapping information.
    UNIHAN_FIELD_kJAPANESEKUN,		//!< Japanese pronunciation(s).
    UNIHAN_FIELD_kJAPANESEON,		//!< Sino-Japanese pronunciation(s) of this character.
    UNIHAN_FIELD_kJIS0213,		//!< JIS X 0213-2000
    UNIHAN_FIELD_kJIS0,			//!< JIS X 0208-1990
    UNIHAN_FIELD_kJIS1,			//!< JIS X 0212-1990
    UNIHAN_FIELD_kKANGXI,		//!< in KangXi dictionary used in the four-dictionary sorting algorithm.
    UNIHAN_FIELD_kKARLGREN,		//!< in Analytic Dictionary of Chinese and Sino-Japanese by Bernhard Karlgren.
    UNIHAN_FIELD_kKOREAN,		//!< The Korean pronunciation(s) of this character.
    UNIHAN_FIELD_kKPS0,		//!< KPS 9566-97
    UNIHAN_FIELD_kKPS1,		//!< KPS 10721-2000
    UNIHAN_FIELD_kKSC0,		//!< KS X 1001:1992 (KS C 5601-1989)
    UNIHAN_FIELD_kKSC1,		//!< KS X 1002:1991 (KS C 5657-1991)
    UNIHAN_FIELD_kLAU,			//!< A Practical Cantonese-English Dictionary by Sidney Lau.
    UNIHAN_FIELD_kMAINLANDTELEGRAPH,	//!< PRC telegraph code for this character.
    UNIHAN_FIELD_kMANDARIN,		//!< Mandarin pronunciation(s) for this character in pinyin.
    UNIHAN_FIELD_kMATTHEWS,		//!< in Mathews' Chinese-English Dictionary.
    UNIHAN_FIELD_kMEYERWEMPE,		//!< Student's Cantonese-English Dictionary.
    UNIHAN_FIELD_kMOROHASHI,		//!< Dae Kanwa Ziten, aka Morohashi dictionary (Japanese).
    UNIHAN_FIELD_kNELSON,		//!< The Modern Reader's Japanese-English Character Dictionary.
    UNIHAN_FIELD_kOTHERNUMERIC,		//!< The numeric value for the character in certain unusual, specialized contexts.
    UNIHAN_FIELD_kPHONETIC,		//!< The phonetic index for the character from Ten Thousand Characters: An Analytic Dictionary.
    UNIHAN_FIELD_kPRIMARYNUMERIC,	//!< The value of the character when used in the writing of numbers in the standard fashion.
    UNIHAN_FIELD_kPSEUDOGB1, 		//!< A "GB 12345-90" code point assigned this character for the purposes of including it within Unihan. 
    UNIHAN_FIELD_kRSADOBE_JAPAN1_6,	//!< Information on the glyphs in Adobe-Japan1-6 as contributed by Adobe.
    UNIHAN_FIELD_kRSJAPANESE,		//!< A Japanese radical/stroke count.
    UNIHAN_FIELD_kRSKANGXI,		//!< The KangXi radical/stroke count.
    UNIHAN_FIELD_kRSKANWA,		//!< A Morohashi radical/stroke count.
    UNIHAN_FIELD_kRSKOREAN,		//!< A Korean radical/stroke count.
    UNIHAN_FIELD_kRSUNICODE,		//!< A standard radical/stroke count.
    UNIHAN_FIELD_kSBGY,			//!< Song Ben Guang Yun (SBGY) 《宋本廣韻》 Medieval Chinese character dictionary.
    UNIHAN_FIELD_kSEMANTICVARIANT,	//!< Semantic variants for this character, including dictionaries that refer it.
    UNIHAN_FIELD_kSIMPLIFIEDVARIANT,	//!< Simplified variant for this character (if any).
    UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, //!< Specialized semantic variant for this character, including dictionaries that refer it.
    UNIHAN_FIELD_kTAIWANTELEGRAPH,	//!< Taiwanese telegraph code for this character.
    UNIHAN_FIELD_kTANG,		//!< T'ang Poetic Vocabulary.
    UNIHAN_FIELD_kTOTALSTROKES,	//!< The total number of strokes in the character (including the radical).
    UNIHAN_FIELD_kTRADITIONALVARIANT,	//!< Traditional Chinese variant(s) for this character.
    UNIHAN_FIELD_kVIETNAMESE,		//!< character's pronunciation(s) in in Quốc ngữ.
    UNIHAN_FIELD_kXEROX,		//!< The Xerox code for this character.
    UNIHAN_FIELD_kXHC1983,		//!< One or more Hanyu pinyin reading as given in Xiandai Hanyu Ciden.
    UNIHAN_FIELD_kZVARIANT,		//!< Z-variants of this character, including the source that refers it.

    /**
     * @defgroup Dict_Ref_Fields Supporting fields for dictionary refering tables.
     * @{
     * @name Supporting fields for dictionary refering tables.
     *
     *
     * @{
     */
    UNIHAN_FIELD_DICT_PAGE,		//!< Page number.
    UNIHAN_FIELD_DICT_POSITION,	//!< The character number in the page.
    UNIHAN_FIELD_DICT_VIRTUAL,	//!< Whether the character is actually in the dictionary. 1 for virtual (the character is not acctually in the dictionary, 0 for real (the character is in the dictionary)
    UNIHAN_FIELD_DICT_VARIANT_SERIAL,	//!< Serial number of variant. 0 for a main entry and greater than 0 for a parenthesized variant.
    UNIHAN_FIELD_DICT_UNENCODED,	//!< Unencoded character in the dictionary which is replaced by one or more encoded variants. Currently used only by kXHC1983.

    /**
     * @}
     * @}
     */

    /**
     * @defgroup IRG_Source_Fields Supporting fields for IRG source tables.
     * @{
     * @name Supporting fields for IRG source tables.
     *
     *
     * @{
     */
    UNIHAN_FIELD_IRG_GSOURCE, 		//!< The abbreviated G source name such as "G0" or "G4K".
    UNIHAN_FIELD_IRG_HSOURCE, 		//!< The abbreviated H source name "H".
    UNIHAN_FIELD_IRG_JSOURCE, 		//!< The abbreviated J source name such as "J0" or "J1".
    UNIHAN_FIELD_IRG_KPSOURCE, 		//!< The abbreviated KP source name such as "KP0" or "KP1".
    UNIHAN_FIELD_IRG_KSOURCE, 		//!< The abbreviated K source name such as "K0" or "K1".
    UNIHAN_FIELD_IRG_TSOURCE, 		//!< The abbreviated T source name such as "T1" or "T2".
    UNIHAN_FIELD_IRG_USOURCE, 		//!< The abbreviated U source name "U".
    UNIHAN_FIELD_IRG_VSOURCE, 		//!< The abbreviated V source name such as "V0" or "V1".
    UNIHAN_FIELD_IRG_SOURCE_MAPPING,	//!< The index (code) in hex as in the corresponding IRG source.
    /**
     * @}
     * @}
     */

    /**
     * @defgroup Pinyin_Fields Supporting fields for pinyin tables.
     * @{
     * @name Supporting fields for pinyin tables.
     *
     * @{
     */
    UNIHAN_FIELD_PINYIN,		//!< Pinyin with tone. Always in lower case.
    UNIHAN_FIELD_PINYIN_BASE,		//!< Pinyin without tone.
    UNIHAN_FIELD_PINYIN_TONE,		//!< Tone of Pinyin
    UNIHAN_FIELD_PINYIN_FREQ,		//!< Frequency appears in Xiandai Hanyu Pinlu Cidian (現代漢語頻率詞典)
    UNIHAN_FIELD_ZHUYIN,		//!< Zhuyin field.
    /**
     * @}
     * @}
     */

    /**
     * @defgroup Radical_Stroke_Fields Supporting fields for radical-stroke tables.
     * @{
     * @name Support fields for radical-stroke tables.
     *
     * \c UNIHAN_FIELD_RADICAL_INDEX, \c UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT and
     * \c UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED are used in Radical-stroke tables.
     *
     * @{
     */
    UNIHAN_FIELD_ADOBE_CID_CV,          //!< C or V. "C" indicates that the Unicode code point maps directly to the Adobe-Japan1-6 CID that appears after it, and "V" indicates that it is considered a variant form, and thus not directly encoded.
    UNIHAN_FIELD_ADOBE_CID,		//!< The Adobe-Japan1-6 CID.
    UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT, //!< Stroke counts of KangXi radical
    UNIHAN_FIELD_RADICAL_INDEX,		//!< Index of KangXi radical.
    UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,  //!< Number of strokes of character without radical. As in paper dictionary.
    UNIHAN_FIELD_RADICAL_IS_SIMPLIFIED,  //!< 1 if radical is simplified, 0 for normal radical.
    /**
     * @}
     * @}
     */

    /**
     * @defgroup Variant_Fields Supporting fields for variant tables.
     * @{
     * @name Supporting fields for variant tables.
     *
     * @{
     */
    UNIHAN_FIELD_SEMANTICVARIANT,   	//!< Semantic Variant in UCS4, without dictionary information.
    UNIHAN_FIELD_SPECIALIZEDSEMANTICVARIANT,   	//!< Specialized Semantic Variant in UCS4, without dictionary information.
    UNIHAN_FIELD_VARIANT_CODE,		//!< Unicode code point of variant character in integer.
    UNIHAN_FIELD_FROM_DICT,		//!< The dictionary that define the semantic relation.
    UNIHAN_FIELD_SEMANTIC_T,		//!< "Tong" (同,synonym). The character and variant one are interchangeable.
    UNIHAN_FIELD_SEMANTIC_B,		//!< "Bu" (不,incompatible). The character and variant one  are not interchangeable.
    UNIHAN_FIELD_SEMANTIC_Z,		//!< "Zheng" (正,preferred). The variant character is preferred. 


    UNIHAN_FIELD_ZVARIANT, 		//!< Z Variant in UCS4, without source information.
    UNIHAN_FIELD_ZVARIANT_SOURCE, 	//!< The "Source" of Z variants, such as "kHKGlyph" 
    /**
     * @}
     * @}
     */

    /**
     * @defgroup Other_Fields Supporting fields for variant tables.
     * @{
     * @name Supporting fields for variant tables.
     *
     * @{
     */
    UNIHAN_FIELD_FREQ_RANK,		//!< The rank of the frequency, 1 stands for most frequent, 2 for less frequent and so on.

    UNIHAN_FIELD_SCALAR_VALUE,		//!< Scalar representation (U+XXXXX) of the character 

    UNIHAN_FIELD_SERIAL,		//!< Hold an artificial sequence number for sorting.
    UNIHAN_FIELD_SERIAL_NO_JOIN,	//!< Similar with \c UNIHAN_FIELD_SERIAL, but this field will not be used in automatic join.

    UNIHAN_FIELD_UTF8,			//!< UTF8 representation of the character.
    /**
     * @}
     * @}
     */


    UNIHAN_FIELD_3RD_PARTY		//!< 3RD party fields.
} UnihanField;

/**
 * Number of recognized Unihan fields.
 */
#define UNIHAN_FIELDS_COUNT	UNIHAN_FIELD_3RD_PARTY 

/**
 * @defgroup Unihan_Field_Flags Bitwise flags for UnihanField.
 * @{
 * @name Bitwise flags for UnihanField.
 *
 * Bitwise flags for UnihanField provides additional control over storing and displaying field values.
 * By default (Flag 0), field values are stored and displayed as string without changing case. 
 * However, this behavior can be chaaged by setting these flags.
 *
 * Most of the flags are self-explaining. But note that:
 * -# Set also the \c  UNIHAN_FIELDFLAG_INTEGER for UCS4 fields, 
 *   hexdecimal fields and 4-digits padded fields.
 *   But \c UNIHAN_FIELDFLAG_UCS4, \c UNIHAN_FIELDFLAG_HEXDECIMAL and \c UNIHAN_FIELDFLAG_0_PADDED_4
 *   are mutually exclusive and should not be set in same field.
 *   Because \c UNIHAN_FIELDFLAG_UCS4 is for the fields that can be convert to UTF-8 directly;
 *   while other 2 flags indicates the string representation for the integer value.
 * -# \c UNIHAN_FIELDFLAG_NO_INDEX only works for real fields. Pseudo fields are not indexed.
 * @{
 */
// #define UNIHAN_FIELDFLAG_PSEUDO		0x1	//!< The field is a pseudo field.
#define UNIHAN_FIELDFLAG_INTEGER		0x2	//!< The field stores an integer. 
#define UNIHAN_FIELDFLAG_UCS4			0x4	//!< The field stores an UCS4 code. Should also set UNIHAN_FIELDFLAG_INTEGER.
#define UNIHAN_FIELDFLAG_HEXDECIMAL_16		0x8	//!< The field should be displayed as 16 bits hexdecimal. Should also set UNIHAN_FIELDFLAG_INTEGER.
#define UNIHAN_FIELDFLAG_0_PADDED_2		0x10	//!< The field should be displayed as zero-padded 2 digits integer. Should also set UNIHAN_FIELDFLAG_INTEGER.
#define UNIHAN_FIELDFLAG_0_PADDED_4		0x10	//!< The field should be displayed as zero-padded 4 digits integer. Should also set UNIHAN_FIELDFLAG_INTEGER.
#define UNIHAN_FIELDFLAG_UPPERCASE     	0x20	//!< The field should be displayed as upper case.
#define UNIHAN_FIELDFLAG_LOWERCASE     	0x40	//!< The field should be displayed as lower case.
#define UNIHAN_FIELDFLAG_MULTIROWS		0x80	//!< The field is combined by multiple rows, such as kSemanticVariant.
#define UNIHAN_FIELDFLAG_NO_INDEX		0x100	//!< The field do not need to be indexed. 
#define UNIHAN_FIELDFLAG_NO_PRIMARYKEY		0x200	//!< The field do not need to be in primary key. Normally fields without flag UNIHAN_FIELDFLAG_SINGLETON are in the primary key. However, this flags explicitly specify the field do not need to be in primary key.
#define UNIHAN_FIELDFLAG_SINGLETON		0x400	//!< The field is functional dependent on code. (i.e. No other values)
#define UNIHAN_FIELDFLAG_MANDARIN		0x800	//!< The field stores a mandarin pronunciation. 

/**
 * @}
 * @}
 */

/**
 * Struct of Field Properties.
 *
 * This struct defines the properties of a field, include the field name, and 
 * field flags which are described in #Unihan_Field_Flags.
 */
typedef struct {
    const gchar *fieldName;	//!< Field Name.
    guint flags;	//!< Combined Unihan field flags.
} FieldProperties;




/**
 * Enumeration of tables.
 *
 * This enumeration lists all tables in Unihan databases, as well as ad hoc
 * values for the return value of unihanField_get_table().
 * These are:
 * <ol>
 *   <li><code>UNIHAN_INVALID_TABLE</code>: Indicate the end of an Unihan table array or invalid table.</li>
 *   <li><code>UNIHAN_AMBIGUOUS_TABLE</code>: Indicate the field appears in multiple tables.</li>
 * </ol>
 *
 * Every tables in libUnihan have 2 or more fields, 
 * one is always UNIHAN_FIELD_CODE ("code") field for the code points of characters,
 * the other fields stores parts of Unihan tag value.
 *
 * Normally, each Unihan tag has a corresponding table, for example, 
 * UNIHAN_TABLE_kDEFINITION ("kDefinitionTable") has UNIHAN_FIELD_CODE and
 * UNIHAN_FIELD_kDEFITION which stores the value of the kDefinition tag.
 *
 * If a tag value is splittable and the parts are often utilized, 
 * the value is store in multiple fields.
 * For example, tag kHanyuPinlu has 2 parts, pinyin and its Pinlu (frequency).
 * Thus table UNIHAN_TABLE_kHANYU_PINLU ("kHanyuPinluTable")  has three fields:
 * UNIHAN_FIELD_CODE, UNIHAN_FIELD_PINYIN, and UNIHAN_FIELD_PINYIN_FREQ,
 * where UNIHAN_FIELD_PINYIN and UNIHAN_FIELD_PINYIN_FREQ store pinyin and 
 * its frequency respectively.
 * 
 * Some Unihan tag values consist optional fields, that is,
 * the fields that do not always have values.
 * Putting all these fields in one table violate the 1st normal form (no null fields).
 * To keep tables normalized, two types of tables are employed:
 * "main" tables  hold compulsory fields;
 * while "extra" tables  hold primary key fields 
 * and optional field.
 *
 * For example, value of tag kIRG_GSource can splits to 
 * compulsory field UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME and 
 * optional field UNIHAN_FIELD_IRG_SOURCE_MAPPING.
 * Tag values are stored in two tables:
 * the "main" table UNIHAN_TABLE_IRG_SOURCE stores UNIHAN_FIELD_CODE and UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME;
 * while the "extra" table UNIHAN_TABLE_IRG_SOURCE_EXTRA stores 
 * primary key fields (UNIHAN_FIELD_CODE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME), and the optional field
 * UNIHAN_FIELD_IRG_SOURCE_MAPPING.
 * 
 * Some Unihan tag values are combined in to one table. 
 *
 * \note \c UNIHAN_TABLE_NOT_INSTALLED returns because the tables are recognized by 
 *        libUnihan but not yet installed in this system; on the other hand, 
 *        \c UNIHAN_INVALID_TABLE returns if the table cannot be recognized,
 *        or other error occurs.
 *
 * @see unihanTable_get_db_fields(), unihanTable_get_fields(), unihanTable_get_primary_key_fields()
 */
typedef enum{
    UNIHAN_TABLE_NOT_INSTALLED=-4,	//!< The table have not been installed.
    UNIHAN_NOT_A_TABLE=-3,		//!< Return value for pseudo fields with unihanField_get_table(), as they are derived from database functions but not table fields.
    UNIHAN_INVALID_TABLE=-2,		//!< End of an Unihan table array or indicate invalid table.
    UNIHAN_AMBIGUOUS_TABLE=-1,		//!< Cannot decide which table is more appropriate, usually because it appears in multiple tables, such as UNIHAN_FIELD_CODE.
    UNIHAN_TABLE_kACCOUNTINGNUMERIC,	//!< Table for accounting numberic.
    UNIHAN_TABLE_kBIGFIVE, 		//!< Table for Big 5
    UNIHAN_TABLE_kCANGJIE,		//!< Table for Cangjie
    UNIHAN_TABLE_kCANTONESE,		//!< Table for Cantonese prouncation
    UNIHAN_TABLE_kCCCII,   		//!< Table for Chinese Character Code for Information Interchange.
    UNIHAN_TABLE_kCHEUNGBAUER,		//!< Table for data regarding the Cheung and Bauer, The Representation of Cantonese with Chinese Characters.
    UNIHAN_TABLE_kCHEUNGBAUERINDEX,	//!< Table for the position of characters in Cheung and Bauer, The Representation of Cantonese with Chinese Characters.
    UNIHAN_TABLE_kCIHAIT,		//!< Table for the position of characters in the Cihai (辭海) dictionary.
    UNIHAN_TABLE_kCNS1986, 		//!< Table for CNS 11643-1986.
    UNIHAN_TABLE_kCNS1992,		//!< Table for CNS 11643-1992.
    UNIHAN_TABLE_kCOMPATIBILITYVARIANT, //!< Table for the compatibility decomposition for ideographs.
    UNIHAN_TABLE_kCOWLES,		//!< Table for Cowles, "A Pocket Dictionary of Cantonese".
    UNIHAN_TABLE_kDAEJAWEON,		//!< Table for Dae Jaweon (Korean) dictionary.
    UNIHAN_TABLE_kDEFINITION,		//!< Table for English definition for characters.
    UNIHAN_TABLE_kEACC,			//!< Table for EACC mapping for characters in hex.
    UNIHAN_TABLE_kFENN,			//!< Table for Fenn's Chinese-English Pocket Dictionary by Courtenay.
    UNIHAN_TABLE_kFENNINDEX,		//!< Table for the position in Fenn's Chinese-English Pocket Dictionary by Courtenay.
    UNIHAN_TABLE_kFOURCORNERCODE,	//!< Table for the four-corner codes.  
    UNIHAN_TABLE_kFREQUENCY,		//!< Table for a rough frequency measurement for characters based on analysis of traditional Chinese USENET postings.
    UNIHAN_TABLE_kGB0,			//!< Table for GB 2312-80
    UNIHAN_TABLE_kGB1,			//!< Table for GB 12345-90
    UNIHAN_TABLE_kGB3,			//!< Table for GB 7589-87
    UNIHAN_TABLE_kGB5,			//!< Table for GB 7590-87
    UNIHAN_TABLE_kGB7,			//!< Table for General Purpose Hanzi List for Modern Chinese Language, and General List of Simplified Hanzi.
    UNIHAN_TABLE_kGB8, 			//!< Table for GB 8565-89
    UNIHAN_TABLE_kGRADELEVEL,		//!< Table for primary grade in the Hong Kong school system by which a student is expected to know the characters.
    UNIHAN_TABLE_kGSR,			//!< Table for Bernhard Karlgren's Grammata Serica Recensa.
    UNIHAN_TABLE_kHANGUL,		//!< Table for modern Korean pronunciation(s)  in Hangul.
    UNIHAN_TABLE_kHANYU,		//!< Table for Hanyu Da Zidian (HDZ) Chinese character dictionary.
    UNIHAN_TABLE_kHANYUPINLU,		//!< Table for Xiandai Hanyu Pinlu Cidian.
    UNIHAN_TABLE_kHDZRADBREAK,		//!< Table for Indicates that Hanyu Da Zidian 《漢語大字典》 has a radical break beginning at characters position.
    UNIHAN_TABLE_kHKGLYPH,		//!< Table for the index of characters in 常用字字形表 (二零零零年修訂本),香港: 香港教育學院
    UNIHAN_TABLE_kHKSCS,   		//!< Table for Big5 extended code points for the HK Supplementary Character Set.
    UNIHAN_TABLE_kIBMJAPAN,		//!< Table for IBM Japanese mapping for characters in hexadecimal.
    UNIHAN_TABLE_kIICORE,		//!< Table for IICore, the IRG-produced minimal set of required ideographs for East Asian use.
    UNIHAN_TABLE_kIRG_GSOURCE,		//!< Table for IRG G (China) sources.
    UNIHAN_TABLE_kIRG_GSOURCE_EXTRA,	//!< Table for IRG G (China) and its mapping/code.
    UNIHAN_TABLE_kIRG_HSOURCE,		//!< Table for IRG H (Hong Kong) source.
    UNIHAN_TABLE_kIRG_HSOURCE_EXTRA,	//!< Table for IRG H (Hong Kong) source and its mapping/code.
    UNIHAN_TABLE_kIRG_JSOURCE,		//!< Table for IRG J (Japan) sources.
    UNIHAN_TABLE_kIRG_JSOURCE_EXTRA,	//!< Table for IRG J (Japan) and its mapping/code.
    UNIHAN_TABLE_kIRG_KPSOURCE,		//!< Table for IRG KP (North Korea) source.
    UNIHAN_TABLE_kIRG_KPSOURCE_EXTRA,	//!< Table for IRG KP (North Korea) source and its mapping/code.
    UNIHAN_TABLE_kIRG_KSOURCE,		//!< Table for IRG K (South Korea) source.
    UNIHAN_TABLE_kIRG_KSOURCE_EXTRA,	//!< Table for IRG K (South Korea) source and its mapping/code.
    UNIHAN_TABLE_kIRG_TSOURCE,		//!< Table for IRG T (Taiwan) source.
    UNIHAN_TABLE_kIRG_TSOURCE_EXTRA,	//!< Table for IRG T (Taiwan) source and its mapping/code.
    UNIHAN_TABLE_kIRG_USOURCE,		//!< Table for IRG U (Unicode/Other) source.
    UNIHAN_TABLE_kIRG_USOURCE_EXTRA,	//!< Table for IRG U (Unicode/Other) source and its mapping/code.
    UNIHAN_TABLE_kIRG_VSOURCE,		//!< Table for IRG V (Vietnam) source.
    UNIHAN_TABLE_kIRG_VSOURCE_EXTRA,	//!< Table for IRG V (Vietnam) source and its mapping/code.

    UNIHAN_TABLE_kIRGDAEJAWEON,	        //!< Table for Dae Jaweon (Korean) dictionary  used in the four-dictionary sorting algorithm.
    UNIHAN_TABLE_kIRGDAIKANWAZITEN,	//!< Table for Dai Kanwa Ziten, aka Morohashi dictionary (Japanese)  used in the four-dictionary sorting algorithm.   
    UNIHAN_TABLE_kIRGHANYUDAZIDIAN,	//!< Table for Hanyu Da Zidian (PRC) used in the four-dictionary sorting algorithm.
    UNIHAN_TABLE_kIRGKANGXI,		//!< Table for KangXi dictionary.
    UNIHAN_TABLE_kJAPANESEKUN,		//!< Table for Japanese pronunciation(s).
    UNIHAN_TABLE_kJAPANESEON,		//!< Table for Sino-Japanese pronunciation(s) of characters.
    UNIHAN_TABLE_kJIS0213,		//!< Table for JIS X 0213-2000
    UNIHAN_TABLE_kJIS0,			//!< Table for JIS X 0208-1990
    UNIHAN_TABLE_kJIS1,			//!< Table for JIS X 0212-1990
    UNIHAN_TABLE_kKANGXI,		//!< Table for KangXi dictionary used in the four-dictionary sorting algorithm.
    UNIHAN_TABLE_kKARLGREN,		//!< Table for Analytic Dictionary of Chinese and Sino-Japanese by Bernhard Karlgren.
    UNIHAN_TABLE_kKOREAN,		//!< Table for Korean pronunciation(s).
    UNIHAN_TABLE_kKPS0,			//!< Table for KPS 9566-97.
    UNIHAN_TABLE_kKPS1,			//!< Table for KPS 10721-2000.
    UNIHAN_TABLE_kKSC0,			//!< Table for KS X 1001:1992 (KS C 5601-1989).
    UNIHAN_TABLE_kKSC1,			//!< Table for KS X 1002:1991 (KS C 5657-1991).
    UNIHAN_TABLE_kLAU,			//!< Table for Practical Cantonese-English Dictionary by Sidney Lau.
    UNIHAN_TABLE_kMAINLANDTELEGRAPH,	//!< Table for PRC telegraph code for this character.
    UNIHAN_TABLE_kMANDARIN,		//!< Table for Mandarin pronunciation(s) for this character in pinyin.
    UNIHAN_TABLE_kMATTHEWS,		//!< Table for Mathews' Chinese-English Dictionary.
    UNIHAN_TABLE_kMEYERWEMPE,		//!< Table for Student's Cantonese-English Dictionary.
    UNIHAN_TABLE_kMOROHASHI,		//!< Table for Dae Kanwa Ziten, aka Morohashi dictionary (Japanese).
    UNIHAN_TABLE_kNELSON,		//!< Table for Modern Reader's Japanese-English Character Dictionary.
    UNIHAN_TABLE_kOTHERNUMERIC,		//!< Table for numeric values for characters in certain unusual, specialized contexts.
    UNIHAN_TABLE_kPHONETIC,		//!< Table for the phonetic index of characters from Ten Thousand Characters: An Analytic Dictionary.
    UNIHAN_TABLE_kPRIMARYNUMERIC,	//!< Table for values of characters when used in the writing of numbers in the standard fashion.
    UNIHAN_TABLE_kPSEUDOGB1, 		//!< Table for "GB 12345-90" code points  for the purposes of including it within Unihan. 
    UNIHAN_TABLE_kRSADOBE_JAPAN1_6,	//!< Table for Information on the glyphs in Adobe-Japan1-6 as contributed by Adobe.
    UNIHAN_TABLE_kRSJAPANESE,		//!< Table for Japanese radical/stroke count.
    UNIHAN_TABLE_kRSKANGXI,		//!< Table for KangXi radical/stroke count.
    UNIHAN_TABLE_kRSKANWA,		//!< Table for Morohashi radical/stroke count.
    UNIHAN_TABLE_kRSKOREAN,		//!< Table for Korean radical/stroke count.
    UNIHAN_TABLE_kRSUNICODE,		//!< Table for standard radical/stroke count.
    UNIHAN_TABLE_kSBGY,			//!< Table for Song Ben Guang Yun (SBGY) 《宋本廣韻》 Medieval Chinese character dictionary.
    UNIHAN_TABLE_kSEMANTICVARIANT,	//!< Table for Unicode value for a semantic variant characters.
    UNIHAN_TABLE_kSEMANTICVARIANT_EXTRA,  //!< Table for dictionary that states the semantical relationship.
    UNIHAN_TABLE_kSIMPLIFIEDVARIANT,	//!< Table for Unicode value for the simplified Chinese variant characters.
    UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT, //!< Table for Unicode value for a specialized semantic variant characters.
    UNIHAN_TABLE_kSPECIALIZEDSEMANTICVARIANT_EXTRA, //!< Table for dictionary that states the semantical relationship.
    UNIHAN_TABLE_kTAIWANTELEGRAPH,	//!< Table for Taiwanese telegraph code for this character.
    UNIHAN_TABLE_kTANG,			//!< Table for T'ang Poetic Vocabulary.
    UNIHAN_TABLE_kTOTALSTROKES,		//!< Table for total number of strokes of characters.(including the radical).
    UNIHAN_TABLE_kTRADITIONALVARIANT,   //!< Table for Unicode value(s) for the traditional Chinese variant characters.
    UNIHAN_TABLE_kVIETNAMESE,		//!< Table for characters' pronunciations in in Quốc ngữ.
    UNIHAN_TABLE_kXEROX,		//!< Table for Xerox codes.
    UNIHAN_TABLE_kXHC1983,		//!< Table for One or more Hanyu pinyin reading as given in Xiandai Hanyu Ciden.
    UNIHAN_TABLE_kZVARIANT,		//!< Table for Z-variants.
    UNIHAN_TABLE_kZVARIANT_EXTRA,	//!< Table for the source of Z variant.

    UNIHAN_TABLE_CODE,			//!< Table for UTF-8.
    UNIHAN_TABLE_3RD_PARTY		//!< Third party table.
} UnihanTable;

/**
 * Number of tables in database.
 */
#define UNIHAN_TABLES_COUNT	UNIHAN_TABLE_3RD_PARTY

/**
 * Enumeration of IRG Source.
 *
 * It generally gives ideas of which regions have use the character.
 * For example U+7E94 (纔) appears in G, J, KP, K and T.
 *
 *
 */
typedef enum{
    UNIHAN_INVALID_IRG_SOURCE=-1,  //!< End of an IRG Source array or indicate invalid IRG Source.
    UNIHAN_IRG_SOURCE_G,	//!< Source from PRC and Singarpore.
    UNIHAN_IRG_SOURCE_H,	//!< Source of Hong Kong Only (HKSCS).
    UNIHAN_IRG_SOURCE_J,	//!< Source from Japan.
    UNIHAN_IRG_SOURCE_KP,	//!< Source from Korea (North).
    UNIHAN_IRG_SOURCE_K,	//!< Source from Korea (South).
    UNIHAN_IRG_SOURCE_T,	//!< Source from Taiwan.
    UNIHAN_IRG_SOURCE_U,	//!< Source directly from Unicode standard.
    UNIHAN_IRG_SOURCE_V		//!< Source from Vietnam.
} UnihanIRG_Source;

/**
 * Number of IRG Sources.
 */
#define UNIHAN_IRG_SOURCES_COUNT	UNIHAN_IRG_SOURCE_V+1

/**
 * Enumeration of IRG Source ID.
 *
 * It indicates the exact the source coming from.
 * For example U+7E94 (纔) appears in G1, J0, KP1, K1 and T1.
 *
 */
typedef enum{
    UNIHAN_INVALID_SOURCEID=-1, //!< End of a source array or indicate invalid source.
    UNIHAN_SOURCE_G0,	//!< GB2312-80
    UNIHAN_SOURCE_G1,	//!< GB12345-90 with 58 Hong Kong and 92 Korean \"Idu\" characters
    UNIHAN_SOURCE_G3,	//!< GB7589-87 unsimplified forms
    UNIHAN_SOURCE_G5,	//!< GB7590-87 unsimplified forms
    UNIHAN_SOURCE_G7,	//!< General Purpose Hanzi List for Modern Chinese Language, and General List of Simplified Hanzi
    UNIHAN_SOURCE_GS,	//!< Singapore characters
    UNIHAN_SOURCE_G8,	//!< GB8685-88
    UNIHAN_SOURCE_GE,	//!< GB16500-95
    UNIHAN_SOURCE_G9,	//!< GB18030-2000
    UNIHAN_SOURCE_G4K,	//!< Siku Quanshu (四庫全書)
    UNIHAN_SOURCE_GBK,	//!< Chinese Encyclopedia
    UNIHAN_SOURCE_GCH,	//!< The Ci Hai (PRC edition) (辭海)
    UNIHAN_SOURCE_GCY,	//!< The Ci Yuan (辭源)
    UNIHAN_SOURCE_GFZ,	//!< Founder Press System
    UNIHAN_SOURCE_GFZ_BK,	//!< Founder Press System
    UNIHAN_SOURCE_GHC,	//!< The Hanyu Da Cidian (漢語大辭典)
    UNIHAN_SOURCE_GHZ,	//!< The Hanyu Da Zidian (漢語大字典)
    UNIHAN_SOURCE_GKX,	//!< The KangXi dictionary (康熙字典)

    UNIHAN_SOURCE_H,	//!< Hong Kong Supplementary Character Set
    UNIHAN_SOURCE_J0,	//!< JIS X 0208:1990
    UNIHAN_SOURCE_J1,	//!< JIS X 0212:1990
    UNIHAN_SOURCE_JA,	//!< Unified Japanese IT Vendors Contemporary Ideographs, 1993
    UNIHAN_SOURCE_J3,	//!< JIS X 0213:2000
    UNIHAN_SOURCE_J3A,	//!< JIS X 0213:2004 level-3
    UNIHAN_SOURCE_J4,	//!< JIS X 0213:2000

    UNIHAN_SOURCE_KP0,	//!< KPS 9566-97
    UNIHAN_SOURCE_KP1,	//!< KPS 10721-2000

    UNIHAN_SOURCE_K0,	//!< KS C 5601-1987
    UNIHAN_SOURCE_K1,	//!< KS C 5657-1991
    UNIHAN_SOURCE_K2,	//!< PKS C 5700-1 1994
    UNIHAN_SOURCE_K3,	//!< PKS C 5700-2 1994
    UNIHAN_SOURCE_K4,	//!< PKS 5700-3:1998

    UNIHAN_SOURCE_T1,	//!< CNS 11643-1992, plane 1
    UNIHAN_SOURCE_T2,	//!< CNS 11643-1992, plane 2
    UNIHAN_SOURCE_T3,	//!< CNS 11643-1992, plane 3 (with some additional characters)
    UNIHAN_SOURCE_T4,	//!< CNS 11643-1992, plane 4
    UNIHAN_SOURCE_T5,	//!< CNS 11643-1992, plane 5
    UNIHAN_SOURCE_T6,	//!< CNS 11643-1992, plane 6
    UNIHAN_SOURCE_T7,	//!< CNS 11643-1992, plane 7
    UNIHAN_SOURCE_TF,	//!< CNS 11643-1992, plane 15

    UNIHAN_SOURCE_U,	//!< Other sources which were used by the Unicode Consortium

    UNIHAN_SOURCE_V0,	//!< TCVN 5773:1993
    UNIHAN_SOURCE_V1,	//!< TCVN 6056:1995
    UNIHAN_SOURCE_V2,	//!< VHN 01:1998
    UNIHAN_SOURCE_V3,	//!< VHN 02:1998
} UnihanIRG_SourceId;

/**
 * Number of the IRG Source ID.
 */
#define UNIHAN_SOURCES_COUNT	UNIHAN_SOURCE_V3+1


/**
 * Enumeration of supported locales.
 */
typedef enum{
    UNIHAN_INVALID_LOCALE=-1, //!< End of a locale array or indicate invalid source.
    UNIHAN_LOCALE_JA_JP, //<! Japan.
    UNIHAN_LOCALE_KO_KP, //<! North Korea.
    UNIHAN_LOCALE_KO_KR, //<! South Korea.
    UNIHAN_LOCALE_ZH_CN, //<! PRC.
    UNIHAN_LOCALE_ZH_HK, //<! Hong Kong.
    UNIHAN_LOCALE_ZH_SG, //<! Singapore.
    UNIHAN_LOCALE_ZH_TW, //<! Taiwan.
    UNIHAN_LOCALE_VI_VN, //<! Vietnam.
} UnihanLocale;
/**
 * Number of supported locale.
 */
#define UNIHAN_LOCALES_COUNT UNIHAN_LOCALE_VI_VN+1

/**
 * Enumeration of Unihan Range.
 *
 * Indicate the range which the character belong to.
 *
 * Used with unihanChar_in_range() and unihanRange_to_string().
 * @see unihanChar_in_range()
 * @see unihanRange_to_string()
 */
typedef enum{
    UNIHAN_INVALID_RANGE=-1, //!< End of a range array or indicate out of range.
    UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS_EXT_A,	//!< U+3400..U+4DB5   : CJK Unified Ideographs Extension A.
    UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS, 	//!< U+4E00..U+9FA5   : CJK Unified Ideographs.
    UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS_4_1,	//!< U+9FA6..U+9FBB   : CJK Unified Ideographs (4.1).
    UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS_5_1,	//!< U+9FBC..U+9FC3   : CJK Unified Ideographs (5.1).
    UNIHAN_RANGE_CJK_COMPATIBILITY_UNIFIED_IDEOGRAPHS_A, //!< U+F900..U+FA2D   : CJK Compatibility Ideographs (a).
    UNIHAN_RANGE_CJK_COMPATIBILITY_UNIFIED_IDEOGRAPHS_B, //!< U+FA30..U+FA6A   : CJK Compatibility Ideographs (b).
    UNIHAN_RANGE_CJK_COMPATIBILITY_UNIFIED_IDEOGRAPHS_4_1, //!< U+FA70..U+FAD9   : CJK Compatibility Ideographs (4.1).
    UNIHAN_RANGE_CJK_UNIFIED_IDEOGRAPHS_EXT_B, //!< U+20000..U+2A6D6 : CJK Unified Ideographs Extension B.
    UNIHAN_RANGE_CJK_COMPATIBILITY_SUPPLEMENT  //!< U+2F800..U+2FA1D : CJK Compatibility Supplement.
} UnihanRange;
/**
 * Number of Unihan range.
 */
#define UNIHAN_RANGES_COUNT UNIHAN_RANGE_CJK_COMPATIBILITY_SUPPLEMENT+1

/**
 * @name Common sources for a locale.
 * Frequently used sources/standards for each locale.
 * @{
 */
/**
 * Frequently used source in Japan.
 */
#define LOCALE_JA_JP_SOURCES_COMMON UNIHAN_SOURCE_J0, UNIHAN_INVALID_SOURCEID

/**
 * Frequently used source in North Korea.
 */
#define LOCALE_KO_KP_SOURCES_COMMON UNIHAN_SOURCE_KP0, UNIHAN_INVALID_SOURCEID

/**
 * Frequently used source in South Korea.
 */
#define LOCALE_KO_KR_SOURCES_COMMON UNIHAN_SOURCE_K0, UNIHAN_INVALID_SOURCEID

/**
 * Frequently used source in China.
 */
#define LOCALE_ZH_CN_SOURCES_COMMON UNIHAN_SOURCE_G0, UNIHAN_INVALID_SOURCEID

/**
 * Frequently used source in Hong Kong.
 */
#define LOCALE_ZH_HK_SOURCES_COMMON UNIHAN_SOURCE_T1, UNIHAN_SOURCE_T2, UNIHAN_SOURCE_H, UNIHAN_INVALID_SOURCEID

/**
 * Frequently used source in Singapore.
 */
#define LOCALE_ZH_SG_SOURCES_COMMON UNIHAN_SOURCE_G0, UNIHAN_SOURCE_GS, UNIHAN_INVALID_SOURCEID

/**
 * Frequently used source in Taiwan.
 */
#define LOCALE_ZH_TW_SOURCES_COMMON UNIHAN_SOURCE_T1, UNIHAN_SOURCE_T2, UNIHAN_INVALID_SOURCEID

/**
 * Frequently used source in Vietnam.
 */
#define LOCALE_VI_VN_SOURCES_COMMON UNIHAN_SOURCE_V0, UNIHAN_INVALID_SOURCEID
/* @}*/
#endif /* UNIHAN_ENUM_H_ */

