/* This macro is to handle port activities */
/* save your contents of %eax somewhere before initiating these macros */

.macro outportb data port
	mov $\data,%al
	outb %al,$\port
.endm

.macro inportb port
	inb $\port,%al
.endm
