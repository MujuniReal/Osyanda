#include <disk.h>
#include <monitor.h>
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
  uint8 flagsLimitHi;
  uint8 baseHi;

}__attribute__((packed)) gdtEntry;

gdtEntry *gdt;

//extern void rdsk(char *s,int size);
extern uint32 find_file_startcluster(char *filename);
extern int lba;

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

  char *fname = "TERMINAL";
  uint32 startClust = find_file_startcluster(fname);

  if(startClust == 0){
    char *fNotFound = "File Not found.\n";
    prints(fNotFound);
    return -1;
  }
 
  gdt = (gdtEntry*)GDT;
  int i = 0;
  
  //Search for free area to place new descriptor in GDT
  for(i; i < GDTMAX; i++){
    gdtEntry gdtentry = gdt[i];

    uint32 base = gdtentry.baseHi << 24  | (gdtentry.baseMid << 16 | gdtentry.baseLo);
    
    uint32 limit = (gdtentry.flagsLimitHi & 0x0f) << 16 | gdtentry.limitLo;

    if(i != 0 && base == 0 && limit == 0){
      //Free space for registering a descriptor in GDT
      break;
    }
  }

  if(i == GDTMAX){
    char *noFreeEntry = "GDT at Limit, Program loading Failed.\n";
    prints(noFreeEntry);
    return 1;
  }

  //Register Descriptor and read file code into free memory
  
  char *progMemory = (char*)FREEMEMORY_START;
  gdtEntry progGdt = gdt[i];

  progGdt.limitLo = 1;
  progGdt.baseLo = FREEMEMORY_START & 0xffff;
  progGdt.baseMid = (FREEMEMORY_START >> 16) & 0xff;
  progGdt.accessByte = 3;
  
  progGdt.flagsLimitHi = 0100 ;
  progGdt.baseHi = FREEMEMORY_START >> 24;

  //  readfatfile(startClust,progMemory,);

  //Read and call, for now as we havent yet decided on the syscall
  //interface, the upper gdt code is useless
  //For now just read the file in memory and call it as below
  
  rdsk((char*)FREEMEMORY_START, 512);

  //Define type caster
  typedef void(*voiFunc)(void);
  
  void (*calledProg)(void) = (voiFunc)FREEMEMORY_START;

  calledProg();

  return 0;
}
