/** 
 * @file Unihan_enum.h
 * @brief Enumeration and definte used in libUnihan.
 * 
 * This header file consists enumeration and definte used in libUnihan.
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
 * Definition:
 * <dl>
 *    <dt>Pseudo Field</dt>
 * </dl>
 * 
 * Frequently used fields:
 * <ol>
 *    <li>UNIHAN_FIELD_CODE: Unicode point of this character in integer.</li>
 *    <li>UNIHAN_FIELD_UTF8: UTF8 representation of the character. Useful for showing the character.</li>
 *    <li>UNIHAN_FIELD_KDEFINITION: An English definition of the character, convenient for dictionaries.</li>
 *    <li>De facto standards:</li>
 *    <ol>
 *       <li>UNIHAN_FIELD_KBIGFIVE: Big5</li>
 *       <li>UNIHAN_FIELD_KGB0: GB 2312-80</li>
 *       <li>UNIHAN_FIELD_KJIS0: GB 0208-1990</li>
 *       <li>UNIHAN_FIELD_KKSC0: KS X 1001:1992</li>
 *    </ol>
 *    <li>Pronunciations:</li>
 *    <ol>
 *        <li>UNIHAN_FIELD_KCANTONESE: Cantonese pronunciation</li>
 *        <li>UNIHAN_FIELD_KJAPANESEKUN: Japanese pronunciation</li>
 *        <li>UNIHAN_FIELD_KMANDARIN: Mandarin pronunciation in Hanyu  Pinyin</li>
 *        <li>UNIHAN_FIELD_ZHUYIN: Mandarin pronunciation as in Zhuyin</li>
 *
 *    </ol>
 *    <li>UNIHAN_INVALID_FIELD: For error output of end of Unihan field array.</li>
 * </ol>
 */
