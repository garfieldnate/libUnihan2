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
#include <sys/types.h>
#include <regex.h>

/**
 * Convert char to unsigned integer.
 *
 * @param c char to be converted.
 * @return unsigned integer representation of \a c.
 */
#define CHAR_TO_UNSIGNEDINT(c)  (unsigned int)  ((int) c >=0)? c : c+256

/**
 * Convert char to guchar.
 *
 * @param c char to be converted.
 * @return guchar representation of \a c.
 */
#define CHAR_TO_UNSIGNEDCHAR(c) (guchar) ((int) c >=0)? c : c+256

/**
 * StringPtrList is a structure that stores a list of string pointers.
 *
 * StringPtrList provides convenient access of a list of strings by wrapping
 * <a href="http://library.gnome.org/devel/glib/stable/glib-Pointer-Arrays.html">GPtrArray</a>.
 *
 * Note the length of the GPtrArray is always the number of strings plus one,
 * as the last element of the GPtrArray is always NULL,
 * to make the pointer of char pointers (char **) conversion easier.
 * Keep this in mind when using GPtrArray functions to manipulate StringPtrArray.
 *
 * @see ::StringList if you want to copy the content as well.
 */
typedef GPtrArray StringPtrList;

/**
 * Create a new StringPtrList instance.
 *
 * @return The pointer to the allocated space.
 */
StringPtrList *stringPtrList_new();

/**
 * Create a new StringPtrList instance with given sizes.
 *
 * This function allocate space for a StringList with given size, thus avoid
 * frequent reallocation.
 *
 * @param chunk_size Size in bytes required for string storage.
 * @param element_count Number of strings.
 * @return the pointer to the allocated space.
 */
StringPtrList *stringPtrList_sized_new(size_t element_count);

/**
 * Clear all content of StringPtrlist.
 *
 * @param sPtrList A StringList.
 */
void stringPtrList_clear(StringPtrList *sPtrList);

/**
 * Return index of the first match string in StringPtrList.
 *
 * This function returns index of the first match string in StringPtrList,
 * if no such string, then return -1.
 *
 * @param sPtrList A StringPtrList.
 * @param str The string to be found.
 * @return The index of the string from 0 if found; -1 otherwise.
 */
gint stringPtrList_find_string(StringPtrList *sPtrList,const gchar* str);

/**
 * Free a StringPtrlist and its content.
 *
 * @param sPtrList A StringPtrList.
 */
void stringPtrList_free_deep(StringPtrList *sPtrList);

/**
 * Whether a string is in StringPtrList.
 *
 * Return TRUE if at least one string in \a sPtrList is identical with \a str;
 *  otherwise return FALSE.
 *
 * @param sPtrList A StringPtrList.
 * @param str The string to be found.
 * @return TRUE if at least one string in \a sPtrList is identical with \a str;
 *         FALSE otherwise.
 */
gboolean stringPtrList_has_string(StringPtrList *sPtrList,const gchar* str);

/**
 * Return the string at the given index.
 *
 * @param sPtrList A StringPtrList.
 * @param index The given index.
 * @return The string at the given index.
 */
const gchar *stringPtrList_index(StringPtrList *sPtrList,guint index);

/**
 * Adds a string to the StringPtrList.
 *
 * This function inserts \a str by copy its pointer.
 *
 * Note that there is no stringList_insert_const() equivalent function,
 * because StringPtrList does not manage the memory.
 * StringList on the other hand, looks for identical strings in constant pool and use them
 * if available.
 *
 * @param sPtrList A StringPtrList.
 * @param str String to be inserted, can be NULL.
 * @return the index of the newly inserted string.
 * @see stringPtrList_insert_const()
 */
gint stringPtrList_insert(StringPtrList *sPtrList, const gchar *str);

/**
 * Return a char pointer pointer (char **) which points to the list of strings.
 *
 * This function returns a char** which points to the places that strings are
 * stored. The pointer directly points to content in StringPtrList instance, so the
 * returned pointer should not be free.
 *
 * @param sPtrList A StringPtrList.
 * @return The index of the string from 0 if found; -1 otherwise.
 */
gchar **stringPtrList_to_gcharPointerPointer(StringPtrList *sPtrList);

