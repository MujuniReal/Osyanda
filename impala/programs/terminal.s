	.code32
	.global terminal
	.global prompt_str
	.text

terminal:
	jmp term
	
prompt_str:	.asciz "impala> "
available_commands: .asciz "ls"
	.asciz "cd"
	.asciz "mkdir"
found_str:	.asciz "Found command !!!!!!!!!!!\n"
n_found:	.asciz "Command not found."

	
term:
//	push %edi
	//	lea (kybd_buff),%edi
	push $0x0a
	call putc
	call putc
	add $0x4,%esp
	
start_pro:	
	push $prompt_str
	call puts
	add $0x4,%esp
	/* %ecx to store the length of the buffered string */
	xor %ecx,%ecx
	push %ecx
read_aga:	
	call read_kybd

	cmp $0x0d,%al	/* If enter has been pressed */
	jnz proceed_c 	

exec_cmd:
	/* Just Call the function The ecx Register is already on the stack */
	call cmd_str_checker
	jmp start_pro	/* Bring back prompt */
proceed_c:	
	cmp $0x00,%al	
	jz read_aga	/* Read more byte if byte not found in map*/
	//	stosb
	//Store byte so that we make sense of it
	pop %ecx
	push %edi
	lea (kybd_buff),%edi
	add %ecx,%edi
	stosb
	inc %ecx
	pop %edi
	push %ecx
	jmp read_aga	/* Read again another byte from Keyboard */

cmd_str_checker:
	/* This first checks the length of the issued command
	Which is passed as an arguement when calling the function */
	mov 0x4(%esp),%ecx /* Length */
	
	push %esi
	push %edi
	lea (kybd_buff),%edi
	lea (available_commands),%esi
cmp_strs:
	nop
	nop
	repz cmpsb
	je cmd_found
	/* Else check if available commands list has reached the end
	if yes, command not found if not call this function again
	making it a recursive function */
	mov 0xc(%esp),%ecx
	jmp cmp_strs

cmd_found:
	pop %edi
	pop %esi
	push $found_str
	call puts
	add $0x4,%esp
	ret

prt_buff:
//	push $kybd_buff
//	call puts
//	add $0x4,%esp
	nop
	nop

	ret
	.data
kybd_buff:	.byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0
