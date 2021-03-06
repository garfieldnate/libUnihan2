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
#include <limits.h>
#include "verboseMsg.h"
#include "Unihan.h"

char fromDataPath[PATH_MAX];
char toDataPath[PATH_MAX];
const char *dataDir=NULL;

typedef enum{
    PINYIN_ALWAYS_F,
    PINYIN_ALWAYS_T,
    PINYIN_ORIGINAL_F,
    PINYIN_ORIGINAL_T,
    PINYIN_UNIHAN_F,
    PINYIN_UNIHAN_T,
    PINYIN_TRAILING_F,
    PINYIN_TRAILING_T,
    PINYIN_INPUT_METHOD_F,
    PINYIN_INPUT_METHOD_T,
    PINYIN_NONE_F,
    PINYIN_NONE_T,
    ZHUYIN_ALWAYS,
    ZHUYIN_ORIGINAL,
    ZHUYIN_INPUT_METHOD,
    ZHUYIN_NUMERICAL,
} TEST_ID;

const char *data_msgs[]={
    "PINYIN ALWAYS F",
    "PINYIN ALWAYS T",
    "PINYIN ORIGINAL F",
    "PINYIN ORIGINAL T",
    "PINYIN UNIHAN F",
    "PINYIN UNIHAN T",
    "PINYIN TRAILING F",
    "PINYIN TRAILING T",
    "PINYIN INPUT METHOD F",
    "PINYIN INPUT METHOD T",
    "PINYIN NONE F",
    "PINYIN NONE T",
    "ZHUYIN ALWAYS",
    "ZHUYIN ORIGINAL",
    "ZHUYIN INPUT METHOD",
    "ZHUYIN NUMERICAL",
    NULL
};


#define TEST_NUM 16


const char *testFiles[]={
    "PinYin_test_always_f.txt",
    "PinYin_test_always_t.txt",
    "PinYin_test_original_f.txt",
    "PinYin_test_original_t.txt",
    "PinYin_test_unihan_f.txt",
    "PinYin_test_unihan_t.txt",
    "PinYin_test_trailing_f.txt",
    "PinYin_test_trailing_t.txt",
    "PinYin_test_inputMethod_f.txt",
    "PinYin_test_inputMethod_t.txt",
    "PinYin_test_none_f.txt",
    "PinYin_test_none_t.txt",
    "ZhuYin_test_always.txt",
    "ZhuYin_test_original.txt",
    "ZhuYin_test_inputMethod.txt",
    "ZhuYin_test_numerical.txt",
    NULL
};

FILE *fromF=NULL, *toF=NULL;

char *genDataPath(char *dataPath,TEST_ID testId){
    if (dataDir){
	snprintf(dataPath, PATH_MAX, "%s/%s",dataDir,testFiles[testId]);
    }else{
	snprintf(dataPath, PATH_MAX, "%s",testFiles[testId]);
    }
    return dataPath;
}

