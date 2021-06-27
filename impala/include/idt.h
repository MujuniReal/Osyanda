#ifndef _IDT_H 
#define _IDT_H

#include "types.h"

typedef struct{
    uint32 gs, fs, es, ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 interrupt_no, interrupt_errcode;
    uint32 eip, cs, eflags, oldesp, ss;

}GP_REGISTERS;


extern void set_idt_interrupt_gate(uint16,uint32);
extern void setup_idt();

#endif