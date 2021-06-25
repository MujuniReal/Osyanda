ENTRY(main)
phys = 0x00060000;
SECTIONS
{
    .text phys : AT(phys) {
        code = .;
        *(text)
        *(.rodata)
        . = ALIGN(4096);
    }
    .data : AT(phys + (data - code))
    {
        data = .;
        *(.data)
        . = ALIGN(4096);
    }
}