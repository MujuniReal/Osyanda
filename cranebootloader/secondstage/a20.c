#include "types.h"
#define BIOS_A20ATTR 0x2401
#define A20SUPPORTATTR 0x2403

extern void prints(char *s);

int16 activate_a20pin(){

  //check if a20 is supported
  int16 supportStat = 0;
  asm("int $0x15":"=b"(supportStat):"a"(A20SUPPORTATTR));

  if(supportStat != 2){
    //Returns 2 in bx register if supported
    char *a20not = "A20 pin Support not available\r\n";
    prints(a20not);
    //    return -1;
  }

  //activate a20Pin
  uint16 a20stat = 0;
  asm("int $0x15"::"a"(BIOS_A20ATTR));
  asm("adc %%ax,%0":"=r"(a20stat):"a"(a20stat));

  //check if carry flag was set
  if(a20stat == 1){
    return -1;
  }
  return 0;
  
}
