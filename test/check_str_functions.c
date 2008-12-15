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
#include "str_functions.h"
#include "Unihan_phonetic.h"

typedef gboolean (* TestFunc)(void *param,void *dataSet);

#define RESET_COUNTER 1
#define MAX_STRING_BUFFER_SIZE 2000

typedef struct{
    char *prompt;
    void *param;
    void *dataSet;
    TestFunc func;
} TestStruct;

typedef void DataSet;


typedef struct {
    const char *pattern;
    const char *str;
    const char *format;
    const char *output;
    unsigned int options;
} RegexEval_DataRec;

RegexEval_DataRec REGEX_EVAL_DATA_SET[]={
    {"[[:alnum:]]*","1-9999","G$0","G1",0},
    {"[[:alnum:]]*","4K","G$0","G4K",0},
    {"([[:alnum:]]*)-(.*)","4K","G$0",NULL,0},
    {PINYIN_REGEX "\\(([[:digit:]]*)\\)","lüan4(439)",
	"$0","lu\xCC\x88""an4(439)",0},
    {PINYIN_REGEX "\\(([[:digit:]]*)\\)","lun4(439)",
	"$0","lun4(439)",0},
    {PINYIN_REGEX "\\(([[:digit:]]*)\\)","lüan4(439)",
	PINYIN_PATTERN_SUBSTITUTE,"lvan",0},
    {PINYIN_REGEX "\\(([[:digit:]]*)\\)","lün4(439)",
	PINYIN_TONE_PATTERN_SUBSTITUTE,"4",0},
    {PINYIN_REGEX ,"hòu",
	PINYIN_PATTERN_SUBSTITUTE,"hou",0},
    {PINYIN_REGEX ,"hòu",
	PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE,"4",0},
    {PINYIN_REGEX ,"lǜ",
	PINYIN_PATTERN_SUBSTITUTE,"lv",0},
    {PINYIN_REGEX ,"lǜ",
	PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE,"4",0},
    {PINYIN_REGEX ,"xie",
	PINYIN_PATTERN_SUBSTITUTE,"xiE",0},
    {PINYIN_REGEX ,"xie",
	PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE,"5",0},
    {PINYIN_REGEX ,"zhuāng",
	PINYIN_PATTERN_SUBSTITUTE,"zhuang",0},
    {PINYIN_REGEX ,"zhuāng",
	PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE,"1",0},
    {PINYIN_REGEX ,"YIN2",
	PINYIN_PATTERN_SUBSTITUTE" $+0","yin 1",0},
    {PINYIN_REGEX ,"YI2",
	PINYIN_TONE_PATTERN_SUBSTITUTE" $+0","2 2",0},
    {PINYIN_REGEX ,"YI1",
	PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE" $+0","5 3",0},
    {"([[:digit:]]*)\\.([[:digit:]]*)([01])","0526.211",
	"$1 $2 $3","0526 21 1",0},
    {"([[:digit:]]+)(')?\\.([[:digit:]]+)","75.6",
	"$1 $N2{1,0} $3","75 0 6",0},
    {"([[:digit:]]+)(')?\\.([[:digit:]]+)","200'.7",
	"$1 $N2{1,0} $3","200 1 7",0},
    {"U\\+[[:xdigit:]]*","U+5275<kHanYu:TZ,kMeyerWempe",
	"$0","U+5275",0},
    {"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*)(:(T?)(B?)(Z?))?","U+5275<kHanYu:TZ,kMeyerWempe",
	"$1 $+0 $2 $N4{1,0} $N5{1,0} $N6{1,0}","U+5275 1 kHanYu 1 0 1", RESET_COUNTER},
    {"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*:?T?B?Z?),(.*)","U+5275<kHanYu:TZ,kMeyerWempe",
	"$1<$3", "U+5275<kMeyerWempe",0},
    {"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*:?T?B?Z?),(.*)","U+5275<kMeyerWempe,kHanYu:TZ",
	"$1<$3", "U+5275<kHanYu:TZ",0},
    {"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*)(:(T?)(B?)(Z?))?","U+5275<kMeyerWempe",
	"$1 $+0 $2 $N3{1,0} $N4{1,0} $N5{1,0}","U+5275 2 kMeyerWempe 0 0 0",0},
    {"([[:digit:]]{4})\\.([[:digit:]]{2})([[:digit:]])(\\*)?[^[:space:]]*:" PINYIN_REGEX,
	"0484.052,0485.021:huà",
       	"$1 $2 $3 $N4{1,0} $+0 " PINYIN_PATTERN_SUBSTITUTE_XHC " " PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE_XHC,
	"0484 05 2 0 1 hua 4",RESET_COUNTER},
    {"([0-9]*)-([0-9]*)-([0-9]*)",
	"4040-4041-20142",
	"$X1 $X2{6} $T3",
	"FC8 000FC9 亮",0},
    {"([[:alnum:]]*)-([[:alnum:]]*)-([[:alnum:]]*)-([[:alnum:]]*)-([[:alnum:]]*)-([[:alnum:]]*)"
	"-([[:alnum:]]*)-([[:alnum:]]*)-([[:alnum:]]*)-([[:alnum:]]*)-([[:alnum:]]*)-([[:alnum:]]*)",
	"ABC-CBA-DEF-FED-GHI-IGH-JKL-LKJ-MNO-ONM-PQR-RQP",
	"$P1{4} $P2{4,+} $P3{3} $P4{3,+} $P5{2} $P6{2,+}"
	" $p7{4} $p8{4,+} $p9{3} $p10{3,+} $p11{2} $p12{2,+}",
	" ABC +CBA DEF FED GHI IGH JKL  LKJ+ MNO ONM PQR RQP",RESET_COUNTER},
    {"[[:alnum:]]*",
     "ABCDEFGHIJKL",
     "$S0{4} $S0{1,4}",
     "EFGHIJKL BCDE",0},
    {"([[:alnum:]]*)",
	"AB",
	"$I1{AB,ab} $I1{CD,cd,!cd} $I1{EF,ef}",
	"ab !cd ",0},
    {NULL,NULL,NULL,NULL,0}
};

