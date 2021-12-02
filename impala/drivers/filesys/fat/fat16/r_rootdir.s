	.code32
//	.include "fs/fat16bpb.h"
//	.global
	.global readrootdir
	.global rootdir_mem
	.global rootdir_start
	.text

readrootdir:
	xor %eax,%eax
	xor %ebx,%ebx
	xor %edx,%edx

	movw SectsPFat,%ax
	movb FatTabs,%bx
	mul %ebx

	addw ResSects,%eax
	addw NHiddenSects,%eax
	/* %eax has the start of the root directory */
	mov %eax,lba
	mov %eax,rootdir_start

	xor %eax,%eax
	movw NRootDirEs,%ax
	mov $ROOTDIRENTRYSZ,%ebx

	mul %ebx

	/* %eax has number of bytes occupied by root directory */
	push %eax
	movw ByPSect,%bx

	div %ebx

	/* %eax has total sectors occupied by the root directory */
	
	mov %eax,sects_to_read
	push $rootdir_mem
	call rdsk

	add $0x8,%esp
	
	ret
	

	.data
//Total size occupied by rootdirectory in bytes	
rootdir_mem:	.space 16384, 0		
rootdir_start:	.int 0x0
