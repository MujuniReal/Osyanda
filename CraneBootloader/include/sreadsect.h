/* sreadsect.h ->   short read sector for 16bit clusters */

.func ReadSect
/*
  %al - number of sectors to read
  %ah - SubFunction 2 for 16bit reads from BIOS interrupts
  %ch - Low 8bits of Cylinder
  %cl - High 2bits of cylinder, 6bits for sector
  %dh - Head Number
  %dl - Drive Number from BIOS
  %es:%bx - Where read data is gonna be stored

  LBA
  Sector = (LBA mod SectsPTrack) + 1
  Head = (LBA / SectsPTrack) mod NumHeads
  Cylinder = (LBA / SectsPTrack) / NumHeads

  divide (dx:ax)/bx or any reg qoutient - %ax remainder - %dx
  Before calling this guy set %cx to 4 so dat it attempts to try wen fail
  we gonna use the cx register as our counter to count
  4 3 more trys for disk reading
  from the ax,bx,cx,dx function calling style i think
  that this function is like so readSect(No_sects,*ptrSrc,*ptrDst)
  This function expects LBA put in %ax register

*/

/* Take note that real systems can actually read any number of sectors that you specify in
the %al register but bochs here can only read one sector at a time bambi */

ReadSect:
	//%cx must be saved before calling this function
	xor %cx,%cx
    mov $0x4,%cx  	//We wanna read 3 more times before leaving

readsect:
	push %ax	//Contains LBA
	push %cx	//Contains number of trial times for reading disk
	push %bx	//Contains adress to store read data

	//Sector
	xor %dx,%dx
	mov SectsPTrck,%bx
	div %bx
	inc %dx
	mov %dl,%cl

	//Head
	xor %dx,%dx	//Since %ax is (LBA/SectsPTrack) No need of editing its contentsi
	mov NHeads,%bx	//Remember we have to save bytes because
	div %bx		//We are limited to 512Bytes
	xchg %dl,%dh

	//cylinder
	mov %al,%ch

	//finalyy
	mov LogDrvNo,%dl
	mov $0x0201,%ax
	pop %bx
	int $0x13
	jc FailedToread
	/*lea (SucReadStr),%si
	call PrintIt */
    pop %cx
    pop %ax
	jmp exitRead


FailedToread:		//This function attempts to try reading
	pop %cx			//the sector 3 more times 3more trials
	xor %ax,%ax
	int $0x13		//Reset the disk and we try again
	//sucessfully resets
	pop %ax			//Put Back LBA in the mighty register
	dec %cx
	cmp $0x0,%cx
	jnz readsect		//Totally failed
	//lea (FailTRStr),%si	//Totally failed to read string
	//call PrintIt

exitRead:
	retw

		
.endfunc
