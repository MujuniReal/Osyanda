#ifndef FAT_H
#define FAT_H

#define FATBPBOFFSET 3
#define FAT1216_BPBSIZE 62
#define VOLUMELABEL_STRLOCATION 43
#define FSNAME_STRLOCATION 54

struct _fatbpb1216{
  char devOEM[8];
  uint16 ByPSect;
  uint8 SectPClust;
  uint16 ResSects;
  uint8 FatTabs;
  uint16 NRootDirEs;
  uint16 TotSects;
  uint8 MedDescr;
  uint16 SectsPFat;
  uint16 SectsPTrck;
  uint16 NHeads;	
  uint16 NHiddenSects;
  uint16 NhiddnSectshi;
  uint32 TotSectsInFS;

  //Extended
  uint8 LogDrvNo;
  uint8 Resrvd;
  uint8 ExtSig;
  uint32 DrvSeriNum;
  char VolLabel[11];
  char FSType[8];
}__attribute__((packed));

struct _fatbpb32{
  char devOEM[8];
  uint16 ByPSect;
  uint8 SectPClust;
  uint16 ResSects;
  uint8 FatTabs;
  uint16 NRootDirEs;
  uint16 TotSects;
  uint8 MedDescr;
  uint16 Reserved;
  uint16 SectsPTrck;
  uint16 NHeads;	
  uint16 NHiddenSects;
  uint16 NhiddnSectshi;
  uint32 TotSectsInFS;

  //Extended
  uint32 SectsPFat;
  uint16 extFlags;
  uint16 fatVersion;
  uint32 firstRootDirClust;
  uint16 fatInfo;
  uint16 mbrCopySect;
  uint32 reserved1;
  uint32 reserved2;
  uint32 reserved3;
  uint8 LogDrvNo;
  uint8 reserved4;
  uint8 ExtSig;
  uint32 DrvSeriNum;
  char VolLabel[11];
  char FSType[8]; 
}__attribute__((packed));

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
