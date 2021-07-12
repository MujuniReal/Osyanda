.code32
.include "macros/port.h"	
.text
.global _read_ps2_config
	
_read_ps2_config:
	outportb 0xf5 0x64
	nop
	nop
	nop
	inportb 0x64
	nop
	inportb 0x60
	nop
	
	outportb 0xf2 0x64
	nop
	nop
	nop
	inportb 0x64
	nop
	inportb 0x60
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	inportb 0x64
	nop
	inportb 0x60
	nop
	
	ret
