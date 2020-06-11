.code16
.text
.org 0x0
.global main_mbr2

//this header file below here is for a 1.4MB floppy disk formatted with FAT
//Fat formated with MBR not GPT

main_mbr2:
	cli

#include <fat/fat32mbr.h>


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

	xor %dx,%dx
	movw SectsPFathi,%dx
	test $0xffff,%dx
	jnz FAT_is32		/* check whether the size of sectors in fat span 32bits */

	xor %ax,%ax

load_fat:
	mov $fatsegment,%ax
	mov %ax,%es

	mov ResSects,%ax
	add NHiddenSects,%ax		/*acquiring the location of the fat */
	mov NhiddnSectshi,%dx
	test $0xffff,%dx
	jnz FAT_is32

	xor %bx,%bx
	xor %cx,%cx
	mov SectPClust,%cl			/* we need to give this a fail safe incase it has still not found the file from this available few fat sectors */
	call ReadMulti				/* we will load one cluster of FAT at a time */
	
	xor %dx,%dx
	mov LogDrvNo,%dl
	xor %ax,%ax
	int $0x13
	
prepare_to_load_root_dir:
	mov Root_dirStartClustlo,%cx

load_rootdir:
	mov $tmprootdirseg,%ax
	mov %ax,%es

	xor %bx,%bx
	xor %dx,%dx
	mov SectsPFat,%ax
	mov FatTabs,%bl
	mul %bx
	add ResSects,%ax
	mov Root_dirStartClusthi,%dx
	test $0xffff,%dx
	jnz FAT_is32
	xor %bx,%bx

	add %cx,%ax
	//sub $0x2,%ax
	push %cx
	xor %cx,%cx
	movb SectPClust,%cl
	call ReadMulti			/* load the first cluster of the root directory */
	pop %cx
	xor %bx,%bx

lookthru_rootdir:
	push %cx
	mov $0x000b,%cx
	lea (%bx),%di
	lea (fileName),%si
	repz cmpsb
	je File_Found
	pop %cx
	add $0x20,%bx
	cmp ByPClust,%bx
	jz check_ifnext_rootdirclust
	jmp lookthru_rootdir

check_ifnext_rootdirclust:
	push %ds
	mov $fatsegment,%dx
	mov %dx,%ds
	xor %bx,%bx				/* prepare registers for multiplication */
	xor %dx,%dx		
	mov $0x4,%bx			/* displacement of location of fat entry */
	mov %cx,%ax
	mul %bx
	test $0xffff,%dx
	jz FAT_is32
	mov %ax,%si
	movw %ds:(%si),%ax		/* low word of next cluster */
	movw %ds:0x2(%si),%dx	/* high word of next cluster */
	cmp $0xfff8,%ax
	jge file_not_found
	cmp $0xffff,%dx
	jz Bad_Clust
	/* else part is we leave %dx as it is coz its gonna make sense in the pair of %dx:%ax for the read long sector */
	mov %ax,%cx
	pop %ds
	jmp load_rootdir
	
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
	lea (well),%si
	call PrintIt



	
/* Save the acquired variables 
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
	*/

FinishProgram:
	jmp FinishProgram

FAT_is32:
	lea (Fatspan32str),%si
	call PrintIt
	call RebootBIOS

Bad_Clust:
	lea (badcstr),%si
	call PrintIt
	call RebootBIOS

FailedToRead:
	lea (FReadStr),%si
	call PrintIt
	call RebootBIOS /*this code can never go below here unless otherwise */


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
Fatspan32str: .asciz "The span of sectors in one fat table is a 32bit value\r\n"
badcstr: .asciz "Bad cluster sister/brother\r\n"
well: .asciz "Well, everything has worked out just fine upto this point\r\n"

ByPClust: .word 0x00,0x00
Root_dirStart: .byte 0,0  //LBA Location for the start of root dir
Root_dirSects: .byte 0,0 //Span of root dir in Sectors
Root_dirClusts: .byte 0,0
file_start: .byte 0,0