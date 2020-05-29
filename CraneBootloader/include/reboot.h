/* this file contains magic numbers to reboot the system */


.func RebootBIOS
RebootBIOS:
	lea (RebootStr),%si
	call PrintIt
	xor %ax,%ax
	int $0x16	/* Waits for input from keyboard */
	.byte 0xea
	.word 0x0000
	.word 0xffff
.endfunc