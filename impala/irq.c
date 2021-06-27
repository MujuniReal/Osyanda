#include "include/idt.h"

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();



void install_irqs(){

    set_idt_interrupt_gate(32, (unsigned)irq0);
    set_idt_interrupt_gate(33, (unsigned)irq1);
    set_idt_interrupt_gate(34, (unsigned)irq2);
    set_idt_interrupt_gate(35, (unsigned)irq3);
    set_idt_interrupt_gate(36, (unsigned)irq4);
    set_idt_interrupt_gate(37, (unsigned)irq5);
    set_idt_interrupt_gate(38, (unsigned)irq6);
    set_idt_interrupt_gate(39, (unsigned)irq7);
    set_idt_interrupt_gate(40, (unsigned)irq8);
    set_idt_interrupt_gate(41, (unsigned)irq9);
    set_idt_interrupt_gate(42, (unsigned)irq10);
    set_idt_interrupt_gate(43, (unsigned)irq11);
    set_idt_interrupt_gate(44, (unsigned)irq12);
    set_idt_interrupt_gate(45, (unsigned)irq13);
    set_idt_interrupt_gate(46, (unsigned)irq14);
    set_idt_interrupt_gate(47, (unsigned)irq15);
    
}

/* function pointers to interrupt handlers interrputs defined by the kernel to start from 32 onwards */
void *interrupt_handlers[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 };

void install_interrupt_handler(uint8 irq, void (*interrupthandler)(GP_REGISTERS *gpregs)){
    interrupt_handlers[irq] = interrupthandler;
}

void interrupt_handler(GP_REGISTERS *gpregs){

    /* beware function declaration below blank function pointer*/
    void (*interrupthandler)(GP_REGISTERS *gpregs);


    interrupthandler = interrupt_handlers[ gpregs->interrupt_no - 32 ];

    /* check if interrupt handler is registered */
    if( interrupthandler ){

        /* Execute the interrupt parsing the gen purpose registers, data segment of kernel etc.*/
        interrupthandler(gpregs);
    }
    
    /* Expect to halt system after this */

    

}