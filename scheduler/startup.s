.section text
.global _asm_entry
_asm_entry:
    LDR sp, =stack_top
    BL c_entry
    B .
