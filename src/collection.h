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
 * Handle Collections such as Hash Set
 *
 */
#ifndef COLLECTION_H_
#define COLLECTION_H_
#include <glib.h>
#define G_ARRAY_COPY(dest,src) g_array_append_vals(dest,src->data,src->len)
#define G_ARRAY_REMOVE_ALL(array) if (array->len>0) g_array_remove_range(array,0,array->len)
#define G_PTR_ARRAY_REMOVE_ALL(array) if (array->len>0) g_ptr_array_remove_range(array,0,array->len)

/**
 * ForeachCallbackFunc:
 * @data: the element in collection
 * @userdata: other option for the callback function.
 * @returns: TRUE to continue, FALSE to break.
 *
 * A prototype for callback functions that used with foreach functions.
 */
typedef gboolean (* ForeachCallbackFunc) (gpointer data, gpointer userdata);

/**
 * SetType:
 * @INTERGER_SET: Specify that set elements are integers
 * @STRING_SET: Specify that set elements are strings
 * @DIRECT_SET: Specify that set elements are pointers
 * @CUSTOM_SET: Used if non of above fit the need.
 *
 * Specify what will be stored in the set.
 */ 
typedef enum{
    INTEGER_SET,
    STRING_SET,
    DIRECT_SET,
    CUSTOM_SET
} SetType;


typedef struct HashSet_{
    GHashTable *hTable;
    SetType setType;
}HashSet;

HashSet *hashSet_new_auto(SetType type);

HashSet *hashSet_new(SetType type,GHashFunc hash_func, GEqualFunc key_equal_func) ;

HashSet *hashSet_new_full(SetType type,GHashFunc hash_func, GEqualFunc key_equal_func,
             GDestroyNotify key_destroy_func, GDestroyNotify value_destroy_func) ;

void hashSet_reset(HashSet *s);

void hashSet_copy(HashSet *dest, HashSet *src);

guint hashSet_get_size(HashSet *s);

gboolean hashSet_has_element(HashSet *set,gconstpointer key);

GList* hashSet_get_elements(HashSet *s);

/**
 * hashSet_add_element:
 * Add new element to @s, if it does not have the element.
 * 
 * @s the HashSet
 * @key the element to be insert
 */
gboolean hashSet_add_element(HashSet *s,gpointer key);

gboolean hashSet_remove_element(HashSet *s,gconstpointer key);

void hashSet_union(HashSet *result, HashSet *s1, HashSet *s2);

void hashSet_interset(HashSet *result, HashSet *s1, HashSet *s2);

gchar* hashSet_to_string(HashSet *s);

void hashSet_destroy(HashSet *s);

gint integer_compareFunc(gconstpointer a,gconstpointer b);

gint g_array_find(GArray *array,gpointer key, gint keySize,GCompareFunc func);

GArray *g_array_copy(GArray *dest,GArray *src);

#endif /*COLLECTION_H_*/

