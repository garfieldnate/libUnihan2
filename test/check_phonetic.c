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
#include "Unihan.h"
#include "Unihan_Phonetic.h"

typedef struct{
    char *input;
    char *expectOutput;
} ExamSet;


const char *PINYIN_TABLES[]={
    "BA",
    "BO",
    "BAI",
    "BEI",
    "BEO",
    "BAN",
    "BEN",
    "BANG",
    "BENG",
    "BU",
    "BI",
    "BIE",
    "BIAO",
    "BIAN",
    "BIN",
    "BING",

    NULL
};

gboolean perform_test(ExamSet *exSet,const char *prompt, gint acce){
    printf("Testing %s",prompt);
    while(exSet!=NULL && exSet->input!=NULL){
	out=pinYin_convert_accent(exSet->input,PINYIN_ACCENT_ALWAYS,FALSE);
	if (strcmp(out,exSet->expectOutput)!=0){
	    g_error("Failed: Orig:%s Out:%s Exp:%s",exSet->input,out,exSet->expectOutput);
	}
	exSet=&conversion_PINYIN_ACCENT_ALWAYS[++i];
    }

}

int main(int argc, char** argv){
    int i=0;
    ExamSet *exSet=&conversion_PINYIN_ACCENT_ALWAYS[i];
    char *out;

    while(exSet!=NULL && exSet->input!=NULL){
	out=pinYin_convert_accent(exSet->input,PINYIN_ACCENT_ALWAYS,FALSE);
	if (strcmp(out,exSet->expectOutput)!=0){
	    g_error("Failed: Orig:%s Out:%s Exp:%s",exSet->input,out,exSet->expectOutput);
	}
	exSet=&conversion_PINYIN_ACCENT_ALWAYS[++i];
    }
    printf("Success!");

    return 0;
}
