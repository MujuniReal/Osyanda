.code32
.text

.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15


.macro irquest num
    push $0x0
    push $\num
    jmp prepregs_irq

.endm

irq0: irquest 32
irq1: irquest 33
irq2: irquest 34
irq3: irquest 35
irq4: irquest 36
irq5: irquest 37
irq6: irquest 38
irq7: irquest 39
irq8: irquest 40
irq9: irquest 41
irq10: irquest 42
irq11: irquest 43
irq12: irquest 44
irq13: irquest 45
irq14: irquest 46
irq15: irquest 47


prepregs_irq:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10,%ax           /* Load data kernel segment selector Kernel Mode :) */
    mov %ax,%ds
    mov %ax,%es
    mov %ax,%fs
    mov %ax,%gs
    mov %esp,%eax
    push %eax		/* This statement stores all of them pushed items as a structure on the stack  before calling the function a way of parsing a structure as an arguement */

    /* Load the C function that deals with priting the exception on screen */
    lea (interrupt_handler),%eax
    call *%eax

    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $0x8,%esp       /* Clear the pushed error code and interrupt handler number*/
    iret                /* pop cs, eip, ss, esp */
    
