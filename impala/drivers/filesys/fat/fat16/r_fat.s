	.code32
//	.include "fs/fat16bpb.h"
//	.global
	.global readfat
	.global fat_tab
	.text

readfat:
  	//create the LBA location of FAT
	xor %eax,%eax
	xor %ebx,%ebx
	movw ResSects,%ax
	addw NHiddenSects,%eax
	
	/* eax is bearing LBA of FAT */
	mov %eax,lba
	movw SectsPFat,%bx
	cmp $0xff,%bx
	jl set_sectors
	sub $0x1,%bx
set_sectors:
	mov %ebx,sects_to_read
	xor %ebx,%ebx
	xor %eax,%eax
	xor %edx,%edx

	movw SectsPFat,%ax
	movw ByPSect,%bx

	mul %ebx

	//When debugging, check in register %edx incase we have missed any high bits
	push %eax
	push $fat_tab
	call rdsk

	add $0x8,%esp
	ret
	

	.data
fat_tab:	.space 131072, 0
