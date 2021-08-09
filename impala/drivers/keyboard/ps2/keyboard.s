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
