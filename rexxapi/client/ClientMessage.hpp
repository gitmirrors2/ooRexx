/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Copyright (c) 1995, 2004 IBM Corporation. All rights reserved.             */
/* Copyright (c) 2005-2024 Rexx Language Association. All rights reserved.    */
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

#ifndef ClientMessage_HPP_INCLUDED
#define ClientMessage_HPP_INCLUDED

#include "rexx.h"
#include "ServiceMessage.hpp"

class ApiConnection;

class ClientMessage : public ServiceMessage
{
public:
    inline ClientMessage(ServerManager target, ServerOperation op) : ServiceMessage()
    {
        messageTarget = target;
        operation = op;
    }

    inline ClientMessage(ServerManager target, ServerOperation op, uintptr_t p1)  : ServiceMessage()
    {
        messageTarget = target;
        operation = op;
        parameter1 = p1;
    }

    inline ClientMessage(ServerManager target, ServerOperation op, const char *p1)  : ServiceMessage()
    {
        messageTarget = target;
        operation = op;
        if (p1 != NULL)
        {
            Utilities::strncpy(nameArg, p1, NAMESIZE);
        }
        else
        {
            strcpy(nameArg, "");
        }
    }

    inline ClientMessage(ServerManager target, ServerOperation op, uintptr_t p1, const char *name) : ServiceMessage()
    {
        messageTarget = target;
        operation = op;
        parameter1 = p1;
        if (name != NULL)
        {
            Utilities::strncpy(nameArg, name, NAMESIZE);
        }
        else
        {
            strcpy(nameArg, "");
        }
    }

    inline ~ClientMessage()
    {
        // free the message data, if obtained from the server
        freeMessageData();
    }

    void send();
    void send(ApiConnection *pipe);
};

#endif

