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
    b stackshit
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
stackshit:
    ldr sp, =svc_stack
    bl c_entry
    msr CPSR_c, #0xd0
    ldr sp, =usr_stack
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
