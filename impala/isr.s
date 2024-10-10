
	.code32
	
	.include "idt_s.h"

	INTERRUPT_SIZE = 8				/* An interrupt weighs 8bytes */
	
	.text
	
	.global install_isr
	.global fault_checker

	.macro setidt_intrpt introffset isr_addr
	/* using the calling scheme of function (3,2,1,0) push 0, push1 ..... */
	push $\isr_addr
	push $\introffset
	call set_idt_interrupt_gate
	add $0x8,%esp				/* always dont forget to put back our stack in its original position */
	.endm
	
install_isr:

	/* Load the location of the idt so that we put the 32 interrupts for CPU */
	//lea (idt),%edi
	
	setidt_intrpt 0  isr0		/* setidt_intrpt offset/location in idt isr */
	setidt_intrpt 1  isr1
	setidt_intrpt 2  isr2
	setidt_intrpt 3  isr3
	setidt_intrpt 4  isr4
	setidt_intrpt 5  isr5
	setidt_intrpt 6  isr6
	setidt_intrpt 7  isr7
	setidt_intrpt 8  isr8
	setidt_intrpt 9  isr9
	setidt_intrpt 10 isr10
	setidt_intrpt 11 isr11
	setidt_intrpt 12 isr12
	setidt_intrpt 13 isr13
	setidt_intrpt 14 isr14
	setidt_intrpt 15 isr15
	setidt_intrpt 16 isr16
	setidt_intrpt 17 isr17
	setidt_intrpt 18 isr18
	setidt_intrpt 19 isr19
	setidt_intrpt 20 isr20
	setidt_intrpt 21 isr21
	setidt_intrpt 22 isr22
	setidt_intrpt 23 isr23
	setidt_intrpt 24 isr24
	setidt_intrpt 25 isr25
	setidt_intrpt 26 isr26
	setidt_intrpt 27 isr27
	setidt_intrpt 28 isr28
	setidt_intrpt 29 isr29
	setidt_intrpt 30 isr30
	setidt_intrpt 31 isr31 
    
	ret
    

//void fault_checker(GP_REGISTERS *regs)    
fault_checker:
	mov %esp,%ebp
    /* offset of location of interrupt number from the global structure of pushed registers */
	/* check if interrupt number is less than 32 if so, print message tobe fetched from */

	push %edi
	push %esi
	
	/* fetch interrupt number */
	/* The essence of ebp/ the neccessity of ebp comes in here ive thought of it to locate the variables that were parsed change this in the future*/
	mov 0x4(%ebp),%esi			/* capture the parsed structure of registers and other segments */
	mov INTRNO(%esi),%eax
	/* check if initiated interrupt is less than 32 */
	cmp $32, %eax
	jge  hang
	
	
	lea (exception_msgs),%edi
	add %eax,%edi			/* find the error message */
	push %edi
	call printf				
	push (halt_msg)
	call printf
	add $0x8,%esp			/* discard error strings from stack */

	pop %esi
	pop %edi

    hang:
        jmp hang



	.data

halt_msg:   .asciz "System Halted !\n"

exception_msgs:
    isr_msg0: .asciz "Division By Zero"
    isr_msg1: .asciz "Debug"
    isr_msg2: .asciz "Non Maskable Interrupt"
    isr_msg3: .asciz "Breakpoint"
    isr_msg4: .asciz "Into Detected Overflow"
    isr_msg5: .asciz "Out of Bounds"
    isr_msg6: .asciz "Invalid Opcode"
    isr_msg7: .asciz "No Coprocessor"
    isr_msg8: .asciz "Double Fault"
    isr_msg9: .asciz "Coprocessor Segment Overrun"
    isr_msg10: .asciz "Bad TSS"
    isr_msg11: .asciz "Segment Not Present"
    isr_msg12: .asciz "Stack Fault"
    isr_msg13: .asciz "General Protection Fault"
    isr_msg14: .asciz "Page Fault"
    isr_msg15: .asciz "Unknown Interrupt"
    isr_msg16: .asciz "Coprocessor Fault"
    isr_msg17: .asciz "Alignment Check"
    isr_msg18: .asciz "Machine Check"
    isr_msg19: .asciz "Reserved"
    isr_msg20: .asciz "Reserved"
    isr_msg21: .asciz "Reserved"
    isr_msg22: .asciz "Reserved"
    isr_msg23: .asciz "Reserved"
    isr_msg24: .asciz "Reserved"
    isr_msg25: .asciz "Reserved"
    isr_msg26: .asciz "Reserved"
    isr_msg27: .asciz "Reserved"
    isr_msg28: .asciz "Reserved"
    isr_msg29: .asciz "Reserved"
    isr_msg30: .asciz "Reserved"
    isr_msg31: .asciz "Reserved"

