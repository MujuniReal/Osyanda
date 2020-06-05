.code16

.text
.org 0x00
.global main

main:
	jmp start
	nop

//this header file below here is for a 1.4MB floppy disk formatted with FAT
//Fat formated with MBR not GPT

#include <fat/fat12mbr.h>


filesegment = 0x0b20
fatsegment = 0x0a00
tmprootdirseg = 0x0800


start:
	//mov the drive number in %dl to thedefined variable reposible to hold it
	cli
	mov %dl,LogDrvNo
	mov %cs,%ax
	mov %ax,%ss
	mov %ax,%es
	mov %ax,%ds
	mov $0x7c00,%ax
	mov %ax,%sp
	sti

	xor %bx,%bx
	//rootDirectory Start Sector Calculation
	mov SectsPFat,%ax
	mov FatTabs,%bl		//multiplication FatTables * SectorsPFat
	mul %bx
	add ResSects,%ax	//Add the reserved sectors
	add NHiddenSects,%ax	//Add the  hidden sectors	
	add NhiddnSectshi,%ax	//Add the hight word of hidden Sects
	mov %ax,Root_dirStart	//Root_dirStart in LBA format

	//rootDirectory Size in sectors
	xor %bx,%bx
	xor %dx,%dx
	mov NRootDirEs,%ax
	mov $0x20,%bx		//size of one root directory entry is 32Bytes in base16
	mul %bx			//These are now the total bytes that the root directory spans
	mov ByPSect,%bx	
	div %bx
	mov %ax,Root_dirSects	//Root directory span sectors

/* ************************************************************* */
/*           FROM NOW ON ALWAYS START FROM BELOW HERE           */
/* *********************************************************** */
	//preparing to read the root directory
	mov $tmprootdirseg,%ax
	mov %ax,%es
	xor %cx,%cx
	xor %bx,%bx
	xor %ax,%ax


read_next_sector:
	mov Root_dirStart,%ax	//LBA Format
	//mov $19,%ax
	add %cx,%ax
	push %cx
	call ReadSect
	pop %cx
    inc %cx
    cmp Root_dirSects,%cx
	//cmp $14,%cx
	jz file_not_found

getFilename:
	push %cx
	mov $0x000b,%cx
	lea (%bx),%di
	lea (fileName),%si
	repz cmpsb
	je File_Found
	pop %cx
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
	add NhiddnSectshi,%ax
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
	mov file_start,%cx
	xor %ax,%ax

/* this below here is filesystem specific */
read_file_nextinline_sector:
	mov %cx,%ax
	add Root_dirStart,%ax
	add Root_dirSects,%ax
	//add $19,%ax
	//add $14,%ax 
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
/* Upto here is file system specific */

/* Save the acquired variables */
	xor %bx,%bx
	xor %dx,%dx
	movb LogDrvNo,%dl
	mov %dl,%es:0x24(%bx)	
	mov Root_dirSects,%ax
	mov %ax,%es:0x3e(%bx)
	mov Root_dirStart,%ax
	mov %ax,%es:0x40(%bx)

/* prepare for loading the second stage bootloader */
	mov $filesegment,%ax
	mov %ax,%es
	mov %ax,%ds
	ljmp $filesegment,$0x0000

FinishProgram:
	hlt

#include <printer.h>
#include <readsect.h>

fileName: .ascii "STAGE2  BIN"
ffounds: .asciz "Filefound\r\n"
notf: .asciz "Filenotfound\r\n"
FailTRStr: .asciz "Failedtoread\r\n"
//SucReadStr: .asciz "Sucesfuly read the disk\r\n"

Root_dirStart: .byte 0,0  //LBA Location for the start of root dir
Root_dirSects: .byte 0,0 //Span of root dir in Sectors
file_start: .byte 0,0

.fill 510-(.-main),1,0
BootMagic: .word 0xaa55 