/**
 * StringList is a structure that stores a list of constant strings.
 *
 * StringList provides convenient index access and length information for a
 * <a href="http://library.gnome.org/devel/glib/stable/glib-String-Chunks.html#GStringChunk">GStringChunk</a>.
 * However, instead of returning char pointers, StringList functions return the
 * indexes of the strings, which can be used later on to located inserted
 * strings.
 *
 * StringList inserts string by copies the string content, so developers do not need to worry about
 * the memory allocation.
 *
 * @see ::StringPtrList if you want to allocate the string on your own.
 */
typedef struct {
    GStringChunk *chunk; //!< GStringChunk that actually stores the strings.
    StringPtrList *ptrArray; //!< A StringPtrList that holds all the string pointers.
    GHashTable *hTable;  //!< Hash table for constant insert. String is key , and pointer of the string is the value.
    guint len;		 //!< Number of strings in the StringList.
    size_t chunk_size_inital;  //!< Size of the GStringChunk.
} StringList;

/**
 * Create a new StringList instance.
 *
 * @return The pointer to the allocated space.
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
 * @return The pointer to the allocated space.
 */
StringList *stringList_sized_new(size_t chunk_size, size_t element_count);

/**
 * Create a new StringList instance from splitting string into a number of tokens not containing any of the characters in delimiter.
 *
 * A token is the non-empty longest string that does not contain any of the characters in delimiters.
 * If max_tokens is reached, the remainder is appended to the last token. Like g_strsplit_set(),
 * this function does insert empty string in StringList.
 *
 * For example the result of stringList_new_strsplit_set("abc +def"," +",-1) inserts "abc", "", "def" into StringList.
 *
 * Note that this function works on bytes not characters, so it can't be used to delimit UTF-8 strings for anything but ASCII characters.
 *
 * @param string	The string to be tokenized.
 * @param delimiters	A nul-terminated string containing bytes that are used to split the string.
 * @param max_tokens The maximum number of tokens to split string into. If this is less than 1, the string is split completely
 * @return A newly allocated StringList instance that holds the split string.
 * @see stringList_new_strsplit_set_skip_empty()
 */
StringList *stringList_new_strsplit_set(const gchar *string, const gchar *delimiters, gint max_tokens);

/**
 * Create a new StringList instance from splitting string into a number of non-empty tokens not containing any of the characters in delimiter.
 *
 * A token is the non-empty longest string that does not contain any of the characters in delimiters.
 * If max_tokens is reached, the remainder is appended to the last token. Unlike g_strsplit_set(),
 * this function does not insert empty string in StringList.
 *
 * For example the result of stringList_new_strsplit_set("abc +def"," +",-1) inserts "abc", "def" into StringList.
 *
 * Note that this function works on bytes not characters, so it can't be used to delimit UTF-8 strings for anything but ASCII characters.
 *
 * @param string	The string to be tokenized.
 * @param delimiters	A nul-terminated string containing bytes that are used to split the string.
 * @param max_tokens The maximum number of tokens to split string into. If this is less than 1, the string is split completely
 * @return A newly allocated StringList instance that holds the split string.
 * @see stringList_new_strsplit_set()
 */
StringList *stringList_new_strsplit_set_skip_empty(const gchar *string, const gchar *delimiters, gint max_tokens);

/**
 * Clear all content of Stringlist.
 *
 * @param sList A StringList.
 */
void stringList_clear(StringList *sList);

/**
 * Return index of the first match string in StringList.
 *
 * This function returns index of the first match string in StringList,
 * if no such string, then return -1.
 *
 * @param sList A StringList.
 * @param str The string to be found.
 * @return The index of the string from 0 if found; -1 otherwise.
 */
gint stringList_find_string(StringList *sList,const char* str);


/**
 * Whether a string is in StringList.
 *
 * Return TRUE if at least one string in \a sList is identical with \a str;
 *  otherwise return FALSE.
 *
 * @param sList A StringList.
 * @param str The string to be found.
 * @return TRUE if at least one string in \a sList is identical with \a str;
 *         FALSE otherwise.
 */
gboolean stringList_has_string(StringList *sList,const gchar* str);

/**
 * Return a char pointer pointer (char **) which points to the list of strings.
 *
 * This function returns a char** which points to the places that strings are
 * stored.
 * The pointer directly points to content in StringList instance, so the
 * returned pointer should not be free.
 *
 * @param sList A StringList.
 * @return The index of the string from 0 if found; -1 otherwise.
 */
