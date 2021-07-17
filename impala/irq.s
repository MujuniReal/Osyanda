.code32
.include "macros/port.h"
.include "macros/io.h"	
PRIMARY_PIC_CMDPORT = 0x20
PRIMARY_PIC_DATAPORT = 0x21

SECONDARY_PIC_CMDPORT = 0xa0
SECONDARY_PIC_DATAPORT = 0xa1
	
.text
.global install_irqs


.macro setirq irqno irqfunc
    push \irqfunc
    push $\irqno
    call set_idt_interrupt_gate
.endm

install_irqs:

    call setmap_PIC

    setirq 32 irq0
    setirq 33 irq1
    setirq 34 irq2
    setirq 35 irq3
    setirq 36 irq4
    setirq 37 irq5
    setirq 38 irq6
    setirq 39 irq7
    setirq 40 irq8
    setirq 41 irq9
    setirq 42 irq10
    setirq 43 irq11
    setirq 44 irq12
    setirq 45 irq13
    setirq 46 irq14
    setirq 47 irq15

    ret




setmap_PIC:
    outportb 0x11 PRIMARY_PIC_CMDPORT
    iowait
    outportb 0x11 SECONDARY_PIC_CMDPORT
    iowait

    outportb 0x20 PRIMARY_PIC_DATAPORT
    iowait  
    outportb 0x28 SECONDARY_PIC_DATAPORT
    iowait

    outportb 0x4 PRIMARY_PIC_DATAPORT
    iowait
    outportb 0x2 SECONDARY_PIC_DATAPORT
    iowait

    outportb 0x1 PRIMARY_PIC_DATAPORT
    iowait
    outportb 0x1 SECONDARY_PIC_DATAPORT
    iowait

    outportb 0x0 PRIMARY_PIC_DATAPORT
    outportb 0x0 SECONDARY_PIC_DATAPORT

    ret

.data
interrupt_handlers:
    irqhandler0: .int 0x0
    irqhandler1: .int 0x0
    irqhandler2: .int 0x0
    irqhandler3: .int 0x0
    irqhandler4: .int 0x0
    irqhandler5: .int 0x0
    irqhandler6: .int 0x0
    irqhandler7: .int 0x0
    irqhandler8: .int 0x0
    irqhandler9: .int 0x0
    irqhandler10: .int 0x0
    irqhandler11: .int 0x0
    irqhandler12: .int 0x0
    irqhandler13: .int 0x0
    irqhandler14: .int 0x0
