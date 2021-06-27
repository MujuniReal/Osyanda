	xor %ax,%ax
	mov $0x2401,%ax
	int $0x15
	jc nope
	lea (Enabld),%si
	call PrintIt 
	jmp hang
