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

#include <stdarg.h>
#include <stdint.h>
#include <uart.h>

int
kprintf(const char *fmt, ...) {
    va_list argl;
    char buf[256];
    const char *p, *s;
    int numwritten = 0;
    uint32_t i;
    va_start(argl, fmt);

    for (p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            kputc(*p);
            numwritten++;
            continue;
        }

        switch (*++p) {
            case '\0':
                return numwritten;
            case '%':
                kputc('%');
                numwritten++;
                break;
            case 's':
                s = va_arg(argl, char *);
                numwritten += kputs(s);
                break;
            case 'p':
                i = va_arg(argl, uint32_t);
                itoa32(i, buf);
                numwritten += kputs("0x");
                numwritten += kputs(buf);
                break;
        }
    }
    va_end(argl);
    return numwritten;
}


void
itoa32(uint32_t num, char *output) {
    int digit, i;

    for (i = 0; i < 8; i++) {
        digit = num & 0xF;
        if (digit < 0xA) {
            output[7 - i] = '0' + digit;
        } else {
            output[7 - i] = 'a' + digit - 0xA;
        }

        num = num >> 4;
    }
    output[8] = '\0';
}

