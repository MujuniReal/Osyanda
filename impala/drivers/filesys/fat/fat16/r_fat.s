	.code32
	.include "fs/fat16bpb.h"
//	.global
	.global readfat
	.global fat_tab
	.text

readfat:
	//create the LBA location of FAT
	xor %eax,%eax
	xor %ebx,%ebx
	mov ResSects,%eax
	add NhHiddenSects,%eax
	
	/* eax is bearing LBA of FAT */
	mov %eax,lba
	mov SectsPFat,%ebx
	mov %ebx,sects_to_read

	xor %ebx,%ebx
	xor %eax,%eax
	xor %edx,%edx

	mov SectsPFat,%eax
	mov ByPsect,%ebx

	mul %ebx

	//When debugging, check in register %edx incase we have missed any high bits
	push %eax
	push fat_tab
	call rdsk

	add $0x8,%esp
	ret
	

	.data
fat_tab:	.space 131072, 0
