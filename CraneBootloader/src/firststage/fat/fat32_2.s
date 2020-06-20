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
//fatpackloc = 0xee0
/*
fatpacket:
		.byte 0x10
		.byte 0x00
		.word 0x8		 we are going to load the first cluster of the fat table 
		.int 0xee0			 fat segment:offset organised in little indian 
		.int 0x20
		.int 0x00	*/

start_mbr2:
	sti
/* Set text mode with monochrome colors */
	xor %ax,%ax
    mov $0x00,%ah
    mov $0x07,%al    /* 0x7 for text mode with monochrome colors */
    int $0x10


	lea (WelcomeNote),%si
	call PrintIt


/*initialize hardisk controller */
	xor %ax,%ax
	xor %dx,%dx
	movb LogDrvNo,%dl
	mov $0x9,%ah
	int $0x13
	nop



/* Query for disk parameters */
	xor %ax,%ax
	xor %bx,%bx
	xor %cx,%cx
	xor %dx,%dx


	mov $0x8,%ah
	movb LogDrvNo,%dl
	int $0x13

	nop

	and $0x3f,%cl
	xor %ch,%ch
	mov %cx,SectsPTrck

	xor %dl,%dl
	xchg %dh,%dl
	mov %dx,NHeads	


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
	//movw SectsPFathi,%dx
	test $0xffff,%dx
	jnz FAT_is32		/* check whether the size of sectors in fat span 32bits */

	/* enable extended functions */
	xor %ax,%ax
	xor %dx,%dx

	mov $0x41,%ah
	mov $0x55aa,%bx
	movb LogDrvNo,%dl
	int $0x13



load_fat:
	xor %si,%si
	xor %ax,%ax
	lea (fatpacket),%si
	mov $fatsegment,%ax
	mov %ax,%es
	
	xor %ax,%ax
	xor %dx,%dx
	mov $0x42,%ah
	movb LogDrvNo,%dl
	int $0x13


	xor %ax,%ax
prepare_to_load_root_dir:	
	mov $tmprootdirseg,%ax
	mov %ax,%es
	xor %bx,%bx

load_rootdir:
	xor %ax,%ax
	xor %si,%si
	lea (rootdpacket),%si
	mov $0x42,%ah
	movb LogDrvNo,%dl
	int $0x13

lookthru_rootdir:
	mov $0x000b,%cx
	lea (%bx),%di
	lea (fileName),%si 
	repz cmpsb
	je File_Found
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
#include <lreadsect.h>
#include <reboot.h>


fatpacket:
	.byte 0x10
	.byte 0x00
	.word 0x0008
	.int 0x0ee00000			 /* segment:offset -> 0x0ee0:0x0000 -> 0x0ee00000 */
	.int 0x20
	.int 0x00

	
rootdpacket:
	.byte 0x10
	.byte 0x00
	.word 0x0008
	.int 0x10000000			/* segment:offset -> 0x1000:0x0000 -> 0x10000000 */
	.int 0x7fe0
	.int 0x00


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

diskaddrpkt:
	.byte 0x00
	.byte 0x00
	.word 0x0000
	.int 0x00000000
	.int 0x00000000
	.int 0x00000000