.code16

.text
.org 0x00
.global main

main:
	jmp start
	nop

//this header file below here is for a 1.4MB floppy disk formatted with FAT
//Fat formated with MBR not GPT

#include <fat/fat32mbr.h>

New_MBR_Segment = 0x0900 /*we have to plan for this segment in the book */
New_MBR_Segment_withcode = 0x0920	/* New_MBR_Segment + 512 bytes because of fat32 */
CLI_instruction = 1  /*Size of the cli instruction is one byte in 16bit assembly this instruction is for security*/
OEM_Size = 8		/* OEM manufacturer string 8bytes */	
BIOS_PB = 25		/* The first 26bytes of the BIOS parameter block next to it is the Logical drive number*/
ExtendedBIOS_PB = 26 /* Size of Extended BIOS parameter block Definately after this is our code of the _start function */
Code_Offset = (CLI_instruction + OEM_Size + BIOS_PB + ExtendedBIOS_PB) - 1 /* this is where the actual code lives minus 1 since we start counting from zero debugging required here*/


#define LogDrvNo_New  0x3e 	/* location of the new logdrvno in hexadecimal variable CLI_instruction + OEM_Size + BIOS_PB */

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
	
	mov $New_MBR_Segment,%ax
	mov %ax,%es
	xor %ax,%ax
	xor %bx,%bx
	mov $0x1,%ax		/* we are skipping one sector which has already been loaded in memory */

/* Take caution that the function below is gonna load all 16 sectors the very first sector
0 is missing coz the BIOS had automatically loaded it, so take caution that one more extra
Sector that belongs to the FAT has been loaded too basing on how our readsect function has
worked in FAT16 mode */
	xor %cx,%cx
	mov SectPClust,%cl
	sub $0x1,%cx		/* Minus one because the bios had already loaded the first sector */
	call ReadMulti

	/* Save the Logical drive number we have earned after booting to the new loaded MBR*/
	xor %dx,%dx
	mov LogDrvNo,%dl
	xor %bx,%bx			/* Make %bx point back to home */
	mov $New_MBR_Segment_withcode,%ax
	mov %ax,%es
	movb %dl,%es:LogDrvNo_New(%bx)	/* this location has to change coz of the location in fat32 */

/* Prepare registers and jump */
	mov $New_MBR_Segment,%ax
	mov %ax,%es
	mov %ax,%ds
	ljmp $New_MBR_Segment_withcode,$Code_Offset

FailedToRead:
	lea (FReadStr),%si
	call PrintIt
	call RebootBIOS /*this code can never go below here unless otherwise */

	
stopMBR:
	hlt	

#include <sreadsect.h>
#include <readmultis.h>
#include <printer.h>
#include <reboot.h>

FReadStr: .asciz "Totally Failed to read Sector\r\n"
RebootStr: .asciz "Press Any Key to Reboot.\r\n"
SucReadStr: .asciz "Successfully read the disk\r\n"

.fill 510-(.-main),1,0
BootMagic: .word 0xaa55