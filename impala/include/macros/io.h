/* once known substitute for inline in c */
/* once we find out how to declare inline functions in assembly we will forego macros */

.macro iowait
    mov $0x0,%al
    outb %al,$0x80
.endm