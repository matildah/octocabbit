KERNEL_BASE   = 0xf0000000; /* virtual address */
PHYS_BASE     = 0x80000000; /* physical address */
KERNEL_OFFSET = KERNEL_BASE - PHYS_BASE;

ENTRY(asm_entry)
SECTIONS
{
    . = KERNEL_BASE;

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
