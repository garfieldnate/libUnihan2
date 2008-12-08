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

typedef struct{
    char *prompt;
    void *param;
    void *dataSet;
    TestFunc func;
} TestStruct;

typedef struct {
    const char *input;
    const char *output;
} RegexEval_DataRec;

RegexEval_DataRec REGEX_EVAL_DATA_SET[]={
    {"[[:alnum:]]*\0""1-9999\0G$0","G1"},
    {"[[:alnum:]]*\0""4K\0G$0","G4K"},
    {"([[:alnum:]]*)-(.*)\0""4K\0G$0",NULL},
    {PINYIN_REGEX "\\(([[:digit:]]*)\\)\0lüan4(439)\0"
	"$0","lu\xCC\x88""an4(439)"},
    {PINYIN_REGEX "\\(([[:digit:]]*)\\)\0lun4(439)\0"
	"$0","lun4(439)"},
//    {PINYIN_REGEX "\\(([[:digit:]]*)\\)\0lüan4(439)\0"
//	PINYIN_PATTERN_SUBSTITUTE(1),"lvan"},
//    {PINYIN_REGEX "\\(([[:digit:]]*)\\)\0lün4(439)\0"
//        PINYIN_TONE_PATTERN_SUBSTITUTE(1),"4"},
//    {PINYIN_REGEX "\0hòu\0"
//        PINYIN_PATTERN_SUBSTITUTE(1),"hou"},
//    {PINYIN_REGEX "\0hòu\0"
//        PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE(1),"4"},
//    {PINYIN_REGEX "\0lǜ\0"
//        PINYIN_PATTERN_SUBSTITUTE(1),"lv"},
//    {PINYIN_REGEX "\0lǜ\0"
//        PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE(1),"4"},
//    {PINYIN_REGEX "\0xie\0"
//        PINYIN_PATTERN_SUBSTITUTE(1),"xiE"},
//    {PINYIN_REGEX "\0xie\0"
//        PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE(1),"5"},
//    {PINYIN_REGEX "\0zhuāng\0"
//        PINYIN_PATTERN_SUBSTITUTE(1),"zhuang"},
//    {PINYIN_REGEX "\0zhuāng\0"
//        PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE(1),"1"},
//    {PINYIN_REGEX "\0YIN2\0"
//        PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE(1)" $+0","YIN 1"},
//    {PINYIN_REGEX "\0YI2\0"
//        PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE(1)" $+0","YI 2"},
//    {PINYIN_REGEX "\0YI1\0"
//        PINYIN_TONE_ACCENT_PATTERN_SUBSTITUTE(1)" $+0","YI 3"},
    {"([[:digit:]]*)\\.([[:digit:]]*)([01])\0""0526.211\0"
	"$1 $2 $3","0526 21 1"},
    {"([[:digit:]]+)(')?\\.([[:digit:]]+)\0""75.6\0"
	"$1 $N2{1,0} $3","75 0 6"},
    {"([[:digit:]]+)(')?\\.([[:digit:]]+)\0""200'.7\0"
	"$1 $N2{1,0} $3","200 1 7"},
    {"U\\+[[:xdigit:]]*\0""U+5275<kHanYu:TZ,kMeyerWempe\0"
	"$0","U+5275"},
    {"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*)(:(T?)(B?)(Z?))?\0U+5275<kHanYu:TZ,kMeyerWempe\0"
	"$1 $+0 $2 $N4{1,0} $N5{1,0} $N6{1,0}","U+5275 1 kHanYu 1 0 1"},
    {"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*:?T?B?Z?),(.*)\0U+5275<kHanYu:TZ,kMeyerWempe\0"
	"$1<$3", "U+5275<kMeyerWempe"},
    {"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*:?T?B?Z?),(.*)\0U+5275<kMeyerWempe,kHanYu:TZ\0"
	"$1<$3", "U+5275<kHanYu:TZ"},
    {"(U\\+[[:xdigit:]]*)<(k[[:alpha:]]*)(:(T?)(B?)(Z?))?\0""U+5275<kMeyerWempe\0"
	"$1 $+0 $2 $N3{1,0} $N4{1,0} $N5{1,0}","U+5275 2 kMeyerWempe 0 0 0"},
    {"([[:digit:]]{4})\\.([[:digit:]]{2})([[:digit:]])(\\*)?[^[:space:]]*:" PINYIN_REGEX 
	"\0""0484.052,0485.021:huà\0"
	    "$1 $2 $3 $N4{1,0} $+0 " PINYIN_TONE_PATTERN_SUBSTITUTE(5),
	"0482.01 1 0 1 hua 2"},
    {NULL,NULL}
};