gboolean perform_test(TEST_ID testId){
    char fromBuf[100];
    char toBuf[100];
    printf("Testing on converting to %s \n",data_msgs[testId]);
    char *out,*out_norm;
    char *toBuf_norm=NULL;
    guint i,j;
    genDataPath(toDataPath,testId);
    for(j=0;j<TEST_NUM;j++){
	if (j==testId)
	    continue;
	printf(" %d: From %s To %s \t...",j,data_msgs[j],data_msgs[testId]);
	genDataPath(fromDataPath,j);
	if ((fromF=fopen(fromDataPath ,"r"))==NULL){
	    fprintf(stderr,"Cannot open file %s\n",fromDataPath);
	    return FALSE;
	}
	if ((toF=fopen(toDataPath ,"r"))==NULL){
	    fprintf(stderr,"Cannot open file %s\n",toDataPath);
	    return FALSE;
	}
	while(fgets(fromBuf,100,fromF)!=NULL){
	    if (fgets(toBuf,100,toF)==NULL){
		fprintf(stderr,"Err reading toF!\n");
		exit(1);
	    }
	    string_trim(fromBuf);
	    string_trim(toBuf);
	    /* Skip non-functional dependency test */
	    if (testId%2==0){
		if (g_strstr_len(toBuf,PINYIN_MAX_LENGTH,"ê")){
		    // Tone mark cannot be add upon ê 
		    continue;
		}else if (g_strstr_len(toBuf,PINYIN_MAX_LENGTH,"v")){
		    // Tone mark cannot be add upon v
		    continue;
		}
	    }
	    if (j%2==0){
		if (g_strstr_len(fromBuf,PINYIN_MAX_LENGTH,"ê")){
		    // Tone make cannot be add upon ê 
		    continue;
		}else if (g_strstr_len(fromBuf,PINYIN_MAX_LENGTH,"v")){
		    // Tone make cannot be add upon v
		    continue;
		}
	    }
	    if (j<ZHUYIN_ALWAYS){
		/* Skip non-functional dependency test */
		if (j>=PINYIN_UNIHAN_F){
		    if (strcmp(fromBuf,"e")==0){
			continue;
		    }else if (g_str_has_prefix(toBuf,"ê")){
			// Ê only appears in ORIGINAL and ALWAYS.
			continue;
		    }else if (g_str_has_prefix(toBuf,"ㄝ")){
			// Single ㄝ can only be converted from PINYIN_ORIGINAL and PINYIN_ALWAYS.
			continue;
		    }
		    if (j==PINYIN_NONE_F || j==PINYIN_NONE_T){
			if (g_str_has_prefix(toBuf,"n") || g_str_has_prefix(toBuf,"l")){
			    if (g_strstr_len(toBuf,PINYIN_MAX_LENGTH,"ǖ")){
				continue;
			    }else if (g_strstr_len(toBuf,PINYIN_MAX_LENGTH,"ǘ")){
				continue;
			    }else if (g_strstr_len(toBuf,PINYIN_MAX_LENGTH,"ǚ")){
				continue;
			    }else if (g_strstr_len(toBuf,PINYIN_MAX_LENGTH,"ǜ")){
				continue;
			    }else if (g_strstr_len(toBuf,PINYIN_MAX_LENGTH,"ü")){
				continue;
			    }else if (g_strstr_len(toBuf,PINYIN_MAX_LENGTH,"v")){
				continue;
			    }else if (g_strstr_len(toBuf,PINYIN_MAX_LENGTH,":")){
				continue;
			    }
			}else if (g_str_has_prefix(toBuf,"ㄋㄩ")){
			    // ㄋㄩ cannot be convert from PINYIN_NONE
			    continue;
			}else if (g_str_has_prefix(toBuf,"ㄌㄩ")){
			    // ㄌㄩ cannot be convert from PINYIN_NONE
			    continue;
			}
		    }
		}

		if (testId<ZHUYIN_ALWAYS){
		    out=pinyin_convert_accent_format(fromBuf,testId/2,(testId%2==0) ? FALSE : TRUE);
		}else{
		    if (j>=PINYIN_UNIHAN_F){
			if (strcmp(fromBuf,"e")==0){
			    continue;
			}
			if (j==PINYIN_NONE_F || j==PINYIN_NONE_T){
			    if (g_str_has_prefix(fromBuf,"nu")){
				continue;
			    }else if (g_str_has_prefix(fromBuf,"lu")){
				continue;
			    }
			}
		    }
		    out=pinyin_to_zhuyin(fromBuf,testId-ZHUYIN_ALWAYS);
		}
	    }else{
		/* j>= ZHUYIN_ALWAYS*/
		/* Skip non-functional dependency test */

		if (testId<ZHUYIN_ALWAYS){
		    out=zhuyin_to_pinyin(fromBuf,testId/2,(testId%2==0) ? FALSE : TRUE);
		}else{
		    out=zhuyin_convert_toneMark_format(fromBuf,testId-ZHUYIN_ALWAYS);
		}
	    }
	    out_norm=g_utf8_normalize(out,-1,G_NORMALIZE_NFD);
	    toBuf_norm=g_utf8_normalize(toBuf,-1,G_NORMALIZE_NFD);
	    if (strcmp(out_norm,toBuf_norm)!=0){
		printf(" Failed: Orig=%s Out=%s Exp=%s\n",fromBuf,out_norm,toBuf_norm);
		printf("                 Out=");
		for(i=0;i<strlen(out_norm);i++){
		    printf(" %X", CHAR_TO_UNSIGNEDINT(out_norm[i]));
		}
		printf("\n                 exp=");
		for(i=0;i<strlen(toBuf_norm);i++){
		    printf(" %X", CHAR_TO_UNSIGNEDINT(toBuf_norm[i]));
		}
		printf("\n");
		return FALSE;
	    }else{
		verboseMsg_print(VERBOSE_MSG_INFO2,"  out=%s, exp=%s matched.\n",out_norm,toBuf_norm);
	    }
	    g_free(out_norm);
	    g_free(toBuf_norm);
	}
	
	printf(" completed.\n");
    }
    printf("All sub-test completed.\n");
    return TRUE;
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
	printf("Invalid test number.\n");
	return 2;
    }
    dataDir=argv[argIndex++];
    if (perform_test(test_index)){
	printf("Success!\n");
	return 0;
    }
    return 1;

}
