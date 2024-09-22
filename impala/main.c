
void just()
{
    prints("Hello Remnant, the interrupt worked......\n");
}

void run_impala()
{

    asm("cli");

    setup_idt();
    install_isr();
    install_irqs();

    clears();

    install_interrupt_handler(1, &just);

    prints("The Remnant Revolution\n");

    /* Install the iread syscall interrupt */
    // push $iread
    // push $0x2	/* int 0x22 */
    // call install_interrupt_handler
    // add $0x8,%esp
    // asm("int $0x22");

    // _initps2();

    // loader();

    asm("cli");
    asm("sti");

hang:
    goto hang;
}