gchar **stringList_to_charPointerPointer(StringList *sList);

/**
 * Return the string at the given index.
 *
 * @param sList A StringList.
 * @param index The given index.
 * @return The string at the given index.
 */
const gchar *stringList_index(StringList *sList,guint index);

/**
 * Adds a copy of string to the StringList.
 *
 * This function inserts a copy of  \a str to the string list, and return the index of
 * the string, which is also the last element in the string list.
 *
 * It calls g_string_chunk_insert() to insert a copy to string,
 * then appends the returned pointer from g_string_chunk_insert() to
 * the pointer array.
 * After that, this function return the index of the appended string pointer.
 *
 * The difference between this function and stringList_insert_const() is that
 * each inserted identical string will have it own spaces.
 *
 * @param sList A StringList.
 * @param str String to be inserted, can be NULL.
 * @return the index of the newly inserted string.
 * @see stringList_insert_const()
 */
guint stringList_insert(StringList *sList, const gchar *str);

/**
 * Adds a copy of string to the StringList, unless the identical string has already
 * been added to the StringList with stringList_insert_const().
 *
 * This function inserts a copy \a str to the string list,
 * unless the identical string has already been previous inserted
 * by this function. Useful if you do not want to spend extra space to store
 * identical strings.
 *
 * If identical string is previous inserted by this function,
 * which means the string is in the const hash table,
 * the pointer to the previous inserted string is append to the pointer array;
 * if no identical string is inserted, then a copy of \a str will be inserted,
 * to the string list by g_string_chunk_insert_const(),
 * then the returned pointer is inserted to the pointer array.
 * After that, this function return the index of the appended string pointer.
 *
 * \note It will not check the duplicate strings inserted by
 *  stringList_insert().
 *
 * @param sList A StringList.
 * @param str String to be inserted.
 * @return the index of the newly inserted string.
 * @see stringList_insert()
 */
guint stringList_insert_const(StringList *sList, const gchar *str);

/**
 * Free the StringList instance.
 *
 * Note that this function assumes the sList is not NULL.
 * Use <code> if (sList) stringList_free(sList);</code> to tolerate the NULL
 * parameter.
 *
 * @param sList A StringList.
 */
void stringList_free(StringList *sList);


