.code16

.text
.org 0x00
.global main

main:	jmp start
	nop

//this header file below here is for a 1.4MB floppy disk formatted with FAT
//Fat formated with MBR not GPT

#include "fatstruct.h"
#include "printer.h"
#include "readsect.h"


Root_dirStart: .word 0x0000	//LBA Location for the start of root dir
Root_dirSects: .word 0x0000	//Span of root dir in Sectors
segmentee:  .word 0x0ee0

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
	
	xor %bx,%bx
	//rootDirectory Start Sector Calculation
	mov SectsPFat,%ax
	mov FatTabs,%bx		//multiplication FatTables * SectorsPFat
	mul %bx
	add ResSects,%ax	//Add the reserved sectors
	add NHiddenSects,%ax	//Add the  hidden sectors	
	adc NhiddnSectshi,%ax	//Add the hight word of hidden Sects
	mov %ax,Root_dirStart	//Root_dirStart in LBA format

	//rootDirectory Size in sectors
	xor %bx,%bx
	xor %dx,%dx
	xor %ax,%ax
	mov NRootDirEs,%ax
	mov $0x20,%bx		//max root directory entries 32 in base16
	mul %bx			//These are now the total bytes that the root directory spans
	mov ByPSect,%bx	
	div %bx
	mov %ax,Root_dirSects	//Root directory span

/* ************************************************************* */
/*           FROM NOW ON ALWAYS START FROM BELOW HERE           */
/* *********************************************************** */

	mov $Root_dirStart,%ax	//LBA Format
	movw segmentee,%es
	xor %bx,%bx
	//need to push %cx our counter
	call ReadSect
	cmp $0x0,%cx
	jz FinishProgram
	lea (%bx),%si
	call PrintIt
	//pop back our counter %cx
	//error checker
         
        //When the read has 100% failed to read

	
FinishProgram:
	hlt


fileName: .ascii "OSYANDA ZIP"
ffounds: .asciz "File found friend!!!\r\n"
notf: .asciz "File not found\r\n"
FailTRStr: .asciz "Totally failed to read sector\r\n"
SucReadStr: .asciz "Successfully read the disk\r\n"


.fill 510-(.-main),1,0
BootMagic: .word 0xaa55 
