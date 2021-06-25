#ifndef __SYSTEM_H__
#define __SYSTEM_H__



typedef signed char     int8;
typedef unsigned char   uint8;
typedef signed short    int16;
typedef unsigned short  uint16;
typedef signed int      int32;
typedef unsigned int    uint32;

/* we define functions needed in the runtime of the kernel ie 
install idt, install exceptions handler
memset, puts
*/

//uint32* memset(uint32* dest, uint8 const_val, uint32 const_size);

extern void setup_idt();
extern void install_exception_handlers();

#endif
