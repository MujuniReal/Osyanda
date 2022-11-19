#include <types.h>

#define BIOSDISKREAD 2

extern uint8 driveNo;
extern uint16 totalHeads;
extern uint16 sectsPerTrack;
extern void prints(char *s);

//Returns the number of sectors read returns 0 if fails
uint8 readsect(char *buf, uint8 numSects, uint32 lba){

  uint32 qoutient = lba / sectsPerTrack;
  
  uint16 sector = (lba % sectsPerTrack) + 1;
  uint16 head = qoutient % totalHeads;
  uint16 cylinder = qoutient / totalHeads;

  uint8 CH = cylinder & 0x00ff;
  uint8 CL = cylinder & 0xc0 | (sector & 0x3f);

  uint8 DH = head & 0x00ff;
  uint8 DL = driveNo;

  uint16 AX =  (BIOSDISKREAD << 8) | numSects;
  uint16 CX = CH << 8 | CL;
  uint16 DX = DH << 8 | DL;
  //  uint16 BX = (int)buf  & 0xf;  //save offset
  //  uint16 ES = (int)buf >> 4;    //divide real address by 16 to get segment
  char *BX = buf;

  uint16 result;
  uint16 carryFlag = 0;

  //save es register
  //  asm("pushw %es");
  // asm("mov %0,%%ax; mov %%ax,%%es"::"a"(ES));

  //Perform Read
  asm("int $0x13": "=a"(result) : "a"(AX),"b"(BX),"c"(CX),"d"(DX));
  
  asm("adc %%ax,%0":"=r"(carryFlag): "a"(carryFlag));
  
  //  asm("popw %es");

  //Do an adc so that we add the bit in the carry flag to
  //carryFlag variable

  //Checking whether %ah is zero and carry flag is not set
  if ((result & 0xff00) == 0 && carryFlag == 0){
    //char *ss = "Disk Successfully read\n";
    //Returns the number of sectors read %al
    return (uint8)(result & 0x00ff);
  }

  char *err = "Error occured while reading disk\n";
  prints(err);
  return 0;
}
