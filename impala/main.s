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
	call initpit

	push $aftr_sleep
	call puts

	add $0x4,%esp

	xor %eax,%eax
	mov $0x1f6,%dx
	out %al,(%dx)
	mov $0x1f3,%dx
	out %al,(%dx)
	mov $0x1f4,%dx
	out %al,(%dx)
	mov $0x1f5,%dx
	out %al,(%dx)
	
	mov $0x1,%al
	mov $0x1f2,%dx
	out %al,(%dx)
	

	push %edi
	lea (disk_dat),%edi

	//outportb 0x20 0x1f7
	xor %edx,%edx
	mov $0x1f7,%dx
	mov $0x20,%al
	out %al,(%dx)

	xor %ecx,%ecx
	xor %edx,%edx
	mov $256,%ecx

	mov $0x1f0,%dx

	rep insw

	nop
	nop
	
	

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
