	push %es


//Lets set up the GDT

SetUp_GDT:
	//Size of a GDT selector is 8bytes/64bits
	//We gonna set it up at 0000:0800

	//The Null Selector first
	// es:di
	xor %cx,%cx
	mov $gdt_segment,%ax
	mov %ax,%es
	mov $gdt_offset,%di
	mov $0x4,%cx
	rep stosw 
//The Null selector is done

//I think our pointer of %es:%ds is  in the right position
//Now the code Section Selector
//We are assuming 2GB ram
//A page is 4KB (assumption)
	
//The Code Selector 

	movw $0x0000,%es:(%di)
	movw $0x0000,%es:0x2(%di)
	movb $0x00,%es:0x4(%di)
	movb $0x9a,%es:0x5(%di)
	movb $0xc8,%es:0x6(%di)
	movb $0x00,%es:0x7(%di)



	
	add $0x8,%di			//Move the pointer to the next free area
	
	//The Data Selector

	movw $0x0000,%es:(%di)
	movw $0x0000,%es:0x2(%di)
	movb $0x00,%es:0x4(%di)
	movb $0x92,%es:0x5(%di)
	movb $0xc8,%es:0x6(%di)
	movb $0x00,%es:0x7(%di)
	nop
//The data selector is done

//Soon in the future we will automate that above function to just drop a bunch of
//2byte registers inside that descriptor
	xor %cx,%cx

SetUp_IDT:
	//Hello IDT
	//at 0000:0000
	// %es:%di
	mov $idt_segment,%ax


	mov %ax,%es
	mov $idt_offset,%di
	mov $2048,%cx			//2048 bytes 2kb left for IDT lets fill the idt area with zeros for now
	rep stosb
	nop
//Done loading IDT
	
	pop %es

