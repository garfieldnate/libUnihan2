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
#include "verboseMsg.h"
#include "Unihan.h"
#include "Unihan_phonetic.h"


typedef enum{
    PINYIN_ALWAYS,
    PINYIN_ORIGINAL,
    PINYIN_UNIHAN,
    PINYIN_TRAILING,
    PINYIN_INPUT_METHOD,
    PINYIN_NONE,
    ZHUYIN_ALWAYS,
    ZHUYIN_ORIGINAL,
    ZHUYIN_INPUT_METHOD,
    ZHUYIN_NUMERICAL,
} TEST_ID;


const char *data_msgs[]={
    "pinyin ALWAYS",
    "pinyin ORIGINAL",
    "pinyin UNIHAN",
    "pinyin TRAILING",
    "pinyin INPUT METHOD",
    "pinyin NONE",
    "zhuyin ALWAYS",
    "zhuyin ORIGINAL",
    "zhuyin INPUT_METHOD",
    "zhuyin NUMERICAL",
    NULL
};


#define TEST_NUM 1


const char *testFiles[]={
    "ZhuYin_test_inputMethod.txt",
    NULL
};

FILE *fromF=NULL, *toF=NULL;

gboolean perform_test(TEST_ID testId){
    char fromBuf[100];
    char toBuf[100];
    char *fromBuf_ptr,*toBuf_ptr;

    printf("Testing on converting to %s \n",data_msgs[testId]);
    char *out;
    guint i,j;
    for(j=0;j<TEST_NUM;j++){
	if ((fromF=fopen(testFiles[j],"r"))==NULL){
	    fprintf(stderr,"Cannot open file %s\n",testFiles[j]);
	    return FALSE;
	}
	while(fgets(fromBuf,100,fromF)!=NULL){
	    string_trim(fromBuf);
	    out=zhuYin_convert_toneMark_format(fromBuf,ZHUYIN_TONEMARK_ORIGINAL);
	    puts(out);
	}
	
	printf(" completed.\n");
    }
    printf("All sub-test completed.\n");
    return TRUE;
}


int main(int argc, char** argv){
    if (argc<2){
	printf("Usage: %s <test num>\n",argv[0]);
	return 1;
    }
    int argIndex=1;
    if (strcmp(argv[argIndex],"-V")==0){
	verboseMsg_set_level(VERBOSE_MSG_WARNING);
	argIndex++;
    }else if (strcmp(argv[argIndex],"-V1")==0){
	verboseMsg_set_level(VERBOSE_MSG_INFO1);
	argIndex++;
    }else if (strcmp(argv[argIndex],"-V2")==0){
	verboseMsg_set_level(VERBOSE_MSG_INFO2);
	argIndex++;
    }else{
	verboseMsg_set_level(VERBOSE_MSG_WARNING);
    }
    int test_index=atoi(argv[argIndex]);
    if (test_index>=TEST_NUM || test_index<0){
	printf("Invalid test number.\n");
	return 2;
    }
    if (perform_test(test_index)){
	printf("Success!\n");
	return 0;
    }
    return 1;

}