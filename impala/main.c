
void run_impala()
{

    asm("cli");

    setup_idt();
    install_isr();
    install_irqs();

    clears();

    prints("The Remnant Revolution\n");

    /* Install the iread syscall interrupt */
    // push $iread
    // push $0x2	/* int 0x22 */
    // call install_interrupt_handler
    // add $0x8,%esp

    _initps2();

    loader();

    asm("cli");
    asm("sti");
}