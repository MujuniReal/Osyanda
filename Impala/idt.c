#include "include/system.h"

#define IDT_ENTRIES 256

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

IDTENTRY idt[256];
#define IDT_INTERRUPT_GATE 0x8e

void set_idt_entry(uint16 interrupt_no,uint8 interrupt_type, uint32 interrupt_handler){
    idt[interrupt_no].interrupthandler_lo = interrupt_handler & 0xffff;                  /* lower 2bytes of handler code*/
    idt[interrupt_no].code_segment_selector = 0x8;                                       /* Code segment selector in memory */
    idt[interrupt_no].zero = 0;                                                          /* Always zero */
    idt[interrupt_no].entry_attrib = interrupt_type;                                     /* descriptor attributes */
    idt[interrupt_no].interrupthandler_hi = (interrupt_handler >> 16) & 0xffff;          /* higher 2 bytes of handler code */

}



void set_idt_interrupt_gate(uint16 interrupt_no, uint32 interrupt_handler){
    set_idt_entry(interrupt_no,IDT_INTERRUPT_GATE,interrupt_handler);
}





//#define IDT_INTERRUPT_GATE 0x8e
#define IDT_INTERRUPT_TASKGATE 0x8f

/* setup idt 256 entries, 256 interrupts */


extern IDTPOINTER idtp;

extern void load_idt();

void setup_idt(){
    idtp.idt_size = ( ( sizeof(IDTENTRY) * IDT_ENTRIES ) - 1 );     /* idt size, 256 interrupts * size of each interrupt */
    idtp.idt_location = (uint32) &idt;

    /* Do the memset function here to load the idt with zeros */
    //memset((uint32*)&idt, 0, sizeof(idt));

    /* Design the memset function from scratch C or assembly fingers crossed */

    load_idt();
}
