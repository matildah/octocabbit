ENTRY(asm_entry)
SECTIONS
{
    . = 0x80300000;
    .startup : { obj/startup.o(.text) }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss COMMON) }
    . = ALIGN(8);
    . = . + 0x1000; /* 4 kB for supervisor stack */
    svc_stack = .;
    . = . + 0x1000; /* 4 kB for user stack */
    usr_stack = .;
}
