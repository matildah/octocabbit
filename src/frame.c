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
dumpregs(struct trapframe *foo) {
    kprintf("BEGINNING OF REGISTER DUMP\n");
    kprintf("SPSR: %p\n", foo->spsr);
    kprintf("SP: %p\n", foo->sp);
    kprintf("LR: %p\n", foo->lr);
    kprintf("R0: %p\n", foo->r0);
    kprintf("R1: %p\n", foo->r1);
    kprintf("R2: %p\n", foo->r2);
    kprintf("R3: %p\n", foo->r3);
    kprintf("R4: %p\n", foo->r4);
    kprintf("R5: %p\n", foo->r5);
    kprintf("R6: %p\n", foo->r6);
    kprintf("R7: %p\n", foo->r7);
    kprintf("R8: %p\n", foo->r8);
    kprintf("R9: %p\n", foo->r9);
    kprintf("R10: %p\n", foo->r10);
    kprintf("R11: %p\n", foo->r11);
    kprintf("R12: %p\n", foo->r12);
    kprintf("PC: %p\n", foo->pc);
    kprintf("END OF REGISTER DUMP\n");
}

