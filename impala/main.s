	.code32
	.include "macros/port.h"
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

	//call _initps2
	//call initpit

	push $aftr_sleep
	call puts

	add $0x4,%esp	

//	outportb 0x12 0x43
//	outportb 0x20 0x40
//	outportb 0x02 0x40
//	outportb 0x00 0x40

	//latch to read
//read_em:	
//	outportb 0x10 0x43
//	inportb 0x40
//	nop
//	cmp $0x0,%al
//	jnz read_em

//	push $welcome_str
//	call puts
//	add $0x4,%esp

hang:
	jmp hang

	
	.data


	.bss
	.lcomm disk_dat, 512

	.data
welcome_str:	.asciz "We are a Revolution\n"
aftr_sleep:	.asciz "After sleeping\n"
