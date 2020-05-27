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


_start:

Welcome_Note:
	lea (LogoString),%si
	call PrintIt
	xor %si,%si
	lea (Welcom_str),%si
	call PrintIt

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

#include "g_idts.s"


hang:
	jmp hang
#include "check_a20.s"
#include "../printer.h"


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

PRamStat: .asciz "Ram A20 pin Active\r\n"
NRamStat: .asciz"Overlapped memory,,, Ram A20 pin not active\r\n"
LogoString: .asciz "\t\t\t\tCrane Bootloader\r\n"
Welcom_str: .asciz "\t\t\t\tWelcome......\r\n"
Enabld: .asciz "The a20 line function exists here and its working\r\n"
NotEn: .asciz "No bro that function maybe errored or it doesnt exist in this BIOS\r\n"
Proced: .asciz "Proceeding to Loading the Descriptors/Selectors\r\n"

/* THIS BELOW HERE IS THE .BSS SECTION KEEP CALM */

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
