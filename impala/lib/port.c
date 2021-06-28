#include "../include/types.h"

uint8 inportb(uint16 portaddr){

    uint8 portresult;
    __asm__ __volatile__("inb %1,%0" : "=a"(portresult): "dN" (portaddr));

    return portresult;
}


void outportb(uint8 data, uint16 portaddr){

    __asm__ __volatile__("outb %0, %1":: "a" (data), "dN" (portaddr));
}