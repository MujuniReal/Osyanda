#include "include/system.h"
#include "include/irq.h"

extern void clears();
extern uint8 putc(uint8);
extern void puts(uint32*);
extern void _read_ps2_config();
extern void _initps2();

void run_impala(){
    __asm__("cli");

    setup_idt();
    install_exception_handlers();
    install_irqs();

    __asm__("sti");

    clears();
//    putc('c');
    //puts("We are Osyanda the revolution\n");
    //puts("Revolution\tFor LIFE\n");
    //_read_ps2_config();
    //puts("[impala] Initializing Keyboard and mouse\n");
    _initps2();
    // puts("[impala] Done\n");
    


hang:
    goto hang;
}
