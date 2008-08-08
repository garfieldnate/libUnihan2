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

#include <stdarg.h>
#include "verboseMsg.h" 

int _verboseLevel=VERBOSE_MSG_CRITICAL;
int _fileVerboseLevel=VERBOSE_MSG_NONE;
FILE *_outputFile;

int verboseMsg_get_level(){
    return _verboseLevel;
}

void verboseMsg_set_level(int verboseLevel){
    _verboseLevel=verboseLevel;
}

int verboseMsg_get_fileLevel(){
    return _fileVerboseLevel;
}

void verboseMsg_set_fileLevel(int fileVerboseLevel){
    _fileVerboseLevel=fileVerboseLevel;
}

void verboseMsg_set_logFile(FILE *outputFile){
    _outputFile=outputFile;
}



int verboseMsg_print(int verboseLevel, const char *format, ...){
    int ret=0;
    va_list ap;
    if (_verboseLevel>=verboseLevel){
        va_start(ap, format);
        ret = vfprintf(stdout, format, ap);
        va_end(ap);
    }
    
    if (_fileVerboseLevel>=verboseLevel){
        va_start(ap, format);
        ret = vfprintf(_outputFile, format, ap);
        va_end(ap);
    }
    return ret;
}

void verboseMsg_increase_level(int difference){
    _verboseLevel+=difference;
    _fileVerboseLevel+=difference;
}
