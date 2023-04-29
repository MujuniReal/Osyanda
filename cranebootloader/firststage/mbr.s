	.code16
	.global _start
	.text
	.org 0x00
	New_MBR_Segment = 0x100000
    GDT_OFFSET = 0x800

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

//ACTIVATE A20
//SET GDT
//SET CONTROL REG
//JUMP
activate_a20:
    movw $0x2401,%ax
    int $0x15

setupGDT:
    push %es
    mov $GDT_OFFSET,%ax
    mov %ax,%es
    
    //First GDT Entry
    xor %ax,%ax
    mov %ax,%di
    movw $0x4,%cx
    rep stosw

    //Second GDT Entry, Code
    movw $0x0000,%es:(%di)
	movw $0x0000,%es:0x2(%di)
	movb $0x00,%es:0x4(%di)
	movb $0x9a,%es:0x5(%di)
	movb $0xc8,%es:0x6(%di)
	movb $0x00,%es:0x7(%di)

    add $0x8,%di
	//The Third GDT Entry, Data

	movw $0x0000,%es:(%di)
	movw $0x0000,%es:0x2(%di)
	movb $0x00,%es:0x4(%di)
	movb $0x92,%es:0x5(%di)
	movb $0xc8,%es:0x6(%di)
	movb $0x00,%es:0x7(%di)
	nop

    pop %es

	xor %eax,%eax
	mov %cr0,%eax
	or $0x1,%eax
	mov %eax,%cr0

	movw $0x10,%ax
	mov %ax,%es
	mov %ax,%gs
	mov %ax,%fs
	mov %ax,%ss

	mov $0x2ffff,%esp
	jmp protected_mode_Jump
	nop
	nop

read_sectors:
	movl $0x1,%eax

	/* remain with bits 24-27 of LBA */
	shr $20,%eax
	/* Clear possible bits before */
	and $0x0f,%eax

	/* Set bit 6 for LBA Mode */
	or $0xe0,%al
	mov $0x1f6,%dx
	out %al,%dx

	movl $0x1,%eax
	mov $0x1f3,%dx
	/* Send bits 0 - 7 of LBA to port */
	out %al,%dx

	mov $0x1f4,%dx
	/* Put bits 8 - 15 in al */
	mov %ah,%al
	/* Send bits 8 - 15 to port */
	out %al,%dx

	movl $0x1,%eax
	shr $16,%eax
	mov $0x1f5,%dx
	/* Send bits 16 - 23 to port */
	out %al,%dx

	/* Number of sectors to read in %al */
	//mov $0x1,%eax

	mov $0x10,%eax
	/* This subtraction is to cater for the overlapping maximum of 1byte since %al is the one able to send data to our controller
	More research here is needed to look for a way of sending 2bytes or even more to the HDD controller */
//	sub $0x1,%eax
	mov $0x1f2,%dx
	out %al,%dx
	
	push %edi
	mov 0x8(%ebp),%edx
	lea (%edx),%edi

	//outportb 0x20 0x1f7
	xor %edx,%edx
	mov $0x1f7,%dx
	/* Read with retry command */
	mov $0x20,%al
	out %al,%dx

read_again:
	in %dx,%al
	test $0x8,%al
	jz read_again

	
	xor %ecx,%ecx
	xor %edx,%edx
	xor %ebx,%ebx

	mov 0xc(%ebp),%eax

	/* Divide by 2 since the rep insw instruction that registers 2 bytes at a time */
	mov $0x2,%ebx
	div %ebx

	/* Add remaider times to cater for odd byte sizes, not efficient procedure because it reads an extra byte from the remainder */
	// Quotient - %eax, Remainder - %edx
	add %edx,%eax

	mov %eax,%ecx
	
//	mov $256,%ecx

	mov $0x1f0,%dx

	rep insw

	pop %edi

protected_mode_Jump:
	.byte 0x66
	.byte 0xea
	.int 0x100000
	.word 0x0008


stopMBR:
	hlt	

	.fill 446-(.-_start),1,0
	
partitionTable:
	.include "ptable.s"

	.fill 64-(.-partitionTable),1,0
	
BootMagic: .word 0xaa55