typedef enum{
    UNIHAN_INVALID_FIELD=-1,		//!< End of an Unihan Field array or indicate invalid field.
    UNIHAN_FIELD_CODE,			//!< Unicode code point in integer.
    UNIHAN_FIELD_KACCOUNTINGNUMERIC,	//!< Character when used in the writing of accounting numerals.
    UNIHAN_FIELD_KBIGFIVE, 		//!< Big5 Encoding
    UNIHAN_FIELD_KCANGJIE,		//!< Cangjie input code.
    UNIHAN_FIELD_KCANTONESE,		//!< Cantonese pronunciation(s) using the jyutping romanization.
    UNIHAN_FIELD_KCCCII,   		//!< Chinese Character Code for Information Interchange
    UNIHAN_FIELD_KCHEUNGBAUER,		//!< Data regarding the Cheung and Bauer, The Representation of Cantonese with Chinese Characters
    UNIHAN_FIELD_KCHEUNGBAUERINDEX,	//!< The position of the character in Cheung and Bauer, "The Representation of Cantonese with Chinese Characters".
    UNIHAN_FIELD_KCIHAIT,		//!< The position of this character in the Cihai (辭海) dictionary.
    UNIHAN_FIELD_KCNS1986, 		//!< CNS 11643-1986
    UNIHAN_FIELD_KCNS1992, 		//!< CNS 11643-1992
    UNIHAN_FIELD_KCOMPATIBILITYVARIANT, //!< The compatibility decomposition for this ideograph.
    UNIHAN_FIELD_KCOWLES,		//!< in Cowles, "A Pocket Dictionary of Cantonese".
    UNIHAN_FIELD_KDAEJAWEON,		//!< in the Dae Jaweon (Korean) dictionary.
    UNIHAN_FIELD_KDEFINITION,		//!< An English definition for this character.
    UNIHAN_FIELD_KEACC,			//!< EACC mapping for this character in hex.
    UNIHAN_FIELD_KFENN,			//!< from Fenn's Chinese-English Pocket Dictionary.
    UNIHAN_FIELD_KFENNINDEX,		//!< The position in Fenn's Chinese-English Pocket Dictionary by Courtenay.
    UNIHAN_FIELD_KFOURCORNERCODE,	//!< The four-corner code(s) for the character.  
    UNIHAN_FIELD_KFREQUENCY,		//!< A rough frequency measurement for the character based on analysis of traditional Chinese USENET postings.
    UNIHAN_FIELD_KGB0,			//!< GB 2312-80
    UNIHAN_FIELD_KGB1,			//!< GB 12345-90
    UNIHAN_FIELD_KGB3,			//!< GB 7589-87
    UNIHAN_FIELD_KGB5,			//!< GB 7590-87
    UNIHAN_FIELD_KGB7,			//!< General Purpose Hanzi List for Modern Chinese Language, and General List of Simplified Hanzi
    UNIHAN_FIELD_KGB8, 			//!< GB 8565-89
    //    UNIHAN_FIELD_KGB9, 		//!< GB18030-2000
    UNIHAN_FIELD_KGRADELEVEL,		//!< The primary grade in the Hong Kong school system by which a student is expected to know the character.
    UNIHAN_FIELD_KGSR,			//!< in Bernhard Karlgren's Grammata Serica Recensa.
    UNIHAN_FIELD_KHANGUL,		//!< modern Korean pronunciation(s)  in Hangul.
    UNIHAN_FIELD_KHANYU,		//!< in Hanyu Da Zidian (HDZ) Chinese character dictionary.
    UNIHAN_FIELD_KHANYUPINLU,		//!< in Xiandai Hanyu Pinlu Cidian  [Modern Standard Beijing Chinese Frequency Dictionary].
    UNIHAN_FIELD_KHDZRADBREAK,		//!< Indicates that 《漢語大字典》 Hanyu Da Zidian has a radical break beginning at this character's position.
    UNIHAN_FIELD_KHKGLYPH,		//!< The index of the character in 常用字字形表 (二零零零年修訂本),香港: 香港教育學院
    UNIHAN_FIELD_KHKSCS,   		//!< Big5 extended code points for the HK Supplementary Character Set.
    UNIHAN_FIELD_KIBMJAPAN,		//!< IBM Japanese mapping for this character in hexadecimal.
    UNIHAN_FIELD_KIICORE,		//!< IICore, the IRG-produced minimal set of required ideographs for East Asian use.
    UNIHAN_FIELD_KIRGDAEJAWEON,		//!< in Dae Jaweon (Korean) dictionary  used in the four-dictionary sorting algorithm.
    UNIHAN_FIELD_KIRGDAIKANWAZITEN,	//!< in Dai Kanwa Ziten, aka Morohashi dictionary (Japanese)  used in the four-dictionary sorting algorithm.   
    UNIHAN_FIELD_KIRGHANYUDAZIDIAN,	//!< in Hanyu Da Zidian (PRC) used in the four-dictionary sorting algorithm.
    UNIHAN_FIELD_KIRGKANGXI,		//!< in KangXi dictionary.
    UNIHAN_FIELD_KIRG_GSOURCE, 	//!< PRC/Singapore sources
    UNIHAN_FIELD_KIRG_HSOURCE, 	//!< Hong Kong sources
    UNIHAN_FIELD_KIRG_JSOURCE, 	//!< Japanese sources
    UNIHAN_FIELD_KIRG_KPSOURCE, 	//!< North Korean sources
    UNIHAN_FIELD_KIRG_KSOURCE, 		//!< South Korean sources
    UNIHAN_FIELD_KIRG_TSOURCE, 		//!< Taiwan sources
    UNIHAN_FIELD_KIRG_USOURCE, 		//!< Unicode/USA sources
    UNIHAN_FIELD_KIRG_VSOURCE, 		//!< Vietname sources
    UNIHAN_FIELD_KJAPANESEKUN,		//!< Japanese pronunciation(s).
    UNIHAN_FIELD_KJAPANESEON,		//!< Sino-Japanese pronunciation(s) of this character.
    UNIHAN_FIELD_KJIS0213,		//!< JIS X 0213-2000
    UNIHAN_FIELD_KJIS0,			//!< JIS X 0208-1990
    UNIHAN_FIELD_KJIS1,			//!< JIS X 0212-1990
    UNIHAN_FIELD_KKANGXI,		//!< in KangXi dictionary used in the four-dictionary sorting algorithm.
    UNIHAN_FIELD_KKARLGREN,		//!< in Analytic Dictionary of Chinese and Sino-Japanese by Bernhard Karlgren.
    UNIHAN_FIELD_KKOREAN,		//!< The Korean pronunciation(s) of this character.
    UNIHAN_FIELD_KKPS0,		//!< KPS 9566-97
    UNIHAN_FIELD_KKPS1,		//!< KPS 10721-2000
    UNIHAN_FIELD_KKSC0,		//!< KS X 1001:1992 (KS C 5601-1989)
    UNIHAN_FIELD_KKSC1,		//!< KS X 1002:1991 (KS C 5657-1991)
    UNIHAN_FIELD_KLAU,			//!< A Practical Cantonese-English Dictionary by Sidney Lau.
    UNIHAN_FIELD_KMAINLANDTELEGRAPH,	//!< PRC telegraph code for this character.
    UNIHAN_FIELD_KMANDARIN,		//!< Mandarin pronunciation(s) for this character in pinyin.
    UNIHAN_FIELD_KMATTHEWS,		//!< in Mathews' Chinese-English Dictionary.
    UNIHAN_FIELD_KMEYERWEMPE,		//!< Student's Cantonese-English Dictionary.
    UNIHAN_FIELD_KMOROHASHI,		//!< Dae Kanwa Ziten, aka Morohashi dictionary (Japanese).
    UNIHAN_FIELD_KNELSON,		//!< The Modern Reader's Japanese-English Character Dictionary.
    UNIHAN_FIELD_KOTHERNUMERIC,		//!< The numeric value for the character in certain unusual, specialized contexts.
    UNIHAN_FIELD_KPHONETIC,		//!< The phonetic index for the character from Ten Thousand Characters: An Analytic Dictionary.
    UNIHAN_FIELD_KPRIMARYNUMERIC,	//!< The value of the character when used in the writing of numbers in the standard fashion.
    UNIHAN_FIELD_KPSEUDOGB1, 		//!< A "GB 12345-90" code point assigned this character for the purposes of including it within Unihan. 
    UNIHAN_FIELD_KRSADOBE_JAPAN1_6,	//!< Information on the glyphs in Adobe-Japan1-6 as contributed by Adobe.
    UNIHAN_FIELD_KRSJAPANESE,		//!< A Japanese radical/stroke count.
    UNIHAN_FIELD_KRSKANGXI,		//!< The KangXi radical/stroke count.
    UNIHAN_FIELD_KRSKANWA,		//!< A Morohashi radical/stroke count.
    UNIHAN_FIELD_KRSKOREAN,		//!< A Korean radical/stroke count.
    UNIHAN_FIELD_KRSUNICODE,		//!< A standard radical/stroke count.
    UNIHAN_FIELD_KSBGY,			//!< Song Ben Guang Yun (SBGY) 《宋本廣韻》 Medieval Chinese character dictionary.
    UNIHAN_FIELD_KSEMANTICVARIANT,	//!< The Unicode value for a semantic variant for this character.
    UNIHAN_FIELD_KSIMPLIFIEDVARIANT,	//!< The Unicode value for the simplified Chinese variant for this character (if any).
    UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT, //!< The Unicode value for a specialized semantic variant for this character.
    UNIHAN_FIELD_KTAIWANTELEGRAPH,	//!< Taiwanese telegraph code for this character.
    UNIHAN_FIELD_KTANG,		//!< T'ang Poetic Vocabulary.
    UNIHAN_FIELD_KTOTALSTROKES,	//!< The total number of strokes in the character (including the radical).
    UNIHAN_FIELD_KTRADITIONALVARIANT,	//!< The Unicode value(s) for the traditional Chinese variant(s) for this character.
    UNIHAN_FIELD_KVIETNAMESE,		//!< character's pronunciation(s) in in Quốc ngữ.
    UNIHAN_FIELD_KXEROX,		//!< The Xerox code for this character.
    UNIHAN_FIELD_KXHC1983,		//!< One or more Hanyu pinyin reading as given in Xiandai Hanyu Ciden.
    UNIHAN_FIELD_KZVARIANT,		//!< The Unicode value(s) for known z-variants of this character.

    UNIHAN_FIELD_UTF8,			//!< UTF8 representation of the character.

    UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME, //!< The abbreviated source name such as "G0" or "JA".
    UNIHAN_FIELD_IRG_SOURCE_MAPPING,	//!< The index (code) in hex as in the corresponding IRG source.

    UNIHAN_FIELD_VARIANT_TYPE,		//!< Type of the variant, such as "kSemanticVariant", "kZVariant".
    UNIHAN_FIELD_VARIANT_CODE,		//!< Unicode code point of variant character in integer.

    UNIHAN_FIELD_FROM_DICT,		//!< The dictionary that define the semantic relation.
    UNIHAN_FIELD_SEMANTIC_T,		//!< "Tong" (同,synonym). The character and variant one are interchangeable.
    UNIHAN_FIELD_SEMANTIC_B,		//!< "Bu" (不,incompatible). The character and variant one  are not interchangeable.
    UNIHAN_FIELD_SEMANTIC_Z,		//!< "Zheng" (正,preferred). The variant character is preferred. 

    UNIHAN_FIELD_RADICAL_INDEX,		//!< Index of KangXi radical.
    UNIHAN_FIELD_ADDITIONAL_STROKE_COUNT,  //!< Number of strokes of character without radical. As in paper dictionary.

    UNIHAN_FIELD_ADOBE_CID_CV,          //!< C or V. "C" indicates that the Unicode code point maps directly to the Adobe-Japan1-6 CID that appears after it, and "V" indicates that it is considered a variant form, and thus not directly encoded.
    UNIHAN_FIELD_ADOBE_CID,		//!< The Adobe-Japan1-6 CID.
    UNIHAN_FIELD_ADOBE_CID_RADICAL_STROKE_COUNT, //!< Stroke counts of KangXi radical

    UNIHAN_FIELD_KANGXI_PAGE,		//!< Page number in KangXi. (Represent as string)
    UNIHAN_FIELD_KANGXI_CHARNUM,	//!< The character number in the page. (Represent as string)
    UNIHAN_FIELD_KANGXI_VIRTUAL,	//!< Whether the character is actually in KangXi. 1 for virtual (the character is not acctually in KangXi, 0 for real (the character is in KangXi)

    UNIHAN_FIELD_FREQ_RANK,		//!< The rank of the frequency, 1 stands for most frequent, 2 for less frequent and so on.

    UNIHAN_FIELD_PINYIN,		//!< HanYu pinyin
    UNIHAN_FIELD_PINYIN_FREQ,		//!< Frequency appears in Xiandai Hanyu Pinlu Cidian (現代漢語頻率詞典)

    UNIHAN_FIELD_ZVARIANT_SOURCE, 	//!< The "Source" of Z variants, such as "kHKGlyph" 

    UNIHAN_FIELD_ZHUYIN			//!< ZhuYin field.
} UnihanField;

