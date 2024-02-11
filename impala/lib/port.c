#include <types.h>

static inline void iowait()
{
  asm("outb %%al,$0x80" ::"a"(0));
}

void outportb(uint8 data, uint16 port)
{

  asm("outb %%al,(%%dx)" ::"a"(data), "dN"(port));
}

uint8 inportb(uint16 port)
{

  uint8 result;
  asm("mov %%ax,%%dx; inb (%%dx)" : "=a"(result) : "a"(port));
  return result;
}

inportw() {}

outportw() {}