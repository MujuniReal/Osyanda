.code16

.text
.org 0x00
.global main

main:
	jmp start


//this header file below here is for a 1.4MB floppy disk formatted with FAT
//Fat formated with MBR not GPT

#include "fatstruct.h"
#include "printer.h"
#include "readsect.h"


Root_dirStart: .word 0x0000	//LBA Location for the start of root dir
Root_dirSects: .word 0x0000	//Span of root dir in Sectors
filesegment = 0x1000
fatsegment = 0x0ee0
tmprootdirseg = 0x0900

start:
	//mov the drive number in %dl to thedefined variable reposible to hold it
	cli
	mov %dl,LogDrvNo
	mov %cs,%ax
	mov %ax,%ss
	mov %ax,%es
	mov %ax,%ds
	mov 0x7c00,%sp
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
	//preparing to read the root directory
	mov $tmprootdirseg,%ax
	mov %ax,%es
	xor %cx,%cx
	xor %bx,%bx

read_next_sector:
	mov Root_dirStart,%ax	//LBA Format
	add %cx,%ax
	push %cx
	call ReadSect
	pop %cx
        inc %cx
        cmp Root_dirSects,%cx
	jz file_not_found
	push %cx

getFilename:
	mov $0x000b,%cx
	lea (%bx),%si
	lea (fileName),%di
	repz cmpsb
	je File_Found
	add $0x20,%bx
	cmp $0x0200,%bx
	jz read_next_sector
	jmp getFilename
	
file_not_found:
	lea (notf),%si
	call PrintIt
	jmp FinishProgram
	
File_Found:
	lea (ffounds),%si
	call PrintIt

FinishProgram:
	hlt


fileName: .ascii "OSYANDA ZIP"
ffounds: .asciz "File found friend!!!\r\n"
notf: .asciz "File not found\r\n"
FailTRStr: .asciz "Totally failed to read sector\r\n"
SucReadStr: .asciz "Successfully read the disk\r\n"
tryss: .asciz "Trying to read again...\r\n"

.fill 510-(.-main),1,0
BootMagic: .word 0xaa55 
