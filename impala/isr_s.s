	.code32
	.text

	.global load_idt

	.global isr0
	.global isr1
	.global isr2
	.global isr3
	.global isr4
	.global isr5
	.global isr6
	.global isr7
	.global isr8
	.global isr9
	.global isr10
	.global isr11
	.global isr12
	.global isr13
	.global isr14
	.global isr15
	.global isr16
	.global isr17
	.global isr18
	.global isr19
	.global isr20
	.global isr21
	.global isr22
	.global isr23
	.global isr24
	.global isr25
	.global isr26
	.global isr27
	.global isr28
	.global isr29
	.global isr30
	.global isr31



load_idt:
	// push %ebp
    // mov %esp, %ebp

	lidt IDTPTR          /* This function loads the IDT into memory the idt that's in the kernel's runtime */
	// pop %ebp
	ret

/* these functions below are to handle interrupt exceptions */
/ * they raise a warning to the user that something has been violated */


	.macro interuptHandlNoArg interupt
	push $0x0
	push $\interupt
	jmp prepregs_isr
	.endm
	
	.macro interuptHandlArg interupt
	push $\interupt
	jmp prepregs_isr
	.endm

isr0: interuptHandlNoArg      0
isr1: interuptHandlNoArg      1
isr2: interuptHandlNoArg      2
isr3: interuptHandlNoArg      3
isr4: interuptHandlNoArg      4
isr5: interuptHandlNoArg      5
isr6: interuptHandlNoArg      6
isr7: interuptHandlNoArg      7
isr8: interuptHandlArg        8
isr9: interuptHandlNoArg      9
isr10: interuptHandlArg       10
isr11: interuptHandlArg       11
isr12: interuptHandlArg       12
isr13: interuptHandlArg       13
isr14: interuptHandlArg       14
isr15: interuptHandlNoArg     15
isr16: interuptHandlNoArg     16
isr17: interuptHandlNoArg     17
isr18: interuptHandlNoArg     18
isr19: interuptHandlNoArg     19
isr20: interuptHandlNoArg     20
isr21: interuptHandlNoArg     21
isr22: interuptHandlNoArg     22
isr23: interuptHandlNoArg     23
isr24: interuptHandlNoArg     24
isr25: interuptHandlNoArg     25
isr26: interuptHandlNoArg     26
isr27: interuptHandlNoArg     27
isr28: interuptHandlNoArg     28
isr29: interuptHandlNoArg     29
isr30: interuptHandlNoArg     30
isr31: interuptHandlNoArg     31

/* prepare to check for an exception */
prepregs_isr:
	pusha
	push %ds
	push %es
	push %fs
	push %gs

	mov $0x10,%ax           /* Load data kernel segment selector */
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%fs
	mov %ax,%gs
	mov %esp,%eax
	push %eax

	lea (fault_checker),%eax
	call *%eax

	pop %eax
	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa
	add $0x8,%esp       /* Clear the pushed error code and interrupt handler number*/
	iret                /* pop cs, eip, ss, esp */

