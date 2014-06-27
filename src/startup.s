/*
 * this is the entry point
 *
 * asm_entry is loaded at 0x10000 and is the first bit of our code that gets
 * executed. We copy the exception vectors to the exception vector base 
 * location and set up stack pointers for all the modes we will use.
 * We then call the c entry point, c_entry.
 */

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

.section .text
.global asm_entry
asm_entry:
    /* copy the table of exception vectors to 0x0 because qemu is a bastard and
    refuses to load it for us */
    mov r0, #0x0
    ldr r1, =_vectors
    ldr r3, =_vectors_end
vector_copy_loop:
    ldr r2, [r1, #0x0]
    str r2, [r0, #0x0]
    add r0, r0, #0x4
    add r1, r1, #0x4
    cmp r1, r3
    bne vector_copy_loop    /* I'M RELOADING */

    /* set up supervisor mode stack and user mode stack */

    ldr sp, =svc_stack
    msr CPSR_c, #0xd0
    ldr sp, =usr_stack
    bl c_entry
    b .

_undef_inst:
    b .
_abort_prefetch:
    b .
_abort_data:
    b .
_irq:
    b .
_fiq:
    b .


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

    r0-r12 have no special meaning and we must preserve them

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

_vectors:
    ldr pc, _reset_
    ldr pc, _undef_inst_
    ldr pc, _swi_
    ldr pc, _abort_prefetch_
    ldr pc, _abort_data_
    B .                         /* padding */
    ldr pc, _irq_
    ldr pc, _fiq_

    _reset_: .word asm_entry
    _undef_inst_: .word _undef_inst
    _swi_: .word _swi
    _abort_prefetch_: .word _abort_prefetch
    _abort_data_: .word _abort_data
    _irq_: .word _irq
    _fiq_: .word _fiq

_vectors_end:
