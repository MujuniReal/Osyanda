#define GDT 0x800

//maximum gdt entries
#define GDTMAX 8192

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

//Max gdt entries 8192 that is 65536Bytes
int loader(){

  gdt = (gdtEntry*)GDT;

  /*

Steps of the loader
1. Should binary file and read file header to acquire metadata like;
Size of .text section, size of .data section so that it allocates the 
efficient memory to hold the contents of the sections



   */

  //  gdt[0].limitLo;

 
  

  return 0;
}
