#include "../include/system.h"

extern uint8 *memset(uint8 *dest, uint8 *c, uint32 size_t);

/*
uint8 *memset(uint8 *dest, uint8 *c, uint32 size_t){
    return _memset(dest,c,size_t);
} */

void main(){
    char veridis[10] = "commodore";
    uint8 *ptr;

    ptr = _memset(&veridis,'o',4);
    
    __asm__("nop");
}