#include "include/system.h"
#include "include/irq.h"

extern void clears();

void run_impala(){
    __asm__("cli");

    setup_idt();
    install_exception_handlers();
    install_irqs();

    __asm__("sti");

    memsetw((uint16*)0xb8000,(uint16)0x720,80*25);

    //clears();
    outportb(14,0x3d4);
    outportb(0x0,0x3d5);
    outportb(15,0x3d4);
    outportb(0x0,0x3d5);

hang:
    goto hang;
}
