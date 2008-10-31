/** 
 * @file file_functions.h
 * @brief File functions.
 *
 * This header filed define file functions.
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

 
#ifndef FILE_FUNCTIONS_H_
#define FILE_FUNCTIONS_H_
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <glib.h>
#include "str_functions.h"

/**
 * DIRECTORY_SEPARATOR is the separator for splits the directories in paths.
 *
 * If WIN32 is defined, DIRECTORY_SEPARATOR is '\\', 
 * otherwise '/' is used as DIRECTORY_SEPARATOR.
 */
#ifdef WIN32
#define DIRECTORY_SEPARATOR '\\'
#else
#define DIRECTORY_SEPARATOR '/'
#endif

/**
 * An enumeration of task running status.
 *
 * This enumeration lists the task running status.
 * It can be used as function return values, or as concurrent process running status.
 */
typedef enum{
    TASK_RUNNING, //! < The task is still running, usually this for concurrent process.
    TASK_CANCELED, //! < The task is canceled.
    TASK_FAILED,   //! < The task is failed.
    TASK_COMPLETED //! < The task is complete.
} TaskStatus;


/**
 * PATH_SEPARATOR is the separator for splits the paths in configuration files or environment variables.
 *
 * If WIN32 is defined, PATH_SEPARATOR is ';', 
 * otherwise ':' is used as PATH_SEPARATOR.
 */
#ifdef WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif


/**
 * Whether the file is readable.
 *
 * @param filename The path name of the file.
 * @return TRUE if the file is readable; FALSE otherwise.
 */
gboolean
isReadable(const gchar *filename);


/**
 * Whether the file is writable.
 *
 * This function checks whether the file is writable, or can be created if \a filename does not exists.
 *
 * @param filename The path name of the file.
 * @return TRUE if the file is writeable ; FALSE otherwise.
 */
gboolean
isWritable(const gchar *filename);

/**
 * @defgroup FileAccessMode File access mode.
 * @{
 * @name File access mode
 *
 * Access modes of a file or directory. 
 * This is similar to \c F_OK, \c R_OK, \c W_OK, \c X_OK in unistd.h.
 * However, as F_OK == 0, which is not very helpful when cooperates with other modes.
 * 
 * @{
 */
#define FILE_MODE_NO_SYMLINK  1<<5  //!< Test whether the file is not symbol link.
#define FILE_MODE_EXIST    1<<4  //!< Test for existence.
#define FILE_MODE_DIRECTORY   1<<3  //!< Test whether the 'file' is directory.
#define FILE_MODE_READ     1<<2  //!< Test for read permission.
#define FILE_MODE_WRITE    1<<1  //!< Test for write permission.
#define FILE_MODE_EXECUTE  1  //!< Test for execute permission.
/**
 * @}
 * @}
 */


/**
 * Whether the file meets the given access mode mask.
 *
 * This function checks whether the \a filename meets the requirement specified as \a access_mode_mask.
 * It returns TRUE if all file access mode are meet; FALSE otherwise.
 *
 * Note that if only \c FILE_MODE_WRITE is given to access_mode_mask, this function returns TRUE even 
 * if the file does not exist, but can be created and written.
 * Use \c FILE_MODE_EXIST|FILE_MODE_WRITE the check the write permission of existing file.
 *
 * @param filename The filename to be checked.
 * @param access_mode_mask the required access mode mask defined in \ref FileAccessMode.
 */
gboolean filename_meets_accessMode(const gchar *filename, guint access_mode_mask);

/**
 * Find a file from the search path.
 *
 * This function searches the given file within the search_paths.
 * It is essentially \c filename_search_paths_mode(filename, search_paths, FILE_MODE_EXIST).
 *
 * @param filename The filename to be located.
 * @param search_paths The paths to be searched.
 * @return A newly allocated string of the exact location of the file; otherwise NULL is returned.
 */
gchar*
filename_search_paths(const gchar *filename,const gchar* search_paths);

/**
 * Find a file with specified access mode from the search path.
 *
 * This function searches the file within the search_paths, after the file is found,
 * \c filename_meets_accessMode() is called to check whether the file meets the required \a access_mode_mask. 
 *
 * This function return newly allocated string of the exact location of the file
 * if the file is found and it match the requirement;
 * otherwise NULL is returned.
 *
 * @param filename The filename to be located.
 * @param search_paths The paths to be searched.
 * @param access_mode_mask the required access mode mask defined in \ref FileAccessMode.
 * @return A newly allocated string of the exact location of the file 
 * if the file is found and it match the requirement;
 * otherwise NULL is returned.
 * @see \ref FileAccessMode.
 * @see filename_meets_accessMode()
 */
gchar*
filename_search_paths_mode(const gchar *filename,const gchar* search_paths,guint access_mode_mask);

