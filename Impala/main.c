#include "include/system.h"



void run_impala(){
    __asm__("cli");

    

    setup_idt();
    install_exception_handlers();


    __asm__("sti");

    __asm__("nop");

    __asm__("int $0x80");

    __asm__("nop");

    __asm__("nop");



hang:
    goto hang;
}
