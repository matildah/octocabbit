#include <stdint.h>
#include <uart.h>
void c_entry() 
{
    char *foo = "hello world!\n";
    kputs(foo);

}


