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
#define FILE_MODE_EXIST    8  //!< Test for existence.
#define FILE_MODE_READ     4  //!< Test for read permission.
#define FILE_MODE_WRITE    2  //!< Test for write permission.
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
 * @param access_mode_mask the required access mode mask defined in #FileAccessMode.
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
 * @param access_mode_mask the required access mode mask defined in #FileAccessMode.
 * @return A newly allocated string of the exact location of the file 
 * if the file is found and it match the requirement;
 * otherwise NULL is returned.
 * @see FileAccessMode.
 * @see filename_meets_accessMode()
 */
gchar*
filename_search_paths_mode(const gchar *filename,const gchar* search_paths,guint access_mode_mask);

/**
 * Prototype of callback function for choosing a file name filename_get_user_chosen.
 *
 * Note that the callback function should be capable of checking whether
 * the selected files are readable (for file opening) or 
 * writable (for file saving).
 *
 * @param filename pre-selected filename. Can be NULL.
 * @param extensions acceptable file extensions. NULL for don't care.
 * @param prompt the string to be shown in UI, usually shown as dialog title for GUI.
 * @param access_mode_mask the required access mode mask defined in #FileAccessMode.
 * @param option Other custom option.
 * @return The filename of selection.
 */
typedef gchar* (* ChooseFilenameFunc) 
(gchar *defaultFilename, const gchar** extensions,const gchar * prompt,guint access_mode_mask, gpointer option);

gchar *filename_determine(gchar* filenameBuf,const gchar* defaultFilename,
	const gchar** extensions,
	const gchar* prompt, ChooseFilenameFunc callback, gpointer option,gboolean isRead);

gchar *filename_determine_readable(gchar* filenameBuf,
	const gchar* defaultFilename,
	const gchar** extensions, const gchar* prompt, 
	ChooseFilenameFunc callback, gpointer option);

gchar *filename_determine_writable(gchar* filenameBuf,
	const gchar* defaultFilename,
	const gchar** extensions, const gchar* prompt, 
	ChooseFilenameFunc callback, gpointer option);

#endif /*FILE_FUNCTIONS_H_*/

