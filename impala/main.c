#include "include/system.h"



void run_impala(){
    __asm__("cli");

    setup_idt();
    install_exception_handlers();

    __asm__("sti");

hang:
    goto hang;
}
