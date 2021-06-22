.code32
.text
.org 0x0
.global _idt_funcs
.global _idtp;


_idt_funcs:
    nop

.data
_idtp: .byte 0,0,0,0,0,0