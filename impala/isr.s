.code32
	
.include "idt_s.h"
	
.text
.global install_exception_handlers
.global fault_checker



.macro exception_handler exnum handler
    push \handler
    push $\exnum
    call set_idt_interrupt_gate
.endm

install_exception_handlers:
    exception_handler 0 isr0
    exception_handler 1 isr1
    exception_handler 2 isr2
    exception_handler 3 isr3
    exception_handler 4 isr4
    exception_handler 5 isr5
    exception_handler 6 isr6
    exception_handler 7 isr7
    exception_handler 8 isr8
    exception_handler 9 isr9
    exception_handler 10 isr10
    exception_handler 11 isr11
    exception_handler 12 isr12
    exception_handler 13 isr13
    exception_handler 14 isr14
    exception_handler 15 isr15
    exception_handler 16 isr16
    exception_handler 17 isr17
    exception_handler 18 isr18
    exception_handler 19 isr19
    exception_handler 20 isr20
    exception_handler 21 isr21
    exception_handler 22 isr22
    exception_handler 23 isr23
    exception_handler 24 isr24
    exception_handler 25 isr25
    exception_handler 26 isr26
    exception_handler 27 isr27
    exception_handler 28 isr28
    exception_handler 29 isr29
    exception_handler 30 isr30
    exception_handler 31 isr31
    
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
    call puts
    pop %esi
    push (halt_msg)
    call puts
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

