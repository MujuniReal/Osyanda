#include "types.h"

#define BIOSDISKREAD 2

extern uint8 LogDrvNo;
extern uint16 NHeads;
extern uint16 SectsPTrck;
extern void PrintIt(char *s);


void readsect(char *buf, uint8 numSects, uint32 lba){

  uint32 qoutient = lba / SectsPTrck;
  
  uint16 sector = (lba % SectsPTrck) + 1;
  uint16 head = qoutient % NHeads;
  uint16 cylinder = qoutient / NHeads;

  uint8 CH = cylinder & 0x00ff;
  uint8 CL = cylinder & 0xc0 | (sector & 0x3f);

  uint8 DH = head & 0x00ff;
  uint8 DL = LogDrvNo;

  uint16 AX =  (BIOSDISKREAD << 8) | numSects;
  uint16 CX = CH << 8 | CL;
  uint16 DX = DH << 8 | DL;
  uint16 BX = (int)buf  & 0xf;  //save offset
  uint16 ES = (int)buf >> 4;    //divide real address by 16 to get segment

  uint16 result;
  uint16 carryFlag = 0;

  //save es register
  asm("pushw %es");
  asm("mov %0,%%ax; mov %%ax,%%es"::"a"(ES));

  //Perform Read
  asm("int $0x13": "=a"(result) : "a"(AX),"b"(BX),"c"(CX),"d"(DX));
  
  asm("adc %%ax,%0":"=r"(carryFlag): "a"(carryFlag));
  
  asm("popw %es");

  //Do an adc so that we add the bit in the carry flag to
  //carryFlag variable

  //Checking whether ah is zero and carry flag is not set
  if ((result & 0xff00) == 0 && carryFlag == 0){
    char *ss = "Disk Successfully read\n";
    PrintIt(ss);
  }
  else{
    char *err = "Error occured while reading disk\n";
    PrintIt(err);
  }
}
