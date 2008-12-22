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

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#define MAX_STRING_BUFFER_SIZE 2000

typedef void DataSet;
typedef void Param;

typedef struct{
    void *inputRec;
    void *expectedRec;
} DataRec;

typedef gboolean (* TestFunc)(Param *param, DataSet *dataSet);
typedef DataRec (* NextRecFunc)(Param *param, DataSet *dataSet);
typedef DataRec (* ExamRecFunc)(Param *param, DataRec *dataSet);

typedef struct{
    char *prompt;
    void *param;
    DataSet *dataSet;
    TestFunc testFunc;
    NextRecFunc nextRecFunc;
} TestStruct;




int compare_strings(const char *prompt, const char *expect, const char *actual);

int get_testId(int argc, char** argv, TestStruct *testCollection);

gboolean perform_test(unsigned int testId, TestStruct *testCollection);

