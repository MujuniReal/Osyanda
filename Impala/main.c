
void Impalas_run(){
    __asm__(
        "movl $0x40,%ebx;"
        "movl $0xbeef,%edx;"
        "nop;"
    );
}