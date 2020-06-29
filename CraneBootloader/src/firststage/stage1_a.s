.code16

.text
.org 0x00
.global main

main:
    jmp start
    nop

LogDrvNo: .byte 0x00

stage1_segment = 0x0800

start:
    cli
    movb %dl,LogDrvNo
    xor %ax,%ax
    mov %ax,%ds
    mov %ax,%es
	mov %ax,%ss
  	mov $0x7c00,%ax
    mov %ax,%sp
	sti

/* since we now know that we have 1MB for our first stages,, hehhehehe owedde gwe */
/* 1 check for hard disk extended functions */
/* 2 Use them extended functions to read the other sectors with the first stages*/
/* 3 that is our official first stage bootloader then */
/* 4 now this bootloader will use ext algorithms thats if ext was installed on Operating systems inorder to load the second stage bootloader */
/* thats if an ext operating system has been selected */
/* otherwise for Oss like windows,, then chain loading will come in place no hustle */
/* our selection cursor code will be used here */
/* 5 according to the OS that will be selected,, different values of CHS will be got and disk will be read */
/* one strict check to make is whether the disk supports extended functions if so,, we use them or else we use old fashioned multireadsect */

/* initialize hardisk controller */

	xor %ax,%ax
	xor %dx,%dx
	movb LogDrvNo,%dl
	mov $0x9,%ah
	int $0x13

/* check whether extended functions work if not we use old read sector function */
/* enable extended functions */
	xor %ax,%ax
	xor %dx,%dx

	mov $0x41,%ah
	mov $0x55aa,%bx
	movb LogDrvNo,%dl
	int $0x13
	jc failed_to_read

	xor %ax,%ax
	mov $stage1_segment,%ax
	mov %ax,%es
	lea (diskpacket),%si
	xor %bx,%bx

	xor %ax,%ax
	xor %dx,%dx
	mov $0x42,%ah
	movb LogDrvNo,%dl
	int $0x13
/* set BIOS text mode */
	xor %ax,%ax
	xor %ah,%ah
	mov $0x07,%al
	int $0x10
	
	lea (loadstr),%si
	call PrintIt

	xor %ax,%ax
	mov $stage1_segment,%ax
	mov %ax,%es
	mov %ax,%ds

	ljmp $stage1_segment,$0x0000


finish:
	jmp finish

failed_to_read:
	lea (extddnot),%si
	call PrintIt


#include <printer.h>

diskpacket:
	.byte 0x10
	.byte 0x00
	.word 0x0008
	.int 0x08000000			 /* segment:offset -> 0x0050:0x0000 -> 0x00500000 */
	.int 0x01
	.int 0x00

extddnot: .asciz "The disk controller doesnt support HDD extended functions\r\n"
loadstr: .asciz "Loading...\r\n"

.fill 446-(.-main),1,0

#include <partble.h>

BootMagic: .word 0xaa55