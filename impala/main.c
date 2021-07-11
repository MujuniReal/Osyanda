#include "include/system.h"
#include "include/irq.h"

extern void clears();
extern uint8 putc(uint8);
extern void puts(uint32*);

void run_impala(){
    __asm__("cli");

    setup_idt();
    install_exception_handlers();
    install_irqs();

    __asm__("sti");

    clears();
//    putc('c');
    puts("We are Osyanda the revolution\n");
    puts("Revolution\tFor LIFE\n");
    


hang:
    goto hang;
}
