/*
 * Copyright (c) 2014 Matilda <sadieperkins@riseup.net>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any 
 * purpose with or without fee is hereby granted, provided that the above 
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES 
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY 
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER 
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, 
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE 
 * USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * i have taken taken things from OpenBSD's sys/arch/arm/include/frame.h:
 * PUSHFRAME and PULLFRAME
 * struct trapframe
 * The copyright notice and license for that file is below.
 */

/*
 * Copyright (c) 1994-1997 Mark Brinicombe.
 * Copyright (c) 1994 Brini.
 * All rights reserved.
 *
 * This code is derived from software written for Brini by Mark Brinicombe
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 * This product includes software developed by Brini.
 * 4. The name of the company nor the name of the author may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BRINI ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL BRINI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * RiscBSD kernel project
 *
 * frame.h
 *
 * Stack frames structures
 *
 * Created      : 30/09/94
 */

#ifndef _FRAME_H_
#define _FRAME_H_

#include <ktypes.h>

struct trapframe {
    register_t spsr;
    register_t r0;
    register_t r1;
    register_t r2;
    register_t r3;
    register_t r4;
    register_t r5;
    register_t r6;
    register_t r7;
    register_t r8;
    register_t r9;
    register_t r10;
    register_t r11;
    register_t r12;
    register_t cur_sp; /* r13 from where we were interrupted */
    register_t cur_lr; /* r14 from where we were interrupted */ 
    register_t svc_sp; /* r13 from supervisor mode */
    register_t svc_lr; /* r14 from supervisor mode */
    register_t pc;
};


/* the following macros DO NOT involve any mode changes */

/*
 * PUSHFRAME - macro to push a trap frame on the stack in the current mode
 * Since the current mode is used, the SVC lr field is not defined.
 */

#define PUSHFRAME                                                            \
    str    lr, [sp, #-4]!;    /* Push the return address */                  \
    sub    sp, sp, #(4*17);   /* Adjust the stack pointer */                 \
    stmia  sp, {r0-r14}^;     /* Push the user mode registers */             \
    mov    r0, r0;            /* NOP for previous instruction */             \
    mrs    r0, spsr_all;      /* Put the SPSR on the stack */                \
    str    r0, [sp, #-4]!

/*
 * PULLFRAME - macro to pull a trap frame from the stack in the current mode
 * Since the current mode is used, the SVC lr field is ignored.
 */

#define PULLFRAME                                                            \
    ldr    r0, [sp], #0x0004;   /* Get the SPSR from stack */                \
    msr    spsr_all, r0;                                                     \
    ldmia  sp, {r0-r14}^;       /* Restore registers (usr mode) */           \
    mov    r0, r0;              /* NOP for previous instruction */           \
    add    sp, sp, #(4*17);     /* Adjust the stack pointer */               \
    ldr    lr, [sp], #0x0004    /* Pull the return address */



#endif /* _FRAME_H_ */
