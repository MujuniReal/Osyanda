#include <types.h>

#define GDT_SEGMENT 0x0000
#define GDT_OFFSET 0x800
#define GDTSIZE 24

typedef struct _gdtEntry{
  uint16 limitLo;
  uint16 baseLo;
  uint8 baseMid;
  uint8 accessByte;
  uint8 flagsLimitHi;
  uint8 baseHi;

}__attribute__((packed)) gdtEntry;

typedef struct _gdtPtr{
  uint16 noEntries;
  uint32 gdtAddr;
}__attribute__((packed)) gdtPtr;

gdtPtr gdtptr;
gdtEntry *gdt;
void initialize_gdt(){
  //Save previous segment
  asm("pushw %ds");
  asm("mov %%ax,%%ds"::"a"(GDT_SEGMENT));
  
  gdt = (gdtEntry*)GDT_OFFSET;


  //First GDT entry Null entry
  gdt[0].limitLo = 0;
  gdt[0].baseLo = 0;
  gdt[0].baseMid = 0;
  gdt[0].accessByte = 0;
  gdt[0].flagsLimitHi = 0;
  gdt[0].baseHi = 0;

  //2nd entry Code Selector
  gdt[1].limitLo = 0;
  gdt[1].baseLo = 0;
  gdt[1].baseMid = 0;
  gdt[1].accessByte = 0x9a;
  gdt[1].flagsLimitHi = 0xc8;
  gdt[1].baseHi = 0;

  //3rd entry Data selector
  gdt[2].limitLo = 0;
  gdt[2].baseLo = 0;
  gdt[2].baseMid = 0;
  gdt[2].accessByte = 0x92;
  gdt[2].flagsLimitHi = 0xc8;
  gdt[2].baseHi = 0;

  asm("popw %ds");
  //Set GDT pointer
  gdtptr.noEntries = GDTSIZE;
  gdtptr.gdtAddr = GDT_OFFSET;
} 

void load_gdt(){
  asm("lgdt gdtptr");
}
