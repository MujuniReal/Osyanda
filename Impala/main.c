#include "include/system.h"

void run_impala(){
    __asm__("cli");

    __asm__("sti");

    setup_idt();




hang:
    goto hang
}
