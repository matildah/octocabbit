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

#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>
size_t kputs(const char *s);
void kputc(char s);
int kprintf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void itoa32(uint32_t num, char *output);
void khexdump(uint8_t *buf, size_t len);
void itoa8(uint8_t num, char *output);

/* http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0224i/Bbabegge.html */
#define UART0       ((volatile uint32_t*)0x44E09000)
/* http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/I18381.html */
#define UARTFR        0x06 /* 0x18 bytes */
#define UARTIMSC      0x0E /* 0x38 bytes */
#define UARTICR       0x11 /* 0x44 bytes */
#define UARTFR_RXFE   0x10
#define UARTFR_TXFF   0x20
#define UARTIMSC_RXIM 0x10
#define UARTIMSC_TXIM 0x20
#define UARTICR_RXIC  0x10
#define UARTICR_TXIC  0x20


#endif /* _UART_H_ */
