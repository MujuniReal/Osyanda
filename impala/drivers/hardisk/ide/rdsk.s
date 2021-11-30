	.code32
	.include "macros/port.h"
	//DSK_CMD
	.text
	.global lba
	.global rdsk

rdsk:
	push %ebp
	mov %esp,%ebp
	
	xor %eax,%eax
	mov lba,%eax
	
	/* remain with bits 24-27 of LBA */
	shr $20,%eax
	/* Clear possible bits before */
	and $0x0f,%eax
	
	/* Set bit 6 for LBA Mode */
	or $0xe0,%al
	mov $0x1f6,%dx
	out %al,%dx

	xor %eax,%eax
	mov lba,%eax
	mov $0x1f3,%dx
	/* Send bits 0 - 7 of LBA to port */
	out %al,%dx

	
	mov $0x1f4,%dx
	/* Put bits 8 - 15 in al */
	mov %ah,%al
	/* Send bits 8 - 15 to port */
	out %al,%dx

	xor %eax,%eax
	mov lba,%eax
	shr $16,%eax
	mov $0x1f5,%dx
	/* Send bits 16 - 23 to port */
	out %al,%dx
	
	mov $0x1,%al
	mov $0x1f2,%dx
	out %al,%dx
	

	push %edi
//	lea (disk_dat),%edi

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

	mov %ebp,%esp
	pop %ebp

	ret

	.data

lba:	.int 0x0
