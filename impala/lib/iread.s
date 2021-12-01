	.code32
	.global iread
	.text


/* For now, this Syscall is directly calling the diskread function
*	because implementation of the file descriptors has not yet been
*	established
*/
	
iread:
	push %ebp
	mov %esp,%ebp
	mov $0x1,%eax
	mov %eax,lba
	push 0xc(%ebp)
	push 0x8(%ebp)
	call rdsk
	/* With this scheme below, it saves us from bringing back the stack pointer */
	mov %ebp,%esp
	pop %ebp
	ret
	
