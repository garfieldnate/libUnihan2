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
#include "check_functions.h"


#define RESET_COUNTER 1

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
    {PINYIN_REGEX_IMPORT "\\(([[:digit:]]*)\\)","lüan4(439)",
	"$0","lu\xCC\x88""an4(439)",0},
    {PINYIN_REGEX_IMPORT "\\(([[:digit:]]*)\\)","lun4(439)",
	"$0","lun4(439)",0},
    {PINYIN_REGEX_IMPORT "\\(([[:digit:]]*)\\)","lüan4(439)",
	PINYIN_IMPORT_SUBSTITUTE,"lvan",0},
    {PINYIN_REGEX_IMPORT "\\(([[:digit:]]*)\\)","lün4(439)",
	PINYIN_IMPORT_SUBSTITUTE_TONE,"4",0},
    {PINYIN_REGEX_IMPORT ,"hòu",
	PINYIN_IMPORT_SUBSTITUTE,"hou",0},
    {PINYIN_REGEX_IMPORT ,"hòu",
	PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT,"4",0},
    {PINYIN_REGEX_IMPORT ,"lǜ",
	PINYIN_IMPORT_SUBSTITUTE,"lv",0},
    {PINYIN_REGEX_IMPORT ,"lǜ",
	PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT,"4",0},
    {PINYIN_REGEX_IMPORT ,"xie",
	PINYIN_IMPORT_SUBSTITUTE,"xiE",0},
    {PINYIN_REGEX_IMPORT ,"xie",
	PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT,"5",0},
    {PINYIN_REGEX_IMPORT ,"zhuāng",
	PINYIN_IMPORT_SUBSTITUTE,"zhuang",0},
    {PINYIN_REGEX_IMPORT ,"zhuāng",
	PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT,"1",0},
    {PINYIN_REGEX_IMPORT ,"YIN2",
	PINYIN_IMPORT_SUBSTITUTE " $+0","yin 1",0},
    {PINYIN_REGEX_IMPORT ,"YI2",
	PINYIN_IMPORT_SUBSTITUTE_TONE " $+0","2 2",0},
    {PINYIN_REGEX_IMPORT ,"YI1",
	PINYIN_IMPORT_SUBSTITUTE_TONE " $+0","1 3",0},
    {PINYIN_REGEX_IMPORT ,"E2",
	PINYIN_IMPORT_SUBSTITUTE,"E",0},
    {PINYIN_REGEX_IMPORT ,"E^2",
	PINYIN_IMPORT_SUBSTITUTE,"E",0},
    {PINYIN_REGEX_IMPORT ,"e2",
	PINYIN_IMPORT_SUBSTITUTE,"e",0},
    {PINYIN_REGEX_IMPORT ,"e^2",
	PINYIN_IMPORT_SUBSTITUTE,"E",0},
    {PINYIN_REGEX_IMPORT ,"Ēr",
	PINYIN_IMPORT_SUBSTITUTE PINYIN_IMPORT_SUBSTITUTE_TONE,"er1",0},
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
    {"([[:digit:]]{4})\\.([[:digit:]]{2})([[:digit:]])(\\*)?[^[:space:]]*:" PINYIN_REGEX_IMPORT,
	"0484.052,0485.021:huà",
       	"$1 $2 $3 $N4{1,0} $+0 " PINYIN_IMPORT_SUBSTITUTE_XHC " " PINYIN_IMPORT_SUBSTITUTE_TONE_ACCENT_XHC,
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


/*==========================================================
 * Start of testing functions.
 */

DataRec *nextRecFunc(Param *param, DataSet *dataSet){
    RegexEval_DataRec *rRec=(RegexEval_DataRec *) dataSet;
    static int index=0;
    RegexEval_DataRec *currRec=&rRec[index++];
    if (rRec[index].pattern==NULL){
	return NULL;
    }
    return (DataRec *) currRec;
}

gboolean examRecFunc(Param *param, DataRec *dataRec){
    RegexEval_DataRec *rRec=(RegexEval_DataRec *) dataRec;
    const gchar *pattern=rRec->pattern;
    const gchar *str=rRec->str;
    const gchar *format=rRec->format;
    gchar *str_normalized=g_utf8_normalize(str,-1,G_NORMALIZE_NFD);

    gchar *actualResult;
    static int counter=0;
    gchar buf[MAX_STRING_BUFFER_SIZE];
    int j,ret;


    verboseMsg_print(VERBOSE_MSG_INFO3,"[Info3]: str(%d)=%s\tstr_normalized(%d)=%s\tpattern=%s\tformat=%s\n",
	    strlen(str),str,strlen(str_normalized),str_normalized,pattern,format);
    if (verboseMsg_get_level()>=VERBOSE_MSG_INFO4){
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

    g_snprintf(buf,MAX_STRING_BUFFER_SIZE,"string_regex_formatted_combine(%s,%s,%s,%X,%X,&(%d))\n",
	    str_normalized, pattern, format, REG_EXTENDED, 0, counter);
    if (rRec->options & RESET_COUNTER){
	counter=0;
    }
    actualResult=string_regex_formatted_combine(str_normalized, pattern, format, REG_EXTENDED, 0, &counter);

    ret=compare_strings(buf,rRec->output,actualResult);
    if(str_normalized){
	g_free(str_normalized);
    }
    if (actualResult){
	g_free(actualResult);
    }
    if (ret){
	return FALSE;
    }
    return TRUE;

}


/*==========================================================
 * End of testing functions.
 */

TestStruct TEST_COLLECTION[]={
    {"regex eval functions",NULL,REGEX_EVAL_DATA_SET, NULL, nextRecFunc, examRecFunc},
    {NULL,NULL, NULL, NULL,NULL,NULL},
};



int main(int argc, char** argv){
    int testId=get_testId(argc,argv,TEST_COLLECTION);
    if (testId<0){
	return testId;
    }
    if (perform_test(testId, TEST_COLLECTION)){
	return 0;
    }
    return 1;
}

