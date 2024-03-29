	.code32
	
	.global prep_r
	.global red_data
	.text
	.global run_impala

	.macro outportb data port
mov $\data,%al
    outb %al,$\port
.endm


.macro inportb port
	inb $\port,%al
.endm

run_impala:
	cli
	call setup_idt
	call install_isr
	call install_irqs
	sti

	call clears

	push $welcome_str
	call prints
	add $0x4,%esp


	// /* initialize file system info */
	// push $fs_msg
	// call prints
	// add $0x4,%esp
	// call readfat
	// call readrootdir

	/* Install the iread syscall interrupt */
	// push $iread
	// push $0x2	/* int 0x22 */
	// call install_interrupt_handler
	// add $0x8,%esp

	// push $keydrv
	// push $0x1
	// call install_interrupt_handler
	// add $0x8,%esp

	
	// xor %eax,%eax
	// xor %ebx,%ebx
	// xor %ecx,%ecx
	// xor %edx,%edx

	// push %edi
	// mov %eax,%edi
	// movl $0x000107ae,264(%edi)
	// movl $0x00060e00,268(%edi)
	

	// pop %edi
//	mov $0x2,%eax		/* Function number */
	/* lba %ebx leave as is */
//	mov $red_data,%ecx
//	mov $0x200,%edx		/* 512 bytes, that is size */
	
//	int $0x22

	// nop
	call _initps2

	//call loader

	

//	call terminal
	// setcursor(1920);

hang:
	call read_kybd
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