/**
 * Combine a list of strings into a specified format.
 *
 * This function combines a list of strings (\a sList) into a newly allocated string,
 * according to the format string \c format.
 *
 * The format string a character string, which is composed of zero or more directives:
 * ordinary characters (not $),
 * which are copied unchanged to the output string;  and  format directives,  each  of
 * which  results in fetching zero or more subsequent arguments.
 * Each format directives is introduced by the character $, followed by optional flags,
 * mandatory argument id, and optional options like substitute strings or padding instruction.
 * In  between  there may be (in this order) zero or more flags, one to three optional
 * options. Note that at most one flag can be used in format directives.
 *
 * The format of a format directive is:
 * <code>$[flag]&lt;argument id&gt;[{[option1[,option2[,option3]]]}]</code>
 * If no flags are given, format directives are substituted by arguments they refer.
 *
 * The argument id starts from 0, but should not exceed the number of arguments.
 *
 * Following flags provide additional output control:
 * - N&lt;id&gt;{str1 [,str2]}:
 *   if argument \c id is nonempty, then \c str1 is outputted for this format directives;
 *   otherwise outputs str2, or empty string if str2 is omitted.
 * - E&lt;id&gt;{str1 [,str2]}:
 *   similar with -N, but output str1 if argument \c id is empty, i.e, is NULL or has 0 length.
 * - U&lt;id&gt;:
 *   argument \c id should be outputted as uppercase. This directive is backed by g_utf8_strup(),
 *   so it will convert non-ascii unicode character as well.
 * - L&lt;id&gt;:
 *   argument \c id should be outputted as lowercase. This directive is backed by g_utf8_strdown(),
 *   so it will convert non-ascii unicode character as well.
 * - P&lt;id&gt;{length[,pad_char]}:
 *   argument \c id should be padded with \c pad_char on the left till it reaches the \c length.
 *   Space (' ') is used as pad_char if it is not given.
 * - p&lt;id&gt;{length[,pad_char]}:
 *   argument \c id should be padded with \c pad_char on the right till it reaches the \c length.
 *   Space (' ') is used as pad_char if it is not given.
 * - X&lt;id&gt;[{length}]:
 *   output argument \c id as hexadecimal if it contains a literal integer.
 *   If length is given, 0  will be padded on the left of the argument.
 *   Note that NULL is returned if argument \c id cannot be converted by strtol().
 * - T&lt;id&gt;:
 *   output argument \c id as UTF-8 string if it contains a literal integer.
 *   Note that NULL is returned if argument \c id cannot be converted by strtol() and g_unichar_to_utf8 ().
 * - S&lt;id&gt;{beginIndex[,length]}:
 *   output substring of argument \c id which begins from \c beginIndex,
 *   if \c length is not given, the it will output till the end of argument \c id.
 * - I&lt;id&gt;{compare_str,true_substitute[,false_substitute]}:
 *   output \c true_substitute if \c compare_str is identical to argument \c id;
 *   otherwise output \c false_substitute if given.
 * - +&lt;id&gt;:
 *   if argument \c id is nonempty, then adds 1 to provided counter and output the number.
 *   if argument \c id is empty, then outputs a empty string.
 * - -&lt;id&gt;:
 *   if argument \c id is nonempty, then minuses 1 to provided counter and output the number.
 *   if argument \c id is empty, then outputs a empty string.
 * - $:
 *   Outputs a '$' character.
 *
 * Character '$' is also an escape character. For example,
 *  '$N1{${}' outputs  '{' if argument 1 is nonempty.
 *
 * This function is similar with sprintf(), except:
 * - This function accept a fixed length StringList.
 * - This function provides conditional control.
 * - This function supports utf8 case changing.
 * - This function is capable of using counter.
 * - This function returns a newly allocated result string.
 * - Format directives can be nested in this function.
 *
 * @param format the format for evaluate output.
 * @param sPtrList The StringPtrList that hold arguments.
 * @param counter_ptr a pointer to an integer counter. Can be NULL if + or - flags are not required.
 * @return a newly allocated result string; or NULL if error occurs.
 */
gchar *string_formatted_combine(const gchar *format,StringPtrList *sPtrList,gint *counter_ptr);

/**
 * @defgroup Regex_Manipulating_Funcs Regex manipulating functions.
 * @{
 * @name Regex manipulating functions.
 *
 * These functions provide evaluation and search-replace functions for regex matches.
 * They are based with \c regex.h, thus format of search pattern and
 * option flags are same as used in regcomp() and regexec().
 *
 * These functions are capable of dealing with parenthesized sub patterns,
 * which are referred as their pattern id.
 * Id 0 refers the whole matched pattern, 1 refers the first sub pattern,
 * and 2 for second sub pattern, and so on.
 *
 * The matched sub-patterns are extracted and stored in a StringPtrList, then processed
 * by string_formatted_combine().
 * @{
 */

/**
 * Combine sub-matches of a regex search into a specified format, if the regex expression is complied as a regex_t.
 *
 * This function combines sub-matches of a regex search into a specified format.
 * Use this function if the regex expression is already complied as a \c regex_t.
 *
 * Use g_free() to free the result, also regfree() \c preg if no longer used.
 *
 * @param str String to be matched.
 * @param preg regex pattern buffer which is generated by regcomp().
 * @param format the format of output string, which consists one to multiple pattern substitute.
 * @param eflags Flags for regexec().
 * @param counter_ptr a pointer to an integer counter. Can be NULL if + or - flags are not required.
 * @return An newly allocated combined string, or NULL if no match or have error.
 *
 * @see string_regex_formatted_combine()
 * @see string_regex_replace_regex_t()
 * @see string_regex_replace()
 */
gchar *string_regex_formatted_combine_regex_t(const gchar *str, const regex_t *preg, const gchar *format,
	gint eflags, gint *counter_ptr);

