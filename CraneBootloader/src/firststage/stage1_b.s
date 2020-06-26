.code16

.text
.org 0x0

.global _main

_main:
    jmp _start
    nop

LogDrvNo: .byte 0x00

_start:
    cli
    mov %cs,%ax
    movb %dl,LogDrvNo
