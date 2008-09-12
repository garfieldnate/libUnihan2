#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include "file_functions.h"
#include "str_functions.h"
#include "verboseMsg.h"

gchar*
truepath(const gchar *path, gchar *resolved_path){
    gchar workingPath[PATH_MAX];
    gchar fullPath[PATH_MAX];
    gchar *result=NULL;
    g_strlcpy(workingPath,path,PATH_MAX);
    
//     printf("*** path=%s \n",path);
        
    if ( workingPath[0] != '~' ){
        result = realpath(workingPath, resolved_path);
    }else{
        gchar *firstSlash, *suffix, *homeDirStr;
        struct passwd *pw;
        
        // initialize variables
        firstSlash = suffix = homeDirStr = NULL;
        
	firstSlash = strchr(workingPath, FILE_SEPARATOR);
        if (firstSlash == NULL)
            suffix = "";
        else
        {
            *firstSlash = 0;    // so userName is null terminated
            suffix = firstSlash + 1;
        }
        
        if (workingPath[1] == '\0')
            pw = getpwuid( getuid() );
        else
            pw = getpwnam( &workingPath[1] );
        
        if (pw != NULL)
            homeDirStr = pw->pw_dir;
        
        if (homeDirStr != NULL){
	    int ret=g_sprintf(fullPath, "%s/%s", homeDirStr, suffix);
	    if (ret>0){
		result = realpath(fullPath, resolved_path);
	    }

	}
    }
    return result;
}

gboolean
isReadable(const gchar *filename){
    return (access(filename, R_OK) == 0)? TRUE: FALSE;
}

gboolean 
isWritable(const gchar *filename){
    gchar parentDirBuf[PATH_MAX];
    gchar *parentDir;
    gboolean result=TRUE;
    
    if (access(filename,W_OK)!=0){
	// Can't write the file , test whether the parent director can write 
	g_strlcpy(parentDirBuf,filename,PATH_MAX);
	parentDir=dirname(parentDirBuf);
	if (access(filename,F_OK)==0 || access(parentDir,W_OK)!=0){
	    result=FALSE;
        }
    }
    return result;
}

gchar *search_file_given_paths(const gchar *filename,const gchar* search_paths,gboolean readable){
    gchar buf[PATH_MAX];
    gchar pSep[2];
    pSep[0]=PATH_SEPARATOR;
    pSep[1]='\0';

    GString *strBuf=g_string_new(NULL);
    gchar** searchDir=g_strsplit(search_paths,pSep,0);
    int i,len;
    for(i=0;searchDir[i]!=NULL;i++){
	len=strlen(searchDir[i]);
	if ((searchDir[i][len-1]==FILE_SEPARATOR) ){
	    g_string_printf(strBuf,"%s%s",searchDir[i],filename);
	}else{
	    g_string_printf(strBuf,"%s%c%s",searchDir[i],FILE_SEPARATOR,filename);
	}
	if (truepath(strBuf->str,buf)==NULL){
	    continue;
	}
	if (readable && isReadable(buf)){
	    g_string_assign(strBuf,buf);
	    return g_string_free(strBuf,FALSE);
	}else if(isWritable(buf)){
	    g_string_assign(strBuf,buf);
	    return g_string_free(strBuf,FALSE); 
	}
    }
    g_string_free(strBuf,TRUE);
    return NULL;
}


gchar *filename_get_user_chosen_callback_open_TUI
(const gchar *defaultFilename, const gchar** extensions, const gchar * prompt,gpointer option){
    gchar buf[PATH_MAX];

    if (!isReadable(defaultFilename)) {
	g_snprintf(buf, PATH_MAX, "[Error] Cannot read %s - check path and permission.", defaultFilename);
	verboseMsg_print(VERBOSE_MSG_ERROR, "%s\n", buf);
	return NULL;
    }
    return g_strdup(defaultFilename);
}

gchar *filename_get_user_chosen_callback_save_TUI
(const gchar *defaultFilename, const gchar** extensions, const gchar * prompt,gpointer option){
    gchar buf[PATH_MAX];

    if (!isWritable(defaultFilename)) {
	g_snprintf(buf, PATH_MAX, "[Error] Cannot write %s - check path and permission.", defaultFilename);
	verboseMsg_print(VERBOSE_MSG_ERROR, "%s\n", buf);
	return NULL;
    }
    return g_strdup(defaultFilename);
}

gchar *filename_determine(gchar* filenameBuf,const gchar* defaultFilename,
	const gchar** extensions,
	const gchar* prompt, ChooseFilenameFunc callback, gpointer option,gboolean isRead){
    gchar *resultName=NULL;
    gchar tmpBuf[PATH_MAX];
    if (isEmptyString(filenameBuf)){
	resultName=callback(defaultFilename, extensions,
		prompt,option);
    }else{
	truepath(filenameBuf,tmpBuf);
	if (isRead){
	    if (isReadable(tmpBuf))
		resultName=tmpBuf;
	}else{
	    if (isWritable(tmpBuf))
		resultName=tmpBuf;
	}
    }
    if (resultName==NULL){
	return NULL;
    }
    strcpy(filenameBuf,resultName);
    return filenameBuf;
}

gchar *filename_determine_readable(gchar* filenameBuf,
	const gchar* defaultFilename,
	const gchar** extensions, const gchar* prompt, 
	ChooseFilenameFunc callback, gpointer option){
    return filename_determine(filenameBuf,defaultFilename,extensions, prompt,
	    callback,option, TRUE);
}

gchar *filename_determine_writable(gchar* filenameBuf,
	const gchar* defaultFilename,
	const gchar** extensions, const gchar* prompt, 
	ChooseFilenameFunc callback, gpointer option){
    return filename_determine(filenameBuf,defaultFilename,extensions, prompt,
	    callback,option, TRUE);
}

