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


Root_dirStart: .byte 0x00,0x00	//LBA Location for the start of root dir
Root_dirSects: .byte 0x00,0x00	//Span of root dir in Sectors
file_start: .byte 0x00,0x00
filesegment = 0x1000
fatsegment = 0x0ee0
tmprootdirseg = 0x1000


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
	//mov Root_dirStart,%ax	//LBA Format
	mov $19,%ax
	add %cx,%ax
	push %cx
	call ReadSect
	pop %cx
        inc %cx
        //cmp Root_dirSects,%cx
	cmp $14,%cx
	jz file_not_found
	push %cx

getFilename:
	mov $0x000b,%cx
	lea (%bx),%si
	lea (fileName),%di
	repz cmpsb
	je File_Found
	add $0x20,%bx
	cmp ByPSect,%bx
	jz read_next_sector
	jmp getFilename


	
file_not_found:
	lea (notf),%si
	call PrintIt
	jmp FinishProgram

	
File_Found:
	pop %cx
	lea (ffounds),%si
	call PrintIt
	mov %es:0x1a(%bx),%ax
	mov %ax,file_start


loaDFAT:
	mov $fatsegment,%ax
	mov %ax,%es
	mov ResSects,%ax
	add NHiddenSects,%ax
	adc NhiddnSectshi,%ax
	mov SectsPFat,%cx
	xor %bx,%bx
	
read_next_fat_sect:
	push %cx
	call ReadSect
	pop %cx
	inc %ax
	add ByPSect,%bx
	loopnz read_next_fat_sect

/* WOOOOOOOOOOOOOOOO THE FAT TABLE HAS BEEN LOADED INTO MEMORY
   NOW LETS SEE SOME ACTION FRIENDS			*/	

	mov $filesegment,%ax
	mov %ax,%es
	xor %bx,%bx
	mov $0x0003,%cx
	xor %ax,%ax


read_file_nextinline_sector:
	mov %cx,%ax
/*	add Root_dirStart,%ax
	add Root_dirSects,%ax*/
	add $19,%ax
	add $14,%ax
	sub $0x2,%ax
	push %cx
	call ReadSect
	pop %cx
	add ByPSect,%bx
	push %ds
        mov $fatsegment,%dx
        //ds:si
        mov %dx,%ds
	mov %cx,%dx
	mov %cx,%si
	shr %dx
	add %dx,%si
	mov %ds:(%si),%dx
	pop %ds
	test $0x1,%cx
	jnz odd_entry
	and $0x0fff,%dx
	jmp continue_to_read
odd_entry:
	shr $0x4,%dx
continue_to_read:
	mov %dx,%cx
	cmp $0xff8,%cx
	jl read_file_nextinline_sector




FinishProgram:
	hlt


fileName: .ascii "VEXER   BIN"
ffounds: .asciz "File found friend!!!\r\n"
notf: .asciz "File not found\r\n"
//FailTRStr: .asciz "Totally failed to read sector\r\n"
SucReadStr: .asciz "Successfully read the disk\r\n"
tryss: .asciz "Trying to read again...\r\n"

.fill 510-(.-main),1,0
BootMagic: .word 0xaa55 
