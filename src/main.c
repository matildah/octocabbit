#include <stdint.h>
#include <uart.h>
void c_entry() 
{
    kprintf("Hello, world!\n");
    return;
    uint32_t forkres = 0xfeedface;
    kprintf("entered c_entry\n");
    asm volatile("svc 0x0\n\t mov %0, r0" : "=r" (forkres)); /* this acts like fork */
    if (forkres == 1) { /* parent */
        while (1) {
            asm volatile("svc 0x0"); /* but further calls just yield control to the other thread */
            kprintf("PARENT!\n");
        }
    } else {
        while (1) {
            asm volatile("svc 0x0");
            kprintf("CHILD!\n");
        }
    }



}


