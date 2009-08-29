/*----------------------------------------------------------------------------*/;
/*                                                                            */;
/* Copyright (c) 1995, 2004 IBM Corporation. All rights reserved.             */;
/* Copyright (c) 2005-2009 Rexx Language Association. All rights reserved.    */;
/*                                                                            */;
/* This program and the accompanying materials are made available under       */;
/* the terms of the Common Public License v1.0 which accompanies this         */;
/* distribution. A copy is also available at the following address:           */;
/* http://www.oorexx.org/license.html                                         */;
/*                                                                            */;
/* Redistribution and use in source and binary forms, with or                 */;
/* without modification, are permitted provided that the following            */;
/* conditions are met:                                                        */;
/*                                                                            */;
/* Redistributions of source code must retain the above copyright             */;
/* notice, this list of conditions and the following disclaimer.              */;
/* Redistributions in binary form must reproduce the above copyright          */;
/* notice, this list of conditions and the following disclaimer in            */;
/* the documentation and/or other materials provided with the distribution.   */;
/*                                                                            */;
/* Neither the name of Rexx Language Association nor the names                */;
/* of its contributors may be used to endorse or promote products             */;
/* derived from this software without specific prior written permission.      */;
/*                                                                            */;
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */;
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */;
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS          */;
/* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */;
/* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,      */;
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */;
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,        */;
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY     */;
/* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING    */;
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS         */;
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.               */;
/*                                                                            */;
/*----------------------------------------------------------------------------*/;

#ifndef APICommon_Included
#define APICommon_Included


#define NO_HMODULE_MSG            "failed to obtain %s module handle; OS error code %d"
#define NO_PROC_MSG               "failed to get procedeure adddress for %s(); OS error code %d"
#define API_FAILED_MSG            "system API %s() failed; OS error code %d"
#define COM_API_FAILED_MSG        "system API %s() failed; COM code 0x%08x"
#define NO_MEMORY_MSG             "failed to allocate memory"
#define FUNC_WINCTRL_FAILED_MSG   "the '%s'() function of the Windows '%s' control failed"
#define MSG_WINCTRL_FAILED_MSG    "the '%s' message of the Windows '%s' control failed"
#define NO_LOCAL_ENVIRONMENT_MSG  "the .local environment was not found"

extern void severeErrorException(RexxMethodContext *c, char *msg);
extern void systemServiceException(RexxMethodContext *context, char *msg);
extern void systemServiceException(RexxMethodContext *context, char *msg, const char *sub);
extern void systemServiceExceptionCode(RexxMethodContext *context, const char *msg, const char *arg1, DWORD rc);
extern void systemServiceExceptionCode(RexxMethodContext *context, const char *msg, const char *arg1);
extern void systemServiceExceptionComCode(RexxMethodContext *context, const char *msg, const char *arg1, HRESULT hr);
extern void outOfMemoryException(RexxMethodContext *c);
extern void userDefinedMsgException(RexxMethodContext *c, CSTRING msg);
extern void userDefinedMsgException(RexxMethodContext *c, int pos, CSTRING msg);
extern void *wrongClassException(RexxMethodContext *c, int pos, const char *n);
extern void invalidTypeException(RexxMethodContext *c, int pos, const char *type);
extern void invalidImageException(RexxMethodContext *c, int pos, CSTRING type, CSTRING actual);
extern void notNonNegativeException(RexxMethodContext *c, int pos, RexxObjectPtr actual);
extern void wrongObjInArrayException(RexxMethodContext *c, int argPos, size_t index, CSTRING obj);
extern void wrongObjInDirectoryException(RexxMethodContext *c, int argPos, CSTRING index, CSTRING needed, RexxObjectPtr actual);
extern void executionErrorException(RexxMethodContext *c, CSTRING msg);
extern void doOverException(RexxMethodContext *c, RexxObjectPtr obj);
extern void failedToRetrieveException(RexxMethodContext *c, CSTRING item, RexxObjectPtr source);
extern void missingIndexInDirectoryException(RexxMethodContext *c, int argPos, CSTRING index);
extern void emptyArrayException(RexxMethodContext *c, int argPos);
extern void nullObjectException(RexxMethodContext *c, CSTRING name, int pos);
extern void nullObjectException(RexxMethodContext *c, CSTRING name);
extern void nullPointerException(RexxMethodContext *c, int pos);
extern void wrongRangeException(RexxMethodContext *c, int pos, int min, int max, RexxObjectPtr actual);
extern void wrongRangeException(RexxMethodContext *c, int pos, int min, int max, int actual);
extern void wrongArgValueException(RexxMethodContext *c, int pos, const char *list, RexxObjectPtr actual);
extern void wrongArgValueException(RexxMethodContext *c, int pos, const char *list, const char *actual);

extern CSTRING rxGetStringAttribute(RexxMethodContext *context, RexxObjectPtr obj, CSTRING name);;
extern bool requiredClass(RexxMethodContext *c, RexxObjectPtr obj, const char *name, int pos);
extern size_t rxArgCount(RexxMethodContext * context);
extern bool rxStr2Number(RexxMethodContext *c, CSTRING str, uint64_t *number, int pos);
extern RexxClassObject rxGetContextClass(RexxMethodContext *c, CSTRING name);
extern RexxObjectPtr rxSetObjVar(RexxMethodContext *c, CSTRING varName, RexxObjectPtr val);
extern bool isInt(RexxMethodContext *, int, RexxObjectPtr);
extern bool isOfClassType(RexxMethodContext *, RexxObjectPtr, CSTRING);
extern void dbgPrintClassID(RexxMethodContext *c, RexxObjectPtr obj);

#endif
