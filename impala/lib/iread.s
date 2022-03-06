	.code32
	.include "idt_s.h"
	.global iread
	.text


/* For now, this Syscall is directly calling the diskread function
*	because implementation of the file descriptors has not yet been
*	established
*/
	
iread:
	push %ebp
	mov %esp,%ebp	/* ebp, ret addr, struct regs */
	push %esi
	mov 0x8(%ebp),%esi
	xor %eax,%eax
	mov R_EBX(%esi),%eax
	mov %eax,lba
	push R_EDX(%esi)	/* size */
	push R_ECX(%esi)	/* char* */
	call rdsk
	/* With this scheme below, it saves us from bringing back the stack pointer */
	add $0x8,%esp
	pop %esi
	mov %ebp,%esp
	pop %ebp

	ret
	
