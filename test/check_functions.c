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
#include "verboseMsg.h"
#include "Unihan.h"

#define TEST_NUM 1

typedef struct{
    const char *prompt;
    int (*func)(void);
} TestFuncStru;


gboolean test_unihan_find_all_matched();

const TestFuncStru funcList[]={
    {"unihan_find_all_matched",test_unihan_find_all_matched},
    {NULL,NULL}
};


const char* value_find_next(const char* str){
    int i=0;
    for(i=0;str[i]!='\0';i++){
    }
    return &str[i+1];
};


/*=========================================================
 * Test functions
 *
 * Pass if returns 0.
 */

typedef struct{
    UnihanField givenField;
    const char *givenValue;
    UnihanField queryField;
    UnihanQueryOption qOption;

    int expectedResultCount;
    const char *expectedResults;
} Unihan_find_all_matched_data;

const Unihan_find_all_matched_data unihan_find_all_matched_dataset[]={
    {UNIHAN_FIELD_UTF8, "天", UNIHAN_FIELD_CODE,
       	UNIHAN_QUERY_OPTION_DEFAULT,
   	1,"22825"},
    {UNIHAN_FIELD_CODE, "22320", UNIHAN_FIELD_UTF8, 
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"地" },
    {UNIHAN_FIELD_UTF8, "玄", UNIHAN_FIELD_CODE,
	UNIHAN_QUERY_OPTION_DEFAULT | UNIHAN_QUERY_OPTION_SCALAR_STRING,
	1,"U+7384"},
    {UNIHAN_FIELD_CODE, "U+9EC3", UNIHAN_FIELD_UTF8, 
	UNIHAN_QUERY_OPTION_DEFAULT | UNIHAN_QUERY_OPTION_SCALAR_STRING,
	1,"黃" },
    {UNIHAN_FIELD_UTF8 ,"宇" , UNIHAN_FIELD_KBIGFIVE, 
	UNIHAN_QUERY_OPTION_DEFAULT ,
	1, "A674"},
    {UNIHAN_FIELD_KCANGJIE,  "JLW", UNIHAN_FIELD_UTF8,  
	UNIHAN_QUERY_OPTION_DEFAULT ,
	1,"宙"},
    {UNIHAN_FIELD_UTF8, "洪", UNIHAN_FIELD_KCANTONESE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"hung4"},
    {UNIHAN_FIELD_KCANTONESE, "fong1", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	27,"㠩\0㠵\0㡃\0㡆\0㤃\0㬻\0㱂\0㵁\0䀮\0䄱\0匚\0坊\0巟\0慌\0方\0枋\0汸\0肓\0肪\0芳\0荒\0衁\0謊\0谎\0邡\0鈁\0钫"},
    {UNIHAN_FIELD_UTF8, "日", UNIHAN_FIELD_KCCCII,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"214273"},
    {UNIHAN_FIELD_KCIHAIT, "655.405", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"月"},
    {UNIHAN_FIELD_UTF8, "盈", UNIHAN_FIELD_KCOWLES,
	UNIHAN_QUERY_OPTION_DEFAULT,
	    1,"5239"},
    {UNIHAN_FIELD_KCNS1986, "2-272B", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"昃"},
    {UNIHAN_FIELD_UTF8, "晨", UNIHAN_FIELD_KCNS1992,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1-5B27"},
    {UNIHAN_FIELD_KDAEJAWEON, "0568.210", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"宿"},
    {UNIHAN_FIELD_UTF8, "列", UNIHAN_FIELD_KDEFINITION,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"a line; to arrange in order, classify"},
    {UNIHAN_FIELD_KEACC, "273D47", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"张"},
    {UNIHAN_FIELD_UTF8, "寒", UNIHAN_FIELD_KFENN,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"100A"},
    {UNIHAN_FIELD_KFENNINDEX, "284.11", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2,"來\0来"},
    {UNIHAN_FIELD_UTF8, "暑", UNIHAN_FIELD_KFOURCORNERCODE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"6060.4"},
    {UNIHAN_FIELD_KGB0, "4589", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"往"},
    {UNIHAN_FIELD_UTF8, "秋", UNIHAN_FIELD_KFREQUENCY,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"4"},
    {UNIHAN_FIELD_KGB1, "4253", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"收"},
    {UNIHAN_FIELD_UTF8, "冬", UNIHAN_FIELD_KGSR,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1002a"},
    {UNIHAN_FIELD_KHANYU, "53311.110", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"藏"},
    {UNIHAN_INVALID_FIELD, NULL, UNIHAN_FIELD_CODE, UNIHAN_QUERY_OPTION_DEFAULT,
     0,NULL }
};


int test_unihan_find_all_matched(){
    int i=0,j;
    SQL_Result *sResult=NULL;
    int result=0;
    int rowCount;
    const char *currResult=NULL;
    for(i=0;unihan_find_all_matched_dataset[i].givenField!=UNIHAN_INVALID_FIELD;i++){
	currResult=unihan_find_all_matched_dataset[i].expectedResults;
	sResult=unihan_find_all_matched(unihan_find_all_matched_dataset[i].givenField,
		unihan_find_all_matched_dataset[i].givenValue,
		unihan_find_all_matched_dataset[i].queryField,
		unihan_find_all_matched_dataset[i].qOption);
	if (sResult->colCount<=0){
	    verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: No result from unihan_find_all_matched(%s,%s,%s,%d)\n",
		    unihanField_to_string(unihan_find_all_matched_dataset[i].givenField),
		    unihan_find_all_matched_dataset[i].givenValue,
		    unihanField_to_string(unihan_find_all_matched_dataset[i].queryField),
		    unihan_find_all_matched_dataset[i].qOption);
	    result=1;
	    break;
	}
	rowCount=sResult->resultList->len;
	for(j=0;j<rowCount;j++){
	    if (j>0){
		if (j>=unihan_find_all_matched_dataset[i].expectedResultCount){
		    verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: unihan_find_all_matched(%s,%s,%s,0x%X):",
			    unihanField_to_string(unihan_find_all_matched_dataset[i].givenField),
			    unihan_find_all_matched_dataset[i].givenValue,
			    unihanField_to_string(unihan_find_all_matched_dataset[i].queryField),
			    unihan_find_all_matched_dataset[i].qOption);
		    verboseMsg_print(VERBOSE_MSG_ERROR," too many results. Return %d results, but expected %d. \n",
			    rowCount,unihan_find_all_matched_dataset[i].expectedResultCount);
		}else{
		    currResult=value_find_next(currResult);
		}
	    }
	    verboseMsg_print(VERBOSE_MSG_INFO1, "%d: currResult=%s\n",j,currResult);
	    if (strcmp(stringList_index(sResult->resultList,j),currResult)!=0){
		verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: unihan_find_all_matched(%s,%s,%s,0x%X):",
			unihanField_to_string(unihan_find_all_matched_dataset[i].givenField),
			unihan_find_all_matched_dataset[i].givenValue,
			unihanField_to_string(unihan_find_all_matched_dataset[i].queryField),
			unihan_find_all_matched_dataset[i].qOption);
		verboseMsg_print(VERBOSE_MSG_ERROR," Result:%s Expect:%s\n",
			stringList_index(sResult->resultList,j),currResult);
		result=3;
		break;
	    }
	}
	if (rowCount < unihan_find_all_matched_dataset[i].expectedResultCount){
	    currResult=value_find_next(currResult);
	    verboseMsg_print(VERBOSE_MSG_INFO1, "%d: currResult=%s\n",j,currResult);
	    verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: unihan_find_all_matched(%s,%s,%s,0x%X):",
		    unihanField_to_string(unihan_find_all_matched_dataset[i].givenField),
		    unihan_find_all_matched_dataset[i].givenValue,
		    unihanField_to_string(unihan_find_all_matched_dataset[i].queryField),
		    unihan_find_all_matched_dataset[i].qOption);
	    verboseMsg_print(VERBOSE_MSG_ERROR," too few results. Return %d results, but expected %d.",
		    rowCount,unihan_find_all_matched_dataset[i].expectedResultCount);
	    verboseMsg_print(VERBOSE_MSG_ERROR," Still need result such as %s.\n",
		    currResult);
	    result=4;
	}
	if (sResult)
	    sql_result_free(sResult,TRUE);
	sResult=NULL;
	if (result)
	    break;
    }
    if (sResult)
	sql_result_free(sResult,TRUE);
    return result;
}

int perform_test(int test_index){
    return funcList[test_index].func();
}

int main(int argc, char** argv){
    if (argc<2){
	printf("Usage: %s [-V1] [-V2] <test num> \n",argv[0]);
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
    int test_index=atoi(argv[argIndex++]);
    if (test_index>=TEST_NUM || test_index<0){
	fprintf(stderr,"Invalid test number.\n");
	return 2;
    }

    int ret=unihanDb_open_default();
    if (ret){
	fprintf(stderr,"Invalid test number. Err num: %d\n",ret);
	return ret;
    }

    printf("Test on %s \t...",funcList[test_index].prompt);
    ret=perform_test(test_index);
    if (ret==0){
	printf("\tSuccess!\n");
    }
    return ret;
}

