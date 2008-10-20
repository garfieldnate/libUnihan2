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
    {UNIHAN_FIELD_UTF8, "閏", UNIHAN_FIELD_KHANGUL,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"윤"},
    {UNIHAN_FIELD_KIRGDAEJAWEON, "1945.240", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "餘"},
    {UNIHAN_FIELD_UTF8, "成", UNIHAN_FIELD_KHANYUPINLU,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2,"cheng2(4462)\0cheng5(17)"},
    {UNIHAN_FIELD_KIRGDAEJAWEON, "0967.170", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "歲"},
    {UNIHAN_FIELD_UTF8, "律", UNIHAN_FIELD_KIICORE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"2.1"},
    {UNIHAN_FIELD_KIRGDAIKANWAZITEN, "03386", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "呂"},
    {UNIHAN_FIELD_UTF8, "调", UNIHAN_FIELD_KIRGHANYUDAZIDIAN,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"63990.010"},
    {UNIHAN_FIELD_KIRGKANGXI, "1347.070", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "阳"},
    {UNIHAN_FIELD_UTF8, "雲", UNIHAN_FIELD_KIRG_GSOURCE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1-5446"},
    {UNIHAN_FIELD_KIRG_JSOURCE, "0-462D", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "騰"},
    {UNIHAN_FIELD_UTF8, "致", UNIHAN_FIELD_KIRG_KPSOURCE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"KP0-EEFA"},
    {UNIHAN_FIELD_KIRG_KSOURCE, "0-696B", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "雨"},
    {UNIHAN_FIELD_UTF8, "露", UNIHAN_FIELD_KIRG_TSOURCE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1-7B3F"},
    {UNIHAN_FIELD_KMAINLANDTELEGRAPH, "4814", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "结"},
    {UNIHAN_FIELD_UTF8, "为", UNIHAN_FIELD_KKANGXI,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"0080.191"},
    {UNIHAN_FIELD_KIRG_VSOURCE, "1-6B58", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "霜"},
    {UNIHAN_FIELD_UTF8, "金", UNIHAN_FIELD_KHDZRADBREAK,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"⾦[U+2FA6]:64167.010"},
    {UNIHAN_FIELD_KJAPANESEKUN, "HAERU", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	4, "映\0暎\0栄\0生"},
    {UNIHAN_FIELD_UTF8, "麗", UNIHAN_FIELD_KJAPANESEON,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2,"REI\0RI"},
    {UNIHAN_FIELD_KJIS0, "3169", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "水"},
    {UNIHAN_FIELD_UTF8, "玉", UNIHAN_FIELD_KKPS0,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"F9EA"},
    {UNIHAN_FIELD_KKSC0, "8583", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "出"},
    {UNIHAN_FIELD_UTF8, "昆", UNIHAN_FIELD_KKARLGREN,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"466"},
    {UNIHAN_FIELD_KTRADITIONALVARIANT, "U+5D17", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "岗"},
    {UNIHAN_FIELD_UTF8, "劍", UNIHAN_FIELD_KPHONETIC,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"182"},
    {UNIHAN_FIELD_KHKGLYPH, "3582", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "號"},
    {UNIHAN_FIELD_UTF8, "巨", UNIHAN_FIELD_KKOREAN,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"KE"},
    {UNIHAN_FIELD_KMATTHEWS, "1712", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "闕"},
    {UNIHAN_FIELD_UTF8, "珠", UNIHAN_FIELD_KLAU,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1566"},
    {UNIHAN_FIELD_KNELSON, "3280", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "称"},
    {UNIHAN_FIELD_UTF8, "夜", UNIHAN_FIELD_KMANDARIN ,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"YE4"},
    {UNIHAN_FIELD_KMEYERWEMPE, "1414", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "光"},
    {UNIHAN_FIELD_UTF8, "果", UNIHAN_FIELD_KRSADOBE_JAPAN1_6,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"C+1356+75.4.4"},
    {UNIHAN_FIELD_KSBGY, "103.54", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "珍"},
    {UNIHAN_FIELD_UTF8, "李", UNIHAN_FIELD_KRSKANGXI,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"75.3"},
    {UNIHAN_FIELD_KJIS1, "3537", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "柰"},
    {UNIHAN_FIELD_UTF8, "菜", UNIHAN_FIELD_KRSUNICODE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"140.8"},
    {UNIHAN_FIELD_KTAIWANTELEGRAPH, "6850", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "重"},
    {UNIHAN_FIELD_UTF8, "芥", UNIHAN_FIELD_KTOTALSTROKES,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"10"},
    {UNIHAN_FIELD_KXHC1983, "0560.050:jiāng", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "姜"},
    {UNIHAN_FIELD_UTF8, "海", UNIHAN_FIELD_KTANG,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"*xə̌i"},
    {UNIHAN_FIELD_KXEROX, "255:366", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "鹹"},
    {UNIHAN_FIELD_UTF8, "河", UNIHAN_FIELD_KVIETNAMESE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"hà"},
    {UNIHAN_FIELD_KSPECIALIZEDSEMANTICVARIANT, "U+6FB9<kMeyerWempe", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "淡"},
    {UNIHAN_FIELD_UTF8, "鳞", UNIHAN_FIELD_KCANGJIE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"NMFDQ"},
    {UNIHAN_FIELD_KCCCII, "224D31", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "潜"},
    {UNIHAN_FIELD_UTF8, "羽", UNIHAN_FIELD_KZVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"U+FA1E"},
    {UNIHAN_FIELD_KCNS1992, "1-6144", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "翔"},
    {UNIHAN_FIELD_UTF8, "龍", UNIHAN_FIELD_KSEMANTICVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"U+9F92<kHanYu:T"},
    {UNIHAN_FIELD_KSIMPLIFIEDVARIANT, "U+5E08", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "師"},
    {UNIHAN_FIELD_UTF8, "火", UNIHAN_FIELD_KSEMANTICVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"U+706C<kMatthews"},
    {UNIHAN_FIELD_KCOWLES, "4074", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "帝"},
    {UNIHAN_FIELD_UTF8, "鸟", UNIHAN_FIELD_KTRADITIONALVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT | UNIHAN_QUERY_OPTION_SCALAR_STRING,
	1,"U+9CE5"},
    {UNIHAN_FIELD_KRSADOBE_JAPAN1_6, "C+1517+40.3.5", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "官"},
    {UNIHAN_FIELD_UTF8, "人", UNIHAN_FIELD_KHANYUPINLU,
	UNIHAN_QUERY_OPTION_DEFAULT | UNIHAN_QUERY_OPTION_PINYIN_TONE_ACCENT,
	2,"rén(16866)\0ren(280)"},
    {UNIHAN_FIELD_KFENN, "74D", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2, "惶\0皇"},
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

