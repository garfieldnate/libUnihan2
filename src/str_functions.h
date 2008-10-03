/** 
 * @file str_functions.h
 * @brief String processing functions.
 * 
 * This header file lists the some string processing functions.
 * Such as subString, and StringList, which provides a memory efficient
 * methods to store a list of constrant strings.
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
 
#ifndef STR_FUNCTIONS_H_
#define STR_FUNCTIONS_H_
#include <string.h>
#include <glib.h>

/**
 * StringList is a structure that stores a list of constant strings.
 *
 * StringList provides convenient index access and length information for a 
 * <a href="http://library.gnome.org/devel/glib/stable/glib-String-Chunks.html#GStringChunk">GStringChunk</a>.
 *
 * However, instead of return char pointers, StringList functions return the
 * indexes of the strings because returning char pointers might cause more
 * confusion.
 */
typedef struct {
    GStringChunk *chunk; //!< GStringChunk that actually stores the strings.
    GPtrArray *ptrArray; //!< A array of char* that points to the strings.
    GArray *constArray;  //!< Stores the indexes of strings which are inserted constantly.
    guint len;		 //!< Number of strings in the StringList.
} StringList;

/**
 * Create a new StringList instance.
 *
 * @return the pointer to the allocated space.
 */
StringList *stringList_new();

/**
 * Create a new StringList instance with given sizes.
 *
 * This function allocate space for a StringList with given size, thus avoid
 * frequent reallocation.
 *
 * @param chunk_size Size in bytes required for string storage.
 * @param element_count Number of strings.
 * @param const_count Number of constant strings (strings without duplication).
 * @return the pointer to the allocated space.
 */
StringList *stringList_sized_new(size_t chunk_size, size_t element_count, size_t const_count);

/**
 * Clear all content of Stringlist.
 *
 * @param sList The StringList to be processed.
 */
void stringList_clear(StringList *sList);

/**
 * Find a string in StringList.
 *
 * If found, this function returns the index of the string from 0, otherwise returns -1.
 *
 * @param sList The StringList to be processed.
 * @param str The character to be found.
 * @return The index of the string from 0 if found; -1 otherwise.
 */
int stringList_find_string(StringList *sList,const char* str);

/**
 * Return a char pointer pointer (char **) which points to the list of strings. 
 *
 * This function returns a char** which points to the places that strings are
 * stored. 
 * The pointer directly points to content in StringList instance, so the
 * returned pointer should not be free.
 *
 * Use the stringList_free to free instead.
 *
 * @param sList The StringList to be processed.
 * @return The index of the string from 0 if found; -1 otherwise.
 */
char **stringList_to_charPointerPointer(StringList *sList);

/**
 * Return the string at the given index.
 *
 * @param sList The StringList to be processed.
 * @param index The given index.
 * @return The string at the given index. 
 */
const char *stringList_index(StringList *sList,guint index);

/**
 * Insert a string to StringList.
 *
 * This functions copies the str to the string list.
 * It behaves like g_string_chunk_insert(), that is, it does not check for the
 * duplicates. 
 * However, it returns the index instead of char pointer of inserted string.
 *
 * The difference between this function and stringList_insert_const() is that
 * each inserted identical string will have it own spaces.
 *
 * @param sList The StringList to be processed.
 * @param str String to be inserted, can be NULL.
 * @return the index of the newly inserted string.
 * @see stringList_insert_const()
 */
guint stringList_insert(StringList *sList, const char *str);

/**
 * Insert a constant string to StringList.
 *
 * This functions copies the str to the string list.
 * It behaves like g_string_chunk_insert_const(), that is, it checks for the
 * duplicates. 
 * However, it returns the index instead of char pointer of inserted string.
 *
 * The difference between this function and stringList_insert() is that
 * each inserted identical string will share the same space.
 *
 * @param sList The StringList to be processed.
 * @param str String to be inserted. 
 * @return the index of the newly inserted string.
 * @see stringList_insert()
 */
guint stringList_insert_const(StringList *sList, const char *str);

/**
 * Free the StringList instance.
 *
 * Note that this function assumes the sList is not NULL.
 * Use <code> if (sList) stringList_free(sList);</code> to tolerate the NULL
 * parameter.
 * 
 * @param sList The StringList to be processed.
 */
void stringList_free(StringList *sList);

