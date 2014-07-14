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

#include <frame.h>
#include <uart.h>

void
dumpregs(struct trapframe *frame) {
    kprintf("BEGINNING OF REGISTER DUMP\n");
    kprintf("R0:  %p R1: %p R2:  %p R3:  %p\n", frame->r0, frame->r1, frame->r2, frame->r3);
    kprintf("R4:  %p R5: %p R6:  %p R7:  %p\n", frame->r4, frame->r5, frame->r6, frame->r7);
    kprintf("R8:  %p R9: %p R10: %p R11: %p\n", frame->r8, frame->r9, frame->r10, frame->r11);
    kprintf("R12: %p SP: %p LR:  %p PC:  %p\n", frame->r12, frame->sp, frame->lr, frame->pc);
    kprintf("SPSR: %p\n", frame->spsr);
    kprintf("END OF REGISTER DUMP\n");
}

