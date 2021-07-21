	.code32
	IDTLIMIT = 2047			/* 2048 minus 1 */
	IDTENTRY_SIZE = 8
	IDT_INTERRUPT_GATE = 0x8e
	IDT_INTERRUPT_TASK_GATE = 0x8f
	CS_SELECTOR_GDT = 0x8
	.comm idt, 2048
	.text
	.global idt
	.global setup_idt
	.global set_idt_interrupt_gate
	.global set_idt_task_gate

setup_idt:
	/* Pull the Idt pointer and initialize it to zero */
	push %esi
	push %edi
	
	xor %ecx,%ecx
	
	/* Set the IDT Pointer */
	lea (idtp),%esi
	movw $IDTLIMIT,(%esi)
	mov $idt,%edx
	mov %edx,0x2(%esi)

	/* Fill the IDT with zeros */
	xor %eax,%eax
	lea (idt),%edi
	movw $IDTLIMIT,%cx
	add $0x1,%cx		/* cater for the other minus 1 */
	repnz stosb

	/* Load the Interrupt descriptor table */
	call load_idt

	pop %edi
	pop %esi

	ret
/* the above function worked successfully */


	.func set_idt_interrupt_gate
set_idt_interrupt_gate:
	mov 0x8(%esp),%eax			/* first parameter isr0,1,2.. */
	mov 0x4(%esp),%ebx				/* second parameter interrupt offset in idt */
	push %eax				/* first arg to calling set_idt_enty */
	push $IDT_INTERRUPT_GATE		/* second arg task/intrpt attribute*/
	push %ebx				/* third arg offset of idt entry*/
	call set_idt_entry

	add $0xc,%esp				/* Put back our stack */

	ret
	.endfunc

	.func set_idt_task_gate
set_idt_task_gate:
	mov 0x8(%esp),%eax			/* first parameter isr0,1,2.. */
	mov 0x4(%esp),%ebx				/* second parameter interrupt offset in idt */
	push %eax				/* first arg to calling set_idt_enty */
	push $IDT_INTERRUPT_TASK_GATE		/* second arg  we push 32bit values coz our stack has a 4byte boundary*/
	push %ebx				/* third arg */
	call set_idt_entry

	add $0xc,%esp

	ret
	.endfunc
	
	.func set_idt_entry
set_idt_entry:
//	CS_SELECTOR_GDT
	xor %eax,%eax
	xor %ebx,%ebx

	/* Calculate the location of the interrupt in the idt */
	movb 4(%esp),%bl		/* last arg in edx the interrupt id */
	movw $IDTENTRY_SIZE,%ax
	mul %bl

	mov %eax,%edx			/* Finally we have the displacement of the interrupt in the idt */
	
	mov 12(%esp),%eax		/* put first arg in eax */
	mov 8(%esp),%ebx		/* second arg task/interrupt attribute*/


	push %edi
	lea (idt),%edi

	add %edx,%edi			/* make our pointer point to the victim area to set our interrupt */
	
	movw %ax,(%edi)			/* isr low 2 bytes */
	movw $CS_SELECTOR_GDT,0x2(%edi)	/* code segment selector 2bytes */
	movb $0x0,0x4(%edi)		/* Always Zero 1byte */
	movb %bl,0x5(%edi)		/* Attribute task/intrpt 1byte */
	shr $16,%eax
	and $0xffff,%eax
	movw %ax,0x6(%edi)		/* isr high 2 bytes */
	
	pop %edi
	
	ret
	.endfunc
