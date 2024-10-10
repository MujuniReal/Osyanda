#include "types.h"
#include "string.h"
#include "display.h"
#include "fat.h"
#define ROOTDIRENTRYSIZE 32
#define EOFMAGIC 0xffffffff

typedef struct _dirEntry dirEntry;

extern uint8 diskread(char *buf, uint8 numSects, uint32 lba);
extern uint32 osyandaStartSector;


typedef struct _fatbpb32 fatbpb;
uint8 bpb[512];
uint32 fat[512];



int load_fat() {
  //Load the BPB
  if ( !diskread((char *)bpb, 1, osyandaStartSector) ){
    //Failed to read BPB
    return 0;
  }

  fatbpb *_bpb = (fatbpb*)(bpb + FATBPBOFFSET);
  uint32 fat_start_sect = osyandaStartSector + _bpb->ResSects;
  // uint32 fat2StartSect = osyandaStartSector + _bpb->ResSects + _bpb->SectsPFat;

  if ( !diskread((char *)fat, 1, fat_start_sect) ) {
    // failed to read the FAT
    return -1;
  }

  return 1;
}


// Returns 0 if file not found, returns file start Cluster number if file found
uint32 find_file(char *filename) {
  
  //Locate BPB and start finding the file
  int fatstat = !load_fat();

  if( fatstat == 0 ){
    printf("Failed to read the BPB of the partition.\n");
    return;
  }

  if( fatstat == -1 ){
    printf("Failed to Read the FAT.\n");
    return;
  }

  char rootdirSect[512];

  fatbpb *_bpb = (fatbpb*)(bpb + FATBPBOFFSET);

  uint32 rootdirStart = osyandaStartSector + _bpb->ResSects + (_bpb->SectsPFat * _bpb->FatTabs);
  uint32 rootdirSectors = (_bpb->NRootDirEs * ROOTDIRENTRYSIZE) / _bpb->ByPSect;
  uint16 dirEntriesInSect = _bpb->ByPSect / ROOTDIRENTRYSIZE;
  uint16 i = 0;
  for (i; i < rootdirSectors; i++) {

    uint32 dirSectLba = rootdirStart + i;

    if ( !diskread((char *)&rootdirSect, 1, dirSectLba) ) {
      // Failed to read sector
      printf("Failed to read Root directory Sector\n");
      break;
    };

    dirEntry *rootdirMem = (dirEntry *)&rootdirSect;

    // The root directory
    for (uint16 e = 0; e < dirEntriesInSect; e++) {

      if (strncmp((char *)&rootdirMem[e].dirName, filename, 11) == 0) {
        /* File Found */
        uint32 filestartCluster = rootdirMem[e].dirFirstClustHi << 16 | rootdirMem[e].dirFirstClustLo;
        return filestartCluster;
      }
    }
  }

  /* File Not Found */
  return 0;
}



int16 read_file(char *dest, uint32 fstartClust) {

  // Cluster below werent fully read maybe because of the LBA investigate this function
  // diskread(0x00102000, 16, 0xa50);

  fatbpb *_bpb = (fatbpb*)(bpb + FATBPBOFFSET);

  uint32 fatSize = _bpb->SectsPFat * _bpb->ByPSect;
  uint32 rootdirStart = osyandaStartSector + _bpb->ResSects + (_bpb->SectsPFat * _bpb->FatTabs);
  uint32 rootdirSectors = (_bpb->NRootDirEs * ROOTDIRENTRYSIZE) / _bpb->ByPSect;
  uint32 firstDataSect = rootdirStart + rootdirSectors;
  uint32 ByPClust = _bpb->SectPClust * _bpb->ByPSect;
  uint16 ByPSeg = ByPClust / 16; // Real address / 16 = segment

  // Because fat16 entry in fat is 2bytes
  // Load Just one sector of the FAT for now
  char fat_mem[512];

  if (load_fat((char *)&fat_mem) == 0) {
    printf("Error reading FAT sector.\n");
    return -1;
  };

  uint16 *fat = (uint16 *)&fat_mem;
  uint32 fileClust = fstartClust;
  char *nextAddr = dest;
  do {
    // Read file cluster into memory
    uint32 clusterLBA = firstDataSect + ((fileClust - 2) * _bpb->SectPClust); // Minus 2

    uint8 readscts = diskread(nextAddr, _bpb->SectPClust, clusterLBA);
    // asm("popw %es");

    if (readscts == 0) {
      return -1;
    }

    uint32 oldClust = fileClust;
    fileClust = fat[oldClust];

    if (fileClust == 0) {
      // Unexpected issue with the first FAT table use the second FAT
      fileClust = fat[oldClust];
    }
    nextAddr += ByPClust;

  } while (fileClust != EOFMAGIC);

  return 0;
}