/**
 * Number of recognized Unihan fields.
 */
#define UNIHAN_FIELDS_COUNT	UNIHAN_FIELD_ZHUYIN+1 

/**
 * Enumeration of tables.
 *
 * This enumeration list all tables in Unihan databases, as well as ad hoc
 * values for the return value of unihanField_get_table().
 * These are:
 * <ol>
 *   <li><code>UNIHAN_NOT_A_TABLE</code>: Indicate the given field is not from a table..</li>
 *   <li><code>UNIHAN_INVALID_TABLE</code>: Indicate the end of an Unihan table array or invalid table.</li>
 *   <li><code>UNIHAN_AMBIGUOUS_TABLE</code>: Indicate the field appears in multiple tables.</li>
 * </ol>
 *
 * Every tables in libUnihan have 2 or more fields, 
 * one is always UNIHAN_FIELD_CODE ("code") field for the code points of characters,
 * the other fields stores parts of Unihan tag value.
 *
 * Normally, each Unihan tag has a corresponding table, for example, 
 * UNIHAN_TABLE_KDEFINITION ("kDefinitionTable") has UNIHAN_FIELD_CODE and
 * UNIHAN_FIELD_KDEFITION which stores the value of the kDefinition tag.
 *
 * If a tag value is splittable and the parts are often utilized, 
 * the value is store in multiple fields.
 * For example, tag kHanyuPinlu has 2 parts, pinyin and its Pinlu (frequency).
 * Thus table UNIHAN_TABLE_KHANYU_PINLU ("kHanyuPinluTable")  has three fields:
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
 * while the "extra" table UNIHAN_TABLE_IRG_SOURCE_MAPPING stores 
 * primary key fields (UNIHAN_FIELD_CODE, UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME), and the optional field
 * UNIHAN_FIELD_IRG_SOURCE_MAPPING.
 * 
 * Some Unihan tag values are combined in to one table. 
 *
 * @see unihanTable_get_db_fields(), unihanTable_get_fields(), unihanTable_get_primary_key_fields()
 */
