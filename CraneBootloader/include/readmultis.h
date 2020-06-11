/* readmultis stands for read multi sectors */

/* it depends on sreadsect.h */

/* this below here is our popular function to manage the read of clusters,
 it caters for %ax as the start of to read sectors ,%cx as the counter of the sectors in a cluster 
 and bx as the %es:%bx pair relation */

 /* make sure you have prepared %ax, %es:%bx and %cx */

 .func ReadMulti

 ReadMulti:

readmulti:
	push %cx
	call ReadSect
	cmp $0x0,%cx
	jz FailedToRead     /* Am gonna make this a popular function to work for fat12 too */
	pop %cx
	inc %ax
	add ByPSect,%bx
	loopnz readmulti

    retw

.endfunc