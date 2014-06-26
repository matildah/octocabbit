#include <stdint.h>
#include <uart.h>
void c_entry() 
{
    asm("svc 0x0");
    char *foo = "hello world!\n";
    kputs(foo);

}


