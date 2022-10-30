#define GDTSEG 0x800

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

gdtEntry **gdts;

//Max gdt entries 8192 that is 65536Bytes
int loader(){

  asm("lea (%1),%%eax": "=r"(gdts): "r"(GDTSEG):"%eax"); //Load GDT Address in pointer gdts

  asm("nop");

  return 0;
}
