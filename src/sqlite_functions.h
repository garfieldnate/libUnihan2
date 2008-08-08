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



#ifndef SQLITE_FUNCTIONS_H_
#define SQLITE_FUNCTIONS_H_
#include <sqlite3.h>
#include "str_functions.h"

int sqlite_count_matches(sqlite3 *db,const char * sqlClause,char **errmsg);

StringList *sqlite_get_fieldNames(sqlite3 *db,const char * sqlClause,char **errmsg);

int sqlite_create_concat_aggregation_function(sqlite3 *db, const char *function_name);

const char *sqlite_value_signed_text_buffer(char *buf,sqlite3_value *value);

const char *sqlite_value_signed_text_cloned(sqlite3_value *value);


#endif /* SQLITE_FUNCTIONS_H_ */

