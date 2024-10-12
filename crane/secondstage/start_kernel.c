#define KERNEL 0x100000

void start_kernel() {

    void(*kernel)(void) = 0x100000;

    kernel();
    
}
