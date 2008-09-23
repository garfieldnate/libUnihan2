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
 
/**
 * Debug message handling functions
 */
#ifndef VERBOSEMSG_H_
#define VERBOSEMSG_H_
#include <stdio.h>
/**
 * Available verboseLevel:
 * <ol>
 *  <li> VERBOSE_MSG_NONE        -1
 *  <li> VERBOSE_MSG_CRITICAL    0 (default)
 *  <li> VERBOSE_MSG_ERROR       1
 *  <li> VERBOSE_MSG_WARNING     2
 *  <li> VERBOSE_MSG_INFO1       3
 *  <li> VERBOSE_MSG_INFO2       4
 *  <li> VERBOSE_MSG_INFO3       5
 *  <li> VERBOSE_MSG_INFO4       6
 *  <li> VERBOSE_MSG_INFO5       7
 * </ol>
 */
#define VERBOSE_MSG_NONE        -1
#define VERBOSE_MSG_CRITICAL    0
#define VERBOSE_MSG_ERROR       1
#define VERBOSE_MSG_WARNING     2
#define VERBOSE_MSG_INFO1       3
#define VERBOSE_MSG_INFO2       4
#define VERBOSE_MSG_INFO3       5
#define VERBOSE_MSG_INFO4       6
#define VERBOSE_MSG_INFO5       7

int verboseMsg_get_level();
void verboseMsg_set_level(int verboseLevel);

int verboseMsg_get_fileLevel();
void verboseMsg_set_fileLevel(int fileVerboseLevel);

void verboseMsg_set_logFile(FILE *outputFile);


/**
 * Verbose message output.
 * It is actually a wrapper of printf and fprintf
 * @param _verboseLevel
 * @param format
 * @param ...
 * @returns same as printf/fprintf 
 */
int verboseMsg_print(int verboseLevel, const char *format, ...);

void verboseMsg_increase_level(int difference);

#endif /*VERBOSEMSG_H_*/
