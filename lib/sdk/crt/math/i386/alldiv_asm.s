/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           Odyssey kernel
 * PURPOSE:           Run-Time Library
 * FILE:              lib/rtl/i386/alldiv_asm.S
 * PROGRAMER:         Alex Ionescu (alex@relsoft.net)
 *
 * Copyright (C) 2002 Michael Ringgaard.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.  
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.  
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission. 

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES// LOSS OF USE, DATA, OR PROFITS// OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 */

#include <asm.inc>

PUBLIC __alldiv
PUBLIC __fltused

 /* DATA ********************************************************************/
.data
ASSUME CS:NOTHING, DS:NOTHING, ES:NOTHING, FS:NOTHING, GS:NOTHING

__fltused:
        .long HEX(9875)


/* FUNCTIONS ***************************************************************/
.code

//
// lldiv - signed long divide
//
// Purpose:
//       Does a signed long divide of the arguments.  Arguments are
//       not changed.
//
// Entry:
//       Arguments are passed on the stack:
//               1st pushed: divisor (QWORD)
//               2nd pushed: dividend (QWORD)
//
// Exit:
//       EDX:EAX contains the quotient (dividend/divisor)
//       NOTE: this routine removes the parameters from the stack.
//
// Uses:
//       ECX
//

__alldiv:

        push    edi
        push    esi
        push    ebx

// Set up the local stack and save the index registers.  When this is done
// the stack frame will look as follows (assuming that the expression a/b will
// generate a call to lldiv(a, b)):
//
//               -----------------
//               |               |
//               |---------------|
//               |               |
//               |--divisor (b)--|
//               |               |
//               |---------------|
//               |               |
//               |--dividend (a)-|
//               |               |
//               |---------------|
//               | return addr** |
//               |---------------|
//               |      EDI      |
//               |---------------|
//               |      ESI      |
//               |---------------|
//       ESP---->|      EBX      |
//               -----------------
//

#define DVNDLO  [esp + 16]       // stack address of dividend (a)
#define DVNDHI  [esp + 20]       // stack address of dividend (a)
#define DVSRLO  [esp + 24]      // stack address of divisor (b)
#define DVSRHI  [esp + 28]      // stack address of divisor (b)

// Determine sign of the result (edi = 0 if result is positive, non-zero
// otherwise) and make operands positive.

        xor     edi,edi         // result sign assumed positive

        mov     eax,DVNDHI // hi word of a
        or      eax,eax         // test to see if signed
        jge     short L1        // skip rest if a is already positive
        inc     edi             // complement result sign flag
        mov     edx,DVNDLO // lo word of a
        neg     eax             // make a positive
        neg     edx
        sbb     eax,0
        mov     DVNDHI,eax // save positive value
        mov     DVNDLO,edx
L1:
        mov     eax,DVSRHI // hi word of b
        or      eax,eax         // test to see if signed
        jge     short L2        // skip rest if b is already positive
        inc     edi             // complement the result sign flag
        mov     edx,DVSRLO // lo word of a
        neg     eax             // make b positive
        neg     edx
        sbb     eax,0
        mov     DVSRHI,eax // save positive value
        mov     DVSRLO,edx
L2:

//
// Now do the divide.  First look to see if the divisor is less than 4194304K.
// If so, then we can use a simple algorithm with word divides, otherwise
// things get a little more complex.
//
// NOTE - eax currently contains the high order word of DVSR
//

        or      eax,eax         // check to see if divisor < 4194304K
        jnz     short L3        // nope, gotta do this the hard way
        mov     ecx,DVSRLO // load divisor
        mov     eax,DVNDHI // load high word of dividend
        xor     edx,edx
        div     ecx             // eax <- high order bits of quotient
        mov     ebx,eax         // save high bits of quotient
        mov     eax,DVNDLO // edx:eax <- remainder:lo word of dividend
        div     ecx             // eax <- low order bits of quotient
        mov     edx,ebx         // edx:eax <- quotient
        jmp     short L4        // set sign, restore stack and return

//
// Here we do it the hard way.  Remember, eax contains the high word of DVSR
//

L3:
        mov     ebx,eax         // ebx:ecx <- divisor
        mov     ecx,DVSRLO
        mov     edx,DVNDHI // edx:eax <- dividend
        mov     eax,DVNDLO
L5:
        shr     ebx,1           // shift divisor right one bit
        rcr     ecx,1
        shr     edx,1           // shift dividend right one bit
        rcr     eax,1
        or      ebx,ebx
        jnz     short L5        // loop until divisor < 4194304K
        div     ecx             // now divide, ignore remainder
        mov     esi,eax         // save quotient

//
// We may be off by one, so to check, we will multiply the quotient
// by the divisor and check the result against the orignal dividend
// Note that we must also check for overflow, which can occur if the
// dividend is close to 2**64 and the quotient is off by 1.
//

        mul     dword ptr DVSRHI // QUOT * DVSRHI
        mov     ecx,eax
        mov     eax,DVSRLO
        mul     esi             // QUOT * DVSRLO
        add     edx,ecx         // EDX:EAX = QUOT * DVSR
        jc      short L6        // carry means Quotient is off by 1

//
// do long compare here between original dividend and the result of the
// multiply in edx:eax.  If original is larger or equal, we are ok, otherwise
// subtract one (1) from the quotient.
//

        cmp     edx,DVNDHI // compare hi words of result and original
        ja      short L6        // if result > original, do subtract
        jb      short L7        // if result < original, we are ok
        cmp     eax,DVNDLO // hi words are equal, compare lo words
        jbe     short L7        // if less or equal we are ok, else subtract
L6:
        dec     esi             // subtract 1 from quotient
L7:
        xor     edx,edx         // edx:eax <- quotient
        mov     eax,esi

//
// Just the cleanup left to do.  edx:eax contains the quotient.  Set the sign
// according to the save value, cleanup the stack, and return.
//

L4:
        dec     edi             // check to see if result is negative
        jnz     short L8        // if EDI == 0, result should be negative
        neg     edx             // otherwise, negate the result
        neg     eax
        sbb     edx,0

//
// Restore the saved registers and return.
//

L8:
        pop     ebx
        pop     esi
        pop     edi

        ret     16

END
