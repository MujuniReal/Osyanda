#include "include/idt.h"



/* programmable interrupt controller command and data ports, interrupts defined by the kernel */
#define PRIMARY_PIC_CMDPORT 0x20
#define PRIMARY_PIC_DATAPORT 0x21

#define SECONDARY_PIC_CMDPORT 0xa0
#define SECONDARY_PIC_DATAPORT 0xa1



extern uint8 inportb(uint16);
extern void outportb(uint8,uint16);
//extern void iowait();


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

static inline void iowait(){

    /* volatile goes with inline in my opinion */
    __asm__ __volatile__("outb %%al, $0x80"::"a"(0));       /* send junk to the delay port, POST port */
}


void setmap_PIC(){
    /* inform the primary and secondary PICs of incoming data */
    /* basically initialize them send 0x11*/
    /* we will wait after each transaction so that we ensure a perfect transaction inline function perfect for that */
    outportb(0x11, PRIMARY_PIC_CMDPORT);
    iowait();
    outportb(0x11, SECONDARY_PIC_CMDPORT);
    iowait();

    /* set offsets to our kernel defined interrupts which start from 32 to 40 */
    outportb(0x20, PRIMARY_PIC_DATAPORT);
    iowait();
    /* secondary PIC gets them interrupts from 40 - */
    outportb(0x28, SECONDARY_PIC_DATAPORT);
    iowait();

    outportb(0x4, PRIMARY_PIC_DATAPORT);  /* tell primary PIC that theres a secondary PIC bit mask 0000 0100 */
    iowait();
    outportb(0x2, SECONDARY_PIC_DATAPORT); /* tell secondary PIC that its other identity is 2 0000 0010 */
    iowait();

    outportb(0x1, PRIMARY_PIC_DATAPORT);      /* set primary PIC to intel operation mode 8086 */
    iowait();
    outportb(0x1, SECONDARY_PIC_DATAPORT);    /* set primary PIC to intel operation mode 8086 */
    iowait();

    /* finish up  just like terminating with null*/
    outportb(0x0, PRIMARY_PIC_DATAPORT);
    outportb(0x0, SECONDARY_PIC_DATAPORT);
}


void install_irqs(){

    setmap_PIC();

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