	.code32
	.global first_datacluster
	.global readfatfile
	.text

readfatfile:
	push %ebp
	mov %esp,%ebp
	xor %ebx,%ebx

	/* File start Cluster */
	movw 0x8(%ebp),%ax
	/* Subtract 2 for fat to cater for the first 2 reserved entries */
	sub $0x2,%ax
	movb SectPClust,%bl
	mul %bx
	
	add first_datacluster,%eax
	/* eax -> file cluster + rootdirstart */
	mov %eax,lba
	
	xor %eax,%eax
	xor %edx,%edx
	
	/* Number of bytes to read */
	mov 0x10(%ebp),%eax
	movw ByPSect,%bx
	div %bx

	cmp $0x0,%edx
	jz cont_to_read
	/* Add one more sector tobe read since there was a remainder after division */
	add $0x1,%eax
cont_to_read:	
	mov %eax,sects_to_read
	push 0x10(%ebp)
	/* Location of the read bytes */
	push 0xc(%ebp)
	call rdsk

	mov %ebp,%esp
	pop %ebp
	ret

	.data

first_datacluster:	.int 0x0
