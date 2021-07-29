	.code32
//	.include "macros/port.h"
	.text
	.global run_impala

run_impala:
	cli
	call setup_idt
	call install_isr
	call install_irqs
	sti

	call clears
	
	push $welcome_str
	call puts
	
	add $0x4,%esp
	
	nop
	nop

hang:
	jmp hang

	
	.data

welcome_str:	.asciz "We are a Revolution\n"
