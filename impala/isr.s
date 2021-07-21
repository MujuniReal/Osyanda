
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
	.endm
	
install_isr:

	/* Load the location of the idt so that we put the 32 interrupts for CPU */
	//lea (idt),%edi
	
	setidt_intrpt 0  isr0		/* setidt_intrpt offset/location in idt isr */
	setidt_intrpt 8   isr1
	setidt_intrpt 16  isr2
	setidt_intrpt 24  isr3
	setidt_intrpt 32  isr4
	setidt_intrpt 40  isr5
	setidt_intrpt 48  isr6
	setidt_intrpt 56  isr7
	setidt_intrpt 64  isr8
	setidt_intrpt 72  isr9
	setidt_intrpt 80  isr10
	setidt_intrpt 88  isr11
	setidt_intrpt 96  isr12
	setidt_intrpt 104 isr13
	setidt_intrpt 112 isr14
	setidt_intrpt 120 isr15
	setidt_intrpt 128 isr16
	setidt_intrpt 136 isr17
	setidt_intrpt 144 isr18
	setidt_intrpt 152 isr19
	setidt_intrpt 160 isr20
	setidt_intrpt 168 isr21
	setidt_intrpt 176 isr22
	setidt_intrpt 184 isr23
	setidt_intrpt 192 isr24
	setidt_intrpt 200 isr25
	setidt_intrpt 208 isr26
	setidt_intrpt 216 isr27
	setidt_intrpt 224 isr28
	setidt_intrpt 232 isr29
	setidt_intrpt 240 isr30
	setidt_intrpt 248 isr31
    
	ret
    

//void fault_checker(GP_REGISTERS *regs)    
fault_checker:
    /* offset of location of interrupt number from the global structure of pushed registers */
    /* check if interrupt number is less than 32 if so, print message tobe fetched from */

    /* fetch interrupt number */
    mov INTRNO_OFFSET(%esp),%eax
    /* check if initiated interrupt is less than 32 */
    cmp $32, %eax
    jge  hang
    lea (exception_msgs),%esi
    add %eax,%esi
    push %esi
    //call puts
    pop %esi
    push (halt_msg)
    //call puts
    pop  (halt_msg)

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

