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
//1024 Sectors in one FAT (1024 * 512) / 4 (32bit int) = 131072 FAT 32bit entries
uint32 fat[131072];
//This disk; 1 cluster = 8 sectors
//128 dir entries in one clust (8 * 512) / 32 = 128
dirEntry rootdirClust[128];

fatbpb *_bpb;
uint32 dataSectLba;
uint32 bytesPClust;

int load_fat() {
  //Load the BPB
  if ( !diskread((char *)bpb, 1, osyandaStartSector) ){
    //Failed to read BPB
    return 0;
  }

  _bpb = (fatbpb*)(bpb + FATBPBOFFSET);
  uint32 fatStartSect = osyandaStartSector + _bpb->ResSects;
  bytesPClust = _bpb->SectPClust * _bpb->ByPSect;
  //sizeof(uint32) = 4
  uint32 fatEntriesClust = bytesPClust / 4;
  uint32 fatClusts = _bpb->SectsPFat / _bpb->SectPClust;

  uint32 *fatPtr = (uint32*)&fat;

  //Load the Whole FAT
  for ( uint32 fc = 0; fc < fatClusts; fc += _bpb->SectPClust) {

    if ( !diskread((char *)fatPtr, _bpb->SectPClust, (fatStartSect + fc)) ) {
    // failed to read the FAT
    return -1;
    }

   fatPtr += fatEntriesClust; 
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

  dataSectLba = osyandaStartSector + _bpb->ResSects + (_bpb->SectsPFat * _bpb->FatTabs);
  uint32 rootDirClust = _bpb->firstRootDirClust;

  while( rootDirClust != EOFMAGIC && rootDirClust != EOFMAGIC_2 ){

    uint32 dirSectLba = dataSectLba + ( (rootDirClust - 2) * _bpb->SectPClust );

    //Read the whole Root dir cluster into memory
    if ( !diskread((char *)rootdirClust, _bpb->SectPClust, dirSectLba) ) {
      // Failed to read sector
      printf("Failed to read Root directory Sector\n");
      break;
    };

    int totalEntrySect = bytesPClust / ROOTDIRENTRYSIZE;

    for ( int i = 0; i < totalEntrySect; i++ ){
      // Find file in Root directory
      if( strncmp((char *)rootdirClust[i].dirName, filename, 11) == 0 ){
        /* File Found */
        uint32 filestartCluster = rootdirClust[i].dirFirstClustHi << 16 | rootdirClust[i].dirFirstClustLo;
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

  if( _bpb == 0 ){
    if( load_fat() != 1 ){
      printf("Failed to Read the FAT.\n");
      return;
    }
  }

  uint32 dataClust = fstartClust;
  char *nextAddr = dest;

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
