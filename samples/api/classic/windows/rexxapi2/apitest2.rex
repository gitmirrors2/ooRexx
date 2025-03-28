/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Copyright (c) 1995, 2004 IBM Corporation. All rights reserved.             */
/* Copyright (c) 2005-2025 Rexx Language Association. All rights reserved.    */
/*                                                                            */
/* This program and the accompanying materials are made available under       */
/* the terms of the Common Public License v1.0 which accompanies this         */
/* distribution. A copy is also available at the following address:           */
/* https://www.oorexx.org/license.html                                        */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or                 */
/* without modification, are permitted provided that the following            */
/* conditions are met:                                                        */
/*                                                                            */
/* Redistributions of source code must retain the above copyright             */
/* notice, this list of conditions and the following disclaimer.              */
/* Redistributions in binary form must reproduce the above copyright          */
/* notice, this list of conditions and the following disclaimer in            */
/* the documentation and/or other materials provided with the distribution.   */
/*                                                                            */
/* Neither the name of Rexx Language Association nor the names                */
/* of its contributors may be used to endorse or promote products             */
/* derived from this software without specific prior written permission.      */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS          */
/* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,      */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,        */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY     */
/* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING    */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS         */
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Testing the REXX-API *****************************************************************/
/*                                                                                      */
/* REXX calls the Function Api_Fill_REXX_Variable_Pool and hands over the name of       */
/* a buffer. The C-function creates a REXX variable with the specified name and         */
/* initializes the variable. REXX is able to access the variable using the buffer name. */
/*                                                                                      */
/****************************************************************************************/

/****************************************************************************/
/* Name: apitest2.rex                                                       */
/* Type: ooRexx Script                                                      */
/* Description:                                                             */
/*                                                                          */
/* REXX calls the Function Api_Fill_REXX_Variable_Pool and hands over the   */
/* name of a buffer. The C-function creates a REXX variable with the        */
/* specified name and initializes the variable.                             */
/* REXX is able to access the variable using the buffer name.               */
/*                                                                          */
/****************************************************************************/

Call RxFuncAdd "ApiLoadFuncs", "REXXAPI2", "ApiLoadFuncs"
Call ApiLoadFuncs

call Api_Fill_REXX_Variable_Pool "ReadBuf"
Say 'Length of buffer created by external function: ' Length(ReadBuf)


Say 'The C-function Api_Fill_REXX_Variable_Pool has put the following data into the buffer: '

Do i = 1 To Length(ReadBuf)
  Say 'Position in buffer:' i 'Decimal Value:' C2D(SubStr(ReadBuf, i, 1)) 'Hex Value: ' C2X(SubStr(ReadBuf, i, 1))
End

call ApiDeregFunc

exit
