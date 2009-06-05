/**
 * @file collection.h
 * @brief Functions for collection data structures such as set and array .
 *
 * This header file lists functions for collection data structures such as set and array.
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

#ifndef COLLECTION_H_
#define COLLECTION_H_
#include <glib.h>

/**
 * Enumerate Type.
 *
 * Type that handles various enumerate.
 * The \c index can be either array index for array-type data;
 * or status id of other sequential  data.
 *
 * Example:
 * <code>Enumerate *someCollection_enumerate()</code>
 *
 * <code>gboolean  someCollection_hasNext(Enumerate *e)</code>
 *
 * <code>void *someCollection_next(Enumerate *e)</code>
 */
typedef struct{
    glong index;    //!< Internal index.
    gpointer userData; //!< User data.
} Enumerate;

/**
 * Enumeration of element types which the collection stores.
 *
 * Specifying the element types of for collection has following benefits:
 * -# Easier type checking
 * -# Automatically assign the corresponding comparison functions.
 *
 * @see ::HashSet
 */
typedef enum{
    ELEMENTS_TYPE_INTEGER, //!< Specify that collection elements are integers.
    ELEMENTS_TYPE_STRING,  //!< Specify that collection elements are strings.
    ELEMENTS_TYPE_POINTER, //!< Specify that collection elements are pointers.
    ELEMENTS_TYPE_CUSTOM   //!< Specify that collection elements are user-defined type.
} ElementType;

/**
 * HashSet: A set which backed by Hash Table.
 *
 * HashSet provides a hash table (GHashTable) backed data structure for set-like data.
 * Unlike GHashTable which works on key-value pairs;
 * HashSet, however, deals with only element values, as they serve as both keys and values.
 * In other words, each element value is inserted to GHashTable as keys and values.
 *
 * The property \c setType not only tells what this HashSet stores, but also determine
 * the default handler functions such as element hash and equal functions.
 *
 * Note that due to the nature or hash table, the element order is deemed to be unstable.
 * Also, since GHashTable does not copy key and value, neither does HashSet.
 * The referred storages should remain present until HashSet is freed.
 *
 * @see ::ElementType
 */
typedef struct {
    GHashTable *hTable; //!< The backing GHashTable.
    ElementType setType; //!< Element type of key.
}HashSet;


/**
 * Foreach callback function prototype.
 *
 * @param data The collection to be process.
 * @param userdata The other options for the callback function. Can be \c NULL.
 * @return TRUE to continue; FALSE to break.
 *
 * A prototype for callback functions that used with foreach functions.
 */
typedef gboolean (* ForeachCallbackFunc) (gpointer data, gpointer userdata);

/**
 * New a HashSet instance with default handling functions.
 *
 * This function returns a new HashSet with default handling functions.
 * Specifically:
 * <table border="1" width="100%">
 * <tr><th>ElementType</th><th>hash_func</th><th>element_equal_func</th>
 *     <th>element_destroy_func</th><th>value_destroy_func</th></tr>
 * <tr><td>ELEMENTS_TYPE_INTEGER</td><td>g_int_hash()</td><td>g_int_equal()</td>
 *     <td>NULL</td><td>NULL</td></tr>
 * <tr><td>ELEMENTS_TYPE_STRING</td><td>g_str_hash()</td><td>g_str_equal()</td>
 *     <td>NULL</td><td>NULL</td></tr>
 * <tr><td>ELEMENTS_TYPE_POINTER</td><td>g_direct_hash()</td><td>g_direct_equal()</td>
 *     <td>NULL</td><td>NULL</td></tr>
 * <tr><td>ELEMENTS_TYPE_CUSTOM</td><td>NULL</td><td>NULL</td>
 *     <td>NULL</td><td>NULL</td></tr>
 * </table>
 *
 * Note that no default handler functions are associated with
 * element type ELEMENTS_TYPE_CUSTOM, please use hashSet_new() or hashSet_new_full()
 * instead.
 * @param type ElementType.
 * @return a new HashSet instance.
 * @see hashSet_new()
 * @see hashSet_new_full()
 */
HashSet *hashSet_new_default(ElementType type);

/**
 * New a HashSet instance.
 *
 * This function returns a new HashSet.
 * It is actually hashSet_new_full(type,hash_func,element_equal_func,NULL).
 *
 * @param type ElementType.
 * @param hash_func GHashFunc callback function for computing hash.
 * @param element_equal_func GEqualFunc callback function for comparing two keys.
 * @return a new HashSet instance.
 * @see hashSet_new_default()
 * @see hashSet_new_full()
 */
