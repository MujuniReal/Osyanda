	.code32
	.include "macros/port.h"
	.include "macros/io.h"
	.include "idt_s.h"

	PRIMARY_PIC_CMDPORT = 0x20
	PRIMARY_PIC_DATAPORT = 0x21

	SECONDARY_PIC_CMDPORT = 0xa0
	SECONDARY_PIC_DATAPORT = 0xa1
	
	.size interrupt_handlers, 64
	
	.global interrupt_handlers	
	.text
	.global install_irqs
	.global interrupt_handler



	.macro setirq irqno irqfunc
	push $\irqfunc
	push $\irqno
	call set_idt_interrupt_gate
	add $0x8,%esp
	.endm

install_irqs:

	call setmap_PIC

	setirq 32 irq0
	setirq 33 irq1
	setirq 34 irq2
	setirq 35 irq3
	setirq 36 irq4
	setirq 37 irq5
	setirq 38 irq6
	setirq 39 irq7
	setirq 40 irq8
	setirq 41 irq9
	setirq 42 irq10
	setirq 43 irq11
	setirq 44 irq12
	setirq 45 irq13
	setirq 46 irq14
	setirq 47 irq15

	ret




setmap_PIC:
	outportb 0x11 PRIMARY_PIC_CMDPORT
	iowait
	outportb 0x11 SECONDARY_PIC_CMDPORT
	iowait

	outportb 0x20 PRIMARY_PIC_DATAPORT
	iowait  
	outportb 0x28 SECONDARY_PIC_DATAPORT
	iowait
	

	outportb 0x4 PRIMARY_PIC_DATAPORT
	iowait
	outportb 0x2 SECONDARY_PIC_DATAPORT
	iowait

	outportb 0x1 PRIMARY_PIC_DATAPORT
	iowait
	outportb 0x1 SECONDARY_PIC_DATAPORT
	iowait

	outportb 0x0 PRIMARY_PIC_DATAPORT
	outportb 0x0 SECONDARY_PIC_DATAPORT

	ret

//void install_interrupt_handler(unint8 irq, void *interrupthandler(registers))
install_interrupt_handler:
	
	mov %esp,%ebp		/* this is gonna help us locate vaiables and also parsed data */
	
	push %edi
	xor %eax,%eax
	xor %edx,%edx
	xor %ebx,%ebx
	
	lea (interrupt_handlers),%edi

	/* the essence of ebp change this in the future */
	mov 0x4(%ebp),%edx		/* function pointer address */
	push %edx			/* Secure it for multilication */
	
	movb 0x8(%ebp),%al		/* chosen interrupt number */
	movb $0x4,%bl
	mul %bl				/* calculate the location to store the interrupt */

	pop %edx			/* retrieve it after multiplication */

	add %eax,%edi
	mov %edx,%edi			/* register the interrupt handler */

	pop %edi
	ret
	
	
interrupt_handler:
	mov %esp,%ebp
	push %esi
	push %edi
	xor %ebx,%ebx

	mov 0x4(%ebp),%esi			/* collect the parsed structure of registers*/
	lea (interrupt_handlers),%edi
	
	mov INTRNO(%esi),%eax
	sub $32,%eax
	/* %eax contains the interrupt number which maps the same index as for an interrupt function in the list of interrupt handlers */

	/* since the size of a function pointer in the list of handlers is 4 bytes we multiply by 4 to locate it */
	movb $0x4,%bl
	mul %bl

	/* Point us to the function from the list of handlers */
	add %eax,%edi
	xor %eax,%eax
	mov (%edi),%eax
	
	cmp $0x0,%eax
	jz no_irq_handler
	push %esi				/* Parse the structure of registers */
	call *%eax				/* Call the interrupt function */
	add $0x4,%esp
	
	/* calclate a displacement to locate whether the called interrupt has an existing handler in the interrupt handlers list */
	
no_irq_handler:	
	pop %edi
	pop %esi


	ret

	.bss
	//.section .bss	/* Assemble all code in this section to the bss
interrupt_handlers: .space 64,0

