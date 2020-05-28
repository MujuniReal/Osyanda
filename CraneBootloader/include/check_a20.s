.func TestA20pin
//this is a checker so a checker is called 
TestA20pin:
	pushf
	push %ds
	push %es

	cli
	//es:di initially
	mov $0x0000,%ax
	mov %ax,%es
	mov $0x0500,%di
	movb $0xfb,%es:(%di)
	
	//%ds:%si After writing
	mov $0xffff,%dx
	mov %dx,%ds
	mov $0x0510,%si
	movb $0xe6,%ds:(%si)
	xor %ax,%ax
	movb %es:(%di),%al

        pop %es
        pop %ds
        popf

	nop
	cmp $0xe6,%al
	jz PinNot

PinYes:
        lea (PRamStat),%si
        call PrintIt
	xor %ax,%ax
	mov $0x1,%ax			//Return 1 if success
	jmp FinCheck

PinNot:
	lea (NRamStat),%si
	call PrintIt
	xor %ax,%ax			//Return 0 if failure
	//Call stuff to deal with enabling A20pin


FinCheck:
	retw
.endfunc