/**
 * Combine sub-matches of a regex search into a specified format.
 *
 * This function combines sub-matches of a regex search into a specified format.
 *
 * It also generates \c regex_t and frees it before the returning.
 * Consider use regcomp() and string_regex_formatted_combine_regex_t() if same \c pattern
 * will be use many times.
 *
 * Use g_free() to free the result.
 * @param str String to be matched.
 * @param pattern Pattern for matching.
 * @param format the format of output string, which consists one to multiple pattern substitute.
 * @param cflags Flags for regcomp().
 * @param eflags Flags for regexec().
 * @param counter_ptr a pointer to an integer counter. Can be NULL if + or - flags are not required.
 * @return An newly allocated combined string, or NULL if no match or have error.
 *
 * @see string_regex_formatted_combine_regex_t()
 * @see string_regex_replace_regex_t()
 * @see string_regex_replace()
 */
gchar *string_regex_formatted_combine(const gchar *str, const gchar *pattern, const gchar *format,
	gint cflags, gint eflags, gint *counter_ptr);

/**
 * Replace a new text for the substring matching a regular expression.
 *
 * This function replaces the regex matched sub-string to the string specified in \c format,
 * and returns a newly allocated string that holds the result.
 *
 * This function differs with string_regex_formatted_combine_regex_t(),
 * as string_regex_formatted_combine_regex_t() substitutes and returns only the matched substring,
 * while this function keeps the parts that does not match the pattern.
 *
 * Use g_free() to free the result.
 *
 * @param str String to be matched.
 * @param preg regex pattern buffer which is generated by regcomp().
 * @param format the format of output string, which consists one to multiple pattern substitute.
 * @param eflags Flags for regexec().
 * @param counter_ptr a pointer to an integer counter. Can be NULL if + or - flags are not required.
 * @return An newly allocated string whose matched pattern is replaced; or NULL if no match or have error.
 *
 * @see string_regex_formatted_combine_regex_t()
 * @see string_regex_formatted_combine()
 * @see string_regex_replace()
 */
gchar *string_regex_replace_regex_t(const gchar *str, const regex_t *preg, const gchar *format,
	gint eflags, gint *counter_ptr);

/**
 * Replace a new text for the substring matching a regular expression.
 *
 * This function replaces the regex matched sub-string to the string specified in \c format,
 * and returns a newly allocated string that holds the result.
 *
 * This function differs with string_regex_eval_regex_t(),
 * as string_regex_formatted_combine_regex_t() substitutes and returns only the matched substring,
 * while this function keeps the parts that does not match the pattern.
 *
 * Use g_free() to free the result.
 *
 * @param str String to be matched.
 * @param pattern Pattern for matching.
 * @param format the format of output string, which consists one to multiple pattern substitute.
 * @param cflags Flags for regcomp().
 * @param eflags Flags for regexec().
 * @param counter_ptr a pointer to an integer counter. Can be NULL if + or - flags are not required.
 * @return An newly allocated string whose matched pattern is replaced., or NULL if no match or have error.
 *
 * @see string_regex_formatted_combine_regex_t()
 * @see string_regex_formatted_combine()
 * @see string_regex_replace_regex_t()
 */
gchar *string_regex_replace(const gchar *str, const gchar *pattern, const gchar *format,
	gint cflags, gint eflags, gint *counter_ptr);

/**
 * @}
 * @}
 */

/**
 * Initialize the string by setting the first char to 0x0.
 *
 * The first byte of \a str will be set as '\0'.
 * Return NULL if \a str is NULL.
 *
 * @param str String to be initialize.
 * @return The initialized string, or NULL if str is NULL.
 */
gchar*
initString(gchar *str);


/**
 * Check whether the string is NULL or have 0 length.
 *
 * @param str String to be check.
 * @return False if the string is not empty, true otherwise.
 */
gboolean
isEmptyString(const gchar *str);

/**
 * Trim the leading and trailing whitespace of the string.
 *
 * Note the content of <code>str</code> might be changed.
 * Use strdup() or  g_strdup() to backup.
 *
 * @param str String to be trim.
 */
void string_trim(gchar *str);


/**
 * Return a substring of the given string.
 *
 * The substring begins at the specified beginIndex and end after <code>length</code> bytes.
 * The index starts from zero.
 * If length is given a negative value, then a substring starting from \c beginIndex to the
 * end of \c str is returned.
 *
 * @param str String to be process
 * @param beginIndex the beginning index, inclusive.
 * @param length total bytes to copy, excluding the trailing '\0'
 * @return A newly allocated string which is a substring of \c str.
 * @see subString_buffer()
 */
gchar*
subString(const gchar *str,gint beginIndex, gint length);

