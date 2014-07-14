#include <stdint.h>
#include <uart.h>
void c_entry() 
{
    uint32_t forkres = 0xfeedface;
    kprintf("entered c_entry\n");
    asm volatile("svc 0x0\n\t mov %0, r0" : "=r" (forkres));
    if (forkres == 1) { /* parent */
        while (1) {
            asm volatile("svc 0x0");
            kprintf("PARENT!\n");
        }
    } else {
        while (1) {
            asm volatile("svc 0x0");
            kprintf("CHILD!\n");
        }
    }



}


