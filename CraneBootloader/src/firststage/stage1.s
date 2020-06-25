.code16

.text
.org 0x00
.global main

main:
    jmp start
    nop

LogDrvNo: .byte 0x00

stage1_segment = 0x50

start:
    mov %dl,LogDrvNo
    xor %ax,%ax
    mov %ax,%ds
    mov %ax,%ss
    mov %ax,%es
/*    mov $0x7c00,%ax   we may ignore to setup the stack as per now
    mov %ax,%sp     */

/* since we now know that we have 1MB for our first stages,, hehhehehe owedde gwe */
/* 1 check for hard disk extended functions */
/* 2 Use them extended functions to read the other sectors with the first stages*/
/* 3 that is our official first stage bootloader then */
/* 4 now this bootloader will use ext algorithms thats if ext was installed on Operating systems inorder to load the second stage bootloader */
/* thats if an ext operating system has been selected */
/* otherwise for Oss like windows,, then chain loading will come in place no hustle */
/* our selection cursor code will be used here */
/* 5 according to the OS that will be selected,, different values of CHS will be got and disk will be read */


.fill 446-(.-main),1,0

#include <partble.h>

BootMagic: .word 0xaa55