#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <glob.h>
#include <dirent.h>
#include "allocate.h"
#include "file_functions.h"
#include "verboseMsg.h"

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

gboolean filename_meets_accessMode(const gchar *filename, guint access_mode_mask){
    if (access_mode_mask & FILE_MODE_READ){
	if (!isReadable(filename)){
	    return FALSE;
	}
    }
    if (access_mode_mask & FILE_MODE_WRITE){
	if (access_mode_mask & (FILE_MODE_READ | FILE_MODE_EXECUTE | FILE_MODE_EXIST)){
	    /* File must exist */
	    if (access(filename,W_OK)!=0){
		return FALSE;
	    }
	}else{
	    /* File need not exist */
	    if (!isWritable(filename)){
		return FALSE;
	    }
	}
    }
    if (access_mode_mask & FILE_MODE_EXECUTE){
	if (access(filename,X_OK)!=0){
	    return FALSE;
	}
    }
    if (access_mode_mask & FILE_MODE_EXIST){
	if (access(filename,F_OK)!=0){
	    return FALSE;
	}
    }
    if (access_mode_mask & FILE_MODE_NO_SYMLINK){
	struct stat st;
	if (lstat(filename,&st)){
	    /* Error on lstat() */
	    return FALSE;
	}
	if (S_ISLNK(st.st_mode))
	    return FALSE;
    }
    return TRUE;
}

gchar *filename_search_paths(const gchar *filename,const gchar *search_paths){
    return filename_search_paths_mode(filename,search_paths,FILE_MODE_EXIST);
}

gchar *filename_search_paths_mode(const gchar *filename,const gchar *search_paths,guint access_mode_mask){
    gchar currPath[PATH_MAX];
    gchar currPath_full[PATH_MAX];
    gchar pSep[2];
    pSep[0]=PATH_SEPARATOR;
    pSep[1]='\0';

    gchar** searchDir=g_strsplit(search_paths,pSep,0);
    gint i,len;
    for(i=0;searchDir[i]!=NULL;i++){
	len=strlen(searchDir[i]);
	g_strlcpy(currPath,searchDir[i],PATH_MAX);
	path_concat(currPath,filename,PATH_MAX);
	if (truepath(currPath,currPath_full)==NULL){
	    continue;
	}
	if (filename_meets_accessMode(currPath_full, access_mode_mask)){
	    g_strfreev(searchDir);
	    return g_strdup(currPath_full);
	}
    }
    g_strfreev(searchDir);
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

gchar *filename_choose(const gchar *filename_default, guint filename_len, StringList *extensions,
 guint access_mode_mask, const gchar * prompt, gpointer option, ChooseFilenameFunc callback){
    gchar *resultName=NEW_ARRAY_INSTANCE(filename_len,gchar);
    initString(resultName);
    if (!isEmptyString(filename_default)){
	truepath(filename_default,resultName);
	if (filename_meets_accessMode(resultName,access_mode_mask)){
	    return resultName;
	}
    }
    int ret;
    while(TRUE){
	ret=callback(resultName, filename_len, extensions,
		access_mode_mask, prompt, option);
	if (ret==TASK_COMPLETED){
	    return resultName;
	}else if (ret==TASK_CANCELED){
	    break;
	}
    }
    g_free(resultName);
    return NULL;
}

StringList *lsDir(const gchar* dir, const gchar *globStr, guint access_mode_mask, gboolean keepPath){
    StringList *sList=stringList_new();
    if (!lsDir_append(sList, dir, globStr, access_mode_mask, keepPath)){
	stringList_free(sList);
	return NULL;
    }
    return sList;
}

StringList *lsDir_append(StringList *sList,const gchar* dir, const gchar *globStr, guint access_mode_mask, gboolean keepPath){
    gchar path_tmp[PATH_MAX];
    int i;
    gchar **globs= g_strsplit_set(globStr," ",-1);
    glob_t globbuf;
    glob_t *globptr=&globbuf;

    globptr->gl_offs=0;

    int globFlag= GLOB_DOOFFS | GLOB_TILDE | GLOB_NOESCAPE;
    int ret=GLOB_NOMATCH;
    for(i=0;globs[i]!=NULL;i++){
	g_strlcpy(path_tmp,dir,PATH_MAX);
	path_concat(path_tmp,globs[i],PATH_MAX);
	if (i==1){
	    globFlag|= GLOB_APPEND;
	}
	ret=glob(path_tmp,globFlag,NULL, &globbuf);
	if (ret==GLOB_ABORTED || ret == GLOB_NOSPACE)
	    break;
    }
    if (ret==GLOB_ABORTED || ret == GLOB_NOSPACE){
	globfree(globptr);
	return NULL;
    }

    for(i=0;i<globptr->gl_pathc;i++){
	if (filename_meets_accessMode(globptr->gl_pathv[i],access_mode_mask)){
	    if (keepPath){
		stringList_insert(sList,globptr->gl_pathv[i]);
	    }else{
		stringList_insert(sList,globptr->gl_pathv[i]);
	    }
	}
    }
    globfree(globptr);
    return sList;
}



gchar *path_concat(gchar *dest, const gchar *src,gsize destSize){
    int len=strlen(dest);
    if (len>0){
	if (dest[len-1]==DIRECTORY_SEPARATOR){
	    /* hasDirSeparator already */
	}else if (len<destSize-1){
	    dest[len]=DIRECTORY_SEPARATOR;
	    dest[++len]='\0';
	}else{
	    return dest;
	}
    }
    g_strlcat(dest,src,destSize);
    return dest;
}

StringList *path_split(const gchar *path){
    gchar delimiter[6];
    g_sprintf(delimiter,"%c",PATH_SEPARATOR);
    gchar ** strs=g_strsplit(path,delimiter,-1);
    int i;
    StringList *sList=NULL;
    for(i=0;strs[i]!=NULL;i++){
	if (i==0){
	    sList=stringList_new();
	}
	string_trim(strs[i]);
	stringList_insert(sList,strs[i]);
    }
    g_strfreev(strs);
    return sList;
}



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

	firstSlash = strchr(workingPath, DIRECTORY_SEPARATOR);
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
	    gint ret=g_sprintf(fullPath, "%s%c%s", homeDirStr, DIRECTORY_SEPARATOR, suffix);
	    if (ret>0){
		result = realpath(fullPath, resolved_path);
	    }

	}
    }
    return result;
}


