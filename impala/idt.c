#include <types.h>
#include <idt.h>
#include <string.h>

#define IDTLIMIT 2047
#define IDT_INTR_GATE 0x8e
#define IDT_TASK_GATE 0x8f
#define CS_SELECTOR_GDT 0x8

struct IdtEntry idt[256];

extern struct IDTPTR;

setup_idt()
{
    IDTPTR.idtSize = IDTLIMIT;
    IDTPTR.idtAddr = &idt;

    memset(&idt, 0, sizeof(idt));

    load_idt();
}

set_idt_entry(int intrno, uint8 attr, uint32 intrAddr)
{
    uint16 lo = 0xffff & intrAddr;
    uint16 hi = (intrAddr >> 16) & 0xffff;
    idt[intrno].handlerLo = lo;
    idt[intrno].gdtCsSelector = CS_SELECTOR_GDT;
    idt[intrno].reserved = 0;
    idt[intrno].attr = attr;
    idt[intrno].handlerHi = hi;
}

set_idt_interrupt_gate(int intrno, uint32 intrAddr)
{
    // Interrupt Gate 0x8e
    set_idt_entry(intrno, IDT_INTR_GATE, intrAddr);
}

set_idt_task_gate(int intrno, uint32 intrAddr)
{
    // Interrupt Task Gate 0x8f
    set_idt_entry(intrno, IDT_TASK_GATE, intrAddr);
}
