.section vectors
.global _vectors
_vectors:
    LDR pc, _reset
    LDR pc, _undef_inst
    LDR pc, _swi
    LDR pc, _abort_prefetch
    LDR pc, _abort_data
    B .                         /* padding */
    LDR pc, _irq
    LDR pc, _fiq

_reset: .word asm_entry
_undef_inst: .word undef_inst
_swi: .word swi
_abort_prefetch: .word abort_prefetch
_abort_data: .word abort_data
_irq: .word irq
_fiq: .word fiq






.section .text
.global asm_entry
asm_entry:
    LDR sp, =stack_top
    BL c_entry

undef_inst:
swi:
abort_prefetch:
abort_data:
irq:
fiq:
    B .



