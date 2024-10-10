#include <port.h>

#define PRIMARY_PIC_CMD 0x20
#define PRIMARY_PIC_DATA 0x21
#define SECONDARY_PIC_CMD 0xa0
#define SECONDARY_PIC_DATA 0xa1

extern char read_kybd();

void just()
{
    printf("Hello Remnant, the interrupt worked Glory To GOD......\n");

    // End of Interrupt EOI
    outportb(0x20, PRIMARY_PIC_CMD);    
}

void run_impala()
{

    asm("cli");

    setup_idt();
    
    install_isr();
    install_irqs();

    clears();

    // install_interrupt_handler(1, &just);

    printf("The Remnant Revolution\n");

    /* Install the iread syscall interrupt */
    // push $iread
    // push $0x2	/* int 0x22 */
    // call install_interrupt_handler
    // add $0x8,%esp
    // asm("int $0x22");

    _initps2();

    //Keyboard initialized, install handler
    install_interrupt_handler(1, &read_kybd);

    // loader();
    // Enable keyboard interrupt handler
    outportb(0xfd, PRIMARY_PIC_DATA);
    outportb(0xff, SECONDARY_PIC_DATA);
    
    asm("sti");

    // asm("int $0x21");
    // asm("cli");
hang:
    goto hang;
}
