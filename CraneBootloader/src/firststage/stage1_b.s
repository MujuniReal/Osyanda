.code16

.text
.org 0x0

.global _main

_main:
    jmp _start
    nop

#include <partble.h>

LogDrvNo: .byte 0x00

partion_one_segment = 0x0
partition_two_segment = 0x0
partition_three_segment = 0x0
partition_four_segment = 0x0

_start:
    cli
    movb %dl,LogDrvNo
    sti


    lea (welcomestr),%si
    call PrintIt

    

hang:
    jmp hang

#include <printer.h>

welcomestr: .asciz "\t\t\tCraneBootloader \r\n"