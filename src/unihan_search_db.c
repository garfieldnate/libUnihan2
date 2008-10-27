/** 
 * @file unihan_search_db.c
 * @brief Search and collect the fields and tables in Unihan database files from given paths.
 *
 * This program searches and collects the fields and tables in Unihan database files 
 * from given paths. If no path is given from the command line option, then use the 
 * path defined in \c UNIHAN_DEFAULT_DB_PATH.
 *
 * @since {libUnihan 0.6.0}
 */


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
#include <unistd.h>
#include <glib/gprintf.h>
#include "allocate.h"
#include "verboseMsg.h"
#include "file_functions.h"
#include "str_functions.h"
#include "Unihan.h"

#define USAGE_MSG "Search and collect the fields and tables in Unihan database files from given paths.\n\
Usage: %s [-h] [-V num] [-v] [SEARCH_PATH]\n\
   Specify SEARCH_PATH to search with custom search path,\n\
   otherwise default search path " UNIHAN_DB_SEARCH_PATH " will be used.\n\
   Use '%c' as path separater.\n\
Options:\
   -h: Show this help message.\n\
   -V [num]: Specify verbose level, the higher the num, the more detail is shown. \n\
      Default is 2 (show warning). \n\
   -v: Show libUnihan version number.\n"

#define BUFFER_SIZE 2000

gchar *searchPath=NULL;

gchar *outputDir=NULL;

static void printUsage(char **argv){
    printf(USAGE_MSG,argv[0],PATH_SEPARATOR);
}

/**
 * Whether the command line options are valid.
 */
static gboolean is_valid_arguments(int argc, char **argv) {
    int opt;
    int verboseLevel=VERBOSE_MSG_WARNING;
    outputDir=UNIHAN_DB_DEFAULT_PATH;
    searchPath=UNIHAN_DB_SEARCH_PATH;

    if (!argc){
	printUsage(argv);
	exit(0);
    }
    while ((opt = getopt(argc, argv, "ho:V:v")) != -1) {
	switch (opt) {
	    case 'h':
		printUsage(argv);
		exit(0);
	    case 'o':

	    case 'V':
		verboseLevel=atoi(optarg);
		break;
	    case 'v':
		printf("libUnihan %s\n",PRJ_VER);
		exit(0);
	    default: /* ’? */
		printf("Unrecognized Option -%c\n\n",opt);
		return FALSE;
	}
    }
    if (argc >  optind+1){
	printf("Invalid number of options. argc=%d, optind=%d\n",argc,optind);
	return FALSE;
    }else if (argc == optind+1){
	searchPath=argv[optind];
    }
    verboseMsg_set_level(verboseLevel);
    return TRUE;
}


int main(int argc,char** argv){
    if (!is_valid_arguments(argc, argv)){
	printUsage(argv);
	exit(-1);
    }
    StringList *sList=lsDir(searchPath, "*.db*", FILE_MODE_READ, TRUE);
    int i;
    for(i=0;i<sList->len;i++){
	printf("File=%s\n",stringList_index(sList,i));
    }
    
    return 0;

}
