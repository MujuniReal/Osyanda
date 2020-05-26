.code16
.text
.org 0x00
.global mainSecond


mainSecond:
	jmp _start
	nop

#include "fatstruct.h"

_start:

Welcome_Note:
	lea (LogoString),%si
	call PrintIt
	xor %si,%si
	lea (Welcom_str),%si
	call PrintIt

/*	Copy the old bytes of the Fat Structure of the old MBR,
	this is done to help catch the variables that were updates, overwriting,
	and modifying the fat table that lives in the second stage bootloader
	which is what we need,, updated variables
*/


Copy_old_variables:
	push %ds	//Save data segment on stack

	xor %ax,%ax
	mov %ax,%es
	mov %ax,%ds
	//variable from header file fatstruct.h
	lea (FATstruct),%di
	lea 0x7c03,%si
	mov $0x0022,%cx
	//copy the 32bytes from %ds:%si to %es:%di
	rep movsb

	pop %ds
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

*/
	push %ds
//Lets set up the GDT
SetUp_GDT:
	//Size of a GDT selector is 8bytes/64bits
	//We gonna set it up at 0000:0800

	//The Null Selector first
	// es:di
	xor %ax,%ax
	mov %ax,%es
	xor %si,%si
	mov $0x0800,%ax
	mov %ax,%di
	mov $0x4,%cx
	rep movsw	//we gonna move 2bytes four times to the area 0x0800 

//The Null selector is done

//I think our pointer of %es:%ds is  in the right position
//Now the code Section Selector
//We are assuming 2GB ram
//A page is 4KB (assumption)
	pop %ds
	movw $0xffff,%es:(%di)
	movw $0x0000,%es:(%di)
	movb $0x00,%es:(%di)
	movb $0x92,%es:(%di)
	movb $0xc7,%es:(%di)
	movb $0x00,%es:(%di)

//The Code Selector is done
//Now to the Data Selector
	
	add $0x8,%di		//Add the 8bytes to point to a fresh area for the code descriptor

	movw $0xffff,%es:(%di)
	movw $0x0000,%es:(%di)
	movb $0x00,%es:(%di)
	movb $0x92,%es:(%di)
	movb $0xc7,%es:(%di)
	movb $0x00,%es:(%di)

//The data selector is done

//Soon in the future we will automate that above function to just drop a bunch of
//2byte registers inside that descriptor

	push %ds
SetUp_IDT:
	//Hello IDT
	//at 0000:0000
	// %es:%di
	xor %ax,%ax
	mov %ax,%es
	mov %ax,%di
	mov $2048,%cx	//2048 bytes 2kb left for IDT
	rep movsb

//Done loading IDT
	pop %ds

/*  Test the presence of the A20 port/pin
Testing for overwrapping 
okay the code below here is writing to some place in memory
this space is dominated by the IDT so keep note */

	pushf
	push %ds
	push %es
	
	//es:bx initially
	mov $0x0000,%ax
	mov %ax,%es
	mov $0x0500,%bx
	movb $0xfb,%es:(%bx)
	
	//%ds:%si After writing
	mov $0xffff,%dx
	mov %dx,%ds
	mov $0x0510,%ax
	mov %ax,%si
	movb $0xe6,%ds:(%si)
	xor %ax,%ax
	mov %es:(%bx),%al

        pop %es
        pop %ds
        popf

	nop
	cmp $0xe6,%al
	jz PinNot

PinYes:
	xor %si,%si
        lea (PRamStat),%si
        call PrintIt
	jmp hang

PinNot:
	xor %si,%si
	lea (NRamStat),%si
	call PrintIt

/*
	xor %ax,%ax
	mov $0x2401,%ax
	int $0x15
	jc nope
	lea (Enabld),%si
	call PrintIt 
	jmp hang

nope:
	lea (NotEn),%si
	call PrintIt	*/
hang:
	jmp hang

#include "printer.h"


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

