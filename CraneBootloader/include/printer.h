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
/* as we end the print function we have to put back the cursor to the margin */
/* step 1 read the cursor position and we reduce its column so that it can get back to the margin of the screen */
/* read cursor position */
        xor %ax,%ax
        xor %bx,%bx
        mov $0x3,%ah
        /* bh video page already set to zero from xor instruction*/
        int $0x10

/* reduce %dl so that we can bring it back to the margin */
        dec %dl

/* set cursor position */
        xor %ax,%ax
        xor %bx,%bx

        mov $0x2,%ah
/*      mov $0x0,%dh     row  already set
        mov $0x0,%dl    column already set      */
        int $0x10

        retw

.endfunc
