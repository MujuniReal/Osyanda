	.code16
	.global _start
	.text
	.org 0x00
	CRANE_OFFSET = 0x8000

_start:
	jmp main
	nop

fatbpb:	
	//To cater for FAT filesystems
	.include "fatbpb.s"

main:

	cli
	mov %cs,%ax
	mov %ax,%ss
	mov %ax,%es
	mov %ax,%ds
	mov $0x7c00,%ax
	mov %ax,%sp
	sti

//READ BOOTLOADER SECTORS
//ACTIVATE A20
//SET GDT
//SET CONTROL REGISTERS
//SET SEGMENT REGISTERS
//JUMP

readCraneSectors:
	//C - 0
    //H - 0
    //S - 2

	//ch - 0
    //cl - 2
    //dh - 0
	push %es
    movw $0x2,%cx
    xor %dh,%dh
	xor %bx,%bx
	movw $CRANE_OFFSET,%ax
	mov %ax,%es
	//%dl is set to drive No
	mov $0x0201,%ax
	int $0x13
	nop
	pop %es
	//Plan
	//REad the configuration from the Next Sector
	//with that config, locate the bootloader

activate_a20:
    movw $0x2401,%ax
    int $0x15
	cli
	// mov 0x92,%dl
	// inb %dl,%al
    // or $0x2,%al
    // out %al,%dl
loadGDT:
	lgdt GDT_PTR

setCTRLREGS:
	xor %eax,%eax
	mov %cr0,%eax
	or $0x1,%eax
	mov %eax,%cr0
	jmp setSEGREGS

GDT:

	.word 0x0
	.word 0x0
	.byte 0x0
	.byte 0x0
	.byte 0x0
	.byte 0x0

csSelector:
	.word 0x0
	.word 0x0
	.byte 0x0
	.byte 0x9a
	.byte 0xc8
	.byte 0x0

dataSelector:
	.word 0x0
	.word 0x0
	.byte 0x0
	.byte 0x92
	.byte 0xc8
	.byte 0x0

GDT_PTR:
	.word 23
	.int GDT


setSEGREGS:
	xor %ax,%ax
	mov $0x10,%ax
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%fs
	mov %ax,%gs
	mov %ax,%ss
	mov $0x2ffff,%esp
	mov %esp,%ebp
	jmp clearPrefetch

	nop
	nop
	nop
clearPrefetch:

protected_mode_jump:
	.byte 0x66
	.byte 0xea
	.int 0x80000
	.word 0x0008


	.fill 446-(.-_start),1,0
	
partitionTable:
	.include "ptable.s"

	.fill 64-(.-partitionTable),1,0
	
BootMagic: .word 0xaa55
