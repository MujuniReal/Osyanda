.code16

.text
.org 0x00

main:	jmp start
	nop

//this header file below here is for a 1.4MB floppy disk formatted with FAT
//Fat formated with MBR not GPT

#include "fatstruct.h"

start:
	//mov the drive number in %dl to thedefined variable reposible to hold it
	cli
	xor %ax,%ax
	mov %ax,%ss
	mov %ax,%es
	mov %ax,%ds
	mov $0x7c00,%sp
	sti

	
	
