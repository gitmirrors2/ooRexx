/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Copyright (c) 1995, 2004 IBM Corporation. All rights reserved.             */
/* Copyright (c) 2005-2014 Rexx Language Association. All rights reserved.    */
/*                                                                            */
/* This program and the accompanying materials are made available under       */
/* the terms of the Common Public License v1.0 which accompanies this         */
/* distribution. A copy is also available at the following address:           */
/* http://www.oorexx.org/license.html                                         */
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
/******************************************************************************/
/* REXX Kernel                                           SupplierClass.hpp    */
/*                                                                            */
/* Primitive Supplier Class Definition                                        */
/*                                                                            */
/******************************************************************************/
#ifndef Included_SupplierClass
#define Included_SupplierClass

class SupplierClass : public RexxObject
{
 public:
           void *operator new(size_t);
    inline void *operator new(size_t size, void *objectPtr) { return objectPtr; };
    inline void  operator delete(void *, void *) {;}
    inline void  operator delete(void *) {;}

    inline SupplierClass(RESTORETYPE restoreType) { ; };
    SupplierClass(ArrayClass  *, ArrayClass  *);
    SupplierClass();


    virtual void live(size_t);
    virtual void liveGeneral(MarkReason reason);
    virtual void flatten(RexxEnvelope *);

    bool         isAvailable()
    RexxInteger *available();
    RexxObject  *next();
    RexxObject  *value();
    RexxObject  *index();
    RexxObject  *initRexx(ArrayClass *values, ArrayClass *indexes);
    RexxObject  *newRexx(RexxObject **, size_t);
    ArrayClass   *indexes() {return indexes; }
    ArrayClass   *values() {return values; }
    void         append(ArrayClass *, ArrayClass *);
    void         append(RexxSuppler *);

    static void createInstance();
    static RexxClass *classInstance;

 protected:

    ArrayClass  *values;                 // array of values
    ArrayClass  *indexes;                // array of indexes
    size_t position;                    // current array position
};

inline SupplierClass *new_supplier(ArrayClass *values, ArrayClass *indexes) { return new SupplierClass(values, indexes); }

#endif