int testId;

/*==========================================================
 * Start of testing functions.
 */

gboolean test_regex_eval(void *param,void *dataSet){

    RegexEval_DataRec *examSet= (RegexEval_DataRec *) dataSet;
    int i,n;
    int j;
    const gchar *pattern;
    const gchar *str;
    gchar *str_normalized;
    const gchar *format;
    gchar *actualResult;
    int counter=0;

    for (n=0;examSet[n].input!=NULL;n++){
	pattern=examSet[n].input;
	for(i=0;examSet[n].input[i]!='\0';i++){
	}
	i++;
	str=&(examSet[n].input[i]);
	str_normalized=g_utf8_normalize(str,-1,G_NORMALIZE_NFD);

	for(;examSet[n].input[i]!='\0';i++){
	}
	i++;
	format=&(examSet[n].input[i]);

	verboseMsg_print(VERBOSE_MSG_INFO1,"[Info1]: str(%d)=%s\tstr_normalized(%d)=%s\tpattern=%s\tformat=%s\n",
		strlen(str),str,strlen(str_normalized),str_normalized,pattern,format);

	if (verboseMsg_get_level()>=VERBOSE_MSG_INFO2){
	    verboseMsg_print(VERBOSE_MSG_INFO2,"*** str_normalized=");
	    for(j=0;j<strlen(str_normalized);j++){
		verboseMsg_print(VERBOSE_MSG_INFO2,"%X ", CHAR_TO_UNSIGNEDCHAR(str_normalized[j]));
	    }
	    verboseMsg_print(VERBOSE_MSG_INFO2,"\n");
	    verboseMsg_print(VERBOSE_MSG_INFO2,"*** str=");
	    for(j=0;j<strlen(str);j++){
		verboseMsg_print(VERBOSE_MSG_INFO2,"%X ",CHAR_TO_UNSIGNEDCHAR(str[j]));
	    }
	    verboseMsg_print(VERBOSE_MSG_INFO2,"\n");
	}

	actualResult=string_regex_eval(str_normalized, pattern, format, REG_EXTENDED, 0, &counter);
	if (examSet[n].output==actualResult){
	    verboseMsg_print(VERBOSE_MSG_INFO2,"[Correct]: No match\n");
	    if(str_normalized){
		g_free(str_normalized);
	    }
	    continue;
	}
	if (examSet[n].output==NULL){
	    verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: string_regex_eval(%s,%s,%s,%X,%X,&(%d)):\n",
		    str,pattern,format,REG_EXTENDED, 0, counter);
	    verboseMsg_print(VERBOSE_MSG_ERROR,"    Expect:[NULL]\tActual:%s\n",
		    actualResult);
	    return FALSE;
	}
	if (actualResult==NULL){
	    verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: string_regex_eval(%s,%s,%s,%X,%X,&(%d)):\n",
		    str,pattern,format,REG_EXTENDED, 0, counter);
	    verboseMsg_print(VERBOSE_MSG_ERROR,"    Expect:%s\tActual:[NULL]\n",
		    examSet[n].output);
	    return FALSE;
	}


	if (strcmp(actualResult,examSet[n].output)){
	    verboseMsg_print(VERBOSE_MSG_ERROR,"[Error]: string_regex_eval(%s,%s,%s,%X,%X,&(%d)):\n",
		    str,pattern,format,REG_EXTENDED, 0, counter);
	    verboseMsg_print(VERBOSE_MSG_ERROR,"    Expect:%s\tActual:%s\n",
		    examSet[n].output,actualResult);
	    return FALSE;
	}else{
	    verboseMsg_print(VERBOSE_MSG_INFO2,"[Correct]: str=%s, eval=%s\n",
		    str,actualResult);
	}
	if(str_normalized){
	    g_free(str_normalized);
	}
	if (actualResult){
	    g_free(actualResult);
	}
    }
    return TRUE;
}

/*==========================================================
 * End of testing functions.
 */

TestStruct TEST_COLLECTION[]={
    {"regex eval functions",NULL,REGEX_EVAL_DATA_SET, test_regex_eval},
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

