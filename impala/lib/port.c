#include <types.h>


void outportb(uint8 data, uint16 port){
  
  asm("outb %%al,(%%dx)"::"a"(data), "dN"(port));
  
}

uint8 inportb(uint16 port){ 

  uint8 result; 
  asm("inb (%%dx)":"=a"(result): "dN"(port)); 
  return result; 
} 
