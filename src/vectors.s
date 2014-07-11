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

    stmfd sp!, {lr}
    stmfd sp!, {r0-r12}
    and r1, sp, #4
    sub sp, sp, r1
    ldr r0, _callable
    ldr r1, _callable
    ldr r2, _callable
    ldr r3, _callable
    ldr r4, _callable
    ldr r5, _callable
    ldr r6, _callable
    ldr r7, _callable
    ldr r8, _callable
    ldr r9, _callable
    ldr r10, _callable
    ldr r11, _callable
    ldr r12, _callable
    ldr r14, _callable
    ldmfd sp!, {r0-r12}
    ldmfd sp!, {pc}^
    _callable: .word 0xca11ab1e

