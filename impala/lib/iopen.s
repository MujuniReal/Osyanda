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

check_rootir:
	
	

	mov %ebp,%esp
	pop %ebp
	ret

	
