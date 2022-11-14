#include "types.h"

#define IDTMAX 256
#define IDT_SEGMENT 0x0000
#define IDT_OFFSET 0x0000
#define IDTSIZE 2048

typedef struct _idtEntry{
  uint16 handlerLo;
  uint16 gdtCsSelector;
  uint8 reserved;
  uint8 attr;
  uint16 handlerHi;
  
}__attribute__((packed)) idtEntry;

typedef struct _idtPtr{
  uint16 noEntries;
  uint32 idtAddr;
}__attribute__((packed)) idtPtr;

idtEntry *idt;
idtPtr idtptr;

void initialize_idt(){
  asm("pushw %ds");
  //Change Data segment before loop
  asm("mov %%ax,%%ds"::"a"(IDT_SEGMENT));
  
  idt = (idtEntry*)IDT_OFFSET;

  //Initialize the IDT with Zeros
  for(int16 i=0; i < (int16)IDTMAX; i++){
    idt[i].handlerLo = 0;
    idt[i].gdtCsSelector = 0;
    idt[i].reserved = 0;
    idt[i].attr = 0;
    idt[i].handlerHi = 0;
  }
  asm("popw %ds");

  //Set IDT pointer
  idtptr.noEntries = IDTSIZE;
  idtptr.idtAddr = IDT_OFFSET;
}

void load_idt(){
  asm("lidt idtptr"); 
}