/**
 * Prototype of callback function for choosing a filename.
 *
 * This callback function should provide an UI for user select a filename.
 * It should return:
 *
 * - \c TASK_COMPLETED if a suitable file is chosen, and the chosen filename is in \a filename_buf.
 * - \c TASK_CANCELED if user canceled the operation.
 * - \c TAKS_FAILED   if user selected an unsuitable file, or encounter I/O error, 
 *                    the selected file should be in \a filename_buf
 * .
 * 
 *
 * The parameter \a filename_buf is a buffer that hold the result filename. 
 * and \a filename_len is the buffer size.
 * The present content of \a filename_buf will be default filename.
 *
 * Parameter \a extensions for available extension filename, assign NULL if no need to have a specific extension.
 * Use \a access_modes_mask to filter the files that has suitable access mode and permission.
 *
 * Value in \a prompt is to be show in UI, such as dialog title or textual prompt in CLI.
 * Use \a option to pass other data to the callback function.
 *
 * @param filename_buf Buffer that holds the filename, the present content will be default filename.
 * @param filename_len pre-selected filename. Can be NULL.
 * @param extensions acceptable file extensions. NULL for don't care.
 * @param access_mode_mask the required access mode mask defined in \ref FileAccessMode.
 * @param prompt the string to be shown in UI, usually shown as dialog title for GUI.
 * @param option Other custom option.
 * @retval TASK_COMPLETED if a suitable file is chosen, and the chosen filename is in \a filename_buf.
 * @retval TASK_CANCELED if user canceled the operation.
 * @retval TAKS_FAILED   if user selected an unsuitable file, or encounter I/O error, the selected file should be in \a filename_buf
 * @see filename_meets_accessMode()
 * @see filename_choose()
 */
typedef TaskStatus (* ChooseFilenameFunc) (gchar *filename_buf, guint filename_len, StringList *extensions, guint access_mode_mask, const gchar * prompt, gpointer option);

/**
 * Choose a suitable filename if default one is not.
 *
 * This function returns either a newly allocated filename string that meets the \a access_mode_mask,
 * or NULL if user cancel the process.
 *
 * This function firstly try the filename given by a non-NULL \a filename_default, if it does not meet 
 * \a access_mode_make, then it will keep calling \a callback() to open an UI for user input until:
 *
 * - user inputs a valid filename, or
 * - user cancels the operation (usually by clicking "cancel" button.)
 * .
 *
 * If \a filename_default is NULL, this function will call \a callback() directly for user input.
 *
 * @param filename_default The default filename to be check, NULL or "" if no default filename.
 * @param filename_len pre-selected filename. Can be NULL.
 * @param extensions acceptable file extensions. NULL for don't care.
 * @param access_mode_mask the required access mode mask defined in \ref FileAccessMode.
 * @param prompt the string to be shown in UI, usually shown as dialog title for GUI.
 * @param option Other custom option.
 * @param callback a ChooseFilenameFunc callback that open a UI for filename input.
 * @return a newly allocated filename string that meets the \a access_mode_mask; NULL otherwise.
 *
 * @see ChooseFilenameFunc()
 * @see filename_meets_accessMode()
 */
gchar *filename_choose
(const gchar *filename_default, guint filename_len, StringList *extensions,
 guint access_mode_mask, const gchar * prompt, gpointer option, ChooseFilenameFunc callback);

/**
 * List files which meet the given pattern and access modes in a directory.
 *
 * This function returns all files that match the pattern \a glob and the
 * access mode \a access_mode_mask; \c NULL if error occurred.
 *
 * The pattern  \a glob is matched in the same way as in shell.
 *
 * Use stringList_free() to free the result StringList.
 *
 * @param dir Directory to be listed.
 * @param globStr Glob/Shell pattern such as "*.*", use space to separate
 * multiple patterns.
 * @param access_mode_mask the required access mode mask defined in \ref FileAccessMode.
 * @param keepPath TRUE to concatenate \a dir to each string in the returned
 * StringList; FALSE for the filename only (without path).
 *
 * @return A newly allocate StringList instance which contains the matched
 * filename; NULL if error occurred.
 * @see lsDir_append()
 */
StringList *lsDir(const gchar* dir, const gchar *globStr, guint access_mode_mask, gboolean keepPath);

/**
 * Append the files which meet the given pattern and access modes in a directory to
 * the existing list.
 *
 * This function appends the files it found to the existing list \a sList,
 * and return it, otherwise it is similar with lsDir().
 *
 * @param sList existing list.
 * @param dir Directory to be listed.
 * @param globStr Glob/Shell pattern such as "*.*", use space to separate
 * multiple patterns.
 * @param access_mode_mask the required access mode mask defined in \ref FileAccessMode.
 * @param keepPath TRUE to concatenate \a dir to each string in the returned
 * StringList; FALSE for the filename only (without path).
 *
 * @return The modified \a sList, or NULL if error occurred.
 * @see lsDir()
 */
StringList *lsDir_append(StringList *sList,const gchar* dir, const gchar *globStr, guint access_mode_mask, gboolean keepPath);

/**
 * Split a composite path string by path separator.
 *
 * This function splits a string that has multiple paths (composite path string) separated by
 * \c PATH_SEPARATOR into individual paths. These paths will be returned as
 * \c StringList.
 *
 * @param path The composite path.
 * @return A newly allocated StringList instance that holds the split paths.
 */
StringList *path_split(const gchar *path);

/**
 * Concatenate two path strings.
 *
 * This function concatenate to path strings, a \c DIRECTORY_SEPARATOR is
 * inserted between \a dest and \a src if \a dest does not ended with a \c DIRECTORY_SEPARATOR.
 * The result string will be returned.
 *
 * @param dest 	destination buffer, already containing one nul-terminated string
 * @param src string to be appended to \a dest.
 * @param destSize length of dest buffer in bytes (not length of existing string inside dest).
 * @return The result string \a dest.
 */
gchar *path_concat(gchar *dest, const gchar *src, gsize destSize);

/**
 * Return the canonicalized absolute pathname.
 *
 * It works exactly the same with realpath(3), except this function can handle the path with ~,
 * where realpath cannot.
 *
 * @param path The path to be resolved.
 * @param resolved_path Buffer for holding the resolved_path.
 * @return resolved path, NULL is the resolution is not sucessful.
 */
gchar*
truepath(const gchar *path, gchar *resolved_path);


#endif /*FILE_FUNCTIONS_H_*/


