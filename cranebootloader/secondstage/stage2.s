
	.code16
	.section gnuasm
	.global mainSecond
	.global driveNo
	.global totalHeads
	.global sectsPerTrack
	.global maxTracks
	.text
	.org 0x00

mainSecond:
	jmp _start
	nop

	.include "fatbpb.s"
	
sectsPerTrack:		.word 0x0
totalHeads:		.word 0x0
driveNo:		.byte 0x0
maxTracks:		.word 0x0

Root_dirSects: .word 0x0000
Root_dirStart: .word 0x0000


_start:
	mov %dl,driveNo
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
	mov %cx,maxTracks

	call crane_main

_hang:
	jmp _hang

.fill 512-(.-mainSecond),1,0