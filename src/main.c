#include <stdint.h>
#include <uart.h>
void c_entry() 
{
    uint32_t foo;
    foo = 0xb100d1ed;
    asm("mov r5, r3");
    asm("mov r6, r3");
    asm("mov r7, r3");
    asm("svc 0x0");
    kprintf("foo %p bar\n", foo);
}


