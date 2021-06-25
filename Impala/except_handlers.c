#include "include/types.h"
#include "include/idt_exceptions.h"

typedef struct{
    uint32 gs, fs, es, ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 interrupt_no, interrupt_errcode;
    uint32 eip, cs, eflags, oldesp, ss;

}GP_REGISTERS;

extern void set_idt_interrupt_gate(uint16,uint32);

/* Install interrupt exception handlers */

void install_exception_handlers(){
    set_idt_interrupt_gate(0,  (unsigned)interrupt_ex_0);
    set_idt_interrupt_gate(1,  (unsigned)interrupt_ex_1);
    set_idt_interrupt_gate(2,  (unsigned)interrupt_ex_2);
    set_idt_interrupt_gate(3,  (unsigned)interrupt_ex_3);
    set_idt_interrupt_gate(4,  (unsigned)interrupt_ex_4);
    set_idt_interrupt_gate(5,  (unsigned)interrupt_ex_5);
    set_idt_interrupt_gate(6,  (unsigned)interrupt_ex_6);
    set_idt_interrupt_gate(7,  (unsigned)interrupt_ex_7);
    set_idt_interrupt_gate(8,  (unsigned)interrupt_ex_8);
    set_idt_interrupt_gate(9,  (unsigned)interrupt_ex_9);
    set_idt_interrupt_gate(10, (unsigned)interrupt_ex_10);
    set_idt_interrupt_gate(11, (unsigned)interrupt_ex_11);
    set_idt_interrupt_gate(12, (unsigned)interrupt_ex_12);
    set_idt_interrupt_gate(13, (unsigned)interrupt_ex_13);
    set_idt_interrupt_gate(14, (unsigned)interrupt_ex_14);
    set_idt_interrupt_gate(15, (unsigned)interrupt_ex_15);
    set_idt_interrupt_gate(16, (unsigned)interrupt_ex_16);
    set_idt_interrupt_gate(17, (unsigned)interrupt_ex_17);
    set_idt_interrupt_gate(18, (unsigned)interrupt_ex_18);
    set_idt_interrupt_gate(19, (unsigned)interrupt_ex_19);
    set_idt_interrupt_gate(20, (unsigned)interrupt_ex_20);
    set_idt_interrupt_gate(21, (unsigned)interrupt_ex_21);
    set_idt_interrupt_gate(22, (unsigned)interrupt_ex_22);
    set_idt_interrupt_gate(23, (unsigned)interrupt_ex_23);
    set_idt_interrupt_gate(24, (unsigned)interrupt_ex_24);
    set_idt_interrupt_gate(25, (unsigned)interrupt_ex_25);
    set_idt_interrupt_gate(26, (unsigned)interrupt_ex_26);
    set_idt_interrupt_gate(27, (unsigned)interrupt_ex_27);
    set_idt_interrupt_gate(28, (unsigned)interrupt_ex_28);
    set_idt_interrupt_gate(29, (unsigned)interrupt_ex_29);
    set_idt_interrupt_gate(30, (unsigned)interrupt_ex_30);
    set_idt_interrupt_gate(31, (unsigned)interrupt_ex_31);

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
        //puts(exception_msgs[regs->interrupt_no]);   //look thru array of exception messages using the index of the exception got print exception
        //puts("System Halted !\n");
        /* make system hang */
        /* In future we will think of what to do */
    }
}