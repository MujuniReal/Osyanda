#include <types.h>
#include <port.h>
#include <idt.h>

#define PRIMARY_PIC_CMD 0x20
#define PRIMARY_PIC_DATA 0x21
#define SECONDARY_PIC_CMD 0xa0
#define SECONDARY_PIC_DATA 0xa1

uint32 interruptHandlers[16];

setmap_PIC()
{

    outportb(0x11, PRIMARY_PIC_CMD);
    iowait();
    outportb(0x11, SECONDARY_PIC_CMD);
    iowait();

    outportb(0x20, PRIMARY_PIC_DATA);
    iowait();
    outportb(0x28, SECONDARY_PIC_DATA);
    iowait();

    outportb(0x4, PRIMARY_PIC_DATA);
    iowait();
    outportb(0x2, SECONDARY_PIC_DATA);
    iowait();

    outportb(0x1, PRIMARY_PIC_DATA);
    iowait();
    outportb(0x1, SECONDARY_PIC_DATA);
    iowait();

    outportb(0x0, PRIMARY_PIC_DATA);
    outportb(0x0, SECONDARY_PIC_DATA);
}

install_irqs()
{
    setmap_PIC();

    set_idt_interrupt_gate(32, &irq0);
    set_idt_interrupt_gate(33, &irq1);
    set_idt_interrupt_gate(34, &irq2);
    set_idt_interrupt_gate(35, &irq3);
    set_idt_interrupt_gate(36, &irq4);
    set_idt_interrupt_gate(37, &irq5);
    set_idt_interrupt_gate(38, &irq6);
    set_idt_interrupt_gate(39, &irq7);
    set_idt_interrupt_gate(40, &irq8);
    set_idt_interrupt_gate(41, &irq9);
    set_idt_interrupt_gate(42, &irq10);
    set_idt_interrupt_gate(43, &irq11);
    set_idt_interrupt_gate(44, &irq12);
    set_idt_interrupt_gate(45, &irq13);
    set_idt_interrupt_gate(46, &irq14);
    set_idt_interrupt_gate(47, &irq15);
}

install_interrupt_handler(int intrno, uint32 intrAddr)
{
    interruptHandlers[intrno] = intrAddr;
}

interrupt_handler(REGISTERS *regs)
{
    int intrIndex = regs->intrno - 32;

    if (interruptHandlers[intrIndex] == 0)
    {
        prints("[impala] Interrupt not found\n");
    }
    else
    {
        // Locate interrupt function and execute it
        void (*intr_function)(REGISTERS *) = interruptHandlers[intrIndex];
        intr_function(regs);
    }
}