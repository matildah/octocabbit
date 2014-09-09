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

#ifndef _FRAME_H_
#define _FRAME_H_

#include <ktypes.h>

struct trapframe {
    register_t spsr;
    register_t sp;
    register_t lr;
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
    register_t pc;
};

void dumpregs(struct trapframe *foo);

#endif /* _FRAME_H_ */
