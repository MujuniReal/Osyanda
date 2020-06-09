struct ver {
    int comod;
    int rexha;
    char co;
}__attribute__((packed));

struct verdict{
    int re;
    char w;
}__attribute__((packed));

void Impalas_run(){
    __asm__(
        "movl $0x40,%ebx;"
        "movl $0xbeef,%edx;"
        "nop;"
    );
    struct ver modore;
    struct verdict rehomba;


    __asm__("mov %0,%%eax"::"r" (&modore));
    __asm__("nop");
    __asm__("mov %0,%%eax"::"r"(&rehomba));
    __asm__("nop");
    __asm__("xchg %ebx,%ebx");
}
