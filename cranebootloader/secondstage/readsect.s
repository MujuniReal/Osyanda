	.code32
	.global diskread
	.text

// extern uint8 diskread(char*buf, uint8 numSects, uint32 lba);
diskread:
	push %ebp
	mov %esp,%ebp

	nop
	mov 0x10(%ebp),%eax 	/* LBA */

	shr $24,%eax
	or $0xe0,%al
	mov $0x1f6,%dx
	out %al,%dx

	//Sects to read
	movb 0xc(%ebp),%al
	mov $0x1f2,%dx
	out %al,%dx

	/* Send bits 0 - 7 of LBA to port */
	mov 0x10(%ebp),%eax 	/* LBA */
	mov $0x1f3,%dx
	out %al,%dx

	mov $0x1f4,%dx
	/* Put bits 8 - 15 in al */
	shr $0x8,%eax
	/* Send bits 8 - 15 to port */
	out %al,%dx

	mov 0x10(%ebp),%eax  	/* LBA */
	shr $16,%eax
	mov $0x1f5,%dx
	/* Send bits 16 - 23 to port */
	out %al,%dx
	
	push %edi
	mov 0x8(%ebp),%edx
	mov %edx,%edi

	//outportb 0x20 0x1f7
	mov $0x1f7,%dx
	mov $0x20,%al
	out %al,%dx

read_again:
	in %dx,%al
	test $0x8,%al
	jz read_again

	
	xor %ecx,%ecx
	xor %edx,%edx
	xor %ebx,%ebx

	movl $0x2000,%eax

	/* Divide by 2 since the rep insw instruction that registers 2 bytes at a time */
	mov $0x2,%ebx
	div %ebx
	add %edx,%eax
	mov %eax,%ecx

	mov $0x1f0,%dx

	rep insw

	pop %edi

	mov 0x4(%ebp),%eax
	pop %ebp

	ret