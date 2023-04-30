	.code16
	.global _start
	.text
	.org 0x00
	NEW_BOOT_ADDRESS = 0x100000
	CRANE_OFFSET = 0x8000
    GDT_OFFSET = 0x800

_start:
	jmp main
	nop

fatbpb:	
	//To cater for FAT filesystems
	.include "fatbpb.s"

GDT_PTR:
	.word 23
	.int 0x8000


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

readCraneSectors:
	//C - 0
    //H - 0
    //S - 1

	//ch - 0
    //cl - 1
    //dh - 0
	push %es
    movw $0x1,%cx
    xor %dh,%dh
	xor %bx,%bx
	movw $CRANE_OFFSET,%ax
	mov %ax,%es
	//%dl is set to drive No
	mov $0x0210,%ax		
	int $0x13
	nop
	pop %es

activate_a20:
    movw $0x2401,%ax
    int $0x15
	// mov 0x92,%dl
	// inb %dl,%al
    // or $0x2,%al
    // out %al,%dl

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


loadGDT:
	lgdt GDT_PTR

	xor %eax,%eax
	mov %cr0,%eax
	or $0x1,%eax
	mov %eax,%cr0


loadPM:
	xor %ax,%ax
	mov $0x10,%ax
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%gs
	mov %ax,%fs
	mov %ax,%ss
	mov $0x2ffff,%esp
	jmp prefetch

	nop
	nop
	nop
prefetch:

protected_mode_Jump:
	.byte 0x66
	.byte 0xea
	.int 0x80000
	.word 0x0008


	// .data

	.fill 446-(.-_start),1,0
	
partitionTable:
	.include "ptable.s"

	.fill 64-(.-partitionTable),1,0
	
BootMagic: .word 0xaa55

	// jmp $0x8,$read_sectors

// read_sectors:
// 	nop
// 	movl $0x1,%eax

// 	shr $24,%eax
// 	or $0xe0,%al
// 	mov $0x1f6,%dx
// 	out %al,%dx

// 	//Sects to read
// 	mov $0x10,%eax
// 	mov $0x1f2,%dx
// 	out %al,%dx

// 	/* Send bits 0 - 7 of LBA to port */
// 	movl $0x1,%eax
// 	mov $0x1f3,%dx
// 	out %al,%dx

// 	mov $0x1f4,%dx
// 	/* Put bits 8 - 15 in al */
// 	shr $0x8,%eax
// 	/* Send bits 8 - 15 to port */
// 	out %al,%dx

// 	movl $0x1,%eax
// 	shr $16,%eax
// 	mov $0x1f5,%dx
// 	/* Send bits 16 - 23 to port */
// 	out %al,%dx
	
// 	push %edi
// 	mov $NEW_BOOT_ADDRESS,%edx
// 	mov %edx,%edi

// 	//outportb 0x20 0x1f7
// 	mov $0x1f7,%dx
// 	mov $0x20,%al
// 	out %al,%dx

// read_again:
// 	in %dx,%al
// 	test $0x8,%al
// 	jz read_again

	
// 	xor %ecx,%ecx
// 	xor %edx,%edx
// 	xor %ebx,%ebx

// 	movl $0x2000,%eax

// 	/* Divide by 2 since the rep insw instruction that registers 2 bytes at a time */
// 	mov $0x2,%ebx
// 	div %ebx
// 	add %edx,%eax
// 	mov %eax,%ecx

// 	mov $0x1f0,%dx

// 	rep insw

// 	pop %edi


// guy:
// 	nop
// 	jmp guy