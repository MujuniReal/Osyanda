.code32
.text
.org 0x0

.global idtp
.global load_idt

.global interrupt_ex_0
.global interrupt_ex_1
.global interrupt_ex_2
.global interrupt_ex_3
.global interrupt_ex_4
.global interrupt_ex_5
.global interrupt_ex_6
.global interrupt_ex_7
.global interrupt_ex_8
.global interrupt_ex_9
.global interrupt_ex_10
.global interrupt_ex_11
.global interrupt_ex_12
.global interrupt_ex_13
.global interrupt_ex_14
.global interrupt_ex_15
.global interrupt_ex_16
.global interrupt_ex_17
.global interrupt_ex_18
.global interrupt_ex_19
.global interrupt_ex_20
.global interrupt_ex_21
.global interrupt_ex_22
.global interrupt_ex_23
.global interrupt_ex_24
.global interrupt_ex_25
.global interrupt_ex_26
.global interrupt_ex_27
.global interrupt_ex_28
.global interrupt_ex_29
.global interrupt_ex_30
.global interrupt_ex_31



load_idt:
    lidt idtp          /* This function loads the IDT into memory the idt that's in the kernel's runtime */
    ret

/* these functions below are to handle interrupt exceptions */
/ * they raise a warning to the user that something has been violated */


.macro interuptHandlNoArg interupt
    push $0x0
    push $\interupt
    jmp check_if_fault
.endm

.macro interuptHandlArg interupt
    push $\interupt
    jmp check_if_fault
.endm

interrupt_ex_0: interuptHandlNoArg      0
interrupt_ex_1: interuptHandlNoArg      1
interrupt_ex_2: interuptHandlNoArg      2
interrupt_ex_3: interuptHandlNoArg      3
interrupt_ex_4: interuptHandlNoArg      4
interrupt_ex_5: interuptHandlNoArg      5
interrupt_ex_6: interuptHandlNoArg      6
interrupt_ex_7: interuptHandlNoArg      7
interrupt_ex_8: interuptHandlArg        8
interrupt_ex_9: interuptHandlNoArg      9
interrupt_ex_10: interuptHandlArg       10
interrupt_ex_11: interuptHandlArg       11
interrupt_ex_12: interuptHandlArg       12
interrupt_ex_13: interuptHandlArg       13
interrupt_ex_14: interuptHandlArg       14
interrupt_ex_15: interuptHandlNoArg     15
interrupt_ex_16: interuptHandlNoArg     16
interrupt_ex_17: interuptHandlNoArg     17
interrupt_ex_18: interuptHandlNoArg     18
interrupt_ex_19: interuptHandlNoArg     19
interrupt_ex_20: interuptHandlNoArg     20
interrupt_ex_21: interuptHandlNoArg     21
interrupt_ex_22: interuptHandlNoArg     22
interrupt_ex_23: interuptHandlNoArg     23
interrupt_ex_24: interuptHandlNoArg     24
interrupt_ex_25: interuptHandlNoArg     25
interrupt_ex_26: interuptHandlNoArg     26
interrupt_ex_27: interuptHandlNoArg     27
interrupt_ex_28: interuptHandlNoArg     28
interrupt_ex_29: interuptHandlNoArg     29
interrupt_ex_30: interuptHandlNoArg     30
interrupt_ex_31: interuptHandlNoArg     31

/* prepare to check for an exception */
check_if_fault:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10,%ax           /* Load data kernel segment selector */
    mov %ax,%ds
    mov %ax,%es
    mov %ax,%fs
    mov %ax,%gs
    mov %esp,%eax
    push %eax

    /* Load the C function that deals with priting the exception on screen */
    lea (fault_checker),%eax
    call *%eax

    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $0x8,%esp       /* Clear the pushed error code and interrupt handler number*/
    iret                /* pop cs, eip, ss, esp */


.data
idtp: .byte 0,0,0,0,0,0