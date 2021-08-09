/* code in here initializes the ps2 controller */
	.code32
	.include "macros/port.h"
	PS2_STATUSPORT	= 0x64
	PS2_CMDPORT	= 0x64
	PS2_DATAPORT	= 0x60

	PS2_DEV1CMD = 0x60
	PS2_DEV1STATUS = 0x64
	PS2_DEV1DATA = 0x60

	.text
	.global _initps2
	
_initps2:
	//push %esi
	//lea (ps2status_initiating),%esi
	//push %esi
	//push $0x20
	//call puts
	//pop %esi
	//pop %esi
	/* 1 Disable all ps2 devices */
	outportb 0xad PS2_CMDPORT		/* for 1st ps2 device */
	outportb 0xa7 PS2_CMDPORT		/* for 2nd ps2 device if available if not, its ignored */

	xor %eax,%eax
	/* 2 Flush the output buffer */
	/* keep on polling bit 0 from the status register of the PS2 controller */
	/* drop a while loop that keeps asking for data from the data port 0x60 as you check the status register until bit 0 of status is set to 0 */
check_ps2outbuff:	
	inportb PS2_DATAPORT			/* get useless data that might have remained in the output buffer */
	inportb PS2_STATUSPORT			/* querry status byte into %al register */
	test $0x1,%al				/* check whether bit zero is set to zero */
	jnz check_ps2outbuff

	/* we proceed with getting, and later or setting the ps2 controller configuration byte */
	outportb 0x20 PS2_CMDPORT
getps2stat:	
	inportb PS2_STATUSPORT
	test $0x1,%al				/* check whether data has arrived on PS2_DATAPORT data port */
	jz getps2stat
	
	/* theres data on the PS2_DATAPORT tobe fetched */
	/* check whether bit 5 is enabled in the ps2 configuration*/
	inportb PS2_DATAPORT
	test $0x10,%al
	jz onechannel			/* the code upon this jump means that the ps2 has only one channel ie supports one device on either keyboard or mouse for our system here it was set */
	/* the code below here means that the PS2 controller has 2 channels ie keyboard and mouse */
onechannel:	
		
/* next step is performing self controller test  send comand 0xaa, see if it returns 0x55 on sucess, 0xfc on fail*/
	outportb 0xaa PS2_CMDPORT
checkbuffstat:	
	inportb PS2_STATUSPORT
	test $0x1,%al
	jz  checkbuffstat
	/* ready to query data from PS2_DATAPORT */
	inportb PS2_DATAPORT
	cmp $0xfc,%al
	jz failed_to_perform_controller_test
	nop


	/* next if the ps2 controller has 2 lines ie mouse and keyboard then send 0xa8 command to enable the 2nd channel of the ps2*/
	/* after sending the a8 command, read the config byte, this time bit 5 should be clear if its set then it cant be a dual channel ps2 */
	outportb 0xa8 PS2_CMDPORT	/* activate the second ps2 channel */
	outportb 0x20 PS2_CMDPORT
waitforbuff:	
	inportb PS2_STATUSPORT
	test $0x1,%al
	jz waitforbuff
	
	inportb PS2_DATAPORT
	test $0x10,%al 			/* result should be zero for the second ps channel tobe well up and running else that chanel dont exist */
	jz onechannel2
	jmp secondchannelup
onechannel2:
	nop
secondchannelup:	/* disable the second channel again and finish step */
	outportb 0xa7 PS2_CMDPORT	/* command to disable second channel */

	/* next is to test the controller channels whether they are working */
	outportb 0xab PS2_CMDPORT	/* command for testing the first ps2 channel 1 */
	inportb PS2_STATUSPORT		/*check again whether we are free to receive data */
	inportb PS2_DATAPORT		/* check whether we are 00 for success else channel has failed test */

	outportb 0xa9 PS2_CMDPORT	/* Command for testing ps2 channel 2 */
	inportb PS2_STATUSPORT		/* check whether we are okay to continue */
	inportb PS2_DATAPORT		/* check whether we are 00 for success else channel has failed test */


	/* Next we power up the channels once again remember they are down ie keyboard and mouse*/
	/* fetch configuration byte again, set bits 0 and 1 which show that the two channels of PS2 are up and running then set the config byte */
	/* by lauching the 0x60 command */
	outportb 0xae PS2_CMDPORT	/* enable the first channel */
	outportb 0xa8 PS2_CMDPORT	/* enable/switch on the second channel */

	outportb 0x20 PS2_CMDPORT	/* read config byte again this time to change some of its values and write it to the ps2 controller */
	inportb PS2_STATUSPORT		/* check if we are clear to fetch data */
	inportb PS2_DATAPORT		/* config byte has arrived */
	or $0x3,%al			/* set bits 0 and 1 to imply that the two ps2 channels are up and working well */
	outb %al,$PS2_CMDPORT		/* set the config byte */
	


wait_for_write:
	inportb PS2_STATUSPORT
	test $0x2,%al
	jnz wait_for_write
	
	outportb 0xf5 PS2_DEV1CMD

read_ackno:	
	inportb PS2_DATAPORT
	cmp $0xfa,%al
	jnz read_ackno			/* Loop to wait for acknoledgement */

	push $ps2status_success
	call puts
	add $0x4,%esp

wait_for_write2:
	inportb PS2_STATUSPORT
	test $0x2,%al
	jnz wait_for_write2
	
	outportb 0xf2 PS2_DEV1CMD

wait_fa:
	inportb PS2_DEV1CMD
	cmp $0xfa,%al
	jnz wait_fa

wait_not_fa:
	inportb PS2_DEV1CMD
	cmp $0xfa,%al
	jz wait_not_fa

	call init_keyboard
	
	ret

failed_to_perform_controller_test:
	jmp failed_to_perform_controller_test

.data
ps2status_initiating:	.asciz "[impala] Initializing Keyboard and mouse\n"
ps2status_success:	.asciz "[impala] Done\n"
ps2status_failed:	.asciz "[impala] Failed to initialize keyboard and mouse\n"
ps2_done_stat:	.asciz "[impala] Done Receiveing the Config byte\n"
