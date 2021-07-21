	.code32
	.text
	.global run_impala

run_impala:
	cli
	call setup_idt
	call install_isr
	sti
	call clears
	push %esi
	lea (welcome_str),%esi
	push %esi
	call puts
	add $0x4,%esp
	pop %esi
	nop
	nop

hang:
	jmp hang

	.data

welcome_str:	.asciz "We are a Revolution\n"
