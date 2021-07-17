	.code32
IDTSIZE = 2047			/* 2048 minus 1 */
	.comm idt, 2048
	.text
	.global setup_idt

setup_idt:
	/* Pull the Idt pointer and initialize it to zero */
	push %esi
	push %edi
	
	xor %eax,%eax
	xor %ecx,%ecx
	
	/* Set the IDT Pointer */
	lea (idtp),%esi
	movw $IDTSIZE,(%esi)
	mov idt,0x2(%esi)

	/* Fill the IDT with zeros */
	lea (idt),%edi
	movw $IDTSIZE,%cx
	add $0x1,%cx		/* cater for the other minus 1 */
	repnz stosb

	/* Load the Interrupt descriptor table */
	call load_idt

	ret
