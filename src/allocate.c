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



void **array2D_new(size_t row_size, size_t col_size, size_t element_size, size_t pointer_size){
    void **arrayPtr;
    arrayPtr=(void**) g_malloc(row_size * pointer_size);
    *arrayPtr=(void*) g_malloc(row_size * col_size * element_size);
    int i,j;
    for(i=0,j=0;j<row_size;i+=col_size,j++){
    	arrayPtr[j]=*arrayPtr+i*element_size;
    }
    return arrayPtr;
}


void array2D_free(void **arrayPtr){
    if (arrayPtr==NULL)
	return;
    g_free(*arrayPtr);
    g_free(arrayPtr);
}
