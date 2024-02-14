#include <types.h>
#include <string.h>

char *_toasci10(int number, char *numAsci)
{

  int quotient = number / 10;
  int rem = number % 10;

  if (quotient == 0)
  {
    *numAsci = (uint8)(0x30 | rem & 0x0f);
    return numAsci + 1;
  }
  numAsci = _toasci10(quotient, numAsci);
  *numAsci = (uint8)(0x30 | rem & 0x0f);
  // Fix this function it returns the pointer plus the length of the string version of the
  // number and so if you print from this address you print nothing
  return numAsci + 1;
}

char *toasci10(int number, char *buff)
{

  // 4,294,967,295 -> 10 bytes as max for 32bit maximum
  char numberAscii[11];
  memset((char *)&numberAscii, '\0', 11);

  _toasci10(number, (char *)&numberAscii);
  strncpy(buff, (char *)&numberAscii, 11);

  return buff;
}

char *_toasci16(int number, char *numAsci)
{

  int quotient = number / 16;
  int rem = number % 16;

  if (quotient == 0)
  {
    if (rem < 10)
    {
      *numAsci = (uint8)(0x30 | rem & 0x0f);
      return numAsci + 1;
    }
    else
    {
      *numAsci = (uint8)(0x57 + rem);
      return numAsci + 1;
    }
  }
  numAsci = _toasci16(quotient, numAsci);
  if (rem < 10)
  {
    *numAsci = (uint8)(0x30 | rem & 0x0f);
  }
  else
  {
    *numAsci = (uint8)(0x57 + rem);
  }
  // Fix this function it returns the pointer plus the length of the string version of the
  // number and so if you print from this address you print nothing
  return numAsci + 1;
}

char *toasci16(int number, char *buff)
{

  // ff ff ff ff -> 10 bytes as max for 32bit maximum
  char numberAscii[5];
  memset((char *)&numberAscii, '\0', 5);

  _toasci16(number, (char *)&numberAscii);
  strncpy(buff, (char *)&numberAscii, 5);

  return buff;
}
