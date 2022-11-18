#include <types.h>


void outportb(uint8 data, uint16 port){
  
  asm("outb %%al,(%%dx)"::"a"(data), "dN"(port));
  
}

/* void inportb(uint16 port){ */

/*   uint8 result; */
/*   asm("inb (%%dx),%%al":"=a"(result): "dN"(port): "%eax"); */
/*   return result; */
/* } */
