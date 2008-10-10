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

#include "allocate.h"
#include "collection.h"
#include <stdio.h>
#include <glib.h>

typedef struct SetToStringArguments_ {
    ElementType type;
    GString *strBuf;
} SetToStringArguments;


static void hashSet_add_element_GHFunc(gpointer key, gpointer value, gpointer user_data) {
    HashSet *hashSet=(HashSet *) user_data;
    hashSet_add_element(hashSet,key);
}

static gboolean hashSet_interset_element_GHFunc(gpointer key, gpointer value, gpointer user_data) {
    HashSet *hashSet=(HashSet *) user_data;
    if (hashSet_has_element(hashSet,key)) {
        return FALSE;
    }
    return TRUE;
}

static void hashSet_to_string_GHFunc(gpointer key, gpointer value, gpointer user_data) {
    SetToStringArguments *arg=(SetToStringArguments *) user_data;
    gint *intValue;
    gchar *strValue;
    switch (arg->type) {
    case ELEMENTS_TYPE_INTEGER:
        intValue=(gint *) key;
        g_string_append_printf(arg->strBuf," %d",*intValue);
        break;
    case ELEMENTS_TYPE_STRING:
        strValue=(gchar *) key;
        g_string_append_printf(arg->strBuf," %s",strValue);
        break;
    case ELEMENTS_TYPE_POINTER:
        g_string_append_printf(arg->strBuf," %p",key);
        break;
    default:
        g_string_append_printf(arg->strBuf," %p",key);
        break;
    }
}

HashSet *hashSet_new_default(ElementType type){
    return hashSet_new(type,NULL,NULL);
}


HashSet *hashSet_new(ElementType type,GHashFunc hash_func, GEqualFunc element_equal_func){
    return hashSet_new_full(type,hash_func,element_equal_func,NULL);
}

HashSet *hashSet_new_full(ElementType type,GHashFunc hash_func, GEqualFunc element_equal_func,
             GDestroyNotify element_destroy_func) {
    GHashFunc hash_f=hash_func;
    GEqualFunc element_equal_f=element_equal_func;
    if (hash_f==NULL) {
        switch (type) {
        case ELEMENTS_TYPE_INTEGER:
            hash_f=g_int_hash;
            break;
        case ELEMENTS_TYPE_STRING:
            hash_f=g_str_hash;
            break;
        case ELEMENTS_TYPE_POINTER:
            hash_f=g_direct_hash;
            break;
        default:
            g_error("hashSet_new: GHashFunc is absent.\n");
            break;
        }
    }
    if (element_equal_func==NULL) {
        switch (type) {
        case ELEMENTS_TYPE_INTEGER:
            element_equal_f=g_int_equal;
            break;
        case ELEMENTS_TYPE_STRING:
            element_equal_f=g_str_equal;
            break;
        case ELEMENTS_TYPE_POINTER:
            element_equal_f=g_direct_equal;
            break;
        default:
            g_error("hashSet_new: GEqualFunc is absent.\n");
            break;
        }
    }
    HashSet *resultSet=NEW_INSTANCE(HashSet);
    resultSet->setType=type;
    resultSet->hTable=g_hash_table_new_full(hash_f,element_equal_f,element_destroy_func,NULL);
    return resultSet;
}

void hashSet_remove_all(HashSet *hashSet) {
    g_hash_table_remove_all(hashSet->hTable);
}

void hashSet_copy(HashSet *dest, HashSet *src) {
    if (dest->setType!=src->setType) {
        g_error("hashSet_copy: setType of dest (%d) and src (%d) should be the same.\n",dest->setType,src->setType);
    }
    hashSet_remove_all(dest);
    g_hash_table_foreach(src->hTable,hashSet_add_element_GHFunc,dest);
}

guint hashSet_get_size(HashSet *hashSet) {
    return g_hash_table_size(hashSet->hTable);
}

gboolean hashSet_has_element(HashSet *hashSet,gconstpointer element) {
    gpointer p=g_hash_table_lookup(hashSet->hTable,element);
    return (p!=NULL)? TRUE:FALSE;
}


gboolean hashSet_add_element(HashSet *hashSet,gpointer element) {
    if (!hashSet_has_element(hashSet,element)) {
        g_hash_table_insert(hashSet->hTable,element,element);
        return TRUE;
    }
    return FALSE;
}

gboolean hashSet_remove_element(HashSet *hashSet,gconstpointer element) {
    return g_hash_table_remove(hashSet->hTable,element);
}

void hashSet_union(HashSet *result, HashSet *s1,HashSet *s2) {
    if (s1!=result && s2!=result) {
        hashSet_remove_all(result);
    }
    g_hash_table_foreach(s1->hTable,hashSet_add_element_GHFunc,result);
    g_hash_table_foreach(s2->hTable,hashSet_add_element_GHFunc,result);
}

