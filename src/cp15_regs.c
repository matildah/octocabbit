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

#include <stdint.h>

void
dump_cp15_regs(void)
{
    uint32_t vbar, sctlr, pfr1, scr, ttbcr;
    __asm__ __volatile__("mrc p15, 0, %0, c12, c0, 0\n" : "=r" (vbar) : : );
    __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0\n" : "=r" (sctlr) : : );
    __asm__ __volatile__("mrc p15, 0, %0, c0, c1, 1\n" : "=r" (pfr1) : : );
    __asm__ __volatile__("mrc p15, 0, %0, c2, c0, 2\n" : "=r" (ttbcr) : : );
/*     __asm__ __volatile__("MRC p15, 0, %0, c1, c1, 0\n" : "=r" (scr) : : ); */
    kprintf("ttbcr is %p, gg\n", ttbcr);
}

