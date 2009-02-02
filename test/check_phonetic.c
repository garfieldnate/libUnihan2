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
#include "check_functions.h"
#include "phonetic_test_tables.c"


#define ZHUYIN_START 7
#define PINYIN_UNIHAN 2
#define PINYIN_NONE 5

const char **dataSet[]={
    PINYIN_COMBINATION_TABLES_ALWAYS,
    PINYIN_COMBINATION_TABLES,
    PINYIN_COMBINATION_TABLES_UNIHAN,
    PINYIN_COMBINATION_TABLES_TRAILING,
    PINYIN_COMBINATION_TABLES_INPUT_METHOD,
    PINYIN_COMBINATION_TABLES_NONE,
    PINYIN_COMBINATION_TABLES_INTERNAL,
    ZHUYIN_COMBINATION_TABLES,
    NULL
};

typedef struct{
    const gchar *inStr;
    const gchar *expectedStr;
    int fromIndex;
} StrDataRec;

StrDataRec strDataRec;

TestStruct TEST_COLLECTION[];
/*==========================================================
 * Start of testing functions.
 */

DataRec *nextRecFunc(Param *param, DataSet *dataSet){
    const char ***rRec=(const char ***) dataSet;
    int toIndex=((char *)param)[0]-'0';
    static int fromIndex=0;
    static int i=0;
    if (fromIndex==toIndex){
	fromIndex++;
    }
    if (rRec[fromIndex]==NULL){
	return NULL;
    }
    strDataRec.inStr=rRec[fromIndex][i];
    strDataRec.expectedStr=rRec[toIndex][i];
    strDataRec.fromIndex=fromIndex;
    if (rRec[fromIndex][++i]==NULL){
	fromIndex++;
	i=0;
    }
    return (DataRec *) &strDataRec;
}

gboolean examRecFunc(Param *param, DataRec *dataRec){
    StrDataRec *strRec=(StrDataRec *) dataRec;
    int toIndex=((char *)param)[0]-'0';
    int fromIndex=strRec->fromIndex;
    char *actualStr=NULL;
    char buf[STRING_BUFFER_SIZE_DEFAULT];

    verboseMsg_print(VERBOSE_MSG_INFO2,"[Info2]: inStr=%s\tfrom %s to %s\n",strRec->inStr,TEST_COLLECTION[fromIndex].prompt,TEST_COLLECTION[toIndex].prompt);
    if (fromIndex<ZHUYIN_START){
	if (toIndex<ZHUYIN_START){
	    /* Skip non-functional dependency test */
	    if (fromIndex>=PINYIN_UNIHAN && fromIndex<=PINYIN_NONE){
		if (strcmp(strRec->inStr,"e")==0){
		    return TRUE;
		}
		if (fromIndex==PINYIN_NONE){
		    if (g_str_has_prefix(strRec->inStr,"nu")){
			return TRUE;
		    }else if (g_str_has_prefix(strRec->inStr,"lu")){
			return TRUE;
		    }
		}
	    }
	    actualStr=pinyin_convert_accent_format(strRec->inStr,toIndex,TRUE);
	    pinyin_strip_tone(actualStr);

	}else{

	    if (fromIndex>=PINYIN_UNIHAN){
		if (strcmp(strRec->inStr,"e")==0){
		    return TRUE;
		}
		if (fromIndex==PINYIN_NONE){
		    if (g_str_has_prefix(strRec->inStr,"nu")){
			return TRUE;
		    }else if (g_str_has_prefix(strRec->inStr,"lu")){
			return TRUE;
		    }
		}
	    }
	    actualStr=pinyin_to_zhuyin(strRec->inStr,toIndex-ZHUYIN_START);
	    zhuyin_strip_tone(actualStr);
	}
    }else{
	if (toIndex<ZHUYIN_START){
	    actualStr=zhuyin_to_pinyin(strRec->inStr,toIndex,TRUE);
	    pinyin_strip_tone(actualStr);
	}else{
	    actualStr=zhuyin_convert_toneMark_format(strRec->inStr,toIndex-ZHUYIN_START);
	    zhuyin_strip_tone(actualStr);
	}

    }
    g_snprintf(buf,STRING_BUFFER_SIZE_DEFAULT,"inStr=%s from %s to %s",strRec->inStr,TEST_COLLECTION[fromIndex].prompt,TEST_COLLECTION[toIndex].prompt);
    return (compare_strings(buf, strRec->expectedStr, actualStr))? FALSE: TRUE;
}


/*==========================================================
 * End of testing functions.
 */
TestStruct TEST_COLLECTION[]={
    {"pinyin ALWAYS",	"0", dataSet , NULL, nextRecFunc, examRecFunc},
    {"pinyin ORIGINAL",	"1",	dataSet, NULL, nextRecFunc, examRecFunc},
    {"pinyin UNIHAN",	"2", dataSet, NULL, nextRecFunc, examRecFunc},
    {"pinyin TRAILING", "3", dataSet, NULL, nextRecFunc, examRecFunc},
    {"pinyin INPUT METHOD","4", dataSet, NULL, nextRecFunc, examRecFunc},
    {"pinyin NONE", 	"5", dataSet, NULL, nextRecFunc, examRecFunc},
    {"pinyin INTERNAL",	"6", dataSet, NULL, nextRecFunc, examRecFunc},
    {"zhuyin ALWAYS", "7", dataSet, NULL, nextRecFunc, examRecFunc},
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


