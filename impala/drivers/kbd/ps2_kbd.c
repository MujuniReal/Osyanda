#include <types.h>
#include <port.h>
#include <monitor.h>

#define KYBDCMD 0x60
#define KYBDDATA 0x60
#define KYBDSTAT 0x64
#define CMDACK 0xfa
#define RESENDCMD 0xfe
#define ECHORESP 0xee
#define SELFTESTPASS 0xaa
#define KYBDSCANOFF 0xf5
#define KYBDSCANON 0xf4

extern uint16 *asci_keys;


uint8 wait_for_write(uint16 port, uint8 writeByte){
  
  uint8 result = inportb(port);
  while( result & writeByte ){
    //Will jump out of loop if and result is zero
    result = inportb(port);
  }
  return result;
}

void wait_kybd_stat(uint16 port, uint8 waitByte){
  
  uint8 result = inportb(port);
  
  while(result != waitByte){
    result = inportb(port);
  }
  
}

char read_kybd(){

  uint8 key = inportb(KYBDDATA);

  while(key == 0xfa){
    key = inportb(KYBDDATA);
  }

  uint8 keyReleased = inportb(KYBDDATA);

  while(keyReleased == key){
    keyReleased = inportb(KYBDDATA);
  }

  char asciChar = *(asci_keys + key);

  printc(asciChar);
  
  return asciChar;
}

void init_keyboard(){

  wait_for_write(KYBDSTAT, 2);

  //Turn off keyboard scanning
  outportb(KYBDSCANOFF, KYBDCMD);

  wait_kybd_stat(KYBDDATA, CMDACK);

  wait_for_write(KYBDSTAT, 2);

  //Turn on Keyboard scanning
  outportb(KYBDSCANON, KYBDCMD);

  //Wait for Acknowledgement
  wait_kybd_stat(KYBDDATA, CMDACK);

  char *succStr = "[impala] Keyboard Sucessfully Initialized\n";

  prints(succStr);
  
}