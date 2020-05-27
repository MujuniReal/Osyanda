start of second stage bootloader 0x10000

1) debugging copying old bootloader code to new
	u 0x7c00 0x10164
	u 0x10000 0x10164
	at around 10053 find your _start function

2)debugging the gdt code:
	u 0x10000 0x101b1

break points 10029 1002f 10034 10039 1003e 10043 