/**
 * Return a substring of the given string in given buffer.
 *
 * This function is similar with subString(), except it stores the result in
 * the developer-provided buffer.
 *
 * Make sure to provide at least length+1 (including the trailing '\0');
 * or strlen(str)-beginIndex+1 if length is negative.
 *
 *
 * @param buf buffer that stores the result.
 * @param str String to be process
 * @param beginIndex the beginning index, inclusive.
 * @param length total bytes to copy.
 * @return The buffer that stores the result.
 * @see subString()
 */
gchar*
subString_buffer(gchar *buf,const gchar *str,gint beginIndex, gint length);

/**
 * Append a character to a string.
 *
 * This function appends a character \a ch to the end of \a str,
 * if the length of the string including the trailing '\0' is less than the given \a length.
 * It returns \c NULL if \a ch cannot be appended because the length limit.
 *
 * Note that \a str will be modified if \a ch is successfully appended.
 * @param str The string.
 * @param ch The char to be appended to \a str.
 * @param length The maximum length of \a str ('\0' included).
 * @return \a str if success, NULL if failed.
 */
gchar* string_append_c(gchar *str, const char ch,size_t length);

/**
 * Whether a string is decomposed (no validation).
 *
 * The main purpose of this function is to provides a quick check of whether a
 * \a str is decomposed, so developers can determine to leave it or composite it back.
 * However, it only compares lengths before and after the normalization, and nothing beyond.
 * Use this function with care.
 *
 *
 * @param str The string to be checked.
 * @return TRUE if the string is decomposed, FALSE otherwise.
 */
gboolean string_is_decomposed_fast(const gchar *str);

/**
 * Pad a string on the left up to certain length.
 *
 * Note that if \c padding_str is multi-bytes, the padding will not exceed the \c length.
 *
 * @param str original string.
 * @param padding_str string to be padded on the left.
 * @param length length in bytes.
 * @return A newly allocated string that store the padded string.
 */
gchar* string_padding_left(const gchar *str, const gchar *padding_str, size_t length);

/**
 * Pad a string on the right up to certain length.
 *
 * Note that if \c padding_str is multi-bytes, the padding will not exceed the \c length.
 *
 * @param str original string.
 * @param padding_str string to be padded on the right.
 * @param length length in bytes.
 * @return A newly allocated string that store the padded string.
 */
gchar* string_padding_right(const gchar *str, const gchar *padding_str, size_t length);

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
gchar* utf8_concat_ucs4(gchar* utf8_str,gunichar ucs4_code);

/**
 * Compare between signed and guchar arrays.
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
gint strcmp_unsigned_signed(const guchar *str1, const gchar *str2);

/**
 * Convert the signed char string to a new allocated guchar string.
 *
 * @param str Signed char string.
 * @return A new allocated guchar string.
 *
 * @see signedStr_to_unsignedStr_buffer()
 * @see unsignedStr_to_signedStr()
 * @see unsignedStr_to_signedStr_buffer()
 */
guchar *signedStr_to_unsignedStr(const gchar *str);

/**
 * Convert the signed char string to the guchar string buffer.
 *
 * @param resultBuf The buffer that stored the conversion result.
 * @param str Signed char string.
 *
 * @see signedStr_to_unsignedStr()
 * @see unsignedStr_to_signedStr()
 * @see unsignedStr_to_signedStr_buffer()
 */
guchar *signedStr_to_unsignedStr_buffer(guchar *resultBuf, const gchar *str);

/**
 * Convert the guchar string to a new allocated signed char string.
 *
 * @param str Unsigned char string.
 * @return A new allocated signed char string.
 *
 * @see signedStr_to_unsignedStr()
 * @see signedStr_to_unsignedStr_buffer()
 * @see unsignedStr_to_signedStr_buffer()
 */
char *unsignedStr_to_signedStr(const guchar *str);

/**
 * Convert the guchar string to the signed char string buffer.
 *
 * @param resultBuf The buffer that stored the conversion result.
 * @param str Unsigned char string.
 *
 * @see signedStr_to_unsignedStr()
 * @see signedStr_to_unsignedStr_buffer()
 * @see unsignedStr_to_signedStr()
 */
gchar *unsignedStr_to_signedStr_buffer(gchar* resultBuf, const guchar *str);


#endif /*STR_FUNCTIONS_H_*/
