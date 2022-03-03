	.code32
	.global iopen
	.text

iopen:
	push %ebp
	mov %esp,%ebp

	//call filesystem to list for us the root directory for now
	//and then we check the root directory for our file

	call readfat
	call readrootdir

check_rootdir:
	


	xor %ecx,%ecx
	push %esi
	push %edi

	mov $11,%cx
	lea $0x8(%ebp),%edi
	lea (rootdir_mem),%esi
	//%ds:%esi -> rootdirmem
	//es:%edi -> search phrase on stack

	mov %ebp,%esp
	pop %ebp
	ret

	
