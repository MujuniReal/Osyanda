#include "types.h"

#define PRINTBIOS 0xe;

void PrintIt(char *s){

  for(; *s != '\0'; s++){
    uint16 printAttr = 0xe << 8 | *s;
    asm("movw %0,%%ax; int $0x10"::"r"(printAttr));
  }
}
