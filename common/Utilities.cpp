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
/****************************************************************************/
/* REXX Kernel                                                              */
/*                                                                          */
/* Utility Functions                                                        */
/*                                                                          */
/****************************************************************************/

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include "Utilities.hpp"

/**
 * Locate the first occurrence of any character from a given set.
 *
 * @param string The string we're searching in.
 * @param set    The set of characters to search for as an ASCII-Z string.
 *               The terminating null is not part of the search set.
 * @param length The length of the string we search in.
 *
 * @return The hit position or null if none of the characters are found.
 */
const char *Utilities::locateCharacter(const char *string, const char *set, size_t length )
{
    while (length-- > 0)
    {
        // check for a match in the string.  NOTE:  this will return a hit
        // for a null character, so we need to check for this after the fact
        if (strchr(set, *string))
        {
            if (*string != '\0')
            {
                return string;
            }
        }
        string++;
    }
    // no matched position
    return NULL;
}


/**
 * Portable implementation of an ascii-z caseless string compare.
 *
 * @param opt1   First string argument
 * @param opt2   Second string argument.
 *
 * @return The compare result.  Returns 0, negative, or positive depending
 *         one the ordering compare result.
 */
int Utilities::strCaselessCompare(const char *op1, const char *op2)
{
    while (toLower(*op1) == toLower(*op2))
    {
        if (*op1 == 0)
        {
            return 0;
        }
        op1++;
        op2++;
    }

    return (toLower(*op1) - toLower(*op2));
}

/**
 * Portable implementation of a caseless memory compare.
 *
 * @param opt1   First memory location to compare.
 * @param opt2   Second memory location.
 * @param len    Length to compare.
 *
 * @return The compare result.  Returns 0, negative, or positive depending
 *         one the ordering compare result.
 */
int Utilities::memicmp(const void *mem1, const void *mem2, size_t len)
{
    const char *op1 = (const char *)mem1;
    const char *op2 = (const char *)mem2;
    while(len != 0)
    {
        if (toLower(*op1) != toLower(*op2))
        {
            return toLower(*op1) - toLower(*op2);

        }
        op1++;
        op2++;
        len--;
    }
    return 0;
}

/**
 * Portable implementation of an ascii-z string to uppercase (in place).
 *
 * @param str    String argument
 *
 * @return The address of the str unput argument.
 */
void Utilities::strupper(char *str)
{
    while (*str)
    {
        *str = toUpper(*str);
        str++;
    }

    return;
}


/**
 * Portable implementation of an ascii-z string to uppercase (in place).
 *
 * @param str    String argument
 *
 * @return The address of the str unput argument.
 */
void Utilities::strlower(char *str)
{
    while (*str)
    {
        *str = toLower(*str);
        str++;
    }

    return;
}


/**
 * Bounded strchr() function.
 *
 * @param data   The data pointer.
 * @param n      The maximum length to scan.
 * @param ch     The character of interest.
 *
 * @return The pointer to the located character, or NULL if it isn't found.
 */
const char *Utilities::strnchr(const char *data, size_t n, char ch)
{
    const char *endPtr = data + n;
    while (data < endPtr && *data != '\0')
    {
        if (*data == ch)
        {
            return data;
        }
        data++;
    }
    return NULL;
}


/**
 * A strncpy() implementation that will always null-terminate.
 *
 * @param dst    The destination pointer.
 * @param src    The source pointer.
 * @param len    The destination buffer length.
 *
 * @return false when no truncation has occured, true otherwise.
 */
bool Utilities::strncpy(char *dest, const char *src, size_t len)
{
    // ::strncpy() is dangerous as it doesn't NUL-terminate dest when truncating,
    // and inefficient as it always writes len bytes to dest, filling up with
    // NUL characters when not truncating.  Alternatives like strlcpy() in libbsd
    // or strncpy_s() aren't readily available, so we implement our own a safe
    // version here.
    char *end = (char *)memchr(src, '\0', len);
    if (end != NULL)
    {
        // we found a terminating NUL character
        memcpy(dest, src, end - src + 1);
        return false; // success
    }
    else
    {
        // no NUL char found
        memcpy(dest, src, len - 1);
        dest[len - 1] = '\0';
        return true; // truncated
    }
}
