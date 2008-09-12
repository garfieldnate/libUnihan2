/*
 * Copyright © 2007  Red Hat, Inc. All rights reserved.
 *  
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions
 * of the GNU General Public License v.2. This program is distributed in
 * the hope that it will be useful, but WITHOUT ANY WARRANTY expressed
 * or implied, including the implied warranties of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details. You should have received a copy of the GNU General
 * Public License along with this program; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA. Any Red Hat trademarks that are incorporated in
 * the source code or documentation are not subject to the GNU General
 * Public License and may only be used or replicated with the express
 * permission of Red Hat, Inc. 
 * 
 * Red Hat Author(s): Ding-Yi Chen <dchen at redhat dot com> 
 */
 
#ifndef FILE_FUNCTIONS_H_
#define FILE_FUNCTIONS_H_
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <glib.h>

#ifdef WIN32
#define FILE_SEPARATOR '\\'
#else
#define FILE_SEPARATOR '/'
#endif

#define PATH_SEPARATOR ';'

/**
 * Return the canonicalized absolute pathname.
 *
 * It works exactly the same with realpath(3), except it can handle the path with ~,
 * where realpath cannot.
 * @param path The path to be resolved
 * @param resolved_path Buffer to hold the resolved_path
 * @returns: resolved path, NULL is the resolution is not sucessful.
 */
gchar*
truepath(const gchar *path, gchar *resolved_path);

gboolean
isReadable(const gchar *filename);


gboolean
isWritable(const gchar *filename);

gchar*
search_file_given_paths(const gchar *filename,const gchar* search_paths,gboolean readable);

/**
 * ChooseFilenameFunc:
 * Callback function for filename_get_user_chosen
 * @defaultFilename: pre-selected filename. Can be NULL.
 * @extensions: acceptable file extensions. NULL for don't care.
 * @prompt: the string to be shown in UI, usually shown as dialog title for GUI.
 * @option: Other custom option.
 *
 * Note that the callback function should be capable of checking whether
 * the selected files are readable (for file opening) or 
 * writable (for file saving).
 *
 * @returns: the filename of selection.
 */
typedef gchar* (* ChooseFilenameFunc) 
(const gchar *defaultFilename, const gchar** extensions,const gchar * prompt,gpointer option);

/**
 * filename_get_user_chosen_callback_open_TUI:
 * TUI for selecting open file. 
 * @defaultFilename: pre-selected filename. Can be NULL.
 * @extensions: acceptable file extensions. NULL for don't care.
 * @prompt: the string to be shown in UI, usually shown as dialog title for GUI.
 * @option: Other custom option.
 *
 * Unlike its GUI counterparts, it merely tests the readability of filename.
 *
 * @returns: Returns the filename if it is readable; NULL otherwise.
 */
gchar *filename_get_user_chosen_callback_open_TUI
(const gchar *defaultFilename, const gchar** extensions,const gchar * prompt,gpointer option);


/**
 * filename_get_user_chosen_callback_sve_TUI:
 * TUI for selecting save file. 
 * @defaultFilename: pre-selected filename. Can be NULL.
 * @extensions: acceptable file extensions. NULL for don't care.
 * @prompt: the string to be shown in UI, usually shown as dialog title for GUI.
 * @option: Other custom option.
 *
 * Unlike its GUI counterparts, it merely tests the writability of filename.
 *
 * @returns: Returns the filename if it is readable; NULL otherwise.
 */
gchar *filename_get_user_chosen_callback_save_TUI
(const gchar *defaultFilename, const gchar** extensions,const gchar * prompt,gpointer option);

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

