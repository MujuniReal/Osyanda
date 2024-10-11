#include "types.h"
#include "string.h"
#include "display.h"
#include "fat.h"
#define ROOTDIRENTRYSIZE 32
#define EOFMAGIC    0x0fffffff
#define EOFMAGIC_2  0x0ffffff8

typedef struct _dirEntry dirEntry;

extern uint8 diskread(char *buf, uint8 numSects, uint32 lba);
extern uint32 osyandaStartSector;


typedef struct _fatbpb32 fatbpb;
uint8 bpb[512];
//1024 Sectors in one FAT 1024 / 4 = 256
uint32 fat[256];
//16 dir entries 16 * 32 = 512
dirEntry rootdirSect[16];

uint32 dataSectLba;

int load_fat() {
  //Load the BPB
  if ( !diskread((char *)bpb, 1, osyandaStartSector) ){
    //Failed to read BPB
    return 0;
  }

  fatbpb *_bpb = (fatbpb*)(bpb + FATBPBOFFSET);
  uint32 fat_start_sect = osyandaStartSector + _bpb->ResSects;
  // uint32 fat2StartSect = osyandaStartSector + _bpb->ResSects + _bpb->SectsPFat;

  //Load the Whole FAT
  // !diskread((char *)fat, _bpb->SectsPFat, fat_start_sect)
  // For now lets load 1 FAT Sector but this is to be changed in the future
  if ( !diskread((char *)fat, 1, fat_start_sect) ) {
    // failed to read the FAT
    return -1;
  }

  return 1;
}


// Returns 0 if file not found, returns file start Cluster number if file found
uint32 find_file(char *filename) {
  
  //Locate BPB and start finding the file
  int fatstat = load_fat();

  if( fatstat == 0 ){
    printf("Failed to read the BPB of the partition.\n");
    return;
  }

  if( fatstat == -1 ){
    printf("Failed to Read the FAT.\n");
    return;
  }

  fatbpb *_bpb = (fatbpb*)(bpb + FATBPBOFFSET);

  dataSectLba = osyandaStartSector + _bpb->ResSects + (_bpb->SectsPFat * _bpb->FatTabs);
  uint32 rootDirClust = _bpb->firstRootDirClust;


  while( rootDirClust != EOFMAGIC && rootDirClust != EOFMAGIC_2 ){

    uint32 dirSectLba = dataSectLba + ( (rootDirClust - 2) * _bpb->SectPClust );

    if ( !diskread((char *)rootdirSect, 1, dirSectLba) ) {
      // Failed to read sector
      printf("Failed to read Root directory Sector\n");
      break;
    };

    int totalEntrySect = _bpb->ByPSect / ROOTDIRENTRYSIZE;

    for ( int i = 0; i < totalEntrySect; i++ ){
      // Find file in Root directory
      if( strncmp((char *)rootdirSect[i].dirName, filename, 11) == 0 ){
        /* File Found */
        uint32 filestartCluster = rootdirSect[i].dirFirstClustHi << 16 | rootdirSect[i].dirFirstClustLo;
        return filestartCluster;
      }
    }

    rootDirClust = fat[rootDirClust];
  }
  /* File Not Found */
  return 0;
}



int16 read_file(char *dest, uint32 fstartClust) {

  //Might Need to load another sector of FAT in memory in case the kernel file is too large

  fatbpb *_bpb = (fatbpb*)(bpb + FATBPBOFFSET);

  uint32 dataClust = fstartClust;
  char *nextAddr = dest;
  uint32 bytesPClust =  _bpb->ByPSect * _bpb->SectPClust;

  int fat_i = 0;

  while( dataClust != EOFMAGIC && dataClust != EOFMAGIC_2 ){

    uint32 fileSectLba = dataSectLba + ( (dataClust - 2) * _bpb->SectPClust );

    if( !diskread(nextAddr, _bpb->SectPClust, fileSectLba) ){
      //Failed to read file data sectors
      return -1;
    }

    nextAddr += bytesPClust;
    dataClust = fat[dataClust];

  }

  return 0;
}
