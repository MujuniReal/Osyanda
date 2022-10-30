

	push %di
	mov $0x7e10,%di
	xor %ebx,%ebx
read_smre:	
	xor %eax,%eax
	xor %edx,%edx
	xor %ecx,%ecx

	mov $0xe820,%eax
	mov $0x534d4150,%edx
	mov $24,%ecx
	int $0x15

	add %cx,%di
	jmp read_smre
	
	
	pop %es
	pop %di

	nop
