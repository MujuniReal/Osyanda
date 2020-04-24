#define PRINTER


.func PrintIt

PrintIt:
        lodsb
        mov $0xe,%ah
        int $0x10
        or %al,%al
        jz EndPrint
        jmp PrintIt


EndPrint:
        retw

.endfunc
