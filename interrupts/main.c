#include <stdint.h>
#include <uart.h>
void c_entry() 
{
    asm("svc 0x0");
    char *foo = "hello world!\n";
    asm("svc 0x0");
    kputs(foo);

}


