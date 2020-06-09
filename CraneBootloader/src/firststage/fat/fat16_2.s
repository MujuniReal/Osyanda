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

	lea (WelcomeNote),%si
	call PrintIt

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
	mov $0x20,%bx		//size of one root directory entry is 32Bytes in base16
	mul %bx			//These are now the total bytes that the root directory spans
	mov ByPSect,%bx	
	div %bx
	mov %ax,Root_dirSects	//Root directory span sectors

	//rootDirectory Size in Clusters irrelevant
	xor %bx,%bx
	xor %dx,%dx
	mov NRootDirEs,%ax
	mov $0x20,%bx		//max root directory entries 32 in base16
	mul %bx			//These are now the total bytes that the root directory spans
	mov ByPClust,%bx	
	div %bx
	mov %ax,Root_dirClusts	//Root directory span


	//preparing to read the root directory
	mov $tmprootdirseg,%ax
	mov %ax,%es
	xor %cx,%cx
	xor %bx,%bx
	xor %ax,%ax


read_next_rdir_sect:
	mov Root_dirStart,%ax	//LBA Format
	add %cx,%ax
	push %cx
	call ReadSect
	pop %cx
    inc %cx
    cmp Root_dirSects,%cx
	jz file_not_found

getFilename:
	push %cx
	mov $0x000b,%cx			/* fat12 and 16 support only filenames of 11Bytes */
	lea (%bx),%di
	lea (fileName),%si		/* compare %es:%di and %ds:%si */
	repz cmpsb
	je File_Found
	pop %cx
	add $0x20,%bx
	cmp ByPSect,%bx
	jz read_next_rdir_sect
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
	mov %ax,file_start			/*file start Cluster */


loaDFAT:
	mov $fatsegment,%ax
	mov %ax,%es

	mov ResSects,%ax
	add NHiddenSects,%ax
	add NhiddnSectshi,%ax
	xor %bx,%bx
	mov SectsPFat,%cx
	call ReadMulti
	xor %bx,%bx			/* Put back %bx to point home */

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
	sub $0x2,%ax
	mulb SectPClust
	add Root_dirStart,%ax
	add Root_dirSects,%ax
	push %cx
	xor %cx,%cx
	movb SectPClust,%cl		/* this function has helped to increament %bx for us */
	call ReadMulti			/* read cluster containing file */
	pop %cx
	push %ds
	mov $fatsegment,%dx
	mov %dx,%ds
	mov %cx,%si
	add %cx,%si			/* final location of fat entry in memory */
	movw %ds:(%si),%dx
	pop %ds
	cmp $0xfff8,%dx
	jge done_readingfile
read_next_file_cluster:
	mov %dx,%cx
	/*bytes per cluster is whats needed to increament %bx even up there where we load root dir and fatsegment dont forget */
	jmp initiate_read
/* Upto here is file system specific */
/*We have to improve our readsect to read sects per cluster */
done_readingfile:
	lea (wooing),%si
	call PrintIt

/* Save the acquired variables */
	xor %bx,%bx
	xor %dx,%dx
	movb LogDrvNo,%dl
	mov %dl,%es:0x24(%bx)	
	mov Root_dirSects,%ax
	mov %ax,%es:0x3e(%bx)
	mov Root_dirStart,%ax
	mov %ax,%es:0x40(%bx)


	mov $filesegment,%ax
	mov %ax,%es
	mov %ax,%ds
	ljmp $filesegment,$0x0000

FailedToRead:
	lea (FReadStr),%si
	call PrintIt
	call RebootBIOS /*this code can never go below here unless otherwise */


FinishProgram:
	hlt

#include <printer.h>
#include <sreadsect.h>
#include <readmultis.h>
#include <reboot.h>

wooing: .asciz "Woooo the nani,, the file has totally been read into memory\r\n"
FReadStr: .asciz "Totally Failed to read Sector\r\n"
RebootStr: .asciz "Press Any Key to Reboot.\r\n"
fileName: .ascii "STAGE2  BIN"
ffounds: .asciz "File found!\r\n"
notf: .asciz "File not found\r\n"
FailTRStr: .asciz "Failed to read\r\n"
SucReadStr: .asciz "Successfully read the disk\r\n"
WelcomeNote: .asciz "Hey hello, the second mbr is up\r\n"

ByPClust: .word 0x00,0x00
Root_dirStart: .byte 0,0  //LBA Location for the start of root dir
Root_dirSects: .byte 0,0 //Span of root dir in Sectors
Root_dirClusts: .byte 0,0
file_start: .byte 0,0