HashSet *hashSet_new(ElementType type,GHashFunc hash_func, GEqualFunc element_equal_func) ;

/**
 * New a HashSet instance, while specifying element destroy function.
 *
 * This function returns a new HashSet, while specifying element destroy function.
 * It passes to GHashTable as \c g_hash_table_new_full(hash_func,element_equal_func,element_destroy_func,NULL).
 *
 * @param type ElementType.
 * @param hash_func GHashFunc callback function for computing hash.
 * @param element_equal_func GEqualFunc callback function for comparing two keys.
 * @param element_destroy_func GGDestroyNotify callback function that free the element storage.
 * @return a new HashSet instance.
 * @see hashSet_new_default()
 * @see hashSet_new()
 */
HashSet *hashSet_new_full(ElementType type,GHashFunc hash_func, GEqualFunc element_equal_func,
             GDestroyNotify element_destroy_func) ;


/**
 *  Copy from another HashSet.
 *
 *  This function copies the elements from \a src to \a dest.
 *  The old elements in \a dest will be removed by hashSet_remove_all().
 *
 * @param dest The HashSet to be copied to.
 * @param src  The HashSet to be copied from.
 */
void hashSet_copy(HashSet *dest, HashSet *src);

/**
 *  Get the number of elements in the HashSet.
 *
 *  This function gets the number of elements in the HashSet.
 *
 * @param hashSet The HashSet to be processed.
 * @return Number of elements in the HashSet.
 */
guint hashSet_get_size(HashSet *hashSet);

/**
 *  Whether a element is in  the HashSet.
 *
 *  This function determines whether a element is in  the HashSet.
 *
 * @param hashSet The HashSet to be processed.
 * @param element The element to be found.
 * @return TRUE if \a element is in \a hashSet ; FALSE otherwise.
 */
gboolean hashSet_has_element(HashSet *hashSet,gconstpointer element);


/**
 * Add an element to the HashSet.
 *
 * Add an element to \a hashSet, if it does not yet have an identical element.
 * Note that this function only copies the pointer of \a element, not the content.
 * So try not free the space that the \a element points to until \a element is removed from hashSet.
 *
 * @param hashSet The HashSet to be processed.
 * @param element The element to be added.
 * @return TRUE if the \a element has been added, FALSE if \a element has not been added because an identical element exists.
 */
gboolean hashSet_add_element(HashSet *hashSet,gpointer element);

/**
 *  Remove all elements in the set.
 *
 *  This function removes all elements in \a hashSet.
 *  If \c element_destroy_func is supplied when \a s is created,
 *  it will be executed to free the elements.
 *
 * @param hashSet The HashSet to be processed.
 * @see hashSet_remove_element()
 * @see hashSet_steal_all()
 * @see hashSet_steal_element()
 */
void hashSet_remove_all(HashSet *hashSet);


/**
 * Remove an element to the HashSet.
 *
 * Remove an element from \a hashSet.
 * Note that the \a element_destroy_func will be executed if it was given when constructing \a hashSet,
 * otherwise, only the pointer \a element will be removed, not the content.
 *
 * @param hashSet The HashSet to be processed.
 * @param element The element to be removed.
 * @return TRUE if the \a element  was found and removed. FALSE otherwise.
 * @see hashSet_remove_all()
 * @see hashSet_steal_all()
 * @see hashSet_steal_element()
 */
gboolean hashSet_remove_element(HashSet *hashSet,gconstpointer element);


/**
 *  Steal all elements in the set.
 *
 * This function "steals" all elements from \a hashSet by removing all the element from it,
 * but not free the content that the elements point to,
 * in spite of whether the \a element_destroy_func is given or not.
 *
 *
 * @param hashSet The HashSet to be processed.
 * @see hashSet_remove_all()
 * @see hashSet_remove_element()
 * @see hashSet_steal_element()
 */
void hashSet_steal_all(HashSet *hashSet);

/**
 * Steal an element to the HashSet.
 *
 * This function "steals" an element from \a hashSet by removing \a element from it,
 * but not free the content that \a element points to,
 * in spite of whether the \a element_destroy_func is given or not.
 *
 * @param hashSet The HashSet to be processed.
 * @param element The element to be removed.
 * @return TRUE if the \a element  was found and removed. FALSE otherwise.
 * @see hashSet_remove_all()
 * @see hashSet_remove_element()
 * @see hashSet_steal_all()
 */
gboolean hashSet_steal_element(HashSet *hashSet,gconstpointer element);

