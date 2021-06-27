#ifndef _IRQ_H
#define _IRQ_H

#include "idt.h"


extern void install_irqs();
extern void install_interrupt_handler(uint8 irq, void *handler(GP_REGISTERS *gpregs));
extern void interrupt_handler();




#endif