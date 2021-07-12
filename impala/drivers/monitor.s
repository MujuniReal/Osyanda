.code32

VGA_ADDRESS = 0xb8000
VIDEO_CMD_PORT = 0x3d4
VIDEO_DATA_PORT = 0x3d5
MAX_COLUMNS = 80              /* maximum number of columns is 80 x axis */
MAX_ROWS = 25                 /* maximum number of rows 25 y axis */
TOTAL_PIXEL = 2000	    /* MAX_ROWS * MAX_COLUMNS */
DEFAULT_ATTRIBUTE = 0x0f      /* white on black, ie higher 4bits->background, lower 4bits-> text/cursor color */
SPACEBAR = 0x20
ATTRIB_SPACE = 0x0f20         /* attribute and character for this case spaces for clear screen 2bytes */
CURSOROFFSET_HI = 14
CURSOROFFSET_LO = 15

.text
.global clears
.global putc
.global puts
	//memsetw(uint16*, )
	//void clears(void);   clearscreen
	//function(3,2,1) -- calling convention
clears:
	xor %eax,%eax
	push $TOTAL_PIXEL
	movw $ATTRIB_SPACE,%ax   /* fill screen with spaces spaces is 0x20 thus clearing screen*/
	push %eax
	push $VGA_ADDRESS
	call memsetw
	add $0xc,%esp

	movw $0x0000,(cursr_pos)               /* After clearing screen, set cursor to 0,0 top left */
	call setcursor
	ret

	//void setcursor();

setcursor:
	xor %eax,%eax
	movb $CURSOROFFSET_HI,%al
	movw $VIDEO_CMD_PORT,%dx
	outb %al,(%dx)
	movw (cursr_pos),%ax
	xchg %ah,%al
	movw $VIDEO_DATA_PORT,%dx
	outb %al,(%dx)			  /* high byte for cursor location */

	movb $CURSOROFFSET_LO,%al
	movw $VIDEO_CMD_PORT,%dx
	outb %al,(%dx)
	movw (cursr_pos),%ax
	movw $VIDEO_DATA_PORT,%dx
	outb %al,(%dx)			  /* low byte for cursor location */
	/* cursor location y = overall location / 80, x = overall location mod 80 */
	ret


getcursor:


scroll:
	/* This function here adds us one row below our final row, ie moving everything already printed one row up */
	/* Since the VGA memory holds 2 bytes per printed character, we are going to drop a movsw */
	xor %eax,%eax
	xor %ecx,%ecx
	push %esi
	push %edi

	
	lea VGA_ADDRESS,%edi
	lea VGA_ADDRESS,%esi
	add $160,%esi
	movw $TOTAL_PIXEL,%ax
	sub $MAX_COLUMNS,%ax
	mov %ax,%cx
	//mov $MAX_COLUMNS,%ecx		/* since we are adding one row down,, it might as well be adding one full line of empty columns,just line a new line */
	repnz movsw

	/* clear the whole row possesing left out characters from previous print */
	movw $80,%cx			/* clear the whole row, at this point, %edi is pointing to the current byte after the above string action */
	movw $ATTRIB_SPACE,%ax
	repnz stosw
	
	movw $1920,(cursr_pos)
	call setcursor

	
	pop %edi
	pop %esi
	ret
	
putc:
	/* procedure for putc,
	get current cursor position and save it
	check if it needs to clear screen check whether 80*25 is reached
	*/
	movw $TOTAL_PIXEL,%dx
	cmp (cursr_pos),%dx
	jnz printc
	call scroll

	printc:
		/* Prepare registers for multiplication result for multiplication %edx:%eax */
		xor %eax,%eax
		xor %ebx,%ebx
		xor %edx,%edx
		movw $VGA_ADDRESS,%di

		/* find cursor location in VGA remember in vga 2 bytes are stored for each character */
		movw $0x2,%bx
		movw (cursr_pos),%ax
		mulw %bx

		add %ax,%di 						/* Cursor position in VGA */
		
		xor %ax,%ax
		movb 0x4(%esp),%al
		movb $DEFAULT_ATTRIBUTE,%ah
		stosw								/* Print the character */
		//movw %ax,(VGA_ADDRESS)			/* Print the character */
	
	setcursor_next:	
	/* after priting anything we set the cursor to the next place */
	add $0x1,(cursr_pos)
	call setcursor
	ret
	

puts:
	/* cater for length of the string which will deal with our looping counter ecx */
	xor %eax,%eax
	mov 0x4(%esp),%esi

	next_char:
		lodsb
		cmp $0x0,%al
		jz endputs
							/* some more checks for the character inserted
		   						like we would want tab to leave 4 spaces, newline to take you to a new y axis
		   					enter/ carriage return to take you to a new y axis
							   all those special functions are to set/control the cursor
							   so they will be in need of the setcursor function
							*/
		cmp $0x1f,%al						/* Following the ascii table All the special characters of tab,delete,return,new line are below 0x1f */
		jg cont_puts
		push %eax
		call handle_special_chars			/* Those special ones that control the cursor are below 0x1f in the ascii */
		pop %eax
		jmp next_char						/* Load next character in the string */

	cont_puts:
		push %eax
		call putc
		pop %eax
		jmp next_char

	endputs:
		ret

handle_special_chars:
	/* will handle whether putting four spaces for tab will handle for both cursor or VGA tube */
	movb 0x4(%esp),%al

	tab_char:
		cmp $0x09,%al			/* for horizontal tab '\t' */
		jnz newline_char		/* jump to check for newline character */
		add $0x4,(cursr_pos)	/* move cursor to four spaces ahead */
		call setcursor
		ret						/* exits function */

	newline_char:
		cmp $0x0a,%al				/* for newline '\n' */
		jnz endspchr
		xor %eax,%eax
		xor %ebx,%ebx
		xor %edx,%edx
		
		movw (cursr_pos),%ax
		movb $MAX_COLUMNS,%bl		/* we get the y axis from the x axis from the columns,, a complete column represents one complete row */
		divw %bx					/* remember %ax:%dx %ax-quotient %dx - remainder */

		push %edx
		inc %ax
		mulw %bx
		pop %edx
		movw %ax,(cursr_pos)
		call setcursor


		/* this ones increaments the y axis how to get y axis is cursr_pos / 80 */
		/* the quotient is y axis and remainder is x axis,, */
		/* plan is  increment quotient by one, multiply quotient with 80 and add the initial remainder from the first division and set new cursor position */



	
	endspchr:
		ret

.data

cursr_pos:
	x: .byte 0x0    /* lower byte for cursor location */
	y: .byte 0x0    /* higher byte for cursor location */
