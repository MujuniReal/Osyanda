.code16
.text
.org 0x0

.global main

main:
	jmp start

/* The following is a structure of filesystem type FAT16 thats required for any FAT16 boot Sector (MBR) Called the boot parameter block BPB
It spans starting from the the fourth byte of the boot sector to the 47th byte,, it weighs 43bytes in size
*/

#include "fatstruct.h"

.func PrintIt
PrintIt:
	lodsb
	mov $0xe,%ah
	int $0x10
	or %al,%al
	jz EndPrint
	jmp PrintIt


EndPrint:
	retw

.endfunc

.func FailedReset
FailedReset:
	lea (Freset),%si
	call PrintIt
	lea (Areboot),%si
	call PrintIt
	xor %ah,%ah
	int $0x16

Reseter:
	lea (SReset),%si
	call PrintIt
	.byte 0xea
	.word 0x0000
	.word 0xffff
.endfunc


start:
	cli
	mov %dl,LogDrvNo
	xor %ax,%ax
	//mov %ax,%cs
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%ss
	mov $0x7c00,%esp
	sti

	lea (Welcomee),%si
	call PrintIt
	lea (StatRes),%si	
	call PrintIt

DiskReset:
	xor %ah,%ah
	mov LogDrvNo,%dl
	int $0x13
	jc FailedReset
	lea (Sreset),%si
	call PrintIt
	hlt
	
	

Welcomee: .asciz "Crane Bootloader\r\n"
StatRes: .asciz "Attempting to reset disk\r\n"
Freset: .asciz "Failed to reset disk\r\n"
Sreset: .asciz "Disk Reset Sucessful....\r\n"
Areboot: .asciz "Press Any Key to reboot.....\r\n"
SReset: .asciz "Rebooting....\r\n"

.fill 510-(.-main),1,0
BootMagic: .word 0xaa55
