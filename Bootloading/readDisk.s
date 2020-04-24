.code16

.text
.org 0x00

main:	jmp start
	nop

//this header file below here is for a 1.4MB floppy disk formatted with FAT
//Fat formated with MBR not GPT

#include "fatstruct.h"
#include "printer.h"

.func ReadSect
/*
  %al - number of sectors to read
  %ah - SubFunction 2 from BIO interrupts
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
ReadSect:
	push %ax
	push %cx
	push %bx

/*	xor %cx,%cx
	mov $0x4,%cx  */

	//Sector
	xor %bx,%bx
	xor %dx,%dx
	mov SectsPTrck,%bx
	div %bx
	inc %dx
	mov %dl,%cl

	//Head
	xor %dx,%dx	//Since %ax is (LBA/SectsPTrack)
	xor %bx,%bx	//No need of editing its contents
	mov NHeads,%bx	//Remember we have to save bytes because
	div %bx		//We are limited to 512Bytes
	xchg %dl,%dh

	//cylinder
	mov %al,%ch

	//finalyy
	mov LogDrvNo,%dl
	mov $0x0201,%ax		//We intend to (read) (one) Sector
	pop %bx
	int $0x13
	jc FailedToread
	lea (SucReadStr),%si
	call PrintIt
	jmp exitRead


FailedToread:			//This function attempts to try reading
	pop %cx			//the sector 3 more times 3more trials
	xor %ax,%ax
	int $0x13		//Reset the disk and we try again
	pop %ax			//Put Back LBA in the mighty register
	dec %cx
	cmp $0x0,%cx
	jnz ReadSect		//Totally failed
	lea (FailTRStr),%si	//Totally failed to read string
	call PrintIt

exitRead:
	pop %cx
	pop %ax
	retw

		
.endfunc

Root_dirStart: .word 0x0000
Root_dirSects: .word 0x0000


start:
	//mov the drive number in %dl to thedefined variable reposible to hold it
	cli
	mov %dl,LogDrvNo
	xor %ax,%ax
	mov %ax,%ss
	mov %ax,%es
	mov %ax,%ds
	mov $0x7c00,%sp
	sti

	//rootDirectory Start Sector Calculation
	mov SectsPFat,%ax
	mul FatTabs		//multiplication FatTables * SectorsPFat
	add ResSects,%ax	//Add the reserved sectors
	add NHiddenSects,%ax	//Add the  hidden sectors	
	adc NhiddnSectshi,%ax	//Add the hight word of hidden Sects
	mov %ax,Root_dirStart	//Root_dirStart in LBA format

	//rootDirectory Size in sectors
	xor %bx,%bx
	xor %dx,%dx
	xor %ax,%ax
	mov NRootDirEs,%ax
	mov $32,%bx
	mul %bx			//These are now the total bytes that the root directory spans
	div ByPSect		//These are now rootdir sectors of span 
	mov %ax,Root_dirSects

	mov Root_dirStart,%ax	//LBA Format
	call ReadSect

	lea (%es:%bx),%si
	lea (fileName),%di
	repz cmpsb
	je File_found



fileName: .ascii "Osyanda.zip"
