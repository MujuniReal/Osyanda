.code16
.text
.org 0x00
.global mainSecond


gdt_segment = 0x0000
gdt_offset = 0x0800

idt_segment = 0x0000
idt_offset = 0x0000

mainSecond:
	jmp _start
	nop

#include <fat/fat16mbr.h>

Root_dirSects: .word 0x0000
Root_dirStart: .word 0x0000
FS_Flag: .byte 0x00				/* 1 is set if filestytem is fat */

impalaseg = 0x6000
tmprootdirsegment = 0x5000
fatsegment = 0x2000

_start:

Welcome_Note:
	lea (LogoString),%si
	call PrintIt
	xor %si,%si
	lea (Welcom_str),%si
	call PrintIt


	/* Looking for and loading the kernel file into memory */
	//xor %dx,%dx

	//movb LogDrvNo,%dl

	//xor %ax,%ax
	//int $0x13		//Reset the disk and we try again
	

	mov $tmprootdirsegment,%ax
	mov %ax,%es
	xor %cx,%cx
	xor %bx,%bx


read_next_rdir_sect:

	cmp Root_dirSects,%cx
	jz file_not_found
	xor %ax,%ax
	mov Root_dirStart,%ax	//LBA Format
	add %cx,%ax
	push %cx
	call ReadSect
	pop %cx
	inc %cx

getFilename:
	push %cx
	mov $0x000b,%cx			/* fat12 and 16 support only filenames of 11Bytes */
	lea (%bx),%di
	lea (kernelfilename),%si		/* compare %es:%di and %ds:%si */
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
	jmp hang

	
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
	xor %bx,%bx
	mov SectsPFat,%cx
	call ReadMulti


	xor %bx,%bx
	mov $impalaseg,%ax
	mov %ax,%es
	mov file_start,%cx

read_file_nextinline_sector:
	//todo: this below will work as loading dots
	lea (read_times),%si
	call PrintIt

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
	jge done_readingkernel
read_next_file_cluster:
	mov %dx,%cx
	/*bytes per cluster is whats needed to increament %bx even up there where we load root dir and fatsegment dont forget */
	jmp read_file_nextinline_sector

done_readingkernel:
/*
	IN ORDER TO GET THIS SYSTEM IN PROTECTED MODE eg. 32BIT
		   WE ARE GOING TO DO THE FOLLOWING
		1) Set up the GDT
			a) The three selectors of the GDT
				i) Null Selector	(filled with zeros only)
				ii) Code Section Selector
				iii) Data Section Selector
			b) Let the CPU know where the GDT is
		2) Setup the IDT
			a)Let this space be filled with zeros for now for 2KB space
			at real address 0x0000
			b)Let the CPU know where the IDT is
		3) Enable the A20 Line (Enabling the 21st address pin of the RAM)
		Inorder to inturn activate the above pins of RAM
		4)Setup and organise the CR0 resgisters the control registers
		5)Jump to the kernel
Test the presence of the A20 port/pin
Testing for overwrapping 
okay the code below here is writing to some place in memory
this space is dominated by the IDT so keep note  */


A20_pincheck:
	call TestA20pin
	nop
	cmp $0x1,%al
	jz LOADGDT_IDT			//A20Pin active so we proceed to Loading Selectors
	//code to activate A20PIN
	jmp hang


LOADGDT_IDT:
	lea (Proced),%si
	call PrintIt
//initialize the GDT and IDT into memory
#include <g_idts.s>

	lgdt GDT		//The CPU now knows the location of the descriptors
	lidt IDT

/* This part here below is of control Registers especially th cr0 register
   Bit with index zero or the first bit is the one whereby if its 1 then it shows
   that we are in protected mode,, bitname PE Protected mode Enabled
   %cr0 is a 32bit register/it is as heavy as 32bits
*/
	xor %eax,%eax
	mov %cr0,%eax
	or $0x1,%eax
	mov %eax,%cr0

