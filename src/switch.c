/*
 * Copyright (c) 2014 Kia <>
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

static int forked = 0;
static int curtask;

struct trapframe pcb[2];


void
forkswtch(struct trapframe *tf) { /* first time this is called, this acts like fork
                                     and the following time, it just switches */
    if (forked == 0) {
        forked = 1;
        /* parent */
        pcb[0] = *tf;
        pcb[0].r0 = 1;
        *tf = pcb[0];
        /* child */
        pcb[1] = *tf;
        pcb[1].r0 = 0;
        curtask = 0;
        return;
    }

    pcb[curtask] = *tf;

    if (curtask == 0) {
        curtask = 1;
    } else {
        curtask = 0;
    }

    *tf = pcb[curtask];
    return;
}

