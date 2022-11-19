	.code16
	.global main
	.text
	.org 0x00


main:
	jmp start
	nop
	/* If disk has no partition Include Fatbpb header bootloader program should take care of this*/

fatbpb:	
	/* below is if installed file system is FAT it requires a bpb */
	/* Else, this space  is blank or filled with zeros */
	.include "fatbpb.s"
	
prints:
	lodsb
	mov $0xe,%ah
	int $0x10		/* Print to monitor function */
	or %al,%al
	jnz prints
	ret


	New_MBR_Segment = 0x0900
	Code_Offset = 0x0
	
sectsPerTrack:		.word 0x0
totalHeads:		.word 0x0
driveNo:		.byte 0x0
maxTracks:		.word 0x0

start:
	cli
	mov %cs,%ax
	mov %ax,%ss
	mov %ax,%es
	mov %ax,%ds
	mov $0x7c00,%ax
	mov %ax,%sp
	sti

	mov %dl,driveNo		/* Save drive  number */	
	mov $New_MBR_Segment,%ax
	mov %ax,%es
	xor %ax,%ax
	xor %bx,%bx

	/*Query drive params */
	xor %ax,%ax
	mov $0x8,%ah
	int $0x13

	xor %bx,%bx
	mov %cl,%bl
	mov %dh,totalHeads
	and $0x3f,%bl		/* 6bits Maximum sector number */
	mov %bl,sectsPerTrack
	shr $0x6,%cl		/* cl - high 2 bits of max tracks */
	and $0x3,%cl		
	xchg %cl,%ch		/* ch - low 8bits max tracks */

	xor %ax,%ax
	mov $0x1,%ax		/* we are skipping one sector which has already been loaded in memory */

readsect:
	xor %dx,%dx
	xor %cx,%cx
	mov sectsPerTrack,%bx
	div %bx

	inc %dx		/* LBA mod sectsPerTrack + 1 */
	mov %dl,%cl
	
	
	xor %dx,%dx
	mov totalHeads,%bx
	div %bx

	xchg %dl,%dh	/* dh - HEAD (LBA/SPT) mod H */
	mov %al,%ch	/* ch cylinder */

	xor %bx,%bx
	mov $Code_Offset,%bx
	mov $New_MBR_Segment,%ax
	mov %ax,%es
	
	movb driveNo,%dl
	mov $0x0210,%ax		/*16 Sectors change this in future */

	int $0x13
	nop

	xor %dx,%dx
	mov driveNo,%dl		/* Save back drive number */


/* Prepare registers and jump */
	mov $New_MBR_Segment,%ax
	mov %ax,%es
	mov %ax,%ds
	ljmp $New_MBR_Segment,$Code_Offset

FailedToRead:
/*	lea (FReadStr),%si
	call PrintIt
	call RebootBIOS */

	
stopMBR:
	hlt	

FReadStr: .asciz "Totally Failed to read Sector\r\n"
RebootStr: .asciz "Press Any Key to Reboot.\r\n"
SucReadStr: .asciz "Successfully read the disk\r\n"

	.fill 446-(.-main),1,0
	
partitionTable:
	.include "ptable.s"

	.fill 64-(.-partitionTable),1,0
	
BootMagic: .word 0xaa55
