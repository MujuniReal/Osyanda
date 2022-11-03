#include <types.h>
#include <string.h>
#define GDT 0x800

//maximum gdt entries
#define GDTMAX 8192

//This is the start address of any external program in memory
//We are giving the kernel a total of 1MB after that, that memory belongs to our programs
#define FREEMEMORY_START 0x160000

typedef unsigned int uint32;
typedef unsigned short int uint16;
typedef unsigned char uint8;

typedef struct _gdtEntry{
  uint16 limitLo;
  uint16 baseLo;
  uint8 baseMid;
  uint8 accessByte;
  uint8 limitHiFlags;
  uint8 baseHi;

}__attribute__((packed)) gdtEntry;

gdtEntry *gdt;

extern void rdsk(char *s,int size);
extern uint32 find_file_startcluster(char *filename);
extern int lba;
uint32 base;
uint32 limit;
//Max gdt entries 8192 that is 65536Bytes
int loader(){

  //Use rdsk
  //rdsk((char*)&mbrSectTmp,512);
  /*

Steps of the loader
1. Should binary file and read file header to acquire metadata like;
Size of .text section, size of .data section so that it allocates the 
efficient memory to hold the contents of the sections



   */

  //  gdt[0].limitLo;
  char *fname = "STAGE2  BIN";
  uint32 startClust = find_file_startcluster(fname);
  
  asm("nop");
 
  gdt = (gdtEntry*)GDT;

  //Search for free area to place new descriptor in GDT
  for(int i=0; i < GDTMAX; i++){
    gdtEntry gdtentry = gdt[i];

    base = gdtentry.baseHi << 24  | (gdtentry.baseMid << 16 | gdtentry.baseLo);
    asm("nop");
    
    limit = (gdtentry.limitHiFlags & 0xf0) << 12 | gdtentry.limitLo;
    asm("nop");

    if(i != 0 && base == 0 && limit == 0){

      //Free space for registering a descriptor in GDT
    }

    
  }

  

  return 0;
}
