#!@OOREXX_SHEBANG_PROGRAM@
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Copyright (c) 1995, 2004 IBM Corporation. All rights reserved.             */
/* Copyright (c) 2005, 2006 Rexx Language Association. All rights reserved.   */
/* Copyright (c) 1981, 2025 Mike Cowlishaw. All rights reserved.              */
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
/* This measure of Rexx execution speed is based on an analysis of            */
/* the dynamic mix of clauses found in a (subjectively chosen)                */
/* collection of Rexx programs (including commands, macros, and               */
/* personal programs).  Approximately 2,500,000 lines of trace                */
/* output were analysed, and the program below recreates the                  */
/* dynamic mix of constructs found in that analysis.                          */
/* In view of the dramatic differences between systems in their               */
/* efficiency of issuing commands, the timed loop does not issue              */
/* commands (an 'RC=expression; PARSE' sequence is used instead).             */
/* This program therefore measures the performance of a Rexx                  */
/* implementation, exclusive of command execution overhead.                   */
/* Elapsed (user-perceived) time is used, rather than any form of             */
/* virtual time, with an adjustment for the inner loop overhead.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 1.0 17 Jan 1981 Original version (Mike Cowlishaw)                          */
/* 2.0  3 Jun 1989 Remove attempt to simulate commands                        */
/* 2.1  7 Oct 1989 Remove use of not symbols, and correct commentary          */
/*     12 Aug 2011 Restore lost comments + minor cleanups                     */
/* 2.2 15 Mar 2025 Merged in changes by Rick McGuire which adjusts for modern */
/*                 CPU speeds.  On Windows platforms in particular, the       */
/*                 granularity of the clock makes it difficult to get         */
/*                 accurate cps data with short runs (such as the default     */
/*                 values.  In general, a run requires at least one second    */
/*                 of 'wall clock' time to give a good result.  This version  */
/*                 of RexxCPS will run with the original averaging and count  */
/*                 values, and if the resulting total time is less than       */
/*                 one second, the count is adjusted so that a one-second     */
/*                 total time should be be achieved, and the run is repeated  */
/*                 with the new values.                                       */
/*----------------------------------------------------------------------------*/

rexxcps=2.2    /* REXXCPS version; quotable only if code unchanged */

/* Loop counts; these are auto-adjusted so total run time is over one second */
count=100      /* Repetition count */
averaging=100  /* Averaging-over count */

tracevar='Off' /* Trace setting (for development use) */

signal on novalue
parse source  source 1 system .
parse version version

say '----- REXXCPS' rexxcps '-- Measuring REXX clauses/second -----'
say ' REXX version is:' version
say '       System is:' system

/* Calibrate for the empty do-loop */
empty=0
do i=1 to averaging
  call time 'R'
  do count; end
  empty=time('R')+empty
  end
empty=empty/averaging

/* measure twice; the first trial (with small counts) is timed and the        */
/* counts are then adjusted, if necessary, to bring the total time to one     */
/* second or more                                                             */
do trial=1 to 2

  /* Now the true timer loop .. average timing again */
  full=0
  do i=1 to averaging
    trace value tracevar
    call time 'R'
    do count;
      /* -----  This is first of the 1000 clauses ----- */
      flag=0; p0='b'
      do loop=1 to 14
        /* This is the "block" comment in loop */
        key1='Key Bee'
        acompound.key1.loop=substr(1234"5678",6,2)
        if flag=acompound.key1.loop then say 'Failed1'
        do j=1.1 to 2.2 by 1.1   /* executed 28 times */
          if j>acompound.key1.loop then say 'Failed2'
          if 17<length(j)-1        then say 'Failed3'
          if j='foobar'            then say 'Failed4'
          if substr(1234,1,1)=9    then say 'Failed5'
          if word(key1,1)='?'      then say 'Failed6'
          if j<5 then do   /* This path taken */
            acompound.key1.loop=acompound.key1.loop+1
            if j=2 then leave
            end
          iterate
          end /* j */
        avar.=1.0''loop
        select
          when flag='string' then say 'FailedS1'
          when avar.flag.2=0 then say 'FailedS2'
          when flag=5+99.7   then say 'FailedS3'
          when flag          then avar.1.2=avar.1.2*1.1
          when flag==0       then flag=0
          end
        if 1 then flag=1
        select
          when flag=='ring'  then say 'FailedT1'
          when avar.flag.3=0 then say 'FailedT2'
          when flag          then avar.1.2=avar.1.2*1.1
          when flag==0       then flag=1
          end
        parse value 'Foo Bar' with v1 +5 v2 .
        trace value trace(); address value address()
        call subroutine 'with' 2 'args', '(This is the second)'1''1
        rc='This is an awfully boring program'; parse var rc p1 (p0) p5
        rc='is an awfully boring program This'; parse var rc p2 (p0) p6
        rc='an awfully boring program This is'; parse var rc p3 (p0) p7
        rc='awfully boring program This is an'; parse var rc p4 (p0) p8
        end loop
      /* -----  This is last of the 1000 clauses ----- */
      end
    full=time('R')+full
    trace off
    end
  total=full /* total time */
  /* say 'total='total */

  /* if total is over one second then it's usable (this should usually */
  /* be the case when trial=2)                                         */
  if total>1 | trial=2 then leave

  /* bump the count so the second run should take about one second */
  count=(1%total + 1) * count
  end trial

/* show the counts */
say '        Averaged:' count 'x' averaging 'iterations',
    'of 1000 clauses (over' format(total,,1)'s)'

/* Now display the statistics */
innertime=total/averaging-empty
thousand=innertime/count
/* Developer's statistics: */
if left(tracevar,1)='O' then nop
 else do
  say
  say 'Total (full DOs):' total 'secs (average of' averaging ,
    'measures of' count 'iterations)'
  say 'Time for one iteration (1000 clauses) was:' thousand 'seconds'
  end

/* And finally, the Result... */
say
say'     Performance:' format(1000/thousand,,0) 'REXX clauses per second'
say

exit


/* Target routine for the timed CALL - called 14 times */
subroutine:
  parse upper arg a1 a2 a3 ., a4
  parse var a3 b1 b2 b3 .
  do 1; rc=a1 a2 a3; parse var rc c1 c2 c3; end
  return

novalue:
  say 'NoValue raised'
