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
#include "Unihan_phonetic_tables.h"
#include "phonetic_test_tables.c"



typedef enum{
    PINYIN_ALWAYS,
    PINYIN_ORIGINAL,
    ZHUYIN_ALWAYS,
    ZHUYIN_ORIGINAL
} TEST_ID;

#define TEST_NUM ZHUYIN_ORIGINAL +1

const char *test_msgs[]={
    "converting to pinyin ALWAYS",
    "converting to pinyin ORIGINAL",
    "converting to zhuyin ALWAYS",
    "converting to zhuyin ORIGINAL",
    NULL
};

const char **dataSet[]={
    PINYIN_COMBINATION_TABLES_ALWAYS,
    PINYIN_COMBINATION_TABLES,
    ZHUYIN_COMBINATION_TABLES,
    ZHUYIN_COMBINATION_TABLES,
};

gboolean perform_test(TEST_ID testId){
    const char **fromArray=NULL;
    const char **toArray=NULL;
    printf("Testing on %s \n",test_msgs[testId]);

    char *out;
    guint i,j;
    for(j=0;j<TEST_NUM;j++){
	printf(" Sub-test %d: ...",j);
	toArray=dataSet[testId];
	fromArray=dataSet[j];
	for(i=0;fromArray[i]!=NULL;i++){
	    verboseMsg_print(VERBOSE_MSG_INFO2,"  j=%d i=%d String=%s   ",j,i,fromArray[i]);
	    if (j<ZHUYIN_ALWAYS){
		if (testId<ZHUYIN_ALWAYS){
		    out=pinYin_convert_accent_format(fromArray[i],testId,FALSE);
		}else{
		    out=pinYin_to_zhuYin(fromArray[i],testId-ZHUYIN_ALWAYS);
		}
	    }else{
		if (testId<ZHUYIN_ALWAYS){
		    out=zhuYin_to_pinYin(fromArray[i],testId,FALSE);
		    out[strlen(out)-1]='\0';
		}else{
		    out=zhuYin_convert_toneMark_format(fromArray[i],testId-ZHUYIN_ALWAYS);
		}
	    }
	    if (strcmp(out,toArray[i])!=0){
		printf(" Failed: Orig=%s Out=%s Exp=%s\n",fromArray[i],out,toArray[i]);
		return FALSE;
	    }else{
		verboseMsg_print(VERBOSE_MSG_INFO2,"  out=%s, exp=%s matched.\n",out,toArray[i]);
	    }
	}
	printf(" completed.\n");
    }
    printf("All sub-test completed.\n");
    return TRUE;
}

int main(int argc, char** argv){
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
    if (perform_test(test_index)){
	printf("Success!");
	return 0;
    }
    return 1;

}
