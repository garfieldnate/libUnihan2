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
#include <string.h>
#include <glib.h>

#include "verboseMsg.h"
#include "check_functions.h"

int compare_strings(const char *prompt, const char *expect, const char *actual){
    int ret;
    if (expect==NULL && actual==NULL){
	verboseMsg_print(VERBOSE_MSG_INFO1,"[Ok]: both are NULL\n");
	return 0;
    }
    if (expect==NULL){
	verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: %s:",prompt);
	verboseMsg_print(VERBOSE_MSG_ERROR,"    Expect:[NULL]\tActual:%s\n",actual);
	return -1;
    }
    if (actual==NULL){
	verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: %s:",prompt);
	verboseMsg_print(VERBOSE_MSG_ERROR,"    Expect:%s\tActual:[NULL]\n",expect);
	return 1;
    }

    ret=strcmp(expect,actual);
    if (ret){
	verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: %s:",prompt);
	verboseMsg_print(VERBOSE_MSG_ERROR,"    Expect:%s\tActual:%s\n",expect,actual);
    }else{
	verboseMsg_print(VERBOSE_MSG_INFO1,"[Ok]: expect and actual matched: %s\n",actual);
    }
    return ret;
}

int get_testId(int argc, char** argv, TestStruct *testCollection){
    int i;
    int argIndex=1;
    int verboseLevel=VERBOSE_MSG_WARNING;
    if (argc<2){
	printf("Usage: %s [-V num] <test num> \n",argv[0]);
	return -1;
    }
    if (strcmp(argv[argIndex],"-V")==0){
	verboseLevel=atoi(argv[++argIndex]);
	argIndex++;
    }
    verboseMsg_set_level(verboseLevel);

    int test_index=atoi(argv[argIndex]);

    /* Detect Invalid test number */
    if (test_index<0){
	printf("Invalid test number.\n");
	return -2;
    }
    for(i=0;i<=test_index;i++){
	if (testCollection[i].testFunc==NULL){
	    printf("Invalid test number.\n");
	    return -2;
	}
    }
    return test_index;
}

gboolean perform_test(unsigned int testId, TestStruct *testCollection){
    if (testCollection[testId].testFunc(testCollection[testId].param, testCollection[testId].dataSet)){
	printf("All sub-test completed.\n");
	return TRUE;
    }
    return FALSE;
}

