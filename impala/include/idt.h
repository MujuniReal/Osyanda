#ifndef IDT_H
#define IDT_H
#include "types.h"

#define IDTENTRY_SIZE 8

struct IdtEntry
{
  uint16 handlerLo;
  uint16 gdtCsSelector;
  uint8 reserved;
  uint8 attr;
  uint16 handlerHi;

} __attribute__((packed));

struct IdtPtr
{
  uint16 idtSize;
  uint32 idtAddr;
} __attribute__((packed));

typedef struct
{
  uint32 GS, FS, ES, DS;
  uint32 EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
  uint32 intrno, intrErrorcode;
  uint32 EIP, CS, eflags, oldesp, SS;

} __attribute__((packed)) REGISTERS;

#endif