/**
 * Initialize the string by setting the first char to 0x0.
 *
 * If str is NULL, then an char array with  MAX_STRING_BUFFER_SIZE will be assined.
 * @param str String to be initialize, NULL for allocate a new string..
 * @return The initialized string.
 */
char*
initString(char *str);


/**
 * Check whether the string is NULL or have 0 length.
 *
 * @param str String to be check.
 * @return False if the string is not empty, true otherwise.
 */
gboolean
isEmptyString(const char *str);

/**
 * Trim the leading and trailing whitespace of the string.
 *
 * Note the content of <code>str</code> might be changed. 
 * Use strdup() or  g_strdup() to backup.
 *
 * @param str String to be trim.
 */
void string_trim(char *str);


/**
 * Returns a substring of the given string. 
 * 
 * The substring begins at the specified beginIndex and end after <code>length</code> bytes.
 * The index starts from zero.
 * 
 * @param buf buffer that stores the result.
 * @param str String to be process
 * @param beginIndex the beginning index, inclusive.
 * @param length total bytes to copy.
 * @return The specified substring.
 */
char*
subString(char *buf,const char *str,int beginIndex, int length);

/**
 * Convert UCS-4 to UTF-8 string.
 *
 * @param ucs4_code the UCS-4 to be converted.
 * @return UTF-8 string that converted from the UCS-4 Code. Use g_free() after use.
 */
char* ucs4_to_utf8(gunichar ucs4_code);

/**
 * Convert UTF-8 string to UCS-4 (gunichar).
 *
 * @param utf8_str the UTF-8 string  to be converted.
 * @return UCS-4 representation of the UTF-8 string.
 */
gunichar* utf8_to_ucs4(const char* utf8_str);

/**
 * Concatenate a UCS-4 (gunichar) to an UTF-8 string
 *
 * @param utf8_str the UTF-8 string.
 * @param ucs4_code the UCS-4 to be appended.
 * @return a pointer to utf8_str;
 */
char* utf8_concat_ucs4(char* utf8_str,gunichar ucs4_code);

/**
 * Compare between signed and unsigned char arrays.
 *
 * It behaves like strcmp() except the comparison is between a unsigned string
 * (char array) and signed string. Mainly for GCC 4.3
 *
 * @param str1 Unsigned string to be compared.
 * @param str2 Signed string to be compared.
 * @return An integer less than, equal to, or greater than  zero  if
 *     str1  is found, respectively, to be less than, to match, or be greater
 *     than str2.
 */
int strcmp_unsigned_signed(const unsigned char *str1, const char *str2);

/**
 * Convert the signed char string to a new allocated unsigned char string.
 *
 * @param str Signed char string.
 * @return A new allocated unsigned char string.
 *
 * @see signedStr_to_unsignedStr_buffer()
 * @see unsignedStr_to_signedStr()
 * @see unsignedStr_to_signedStr_buffer()
 */
unsigned char *signedStr_to_unsignedStr(const char *str);

/**
 * Convert the signed char string to the unsigned char string buffer.
 *
 * @param resultBuf The buffer that stored the conversion result.
 * @param str Signed char string.
 *
 * @see signedStr_to_unsignedStr()
 * @see unsignedStr_to_signedStr()
 * @see unsignedStr_to_signedStr_buffer()
 */
unsigned char *signedStr_to_unsignedStr_buffer(unsigned char *resultBuf, const char *str);

/**
 * Convert the unsigned char string to a new allocated signed char string.
 *
 * @param str Unsigned char string.
 * @return A new allocated signed char string.
 *
 * @see signedStr_to_unsignedStr()
 * @see signedStr_to_unsignedStr_buffer()
 * @see unsignedStr_to_signedStr_buffer()
 */
char *unsignedStr_to_signedStr(const unsigned char *str);

/**
 * Convert the unsigned char string to the signed char string buffer.
 *
 * @param resultBuf The buffer that stored the conversion result.
 * @param str Unsigned char string.
 *
 * @see signedStr_to_unsignedStr()
 * @see signedStr_to_unsignedStr_buffer()
 * @see unsignedStr_to_signedStr()
 */
char *unsignedStr_to_signedStr_buffer(char* resultBuf, const unsigned char *str);


#endif /*STR_FUNCTIONS_H_*/
