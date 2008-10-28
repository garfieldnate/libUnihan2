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
    {UNIHAN_FIELD_UTF8 ,"宇" , UNIHAN_FIELD_kBIGFIVE, 
	UNIHAN_QUERY_OPTION_DEFAULT ,
	1, "A674"},
    {UNIHAN_FIELD_kCANGJIE,  "JLW", UNIHAN_FIELD_UTF8,  
	UNIHAN_QUERY_OPTION_DEFAULT ,
	1,"宙"},
    {UNIHAN_FIELD_UTF8, "洪", UNIHAN_FIELD_kCANTONESE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"hung4"},
    {UNIHAN_FIELD_kCANTONESE, "fong1", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	27,"㠩\0㠵\0㡃\0㡆\0㤃\0㬻\0㱂\0㵁\0䀮\0䄱\0匚\0坊\0巟\0慌\0方\0枋\0汸\0肓\0肪\0芳\0荒\0衁\0謊\0谎\0邡\0鈁\0钫"},
    {UNIHAN_FIELD_UTF8, "日", UNIHAN_FIELD_kHDZRADBREAK,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"⽇[U+2F47]:21482.010"},
    {UNIHAN_FIELD_kCIHAIT, "655.405", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"月"},
    {UNIHAN_FIELD_UTF8, "盈", UNIHAN_FIELD_kCOWLES,
	UNIHAN_QUERY_OPTION_DEFAULT,
	    1,"5239"},
    {UNIHAN_FIELD_kCNS1986, "2-272B", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"昃"},
    {UNIHAN_FIELD_UTF8, "晨", UNIHAN_FIELD_kCNS1992,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1-5B27"},
    {UNIHAN_FIELD_kDAEJAWEON, "0568.210", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"宿"},
    {UNIHAN_FIELD_UTF8, "列", UNIHAN_FIELD_kDEFINITION,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"a line; to arrange in order, classify"},
    {UNIHAN_FIELD_kEACC, "273D47", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"张"},
    {UNIHAN_FIELD_UTF8, "寒", UNIHAN_FIELD_kFENN,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"100A"},
    {UNIHAN_FIELD_kFENNINDEX, "284.11", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2,"來\0来"},
    {UNIHAN_FIELD_UTF8, "暑", UNIHAN_FIELD_kRSKOREAN,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"72.9"},
    {UNIHAN_FIELD_kGB0, "4589", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"往"},
    {UNIHAN_FIELD_UTF8, "秋", UNIHAN_FIELD_kFREQUENCY,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"4"},
    {UNIHAN_FIELD_kGB1, "4253", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"收"},
    {UNIHAN_FIELD_UTF8, "冬", UNIHAN_FIELD_kGSR,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1002a"},
    {UNIHAN_FIELD_kHANYU, "53311.110", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"藏"},
    {UNIHAN_FIELD_UTF8, "閏", UNIHAN_FIELD_kHANGUL,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"윤"},
    {UNIHAN_FIELD_kIRGDAEJAWEON, "1945.240", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "餘"},
    {UNIHAN_FIELD_UTF8, "成", UNIHAN_FIELD_kHANYUPINLU,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2,"cheng2(4462)\0cheng5(17)"},
    {UNIHAN_FIELD_kIRGDAEJAWEON, "0967.170", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "歲"},
    {UNIHAN_FIELD_UTF8, "律", UNIHAN_FIELD_kIICORE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"2.1"},
    {UNIHAN_FIELD_kIRGDAIKANWAZITEN, "03386", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "呂"},
    {UNIHAN_FIELD_UTF8, "调", UNIHAN_FIELD_kIRGHANYUDAZIDIAN,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"63990.010"},
    {UNIHAN_FIELD_kIRGKANGXI, "1347.070", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "阳"},
    {UNIHAN_FIELD_UTF8, "雲", UNIHAN_FIELD_kIRG_GSOURCE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1-5446"},
    {UNIHAN_FIELD_kIRG_JSOURCE, "0-462D", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "騰"},
    {UNIHAN_FIELD_UTF8, "致", UNIHAN_FIELD_kIRG_KPSOURCE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"KP0-EEFA"},
    {UNIHAN_FIELD_kIRG_KSOURCE, "0-696B", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "雨"},
    {UNIHAN_FIELD_UTF8, "露", UNIHAN_FIELD_kIRG_TSOURCE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1-7B3F"},
    {UNIHAN_FIELD_kMAINLANDTELEGRAPH, "4814", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "结"},
    {UNIHAN_FIELD_UTF8, "为", UNIHAN_FIELD_kKANGXI,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"0080.191"},
    {UNIHAN_FIELD_kIRG_VSOURCE, "1-6B58", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "霜"},
    {UNIHAN_FIELD_UTF8, "金", UNIHAN_FIELD_kCOMPATIBILITYVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT  | UNIHAN_QUERY_OPTION_SCALAR_STRING,
	1,"U+91D1"},
    {UNIHAN_FIELD_kJAPANESEKUN, "HAERU", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	4, "映\0暎\0栄\0生"},
    {UNIHAN_FIELD_UTF8, "丽", UNIHAN_FIELD_kRSKANWA,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"3.7"},
    {UNIHAN_FIELD_kJIS0, "3169", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "水"},
    {UNIHAN_FIELD_UTF8, "玉", UNIHAN_FIELD_kKPS0,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"F9EA"},
    {UNIHAN_FIELD_kKSC0, "8583", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "出"},
    {UNIHAN_FIELD_UTF8, "昆", UNIHAN_FIELD_kKARLGREN,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"466"},
    {UNIHAN_FIELD_kTRADITIONALVARIANT, "U+5D17", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "岗"},
    {UNIHAN_FIELD_UTF8, "劍", UNIHAN_FIELD_kPHONETIC,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"182"},
    {UNIHAN_FIELD_kHKGLYPH, "3582", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "號"},
    {UNIHAN_FIELD_UTF8, "巨", UNIHAN_FIELD_kKOREAN,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"KE"},
    {UNIHAN_FIELD_kMATTHEWS, "1712", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "闕"},
    {UNIHAN_FIELD_UTF8, "珠", UNIHAN_FIELD_kLAU,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"1566"},
    {UNIHAN_FIELD_kNELSON, "3280", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "称"},
    {UNIHAN_FIELD_UTF8, "夜", UNIHAN_FIELD_kMANDARIN ,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"YE4"},
    {UNIHAN_FIELD_kMEYERWEMPE, "1414", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "光"},
    {UNIHAN_FIELD_UTF8, "果", UNIHAN_FIELD_kRSADOBE_JAPAN1_6,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"C+1356+75.4.4"},
    {UNIHAN_FIELD_kSBGY, "103.54", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "珍"},
    {UNIHAN_FIELD_UTF8, "李", UNIHAN_FIELD_kRSKANGXI,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"75.3"},
    {UNIHAN_FIELD_kJIS1, "3537", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "柰"},
    {UNIHAN_FIELD_UTF8, "菜", UNIHAN_FIELD_kRSUNICODE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"140.8"},
    {UNIHAN_FIELD_kTAIWANTELEGRAPH, "6850", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "重"},
    {UNIHAN_FIELD_UTF8, "芥", UNIHAN_FIELD_kTOTALSTROKES,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"10"},
    {UNIHAN_FIELD_kXHC1983, "0560.050:jiāng", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "姜"},
    {UNIHAN_FIELD_UTF8, "海", UNIHAN_FIELD_kTANG,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"*xə̌i"},
    {UNIHAN_FIELD_kXEROX, "255:366", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "鹹"},
    {UNIHAN_FIELD_UTF8, "河", UNIHAN_FIELD_kVIETNAMESE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"hà"},
    {UNIHAN_FIELD_kSPECIALIZEDSEMANTICVARIANT, "U+6FB9<kMeyerWempe", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "淡"},
    {UNIHAN_FIELD_UTF8, "鳞", UNIHAN_FIELD_kCANGJIE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"NMFDQ"},
    {UNIHAN_FIELD_kCCCII, "224D31", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "潜"},
    {UNIHAN_FIELD_UTF8, "羽", UNIHAN_FIELD_kZVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"U+FA1E"},
    {UNIHAN_FIELD_kCNS1992, "1-6144", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "翔"},
    {UNIHAN_FIELD_UTF8, "龍", UNIHAN_FIELD_kSEMANTICVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"U+9F92<kHanYu:T"},
    {UNIHAN_FIELD_kSIMPLIFIEDVARIANT, "U+5E08", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "師"},
    {UNIHAN_FIELD_UTF8, "火", UNIHAN_FIELD_kSEMANTICVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"U+706C<kMatthews"},
    {UNIHAN_FIELD_kCOWLES, "4074", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "帝"},
    {UNIHAN_FIELD_UTF8, "鸟", UNIHAN_FIELD_kTRADITIONALVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT | UNIHAN_QUERY_OPTION_SCALAR_STRING,
	1,"U+9CE5"},
    {UNIHAN_FIELD_kRSADOBE_JAPAN1_6, "C+1517+40.3.5", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "官"},
    {UNIHAN_FIELD_UTF8, "人", UNIHAN_FIELD_kHANYUPINLU,
	UNIHAN_QUERY_OPTION_DEFAULT | UNIHAN_QUERY_OPTION_PINYIN_TONE_ACCENT,
	2,"rén(16866)\0ren(280)"},
    {UNIHAN_FIELD_kFENN, "74D", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2, "惶\0皇"},

    {UNIHAN_FIELD_UTF8, "始", UNIHAN_FIELD_kJAPANESEON,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"SHI"},
    {UNIHAN_FIELD_kKPS0, "EBE9", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "制"},
    {UNIHAN_FIELD_UTF8, "文", UNIHAN_FIELD_kFOURCORNERCODE,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"0040.0"},
    {UNIHAN_FIELD_kTAIWANTELEGRAPH,  "1316", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "字"},

    {UNIHAN_FIELD_UTF8, "乃", UNIHAN_FIELD_kSEMANTICVARIANT,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2,"U+5EFC<kMatthews\0U+8FFA<kMatthews"},
    {UNIHAN_FIELD_kMOROHASHI, "14345'", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "服"},
    {UNIHAN_FIELD_UTF8, "衣", UNIHAN_FIELD_kXHC1983,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2,"1350.040:yì""\0""1368.050:yī"},
    {UNIHAN_FIELD_kMAINLANDTELEGRAPH,  "5951", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "裳"},
    
    {UNIHAN_FIELD_UTF8, "推", UNIHAN_FIELD_IRG_SOURCE_SHORT_NAME,
	UNIHAN_QUERY_OPTION_DEFAULT,
	6,"G0\0J0\0KP0\0K0\0T1\0V1"},
    {UNIHAN_FIELD_IRG_SOURCE_MAPPING,  "5951", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	16, "了\0位\0叮\0杲\0欃\0欯\0皜\0禸\0膒\0貫\0賕\0郶\0𡡰\0𤑶\0𤡰\0𦰶"},

    {UNIHAN_FIELD_UTF8, "拾", UNIHAN_FIELD_kACCOUNTINGNUMERIC,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"10"},
    {UNIHAN_FIELD_kACCOUNTINGNUMERIC, "100", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	2, "佰\0陌"},
    {UNIHAN_FIELD_UTF8, "二", UNIHAN_FIELD_kPRIMARYNUMERIC,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"2"},
    {UNIHAN_FIELD_kPRIMARYNUMERIC, "7", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "七"},
    {UNIHAN_FIELD_UTF8, "卅", UNIHAN_FIELD_kOTHERNUMERIC,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"30"},
    {UNIHAN_FIELD_kOTHERNUMERIC, "2", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	3, "㒃\0兩\0𢎐"},

    {UNIHAN_FIELD_UTF8, "櫈", UNIHAN_FIELD_kCHEUNGBAUER,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1,"075/14;DNON;dang3"},
    {UNIHAN_FIELD_kCHEUNGBAUERINDEX, "341.05", UNIHAN_FIELD_UTF8,
	UNIHAN_QUERY_OPTION_DEFAULT,
	1, "氽"},

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
    int verboseLevel=VERBOSE_MSG_WARNING;
    if (argc<2){
	printf("Usage: %s [-V num] <test num> \n",argv[0]);
	return 1;
    }
    int argIndex=1;
    if (strcmp(argv[argIndex],"-V")==0){
	verboseLevel=atoi(argv[++argIndex]);
	argIndex++;
    }
    verboseMsg_set_level(verboseLevel);
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

