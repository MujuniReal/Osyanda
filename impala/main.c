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
   puts("We are Osyanda the revolution\n");
   puts("pat\n");
    puts("Grace\n");
    puts("abel\n");
    puts("mujuni\n");
    puts("Commodore\n");
    puts("Joramos\n");
    puts("Patrick\n");
    puts("Veridis\n");
    puts("DaftPunk\n");
    puts("CJ\n");
    puts("Musisire\n");
    puts("Bryo brian\n");
    puts("feriionsf\n");
    puts("Bambooooo\n");
    puts("Lets get ouutta here\n");
    puts("Find me in\n");
    puts("Soldier boy\n");
    puts("Vamonos\n");
puts("codium\n");
    puts("Neels\n");
    puts("Here wiht  edsd\n");
    puts("Revolution !!!!!!!!!\n");
    puts("Revolution Scrolled\n");
    


hang:
    goto hang;
}
