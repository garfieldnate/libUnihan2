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
 * Convenient macros and functions to allocate objects, arrays or 2D arrays.
 *
 *
 */
#ifndef ALLOCATE_UTILS_H_
#define ALLOCATE_UTILS_H_
#include <stdlib.h>
#include <glib.h>
#define NEW_INSTANCE(type) (type*)g_malloc(sizeof(type))
#define NEW_ARRAY_INSTANCE(element_count,type) (type*)g_malloc(element_count*sizeof(type))

void **array2D_new(size_t row_size, size_t col_size, size_t element_size, size_t pointer_size);
void array2D_free(void **arrayPtr);
#define NEW_ARRAY2D_INSTANCE(row_size,col_size,type) (type**) array2D_new(row_size,col_size,sizeof(type),sizeof(type*));


#endif /*ALLOCATE_UTILS_H_*/
