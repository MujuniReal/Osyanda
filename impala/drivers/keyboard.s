	.code32
	.include "macros/port.h"

	KYBD_CMD = 0x60
	KYBD_DATA = 0x60
	KYBD_STAT = 0x64
	
	CMD_ACK = 0xfa
	RESEND_CMD = 0xfe
	ECHO_RESP = 0xee
	SELFTEST_PASS = 0xaa

	KYBD_SCAN_OFF = 0xf5
	KYBD_SCAN_ON = 0xf4

	
	.text
	.global init_keyboard
	
init_keyboard:	

	/* Turn off Keyboard scanning */
	push $0x2			/* To check whether bit 1 allows us to send command to the keyboard*/
	push $KYBD_STAT
	call wait_for_write_kybd
	add $0x8,%esp

	/* Only if the keyboard controller is ready to receive commands */
	
	outportb KYBD_SCAN_OFF KYBD_CMD

	push $CMD_ACK		/* Wait for acknowlegement from data port */
	push $KYBD_DATA		/* Port to wait acknowledgement on */
	call wait_kybd_stat
	add $0x8,%esp
	

	/* Turn off Keyboard scanning */
	push $0x2			/* To check whether bit 1 allows us to send command to the keyboard*/
	push $KYBD_STAT
	call wait_for_write_kybd
	add $0x8,%esp

	/* Turn on Keyboard Scanning */
	/* Only if controller is ready to receive commands */
	outportb KYBD_SCAN_ON KYBD_CMD
	
	push $CMD_ACK		/* Wait for acknowlegement from data port */
	push $KYBD_DATA		/* Port to wait acknowledgement on */
	call wait_kybd_stat
	add $0x8,%esp
	
	push $succ_msg_keybd
	call puts
	add $0x4,%esp



	
get_key:
	inportb KYBD_DATA
	cmp $0xfa,%al
	jz get_key


	push %eax
wait_key_b:
	inportb KYBD_DATA
	pop %ebx
	push %ebx
	cmp %al,%bl
	jz wait_key_b
	
	pop %eax
	push %eax
	push %edi
	mov $asci_keys,%edi
	add %eax,%edi
	xor %eax,%eax
	movb (%edi),%al
	pop %edi
	push %eax
	call putc
	add $0x4,%esp
	pop %eax		/* old character from kybd */
	push %eax

read_more:
	inportb KYBD_DATA
	pop %ebx
	push %ebx
	cmp %al,%bl
	jz read_more

	add $0x4,%esp
	push %eax

read_other_scaned:
	inportb KYBD_DATA
	pop %ebx
	push %ebx
	cmp %al,%bl
	jz read_other_scaned

	pop %eax
	push %eax
	push %edi
	mov $asci_keys,%edi
	add %eax,%edi
	xor %eax,%eax
	movb (%edi),%al
	pop %edi
	push %eax
	call putc
	add $0x4,%esp
	pop %eax
	push %eax
	jmp read_more
	

	
keyboard_program:
	




end_init_keyboard:	
	ret

	

	.func wait_kybd_stat

//wait_kybd(source port, data to wait for)	
wait_kybd_stat:
	movb 0x8(%esp),%bl	/* Data to wait for */
	movw 0x4(%esp),%dx	/* Port to bring in data from */
	
check_indata:	
	inb (%dx),%al
	cmp %bl,%al
	jnz check_indata

end_wait_kyb_stat:
	ret

	.endfunc


	
	.func wait_for_write_kybd
	
//wait_for_write_kybd(source port, test bit)
wait_for_write_kybd:
	movb 0x8(%esp),%bl	/* Bit to check for in received data */
	movw 0x4(%esp),%dx	/* Port address */

wait_for_bit:
	inb (%dx),%al
	test %bl,%al
	jnz wait_for_bit

end_wait_for_write_kybd:
	ret

	.endfunc


	.data

succ_msg_keybd:	.asciz "[impala] Keyboard Sucessfully Initialized\n"
diff_key:	.asciz "Different key pressed\n"
arrv_mes:	.asciz "Scancode arrived\n"
asci_keys:
key_nothing: .byte 0x00
key_0: .byte 0x00			
key_1: .byte 0x31
key_2: .byte 0x32
key_3: .byte 0x33
key_4: .byte 0x34
key_5: .byte 0x35
key_6: .byte 0x36
key_7: .byte 0x37
key_8: .byte 0x38
key_9: .byte 0x39
key_10: .byte 0x30
key_11: .byte 0x2d
key_12: .byte 0x3d
key_13: .byte 0x08
key_14: .byte 0x09
key_15: .byte 0x71
key_16: .byte 0x77
key_17: .byte 0x65
key_18: .byte 0x72
key_19: .byte 0x74
key_20: .byte 0x79
key_21: .byte 0x75
key_22: .byte 0x69
key_23: .byte 0x6f
key_24: .byte 0x70
key_25: .byte 0x5b
key_26: .byte 0x5d
key_27: .byte 0x0d
key_28: .byte 0x00 	
key_29: .byte 0x61
key_30: .byte 0x73
key_31: .byte 0x64
key_32: .byte 0x66
key_33: .byte 0x67
key_34: .byte 0x68
key_35: .byte 0x6a
key_36: .byte 0x6b
key_37: .byte 0x6c
key_38: .byte 0x3b
key_39: .byte 0x27
key_40: .byte 0x60
key_41: .byte 0x00		
key_42: .byte 0x5c
key_43: .byte 0x7a
key_44: .byte 0x78
key_45: .byte 0x63
key_46: .byte 0x76
key_47:	.byte 0x62
key_48: .byte 0x6e
key_49: .byte 0x6d
key_50: .byte 0x2c
key_51: .byte 0x2e
key_52: .byte 0x2f
key_53: .byte 0x0	
key_54: .byte 0x0	 
key_55: .byte 0x0		
key_56: .byte 0x20
key_57: .byte 0x00		
key_58: .byte 0x00		
key_59: .byte 0x00		
key_60: .byte 0x00		
key_61: .byte 0x00		
key_62: .byte 0x00		
key_63: .byte 0x00		
key_64: .byte 0x00		
key_65: .byte 0x00		
key_66:	.byte 0x00		
key_67: .byte 0x00		
key_68: .byte 0x00		 
key_69: .byte 0x00		
key_70: .byte 0x00		
key_71: .byte 0x00		
key_72:	.byte 0x00		
key_73: .byte 0x00		
key_74: .byte 0x00		
key_75: .byte 0x00		
key_76: .byte 0x00		
key_77: .byte 0x00		
key_78: .byte 0x00		
key_79: .byte 0x00		
key_80: .byte 0x00		
key_81: .byte 0x00		
key_82: .byte 0x00		
