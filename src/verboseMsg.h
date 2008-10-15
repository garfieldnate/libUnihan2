/** 
 * @file verboseMsg.h
 * @brief Verbose message handling.
 *
 * Verbose messages show critical errors, errors, warnings, and various messages 
 * for information or debugging use.
 *
 * They can display on screen, depending on the <i>current verbose level</i> and 
 * <i>message verbose level</i>.
 * If verbose level messages are lesser than or equals to the current verbose level, 
 * the message will show on screen; otherwise the message will be ignored and not showing.
 *
 * Similarly, the verbose messages can save to log files,
 * depending on the <i>file verbose level</i>.
 * If verbose level messages are lesser than or equals to the file verbose level, 
 * the message will print to the given log file; otherwise the message will not appear in log file.
 * See  also verboseMsg_print().
 *
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
 
#ifndef VERBOSEMSG_H_
#define VERBOSEMSG_H_
#include <stdio.h>
/**
 * @name Available verboseLevel
 *
 * Predefined verbose levels. 
 *
 * You can define more levels by yourself if necessary.
 * @{
 */
#define VERBOSE_MSG_NONE        -1 //!< No debug message output.
#define VERBOSE_MSG_CRITICAL    0  //!< Output critical messages.
#define VERBOSE_MSG_ERROR       1  //!< Output general errors and above.
#define VERBOSE_MSG_WARNING     2  //!< Output warning messages and above.
#define VERBOSE_MSG_INFO1       3  //!< Output the information message level 1 and above.
#define VERBOSE_MSG_INFO2       4  //!< Output the information message level 2 and above.
#define VERBOSE_MSG_INFO3       5  //!< Output the information message level 3 and above.
#define VERBOSE_MSG_INFO4       6  //!< Output the information message level 4 and above.
#define VERBOSE_MSG_INFO5       7  //!< Output the information message level 5 and above.
#define VERBOSE_MSG_INFO6       8  //!< Output the information message level 6 and above.

/**
 * @}
 */

/**
 * Get the current verbose level.
 *
 * @return current verbose level.
 */
gint verboseMsg_get_level();

/**
 * Set the current verbose level.
 *
 * @param verboseLevel the verbose level to be set as current verbose level.
 */
void verboseMsg_set_level(gint verboseLevel);

/**
 * Get the file verbose level.
 * 
 * @return file verbose level.
 */
gint verboseMsg_get_fileLevel();

/**
 * Set the file verbose level.
 *
 * @param fileVerboseLevel the verbose level to be set as file verbose level.
 */
void verboseMsg_set_fileLevel(gint fileVerboseLevel);

/**
 * Set the log file.
 * 
 * @param outputFile Output file.
 */
void verboseMsg_set_logFile(FILE *outputFile);


/**
 * Output Verbose message.
 *
 * This function prints the verbose to screen, and log files.
 *  if the \a outputFile in verboseMsg_set_logFile() is given.
 * The message will be displayed on screen if \a verboseLevel is lesser or equal to current verbose level.
 * The message will also be printed to the log if the \a outputFile is given and
 *  \a verboseLevel is lesser or equal to file verbose level.
 *
 * The rest of this function works like fprintf.
 * @param verboseLevel
 * @param format
 * @param ...
 * @returns same as printf/fprintf 
 * @see verboseMsg_set_logFile()
 */
gint verboseMsg_print(gint verboseLevel, const gchar *format, ...);

/**
 * Increase or decrease verbose level.
 *
 * This function can increase the verbose level by setting a positive \a difference;
 * while setting a negative \a difference decrease the verbose level.
 *
 * @param difference The amount of verbose level be changed.
 */
void verboseMsg_increase_level(gint difference);

#endif /*VERBOSEMSG_H_*/
