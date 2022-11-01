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

  //  gdt[0].limitLo;

 
  gdt = (gdtEntry*)GDT;

  lba = 0x0;

  return 0;
}
