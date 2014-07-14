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
.global _swi
_swi:
    /* If this code (which is reachable from executing the swi/svc instructions
    or calling _swi) is never reached from supervisor mode code (note that
    _swi and everything it calls is itself supervisor mode code) we can:

    1. Assume 8-byte stack alignment upon entry to _swi (the EABI / AAPCS
    requires we must have 8-byte stack alignment when we call C/Rust code)

    2. Not have to worry about reentrancy in _swi. If we execute swi/svc in code
    that _swi runs, we would clobber LR_svc and SPSR_svc (which would prevent
    the original invocation of _swi from returning to the right place)

    while we can force the "only execute swi/svc or call _swi" from user mode
    constraint, we might as well make _swi reentrant (this involves forcing 8
    byte stack alignment before calling C/Rust code and pushing LR_svc and
    SPSR_svc onto the stack before doing anything which might execute swi/svc.

    registers:

    r0-r12 have no special meaning (well, they might contain the arguments
    to the syscall or the syscall number) and we must preserve them

    r13 is the stack pointer, is banked by mode, and gets set when we enter
        supervisor mode

    r14 is the link register, is banked by mode, and gets set each time we
        execute swi/svc

    r15 is the program counter

    SPSR_svc is the saved program status register, is banked by mode, and gets
        set each time we execute swi/svc

    CPSR is the current program status register

    references
    http://infocenter.arm.com/help/topic/com.arm.doc.dui0056d/Cegbbfgj.html
    http://infocenter.arm.com/help/topic/com.arm.doc.dui0471c/Bgbeacfi.html
    */

    stmfd sp!, {lr}         /* save lr (the pc of the interrupted code) */
    stmfd sp!, {r0-r12}     /* saves r0-r12 of interrupted code */
    stmfd sp!, {sp, lr}^    /* saves the sp and lr of interrupted code */

    mrs r0, SPSR            /* save SPSR into r0 */
    stmfd sp!, {r0}         /* and push it */

    mov r1, sp              /* the trap frame is done, so save a pointer to it */

    and r0, sp, #4          /* test stack alignment */
    sub sp, sp, r0          /* and adjust the stack to be 8 byte aligned */
    stmfd sp!, {r0, lr}     /* store alignment and lr (we store lr too just to
                               keep the stack aligned) */

    mov r0, r1              /* only argument to the C trap handler is a pointer
                               to the trap frame */
    bl swi                  /* call it */

    ldmfd sp!, {r0, lr}     /* pop stack alignment (and saved lr) */
    add sp, sp, r0          /* restore previous stack position */

    ldmfd sp!, {r0}         /* pop SPSR */
    msr SPSR, r0            /* shove it into SPSR */

    ldmfd sp!, {sp, lr}^    /* restore sp and lr of interrupted code */
    ldmfd sp!, {r0-r12}     /* restore r0-r12 of interrupted code */
    ldmfd sp!, {pc}^        /* return */
    _callable: .word 0xca11ab1e

