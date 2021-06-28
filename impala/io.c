
static inline void iowait(){

    /* volatile goes with inline in my opinion */
    __asm__ __volatile__("outb %%al, $0x80"::"a"(0));       /* send junk to the delay port, POST port */
}