/* Initialize the segment registers to point to the data descriptor from the GDT
   this time we are not specifying the whole segment:offset thingi we are just gonna
   put the descriptors' offset in the segments
	%es, %ds, %fs, %gs, %ss from the GDT data's offset is 0x10 sixteen
*/
	xor %ax,%ax
	mov $0x10,%ax
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%gs
	mov %ax,%fs
	mov %ax,%ss
	mov $0x2ffff,%esp	/* we are already in 32bit mode  stack starts from 0x30000 growing downwards */
	

/* one more step left too enter 32bit protected mode that is cllearing the
   prefetch Queue,, the 16bits would have been fetched instructions to go away from
   the CPU 
*/
	jmp clear_the_fetchqueue
	nop
	nop
	nop
clear_the_fetchqueue:

/* Cool now make the Jump to the kernel 
   In oeder to make this jump the jump is a 32bit instruction and
   Our compiler and 16bit assembler didnt have it,, so we just gonna hand code
   The encoded 32bit instructions for the 32bit jump
*/

	.byte 0x66
	.byte 0xea		/* 32bit jump instruction */
	.int 0x60000		/* segment where kernel is loaded */
	.word 0x0008 		/* Code Selector from gdt */

FailedToRead:
	lea (FReadStr),%si
	call PrintIt
	 /*this code can never go below here unless otherwise */

hang:
	jmp hang
/* Ive decided to put the reusable functions below here */

#include <check_a20.s>

/* #include "activate_a20.s" 
#include <sreadsect.h>
#include
/*
		 THIS BELOW HERE IS THE .DATA SECTION KEEP CALM
*/

GDT:
	//the GDT pointer
	.word 24	//Limit or size of GDT
	.int 0x800 	//Base location of GDT

IDT:
	.word 2048	//Limit or size of IDT
	.int 0x0	//Base location of IDT

#include <printer.h>
#include <sreadsect.h>
#include <readmultis.h>
kernelfilename: .ascii  "IMPALA  IMG"

read_times: .asciz "Loading kernel progres\r\n"
PRamStat: .asciz "Ram A20 pin Active\r\n"
NRamStat: .asciz "Overlapped memory,,, Ram A20 pin not active\r\n"
FReadStr: .asciz "Failed to read kernel Sector\r\n"
LogoString: .asciz "\t\t\t\tCrane Bootloader\r\n"
Welcom_str: .asciz "\t\t\t\tWelcome......\r\n"
Enabld: .asciz "The a20 line function exists here and its working\r\n"
NotEn: .asciz "No bro that function maybe errored or it doesnt exist in this BIOS\r\n"
Proced: .asciz "Proceeding to Loading the Descriptors/Selectors\r\n"
notf: .asciz "Kernel not Found.\r\n"
ffounds: .asciz "Kernel Found !!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n"
SucReadStr: .asciz "Successfully read the disk\r\n"

/* THIS BELOW HERE IS THE .BSS SECTION KEEP CALM */
//Root_dirStart: .byte 0,0
//Root_dirSects: Root_dirSects: .byte 0,0
file_start: .byte 0,0

/*	Copy the old bytes of the Fat Structure of the old MBR,
	this is done to help catch the variables that were updates, overwriting,
	and modifying the fat table that lives in the second stage bootloader
	which is what we need,, updated variables
*/

/* We are going to put this functionality in an uninitialized space coz
already made runtime code isnot re-writable
Copy_old_variables:
	push %ds	//Save data segment on stack
	xor %ax,%ax
	mov %ax,%es
	mov %ax,%ds
	//variable from header file fatstruct.h
	lea FATstruct,%di
	mov $0x7c03,%si
	xor %cx,%cx
	mov $0x22,%cx
	//copy the 32bytes from %ds:%si to %es:%di
	rep movsb
	
	xor %dx,%dx
	movb %es:(0x0000),%dl
	nop
	pop %ds */