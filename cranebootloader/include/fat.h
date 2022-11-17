#ifndef FAT_H
#define FAT_H

struct _dirEntry{
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
  uint16 dirFirstClustLo;
  uint32 dirFileSize;
  
}__attribute__((packed));

#endif
