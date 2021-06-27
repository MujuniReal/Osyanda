#include "include/system.h"
#include "include/irq.h"


void run_impala(){
    __asm__("cli");

    setup_idt();
    install_exception_handlers();
    install_irqs();

    __asm__("sti");

hang:
    goto hang;
}
