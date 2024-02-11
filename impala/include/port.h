#include "types.h"

#ifndef PORT_H

#define PORT_H

extern inline void iowait();
extern void outportb(uint8 data, uint16 port);
extern uint8 inportb(uint16 port);

#endif
