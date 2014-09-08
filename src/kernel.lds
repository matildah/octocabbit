KERNEL_BASE   = 0xf0000000; /* virtual address */
PHYS_BASE     = 0x80000000; /* physical address */
KERNEL_OFFSET = KERNEL_BASE - PHYS_BASE;

ENTRY(asm_entry)
SECTIONS
{
    . = PHYS_BASE;

    .boot . :
    {
        *(.boot.text)
        *(.boot.rodata)
        *(.boot.data)
        . = ALIGN(64K);
    }

    . = . + KERNEL_OFFSET;

    .text . : AT(ADDR(.text) - KERNEL_OFFSET)
    {
        . = ALIGN(64K);
        *(.vectors)
        *(.vectors.text)
        *(.text)
    }
    .rodata . : AT(ADDR(.rodata) - KERNEL_OFFSET)
    {
        *(.rodata)
        *(.rodata.*)
    }

    .data . : AT(ADDR(.data) - KERNEL_OFFSET)
    {
        *(.data)
        . = ALIGN(8);
        . = . + 0x1000;
        svc_stack = .;
        . = . + 0x1000;
        usr_stack = .;
    }

    .bss . : AT(ADDR(.bss) - KERNEL_OFFSET)
    {
        *(.bss)
        *(COMMON)
    }

    /DISCARD/ :
    {
        *(.note.gnu.build-id)
        *(.comment)
        *(.ARM.attributes)
    }

}
