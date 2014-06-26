#include <stdint.h>

volatile uint32_t * my_uart = 0x101f1000 ;
void c_entry() 
{
    char *foo = "hello world!\n";
    while (*foo != 0) {
        *my_uart = *foo;
        foo++;
    }

}
