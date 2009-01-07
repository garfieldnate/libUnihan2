/** 
 * @file Unihan_phonetic-private.h
 * @brief Phonetic symbols (Pinyin and Zhuyin) processing private definition
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

#ifndef UNIHAN_PHONETIC_PRIVATE_H_
#define UNIHAN_PHONETIC_PRIVATE_H_


/*=================================================================
 * PINYIN_REGEX_IMPORT
 */
/**
 * Regex pattern for tone accent mark.
 */
#define PINYIN_REGEX_IMPORT_TONE_ACCENTS  "((\xCC\x84)?(\xCC\x81)?(\xCC\x8C)?(\xCC\x80)?)?" // 13-17

#define PINYIN_REGEX_IMPORT_TEST_JQXY "(([JjQqXx])?([Yy])?)?"             // 2-4
#define PINYIN_REGEX_IMPORT_TEST_INITIAL "("  PINYIN_REGEX_IMPORT_TEST_JQXY\
    "([b-df-hk-npr-twzB-DF-HK-NPR-TWZ]*))"             // 1-5
#define PINYIN_REGEX_IMPORT_TEST_IUVE  "(([Ii])?([Uu]\xCC\x88|[Vv]|[Uu]:)?([Uu])?)?"\
    "([Ee]\xCC\x82|[Ee]\\^)?([Ee])?" // 6-9 10-11
#define PINYIN_REGEX_IMPORT_PRIVATE PINYIN_REGEX_IMPORT_TEST_INITIAL \
    PINYIN_REGEX_IMPORT_TEST_IUVE "([aeiouAEIOU]*)" \
    PINYIN_REGEX_IMPORT_TONE_ACCENTS "(:)?([ginoruGINORU]*)([1-5])?" // 1-5 6-12 13-20



/*-----------------------------------------------------------------
 * PINYIN_IMPORT_SUBSTITUTE
 */
#define PINYIN_IMPORT_SUBSTITUTE_E "$N11{$N6{E,$N4{E,$E1{$E12{$E19{$11,e},e},e}}}}"
/**
 * Pinyin pattern substitute (store format). Pinyin fields are stored as \c PINYIN_ACCENT_INTERNAL, without tone accent mark or number.
 */
#define PINYIN_IMPORT_SUBSTITUTE_PRIVATE "$L1$L7$N8{v}$N9{$N18{v,$N2{$E7{v,u},u}}}$N10{E}" \
    PINYIN_IMPORT_SUBSTITUTE_E "$L12$L19"

/**
 * Pinyin tone accent mark pattern substitute (store format).
 */
#define PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT_PRIVATE "$E13{$E20{5}}$N14{1}$N15{2}$N16{3}$N17{4}"

/*-----------------------------------------------------------------
 * PINYIN_IMPORT_SUBSTITUTE_XHC
 */

#define PINYIN_IMPORT_SUBSTITUTE_E_XHC "$N15{$N10{E,$N8{E,$E5{$E16{$E22{$15,e},e},e}}}}"

#define PINYIN_IMPORT_SUBSTITUTE_XHC_PRIVATE "$L5$L11$N12{v}$N13{$N22{v,$N6{$E11{v,u},u}}}$N14{E}" \
    PINYIN_IMPORT_SUBSTITUTE_E_XHC "$L16$L23"

#define PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT_XHC_PRIVATE "$E17{$E24{5}}$N18{1}$N19{2}$N20{3}$N21{4}"

/**
 * Combine sub-matches of a pinyin regex import search into a specified format.
 *
 * This function used the compiled pinyin regex import expression, #PINYIN_REGEX_IMPORT,
 * for search, then matched sub patterns are combined as specified in \a format.
 * 
 *
 * @param str String to be searched.
 * @param format Format of the output string.
 * @return An newly allocated combined string, or NULL if no match or have error.
 * @see #PINYIN_REGEX_IMPORT
 */
gchar *pinyin_regex_import_formatted_combine(const gchar *str, const gchar *format);



/**
 * Combine sub-matches of a pinyin regex search into a specified format.
 *
 * This function used the compiled pinyin regex import expression, #PINYIN_REGEX,
 * for search, then matched sub patterns are combined as specified in \a format.
 * 
 *
 * @param str String to be searched.
 * @param format Format of the output string.
 * @return An newly allocated combined string, or NULL if no match or have error.
 * @see PINYIN_REGEX_IMPORT
 */
gchar *pinyin_regex_formatted_combine(const gchar *str, const gchar *format);

/**
 * Combine sub-matches of a zhuyin regex search into a specified format.
 *
 * This function used the compiled zhuyin regex import expression, #ZHUYIN_REGEX,
 * for search, then matched sub patterns are combined as specified in \a format.
 * 
 *
 * @param str String to be searched.
 * @param format Format of the output string.
 * @return An newly allocated combined string, or NULL if no match or have error.
 * @see ZHUYIN_REGEX_IMPORT
 */
gchar *zhuyin_regex_formatted_combine(const gchar *str, const gchar *format);


#endif /* UNIHAN_PHONETIC_PRIVATE_H_ */
