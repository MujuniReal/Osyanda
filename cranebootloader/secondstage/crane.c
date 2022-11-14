#include "types.h"

extern void PrintIt(char *s);
extern void readsect(char*buf, uint8 numSects, uint32 lba);

extern void initialize_gdt();
extern void initialize_idt();
extern void load_gdt();
extern void load_idt();
extern int16 test_a20pin();

void crane_main(){

  char *welcome = "CRANE BOOTLOADER\r\n";

  char quoVadis[512];

  PrintIt(welcome);

  asm("nop");

  //  readsect((char*)&quoVadis, 1, 0x210);

  test_a20pin();
  initialize_gdt();
  initialize_idt();
  
  load_idt();
  load_gdt();
  asm("nop");
  

  

  //
  
}
