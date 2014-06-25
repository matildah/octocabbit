ENTRY(_vectors)
SECTIONS
{
    . = 0x0000;
    .vectors : { startup.o(.vectors) }
    . = 0x10000;
    .startup : { startup.o(.text) }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss COMMON) }
    . = ALIGN(8);
    . = . + 0x1000; /* 4kB of stack memory */
    stack_top = .;
}
