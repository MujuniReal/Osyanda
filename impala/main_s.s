	.code32
	.text
	.global run_impala

run_impala:
	cli
	call setup_idt
	call install_isr
	call clears
	nop
	nop

hang:
	jmp hang
