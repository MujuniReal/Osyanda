.code16
.text
.org 0x0
.global main_mbr2

//this header file below here is for a 1.4MB floppy disk formatted with FAT
//Fat formated with MBR not GPT

main_mbr2:
	cli

#include <fat/fat16mbr.h>


filesegment = 0x1000
fatsegment = 0x0ee0
tmprootdirseg = 0x1000

start_mbr2:
	sti

	mov ByPSect,%ax
	xor %bx,%bx
	mov SectPClust,%bl
	mul %bx
	mov %ax,ByPClust


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
	mov $0x20,%bx		//max root directory entries 32 in base16
	mul %bx			//These are now the total bytes that the root directory spans
	mov ByPSect,%bx	
	div %bx
	mov %ax,Root_dirSects	//Root directory span sectors

	//rootDirectory Size in Clusters
	xor %bx,%bx
	xor %dx,%dx
	mov NRootDirEs,%ax
	mov $0x20,%bx		//max root directory entries 32 in base16
	mul %bx			//These are now the total bytes that the root directory spans
	mov ByPClust,%bx	
	div %bx
	mov %ax,Root_dirClusts	//Root directory span

/* ************************************************************* */
/*           FROM NOW ON ALWAYS START FROM BELOW HERE           */
/* *********************************************************** */
	//preparing to read the root directory
	mov $tmprootdirseg,%ax
	mov %ax,%es
	xor %cx,%cx
	xor %bx,%bx
	xor %ax,%ax


read_next_rdir_clust:
	mov Root_dirStart,%ax	//LBA Format
	add %cx,%ax
	push %cx
	call ReadSect
	pop %cx
    inc %cx
    cmp Root_dirClusts,%cx
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
	cmp ByPClust,%bx
	jz read_next_rdir_clust
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

	push %ax
	mov SectsPFat,%ax
	xor %bx,%bx
	mov SectPClust,%bl
	div %bx
	pop %ax
	mov %ax,%cx			/*Clusters Per FAT */
	xor %bx,%bx
	
read_next_fat_clust:
	push %cx
	call ReadSect
	pop %cx
	add SectPClust,%ax
	add ByPClust,%bx
	loopnz read_next_fat_clust

/* WOOOOOOOOOOOOOOOO THE FAT TABLE HAS BEEN LOADED INTO MEMORY
   NOW LETS SEE SOME ACTION FRIENDS			*/	

	mov $filesegment,%ax
	mov %ax,%es
	xor %bx,%bx
	mov file_start,%cx
	xor %ax,%ax

/* this below here is filesystem specific */
initiate_read:
	mov %cx,%ax
	add Root_dirStart,%ax
	add Root_dirSects,%ax
	sub $0x2,%ax
	push %cx
	call ReadSect
	pop %cx
	push %ds
	mov $fatsegment,%dx
	mov %dx,%ds
	mov %cx,%si
	add %cx,%si			//final location of fat entry in memory
	movw %ds:(%si),%dx
	pop %ds
	cmp $0xffff,%dx
	je done_readingfile
read_next_file_cluster:
	mov %dx,%cx
	add ByPClust,%bx /* this is actually wrong we need bytes per cluster calculated */
	/*bytes per cluster is whats needed to increament %bx even up there where we load root dir and fatsegment dont forget */
	jmp initiate_read
/* Upto here is file system specific */
/*We have to improve our readsect to read sects per cluster */
done_readingfile:
	mov $filesegment,%ax
	mov %ax,%es
	mov %ax,%ds
	ljmp $filesegment,$0x0000

FinishProgram:
	hlt

#include <printer.h>
#include <readsect.h>

fileName: .ascii "STAGE2  BIN"
ffounds: .asciz "File found!\r\n"
notf: .asciz "File not found\r\n"
FailTRStr: .asciz "Failed to read\r\n"
SucReadStr: .asciz "Successfully read the disk\r\n"

ByPClust: .word 0x00,0x00
Root_dirStart: .byte 0,0  //LBA Location for the start of root dir
Root_dirSects: .byte 0,0 //Span of root dir in Sectors
Root_dirClusts: .byte 0,0
file_start: .byte 0,0