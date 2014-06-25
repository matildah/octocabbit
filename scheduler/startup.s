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
    /*
    mov r0, #0x0
    ldr r1, =_vectors
    ldr r3, =_vectors_end
keep_honking:
    ldr r2, [r1, #0x0]
    str r2, [r0, #0x0]
    add r0, r0, #0x4
    add r1, r1, #0x4
    cmp r1, r3
    bne keep_honking    /* I'M RELOADING */

    ldr sp, =stack_top
    bl c_entry

undef_inst:
swi:
abort_prefetch:
abort_data:
irq:
fiq:
    b .



_vectors:
    ldr pc, _reset
    ldr pc, _undef_inst
    ldr pc, _swi
    ldr pc, _abort_prefetch
    ldr pc, _abort_data
    B .                         /* padding */
    ldr pc, _irq
    ldr pc, _fiq

_reset: .word asm_entry
_undef_inst: .word undef_inst
_swi: .word swi
_abort_prefetch: .word abort_prefetch
_abort_data: .word abort_data
_irq: .word irq
_fiq: .word fiq

_vectors_end:
