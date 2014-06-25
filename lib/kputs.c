#include <uart.h>
void kputs(const char *s) {
    while (*s != 0) {
        *UART0 = *s;
        s++;
    }
}

