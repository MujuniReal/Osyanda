#include "types"
#include "string.h"

uint8 to_ascii(uint8 c){

  
}

char *toasci10(int number, char *buff){
  
  //4,294,967,295 -> 10 bytes as max for 32bit maximum
  char numberAscii[11];
  memset((char*)&numberAscii, '\0', 11);

  _toasci10(number, (char*)&numberAscii);
  strncpy(buff, (char*)&numberAscii, 11);
  
  return buff;
  
}

char *_toasci10(int number, char* numAsci){
  
  int quotient = number / 10;
  int rem = number % 10;
  
  
  if(quotient == 0){
    *numAsci = (uint8)(0x30 | rem & 0x0f);
    return numAsci + 1;
  }
  numAsci = toasci10(quotient, numAsci);
  *numAsci  = (uint8)(0x30 | rem & 0x0f);
  return numAsci + 1;

}
