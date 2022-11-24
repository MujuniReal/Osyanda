#include "types.h"
#define PRINTBIOS 0xe;

void prints(char *s){

  for(; *s != '\0'; s++){
    uint16 printAttr = PRINTBIOS << 8 | *s;
    asm("movw %0,%%ax; int $0x10"::"r"(printAttr));
  }
}