typedef enum{
    UNIHAN_NOT_A_TABLE=-3,		//!< Return value for pseudo fields with unihanField_get_table(), as they are derived from database functions but not table fields.
    UNIHAN_INVALID_TABLE=-2,		//!< End of an Unihan table array or indicate invalid table.
    UNIHAN_AMBIGUOUS_TABLE=-1,		//!< Cannot decide which table is more appropriate, usually because it appears in multiple tables, such as UNIHAN_FIELD_CODE.
    UNIHAN_TABLE_KACCOUNTINGNUMERIC,	//!< Table for accounting numberic.
    UNIHAN_TABLE_KBIGFIVE, 		//!< Table for Big 5
    UNIHAN_TABLE_KCANGJIE,		//!< Table for Cangjie
    UNIHAN_TABLE_KCANTONESE,		//!< Table for Cantonese prouncation
    UNIHAN_TABLE_KCCCII,   		//!< Table for Chinese Character Code for Information Interchange.
    UNIHAN_TABLE_KCHEUNGBAUER,		//!< Table for data regarding the Cheung and Bauer, The Representation of Cantonese with Chinese Characters.
    UNIHAN_TABLE_KCHEUNGBAUERINDEX,	//!< Table for the position of characters in Cheung and Bauer, The Representation of Cantonese with Chinese Characters.
    UNIHAN_TABLE_KCIHAIT,		//!< Table for the position of characters in the Cihai (辭海) dictionary.
    UNIHAN_TABLE_KCNS1986, 		//!< Table for CNS 11643-1986.
    UNIHAN_TABLE_KCNS1992,		//!< Table for CNS 11643-1992.
    UNIHAN_TABLE_KCOMPATIBILITYVARIANT, //!< Table for the compatibility decomposition for ideographs.
    UNIHAN_TABLE_KCOWLES,		//!< Table for Cowles, "A Pocket Dictionary of Cantonese".
    UNIHAN_TABLE_KDAEJAWEON,		//!< Table for Dae Jaweon (Korean) dictionary.
    UNIHAN_TABLE_KDEFINITION,		//!< Table for English definition for characters.
    UNIHAN_TABLE_KEACC,			//!< Table for EACC mapping for characters in hex.
    UNIHAN_TABLE_KFENN,			//!< Table for Fenn's Chinese-English Pocket Dictionary by Courtenay.
    UNIHAN_TABLE_KFENNINDEX,		//!< Table for the position in Fenn's Chinese-English Pocket Dictionary by Courtenay.
    UNIHAN_TABLE_KFOURCORNERCODE,	//!< Table for the four-corner codes.  
    UNIHAN_TABLE_KFREQUENCY,		//!< Table for a rough frequency measurement for characters based on analysis of traditional Chinese USENET postings.
    UNIHAN_TABLE_KGB0,			//!< Table for GB 2312-80
    UNIHAN_TABLE_KGB1,			//!< Table for GB 12345-90
    UNIHAN_TABLE_KGB3,			//!< Table for GB 7589-87
    UNIHAN_TABLE_KGB5,			//!< Table for GB 7590-87
    UNIHAN_TABLE_KGB7,			//!< Table for General Purpose Hanzi List for Modern Chinese Language, and General List of Simplified Hanzi.
    UNIHAN_TABLE_KGB8, 			//!< Table for GB 8565-89
    UNIHAN_TABLE_KGRADELEVEL,		//!< Table for primary grade in the Hong Kong school system by which a student is expected to know the characters.
    UNIHAN_TABLE_KGSR,			//!< Table for Bernhard Karlgren's Grammata Serica Recensa.
    UNIHAN_TABLE_KHANGUL,		//!< Table for modern Korean pronunciation(s)  in Hangul.
    UNIHAN_TABLE_KHANYU,		//!< Table for Hanyu Da Zidian (HDZ) Chinese character dictionary.
    UNIHAN_TABLE_KHANYUPINLU,		//!< Table for Xiandai Hanyu Pinlu Cidian.
    UNIHAN_TABLE_KHDZRADBREAK,		//!< Table for Indicates that Hanyu Da Zidian 《漢語大字典》 has a radical break beginning at characters position.
    UNIHAN_TABLE_KHKGLYPH,		//!< Table for the index of characters in 常用字字形表 (二零零零年修訂本),香港: 香港教育學院
    UNIHAN_TABLE_KHKSCS,   		//!< Table for Big5 extended code points for the HK Supplementary Character Set.
    UNIHAN_TABLE_KIBMJAPAN,		//!< Table for IBM Japanese mapping for characters in hexadecimal.
    UNIHAN_TABLE_KIICORE,		//!< Table for IICore, the IRG-produced minimal set of required ideographs for East Asian use.
    UNIHAN_TABLE_KIRGDAEJAWEON,	        //!< Table for Dae Jaweon (Korean) dictionary  used in the four-dictionary sorting algorithm.
    UNIHAN_TABLE_KIRGDAIKANWAZITEN,	//!< Table for Dai Kanwa Ziten, aka Morohashi dictionary (Japanese)  used in the four-dictionary sorting algorithm.   
    UNIHAN_TABLE_KIRGHANYUDAZIDIAN,	//!< Table for Hanyu Da Zidian (PRC) used in the four-dictionary sorting algorithm.
    UNIHAN_TABLE_KIRGKANGXI,		//!< Table for KangXi dictionary.
    UNIHAN_TABLE_KJAPANESEKUN,		//!< Table for Japanese pronunciation(s).
    UNIHAN_TABLE_KJAPANESEON,		//!< Table for Sino-Japanese pronunciation(s) of characters.
    UNIHAN_TABLE_KJIS0213,		//!< Table for JIS X 0213-2000
    UNIHAN_TABLE_KJIS0,			//!< Table for JIS X 0208-1990
    UNIHAN_TABLE_KJIS1,			//!< Table for JIS X 0212-1990
    UNIHAN_TABLE_KKANGXI,		//!< Table for KangXi dictionary used in the four-dictionary sorting algorithm.
    UNIHAN_TABLE_KKARLGREN,		//!< Table for Analytic Dictionary of Chinese and Sino-Japanese by Bernhard Karlgren.
    UNIHAN_TABLE_KKOREAN,		//!< Table for Korean pronunciation(s).
    UNIHAN_TABLE_KKPS0,			//!< Table for KPS 9566-97.
    UNIHAN_TABLE_KKPS1,			//!< Table for KPS 10721-2000.
    UNIHAN_TABLE_KKSC0,			//!< Table for KS X 1001:1992 (KS C 5601-1989).
    UNIHAN_TABLE_KKSC1,			//!< Table for KS X 1002:1991 (KS C 5657-1991).
    UNIHAN_TABLE_KLAU,			//!< Table for Practical Cantonese-English Dictionary by Sidney Lau.
    UNIHAN_TABLE_KMAINLANDTELEGRAPH,	//!< Table for PRC telegraph code for this character.
    UNIHAN_TABLE_KMANDARIN,		//!< Table for Mandarin pronunciation(s) for this character in pinyin.
    UNIHAN_TABLE_KMATTHEWS,		//!< Table for Mathews' Chinese-English Dictionary.
    UNIHAN_TABLE_KMEYERWEMPE,		//!< Table for Student's Cantonese-English Dictionary.
    UNIHAN_TABLE_KMOROHASHI,		//!< Table for Dae Kanwa Ziten, aka Morohashi dictionary (Japanese).
    UNIHAN_TABLE_KNELSON,		//!< Table for Modern Reader's Japanese-English Character Dictionary.
    UNIHAN_TABLE_KOTHERNUMERIC,		//!< Table for numeric values for characters in certain unusual, specialized contexts.
    UNIHAN_TABLE_KPHONETIC,		//!< Table for the phonetic index of characters from Ten Thousand Characters: An Analytic Dictionary.
    UNIHAN_TABLE_KPRIMARYNUMERIC,	//!< Table for values of characters when used in the writing of numbers in the standard fashion.
    UNIHAN_TABLE_KPSEUDOGB1, 		//!< Table for "GB 12345-90" code points  for the purposes of including it within Unihan. 
    UNIHAN_TABLE_KRSADOBE_JAPAN1_6,	//!< Table for Information on the glyphs in Adobe-Japan1-6 as contributed by Adobe.
    UNIHAN_TABLE_KRSJAPANESE,		//!< Table for Japanese radical/stroke count.
    UNIHAN_TABLE_KRSKANGXI,		//!< Table for KangXi radical/stroke count.
    UNIHAN_TABLE_KRSKANWA,		//!< Table for Morohashi radical/stroke count.
    UNIHAN_TABLE_KRSKOREAN,		//!< Table for Korean radical/stroke count.
    UNIHAN_TABLE_KRSUNICODE,		//!< Table for standard radical/stroke count.
    UNIHAN_TABLE_KSBGY,			//!< Table for Song Ben Guang Yun (SBGY) 《宋本廣韻》 Medieval Chinese character dictionary.
    UNIHAN_TABLE_KSEMANTICVARIANT,	//!< Table for Unicode value for a semantic variant characters.
    UNIHAN_TABLE_KSIMPLIFIEDVARIANT,	//!< Table for Unicode value for the simplified Chinese variant characters.
    UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT, //!< Table for Unicode value for a specialized semantic variant characters.
    UNIHAN_TABLE_KTAIWANTELEGRAPH,	//!< Table for Taiwanese telegraph code for this character.
    UNIHAN_TABLE_KTANG,			//!< Table for T'ang Poetic Vocabulary.
    UNIHAN_TABLE_KTOTALSTROKES,		//!< Table for total number of strokes of characters.(including the radical).
    UNIHAN_TABLE_KTRADITIONALVARIANT,   //!< Table for Unicode value(s) for the traditional Chinese variant characters.
    UNIHAN_TABLE_KVIETNAMESE,		//!< Table for characters' pronunciations in in Quốc ngữ.
    UNIHAN_TABLE_KXEROX,		//!< Table for Xerox codes.
    UNIHAN_TABLE_KXHC1983,		//!< Table for One or more Hanyu pinyin reading as given in Xiandai Hanyu Ciden.
    UNIHAN_TABLE_KZVARIANT,		//!< Table for Z-variants.

    UNIHAN_TABLE_UTF8,			//!< Table for UTF-8.
    UNIHAN_TABLE_IRG_SOURCE,		//!< Table for IRG Sources.
    UNIHAN_TABLE_IRG_SOURCE_MAPPING,	//!< Table for IRG Sources and its mapping/code.
    UNIHAN_TABLE_KSEMANTICVARIANT_EXTRA,  //!< Table for dictionary that states the semantical relationship.
    UNIHAN_TABLE_KSPECIALIZEDSEMANTICVARIANT_EXTRA, //!< Table for dictionary that states the semantical relationship.
    UNIHAN_TABLE_KZVARIANT_EXTRA	//!< Table for the source of Z variant.
} UnihanTable;

/**
 * Number of tables in database.
 */
#define UNIHAN_TABLES_COUNT	UNIHAN_TABLE_KZVARIANT_EXTRA +1

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

