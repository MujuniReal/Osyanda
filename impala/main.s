	.code32
	.include "macros/port.h"
	.global prep_r
	.global red_data
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


	/* initialize file system info */
	push $fs_msg
	call puts
	add $0x4,%esp
	call readfat
	call readrootdir

	/* Install the iread syscall interrupt */
	push $iread
	push $0x2	/* int 0x22 */
	call install_interrupt_handler
	add $0x8,%esp

	xor %eax,%eax
	xor %ebx,%ebx
	xor %ecx,%ecx
	xor %edx,%edx

	mov $0x2,%eax		/* Function number */
	/* lba %ebx leave as is */
	mov $red_data,%ecx
	mov $0x200,%edx		/* 512 bytes, that is size */
	
	int $0x22

	nop

	call _initps2	

	//	call sample_func

	//

//	push $sample_func
//	push $0x1
//	call install_interrupt_handler

	nop
	nop

//	int $0x21

	
	nop
	nop

//	call _initps2
	

//	push $sample_test
//	call puts
//	add $0x4,%esp
//	call readfat
//	call readrootdir
//	call listdir


	
//	push $0x200
//	push $red_data
//	push $0x3
//	call readfatfile

//	add $0xc,%esp

hang:
	jmp hang


	.bss
	.lcomm disk_dat, 512

	.data
red_data:	.space 512, 0
sample_test:	.int 0x00414141
welcome_str:	.asciz "We are a Revolution\n"
aftr_sleep:	.asciz "After sleeping\n"
prep_r:	 .asciz "Veridis Quo Dafrt"
fs_msg:	.asciz "[impala] Initializing filesystem\n"
