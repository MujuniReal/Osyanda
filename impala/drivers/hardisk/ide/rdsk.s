	.code32
	.include "macros/port.h"
	//DSK_CMD
	.text
	.global rdsk

rdsk:
	xor %eax,%eax
	mov $0xe0,%al
	mov $0x1f6,%dx
	out %al,%dx

	xor %eax,%eax
	mov $0x1f3,%dx
	out %al,%dx
	mov $0x1f4,%dx
	out %al,%dx

	xor %eax,%eax
	mov $0x1f5,%dx
	out %al,%dx
	
	mov $0x1,%al
	mov $0x1f2,%dx
	out %al,%dx
	

	push %edi
	lea (disk_dat),%edi

	//outportb 0x20 0x1f7
	xor %edx,%edx
	mov $0x1f7,%dx
	mov $0x20,%al
	out %al,%dx

read_again:
	in %dx,%al
	test $0x8,%al
	jz still_gg

	nop
	add $0x4,%esp
	
	xor %ecx,%ecx
	xor %edx,%edx
	mov $256,%ecx

	mov $0x1f0,%dx

	rep insw
	nop
	nop
	pop %edi

	ret
