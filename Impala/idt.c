#include "include/system.h"

#define IDT_SIZE 256

typedef struct {
    uint16 interrupthandler_lo;     /* Low 2bytes of location of interrupt handler */
    uint16 code_segment_selector;   /* Index of code segment descriptor in gdt */
    uint8  zero;                    /* Always set to zero */
    uint8  entry_attrib;            /* idt entry attributes; defines gate type, storage segment, privilleges, presence of idt entry */
    uint16 interrupthandler_hi;     /* High 2bytes of location of interrupt handler */
} __attribute__((packed)) IDTENTRY;


typedef struct {
    uint16 idt_size;                /* size/limit of idt, ensure to subtract 1 when declaring this, to avoid +1 - errors*/
    uint32 idt_location;           /* base/location of idt in memory (absolute) */
}__attribute__((packed)) IDTPOINTER;

/* setup idt 256 entries, 256 interrupts */
IDTENTRY idt[256];

extern IDTPOINTER idtp;

void setup_idt(){
    idtp.idt_size = ( ( sizeof(IDTENTRY) * IDT_SIZE ) - 1 );     /* idt size, 256 interrupts * size of each interrupt */
    idtp.idt_location = (uint32) &idt;

    /* Do the memset function here to load the idt with zeros */
}