int testId;

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

/*==========================================================
 * Start of testing functions.
 */

gboolean test_regex_formatted_output(void *param,DataSet *dataSet){
    RegexEval_DataRec *examSet= (RegexEval_DataRec *) dataSet;
    int n,ret;
    int j;
    const gchar *pattern;
    const gchar *str;
    gchar *str_normalized;
    const gchar *format;
    gchar *actualResult;
    int counter=0;
    gchar buf[MAX_STRING_BUFFER_SIZE];

    for (n=0;examSet[n].pattern!=NULL;n++){
	pattern=examSet[n].pattern;
	str=examSet[n].str;
	str_normalized=g_utf8_normalize(str,-1,G_NORMALIZE_NFD);
	format=examSet[n].format;

	verboseMsg_print(VERBOSE_MSG_INFO2,"[Info2]: str(%d)=%s\tstr_normalized(%d)=%s\tpattern=%s\tformat=%s\n",
		strlen(str),str,strlen(str_normalized),str_normalized,pattern,format);

	if (verboseMsg_get_level()>=VERBOSE_MSG_INFO3){
	    printf("*** str_normalized=");
	    for(j=0;j<strlen(str_normalized);j++){
		printf("%X ", CHAR_TO_UNSIGNEDCHAR(str_normalized[j]));
	    }
	    printf("\n");
	    printf("*** str=");
	    for(j=0;j<strlen(str);j++){
		printf("%X ",CHAR_TO_UNSIGNEDCHAR(str[j]));
	    }
	    printf("\n");
	}

	g_snprintf(buf,MAX_STRING_BUFFER_SIZE,"string_regex_formatted_output(%s,%s,%s,%X,%X,&(%d))\n",
		str_normalized, pattern, format, REG_EXTENDED, 0, counter);
	if (examSet[n].options & RESET_COUNTER){
	    counter=0;
	}
	actualResult=string_regex_formatted_output(str_normalized, pattern, format, REG_EXTENDED, 0, &counter);

	ret=compare_strings(buf,examSet[n].output,actualResult);
	if(str_normalized){
	    g_free(str_normalized);
	}
	if (actualResult){
	    g_free(actualResult);
	}
	if (ret){
	    return FALSE;
	}
    }
    return TRUE;
}

/*==========================================================
 * End of testing functions.
 */

TestStruct TEST_COLLECTION[]={
    {"regex eval functions",NULL,REGEX_EVAL_DATA_SET, test_regex_formatted_output},
    {NULL,NULL, NULL, NULL},
};


gboolean perform_test(unsigned int testId){
    if (TEST_COLLECTION[testId].func(TEST_COLLECTION[testId].param, TEST_COLLECTION[testId].dataSet)){
	printf("All sub-test completed.\n");
	return TRUE;
    }
    return FALSE;
}

int main(int argc, char** argv){
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

    unsigned int test_index=atoi(argv[argIndex]);
    int i;

    /* Detect Invalid test number */
    if (test_index<0){
	printf("Invalid test number.\n");
	return -2;
    }
    for(i=0;i<=test_index;i++){
	if (TEST_COLLECTION[i].func==NULL){
	    printf("Invalid test number.\n");
	    return -2;
	}
    }

    if (perform_test(test_index)){
	printf("Success!\n");
	return 0;
    }
    return 1;
}

