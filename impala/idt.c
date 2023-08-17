#include "types.h"
#include "idt.h"
#include "string.h"
#include "config.h"
#include "monitor.h"

#define TOTAL_INTERRUPTS 512
struct _idtEntry idt[TOTAL_INTERRUPTS];
struct _idtPtr IDTPTR;

extern void load_idt();

create_interupt(int intrNo, void * addr){

    struct _idtEntry* entry = &idt[intrNo];

    entry->handlerLo = (uint32)addr & 0x0000ffff;
    entry->gdtCsSelector = KERNEL_CODE_SELECTOR;
    entry->reserved = 0;
    entry->attr = 0xee;
    entry->handlerHi = (uint32)addr >> 16;
}


setup_idt(){

    IDTPTR.idtSize = sizeof(idt) - 1;
    IDTPTR.idtAddr = (uint32)&idt;

    //asm(load idt)

    memset(idt, 0, sizeof(idt));

    //asm(load_idt)
    load_idt();
    
    // int e = 4 / 0;
}


set_idt_interrupt_gate(){

}

set_idt_task_gate(){

}

set_idt_entry(){

}