#include <types.h>

struct dirEntry{
  char dirName[11];
  char dirAttrib;
  char dirRes;
  char dirCrtTimeTenth;
  uint16 dirCrtTime;
  uint16 dirCrtDate;
  uint16 dirLastAccDate;
  uint16 dirFirstClustHi;
  uint16 dirWrtTime;
  uint16 dirWrtDate;
  uint16 dirFirstClust;
  uint32 dirFileSize;
  
}__attribute__((packed));
