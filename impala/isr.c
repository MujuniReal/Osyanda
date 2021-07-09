#include "include/types.h"
#include "include/idt.h"


extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void puts(uint32*);
/* Install interrupt exception handlers */

void install_exception_handlers(){
    set_idt_interrupt_gate(0,  (unsigned)isr0);
    set_idt_interrupt_gate(1,  (unsigned)isr1);
    set_idt_interrupt_gate(2,  (unsigned)isr2);
    set_idt_interrupt_gate(3,  (unsigned)isr3);
    set_idt_interrupt_gate(4,  (unsigned)isr4);
    set_idt_interrupt_gate(5,  (unsigned)isr5);
    set_idt_interrupt_gate(6,  (unsigned)isr6);
    set_idt_interrupt_gate(7,  (unsigned)isr7);
    set_idt_interrupt_gate(8,  (unsigned)isr8);
    set_idt_interrupt_gate(9,  (unsigned)isr9);
    set_idt_interrupt_gate(10, (unsigned)isr10);
    set_idt_interrupt_gate(11, (unsigned)isr11);
    set_idt_interrupt_gate(12, (unsigned)isr12);
    set_idt_interrupt_gate(13, (unsigned)isr13);
    set_idt_interrupt_gate(14, (unsigned)isr14);
    set_idt_interrupt_gate(15, (unsigned)isr15);
    set_idt_interrupt_gate(16, (unsigned)isr16);
    set_idt_interrupt_gate(17, (unsigned)isr17);
    set_idt_interrupt_gate(18, (unsigned)isr18);
    set_idt_interrupt_gate(19, (unsigned)isr19);
    set_idt_interrupt_gate(20, (unsigned)isr20);
    set_idt_interrupt_gate(21, (unsigned)isr21);
    set_idt_interrupt_gate(22, (unsigned)isr22);
    set_idt_interrupt_gate(23, (unsigned)isr23);
    set_idt_interrupt_gate(24, (unsigned)isr24);
    set_idt_interrupt_gate(25, (unsigned)isr25);
    set_idt_interrupt_gate(26, (unsigned)isr26);
    set_idt_interrupt_gate(27, (unsigned)isr27);
    set_idt_interrupt_gate(28, (unsigned)isr28);
    set_idt_interrupt_gate(29, (unsigned)isr29);
    set_idt_interrupt_gate(30, (unsigned)isr30);
    set_idt_interrupt_gate(31, (unsigned)isr31);

}

char *exception_msgs[] =
{
    "Division By Zero",
  "Debug",
  "Non Maskable Interrupt",
  "Breakpoint",
  "Into Detected Overflow",
  "Out of Bounds",
  "Invalid Opcode",
  "No Coprocessor",

  "Double Fault",
  "Coprocessor Segment Overrun",
  "Bad TSS",
  "Segment Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault",
  "Unknown Interrupt",

  "Coprocessor Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",

  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};

void fault_checker(GP_REGISTERS *regs){
    if(regs->interrupt_no < 32){
        puts(exception_msgs[regs->interrupt_no]);   //look thru array of exception messages using the index of the exception got print exception
        puts("System Halted !\n");
        goto hang;
        /* make system hang */
        /* In future we will think of what to do */
    }
    
    hang:
        goto hang;
}