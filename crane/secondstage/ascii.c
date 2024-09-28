#include "types.h"

char *toasci10(uint32 number, char *buff) {

  // 4,294,967,295 -> 10 bytes as max for 32bit maximum
  int quotient = number / 10;
  int rem = number % 10;

  if (quotient == 0) {
    *buff = (uint8)(0x30 | rem & 0x0f);
    return buff + 1;
  }

  buff = toasci10(quotient, buff);
  *buff = (uint8)(0x30 | rem & 0x0f);

  return buff + 1;
}

char *toasci16(uint32 number, char *buff) {

  // ff ff ff ff -> 10 bytes as max for 32bit maximum
  int quotient = number / 16;
  int rem = number % 16;

  if (quotient == 0) {
    if (rem < 10) {
      *buff = (uint8)(0x30 | rem & 0x0f);
      return buff + 1;
    }
    else {
      *buff = (uint8)(0x57 + rem);
      return buff + 1;
    }
  }

  buff = toasci16(quotient, buff);
  if (rem < 10) {
    *buff = (uint8)(0x30 | rem & 0x0f);
  }
  else {
    *buff = (uint8)(0x57 + rem);
  }
  // Fix this function it returns the pointer plus the length of the string version of the
  // number and so if you print from this address you print nothing
  return buff + 1;
}
