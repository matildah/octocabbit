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

#include <stdarg.h>
#include <stdint.h>
#include <uart.h>

void
khexdump(uint8_t *buf, size_t len) {
    size_t i;
    char obuf[3];

    for (i = 0; i < len; i++) {
        itoa8(buf[i], obuf);
        kputs(obuf);
        kputs("\n");
    }
}


void
itoa8(uint8_t num, char *output) {
    int digit;

    digit = (num & 0xF0) >> 4;
    if (digit < 0xA) {
        output[0] = '0' + digit;
    } else {
        output[0] = 'a' + digit - 0xA;
    }
    digit = num & 0x0F;
    if (digit < 0xA) {
        output[1] = '0' + digit;
    } else {
        output[1] = 'a' + digit - 0xA;
    }
    output[2] = '\0';
}