void hashSet_interset(HashSet *result, HashSet *s1,HashSet *s2) {
    HashSet *hashSet1,*hashSet2;
    if (s1!=result && s2!=result) {
        hashSet_copy(result,s1);
        hashSet1=result;
        hashSet2=s2;
    } else if (s1==result) {
        hashSet1=result;
        hashSet2=s2;
    } else {
        hashSet1=result;
        hashSet2=s1;
    }
    g_hash_table_foreach_remove(hashSet1->hTable,hashSet_interset_element_GHFunc,hashSet2);
}

gchar* hashSet_to_string(HashSet *hashSet) {
    GString *strBuf=g_string_new("[");

    SetToStringArguments arg;
    arg.type=hashSet->setType;
    arg.strBuf=strBuf;
    g_hash_table_foreach(hashSet->hTable,hashSet_to_string_GHFunc,&arg);
    g_string_append(strBuf," ]");
    return g_string_free(strBuf,FALSE);
}

void hashSet_destroy(HashSet *s){
    g_hash_table_destroy(s->hTable);
    g_free(s);
}

gint
integer_compareFunc(gconstpointer a, gconstpointer b){
    int *ia=(int *) a;
    int *ib=(int *) b;
    if (*ia<*ib){
        return -1;
    }else if (*ia>*ib){
        return 1;
    }
    return 0;
}


gint 
g_array_find(GArray *array,gpointer key, gint keySize,GCompareFunc func){
    gint len=array->len;
    gint i;
    for(i=0;i<len;i++){
        gpointer k=& array->data[i*keySize];
        if (func(k,key)==0)
            return i;
    }
    return -1;
}

GArray *g_array_copy(GArray *dest,GArray *src){
    if (src==NULL){
        if (dest){
            g_array_free(dest,TRUE);
        }
        return NULL;
    }
    if (dest==NULL){
        g_error("g_array_copy: dest cannot be null");
    }
    G_ARRAY_REMOVE_ALL(dest);
    return G_ARRAY_CONCAT(dest,src);
}

//int main(int argc,char** argv) {
//    GArray *array=g_array_new(FALSE,FALSE,sizeof(gint));
//    gint a1[]={10,9,8,7,6,5,4,3,2,1};
//    gint i;
//    for(i=0;i<10;i++){
//        g_array_append_val(array,a1[i]);
//    }
//    gint k[]={6,3,11};
//    gint result;
//    for(i=0;i<3;i++){
//        result=g_array_find(array,&k[i],sizeof(gint),integer_compareFunc);
//        printf("Result %d=%d\n",i+1,result);
//    }
//    return 0;
//}

//int main(int argc,char** argv) {
//    HashSet *s1=hashSet_new(ELEMENTS_TYPE_INTEGER,NULL,NULL);
//    HashSet *s2=hashSet_new(ELEMENTS_TYPE_INTEGER,NULL,NULL);
//    HashSet *s3=hashSet_new(ELEMENTS_TYPE_INTEGER,NULL,NULL);
//    int a1[]={ 1, 2, 3, 4, 5, 5};
//    int a2[]={ 2, 4, 4, 6, 8,10 };
//    int i;
//    for (i=0;i<6;i++) {
//        hashSet_add_element(s1,&a1[i]);
//        hashSet_add_element(s2,&a2[i]);
//    }
//    printf("Inital\n");
//    printf("s1=%s\n",hashSet_to_string(s1));
//    printf("s2=%s\n",hashSet_to_string(s2));
//    printf("s3=%s\n",hashSet_to_string(s3));


//    hashSet_union(s3,s1,s2);
//    printf("s3=s1+s2\n");
//    printf("s1=%s\n",hashSet_to_string(s1));
//    printf("s2=%s\n",hashSet_to_string(s2));
//    printf("s3=%s\n",hashSet_to_string(s3));

//    hashSet_interset(s3,s1,s2);
//    printf("s3=s1*s2\n");
//    printf("s1=%s\n",hashSet_to_string(s1));
//    printf("s2=%s\n",hashSet_to_string(s2));
//    printf("s3=%s\n",hashSet_to_string(s3));

//    hashSet_remove_all(s1);
//    hashSet_remove_all(s2);
//    for (i=0;i<6;i++) {
//        hashSet_add_element(s1,&a1[i]);
//        hashSet_add_element(s2,&a2[i]);
//    }
//    hashSet_union(s1,s1,s2);
//    printf("s1=s1+s2\n");
//    printf("s1=%s\n",hashSet_to_string(s1));
//    printf("s2=%s\n",hashSet_to_string(s2));
//    printf("s3=%s\n",hashSet_to_string(s3));

//    hashSet_remove_all(s1);
//    hashSet_remove_all(s2);
//    for (i=0;i<6;i++) {
//        hashSet_add_element(s1,&a1[i]);
//        hashSet_add_element(s2,&a2[i]);
//    }
//    hashSet_interset(s2,s1,s2);
//    printf("s2=s1*s2\n");
//    printf("s1=%s\n",hashSet_to_string(s1));
//    printf("s2=%s\n",hashSet_to_string(s2));
//    printf("s3=%s\n",hashSet_to_string(s3));
//}


