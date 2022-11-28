#include "types.h"

struct _idtEntry{
  uint16 handlerLo;
  uint16 gdtCsSelector;
  uint8 reserved;
  uint8 attr;
  uint16 handlerHi;
  
}__attribute__((packed));

struct _idtPtr{
  uint16 noEntries;
  uint32 idtAddr;
}__attribute__((packed));