/**
 * @name Set operations.
 *
 * Set operation functions such as union and interset.
 * @{
 */
/**
 * Union two sets.
 *
 * This function performs a set union operation on \a hashSet1 and \a hashSet2,
 * and put the result set in \a result.
 * The set \a result can be either \a hashSet1, \a hashSet2 or another HashSet,
 * but cannot be \c NULL.
 *
 *
 * @param hashSet1 The HashSet to be processed.
 * @param hashSet2 The HashSet to be processed.
 * @param result The HashSet that holds the result.
 */
void hashSet_union(HashSet *result, HashSet *hashSet1, HashSet *hashSet2);

/**
 * Intersect two sets.
 *
 * This function performs a set intersect operation on \a hashSet1 and \a hashSet2,
 * and put the result set in \a result.
 * The set \a result can be either \a hashSet1, \a hashSet2 or another HashSet,
 * but cannot be \c NULL.
 *
 *
 * @param hashSet1 The HashSet to be processed.
 * @param hashSet2 The HashSet to be processed.
 * @param result The HashSet that holds the result.
 */
void hashSet_intersect(HashSet *result, HashSet *hashSet1, HashSet *hashSet2);

/**
 * @}
 */


/**
 * New a string representation for the content of the HashSet.
 *
 * This function produces a string representation of the HashSet.
 * The output formats are like (in printf() format):
 *
 * - ELEMENTS_TYPE_INTEGER: [ %d %d %d ... ]
 * - ELEMENTS_TYPE_STRING:  [ %s %s %s ... ]
 * - ELEMENTS_TYPE_POINTER: [ %p %p %p ... ]
 * - ELEMENTS_TYPE_CUSTOM:  [ %p %p %p ... ]
 *
 * The return string is new allocated, use \c free() or \c g_free() to free it.
 *
 * @param hashSet The HashSet to be processed.
 * @return a newly allocated string which represents the content of  result The HashSet that holds the result.
 */
char* hashSet_to_string(HashSet *hashSet);

/**
 * Free the hashSet instance.
 *
 * @param hashSet The HashSet to be processed.
 */
void hashSet_destroy(HashSet *hashSet);

/**
 * GCompareFunc that compares two intergers.
 *
 * @param a pointer to an integer.
 * @param b pointer to another integer.
 * @return negative value if value of a < b; zero if value of a = b; positive value if value of  a > b.
 */
int integer_compareFunc(gconstpointer a,gconstpointer b);

/**
 * Remove all elements of a GPTRArray.
 *
 * This macro removes all elements in \a array.
 * @param array GPtrArray to be processed.
 */
#define G_PTR_ARRAY_REMOVE_ALL(array) if (array->len>0) g_ptr_array_remove_range(array,0,array->len)

/**
 * Concatenate two GArrays.
 *
 * This macro appends GArray \a src to \a dest . The results is stored in \a dest.
 *
 * @param dest The GArray to be append to.
 * @param src The GArray to be appended from.
 * @return The GArray \a dest.
 */
#define G_ARRAY_CONCAT(dest,src) g_array_append_vals(dest,src->data,src->len)

/**
 * Remove all elements of a GArray.
 *
 * This macro removes all elements in \a array.
 * @param array GArray to be processed.
 */
#define G_ARRAY_REMOVE_ALL(array) if (array->len>0) g_array_remove_range(array,0,array->len)

/**
 * Find an element  in a GArray.
 *
 * This function uses \a func, A GCompareFunc to compare and find an element in \a array.
 * The prototype of GCompareFunc is:
 * <tt>int  (*GCompareFunc)  (gconstpointer a, gconstpointer b)</tt>
 *
 * Note that it finds whether the content of \a element is in the \a array .
 *
 * @param array The array to be processed.
 * @param element The element to be found.
 * @param elementSize  The number of bytes which the content of \a element occupies.
 * @param func The GCompareFunc that compar
 * @return index of the element in the array; -1 if such element cannot be found.
 */
int g_array_find(GArray *array, gpointer element, gint elementSize,GCompareFunc func);

/**
 * Copy from another GArray.
 *
 *  This function copies the elements from \a src to \a dest.
 *  The old elements in \a dest will be removed by G_ARRAY_REMOVE_ALL().
 *  Note that if \a src is NULL, content of \a dest will be freed.
 *
 * @param dest GArray to be copied to.
 * @param src GArray to be copied to.
 * @return The GArray \a dest.
 */
GArray *g_array_copy(GArray *dest,GArray *src);

#endif /*COLLECTION_H_*/

