#include "include/system.h"
#include "include/irq.h"

extern void clears();
extern uint8 putc(uint8);

void run_impala(){
    __asm__("cli");

    setup_idt();
    install_exception_handlers();
    install_irqs();

    __asm__("sti");

    clears();
    putc('c');

hang:
    goto hang;
}
