/** 
 * @file allocate.h
 * @brief Convenient macros and functions for allocating objects, arrays or 2D arrays.
 * 
 * This header file lists the macros and functions for allocating instance,
 * 1-D and 2-D instance array of given type.
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
 
#ifndef ALLOCATE_UTILS_H_
#define ALLOCATE_UTILS_H_
#include <stdlib.h>
#include <glib.h>

/**
 * Allocate a new two dimension array.
 *
 * Note that NEW_ARRAY2D_INSTANCE() is a more convenient wrapper macro of this function,
 * so call that macro instead.
 *
 * @param row_size Number of row.
 * @param col_size Number of column.
 * @param element_size Size of one element.
 * @param pointer_size Size of element pointer.
 * @return A two dimension array of element type.
 * @see NEW_ARRAY2D_INSTANCE()
 */
void **array2D_new(size_t row_size, size_t col_size, size_t element_size, size_t pointer_size);

/**
 * Free the 2D array create by NEW_ARRAY2D_INSTANCE()
 *
 * @param arrayPtr the 2D array to be freed.
 */
void array2D_free(void **arrayPtr);


/**
 * Allocate a new instance for type <code>type</code>.
 *
 * @param type Element type to be allocated.
 * @return A newly allocated space for type <code>type</code>.
 */
#define NEW_INSTANCE(type) g_new(type,1)


/**
 * Allocate a new instance array for type <code>type</code>.
 *
 * @param element_count Number of element to be required.
 * @param element_type Element type to be allocated.
 * @return A newly allocated array of element type.
 */
#define NEW_ARRAY_INSTANCE(element_count,element_type) g_new(element_type,element_count)

/**
 * Allocate a new two dimension array.
 *
 * @param row_size Number of row.
 * @param col_size Number of column.
 * @param element_type Element type to be allocated.
 * @return A two dimension array of element type.
 */
#define NEW_ARRAY2D_INSTANCE(row_size,col_size,element_type) (element_type**) array2D_new(row_size,col_size,sizeof(element_type),sizeof(element_type*));

#endif /*ALLOCATE_UTILS_H_*/
