	.code32
	.global terminal
	.global prompt_str
	.text

terminal:
	jmp term
	
prompt_str:	.asciz "impala> "

	
term:
	push %edi
	lea (kybd_buff),%edi
	
start_pro:	
	push $prompt_str
	call puts
	add $0x4,%esp
read_aga:	
	call read_kybd

	cmp $0x0d,%al
	jz prt_buff
	stosb
	jmp read_aga


prt_buff:
	push $kybd_buff
	call puts
	add $0x4,%esp
	nop
	nop

	ret
	.data
kybd_buff:	.byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0


