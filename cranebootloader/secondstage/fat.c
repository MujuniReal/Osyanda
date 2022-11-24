#include "types.h"
#include "string.h"
#include "fat.h"
#define ROOTDIRENTRYSIZE 32
#define EOFMAGIC 0xffff

typedef struct _fatbpb1216 fatbpb1216;
typedef struct _dirEntry dirEntry;
typedef uint32 (*findFileFunc)(char*);
typedef int16 (*readFileFunc)(uint16, uint16, uint32);

extern void prints(char *s);
extern uint8 readsect(char *buf, uint8 numSects, uint32 lba);
extern char *toasci10(int number, char *buff);
extern findFileFunc findFile;
extern readFileFunc readFile;
extern uint16 sectsPerTrack;
extern uint16 totalHeads;
extern uint32 osyandaStartSector;

uint32 find_file16(char*);
int16 read_file16(uint16, uint16, uint32);
fatbpb1216 *activeBpb;

void loadFatDependancies(fatbpb1216 *fatbpb){

  //Detect which FAT is Exactly
  //Initialize Rootdir
  //Initialize FAT
  //Initialize required variables

  activeBpb = fatbpb;

  if(strncmp(fatbpb->FSType, "FAT16", 5) == 0){
    //prints("FAT16 Detected\r\n");
    //Set data from bpb as standard
    sectsPerTrack = fatbpb->SectsPTrck;
    totalHeads = fatbpb->NHeads;
    findFile = (findFileFunc)find_file16;
    readFile = (readFileFunc)read_file16;
  }
  else{
    //Handle Other file systems here
    prints("Other FAT is detected\r\n");
  }
  
}


//Returns 0 if file not found, returns file start Cluster number if file found
uint32 find_file16(char *filename){

  char rootdirSect[512];

  uint32 rootdirStart = osyandaStartSector + activeBpb->ResSects + (activeBpb->SectsPFat * activeBpb->FatTabs);
  uint32 rootdirSectors = (activeBpb->NRootDirEs * ROOTDIRENTRYSIZE) / activeBpb->ByPSect;
  uint16 dirEntriesInSect = activeBpb->ByPSect / ROOTDIRENTRYSIZE;


  uint16 i = 0;
  for(i; i < rootdirSectors; i++){
    
    uint32 dirSectLba = rootdirStart + i;

    if(readsect((char*)&rootdirSect, 1, dirSectLba) == 0){
      //Failed to read sector
      break;
    };
    
    dirEntry *rootdirMem = (dirEntry*)&rootdirSect;

    //The root directory
    for(uint16 e=0; e < dirEntriesInSect; e++){

      if(strncmp((char*)&rootdirMem[e].dirName,filename, 11) == 0){
	      /* File Found */
	      uint32 filestartCluster = rootdirMem[e].dirFirstClustHi << 16 | rootdirMem[e].dirFirstClustLo;
	      return filestartCluster;
      } 
    }
  }

  
  /* File Not Found */
  return 0;
}

uint16 *load_fat(uint16 *fat){

  
  uint32 fatStartSect = osyandaStartSector + activeBpb->ResSects + 0;

  if(readsect((char*)fat, 1, fatStartSect) == 0){
    uint16 *nullPtr = 0;
    return nullPtr;
  }

  return fat;
  
}


int16 read_file16(uint16 segment, uint16 offset, uint32 fstartClust){

  uint32 fatSize = activeBpb->SectsPFat * activeBpb->ByPSect;
  uint32 rootdirStart = osyandaStartSector + activeBpb->ResSects + (activeBpb->SectsPFat * activeBpb->FatTabs);
  uint32 rootdirSectors = (activeBpb->NRootDirEs * ROOTDIRENTRYSIZE) / activeBpb->ByPSect;
  uint32 firstDataSect = rootdirStart + rootdirSectors;
  uint32 ByPClust = activeBpb->SectPClust * activeBpb->ByPSect;
  uint16 ByPSeg = ByPClust / 16;     //Real address / 16 = segment
  
  //Because fat16 entry in fat is 2bytes
  //Load Just one sector of the FAT for now
  uint16 fat[activeBpb->ByPSect];

  if(load_fat(fat) == 0){
    prints("Error reading FAT sector.\r\n");
    return -1;
  };
  
  uint16 fileClust = fstartClust;
  uint16 nextSegment = segment;
  do {
    //Read file cluster into memory
    uint32 clusterLBA = firstDataSect + ((fileClust - 2) * activeBpb->SectPClust);  //Minus 2

    //Since we are reading the file to a special segment
    asm("pushw %es");

    asm("mov %%ax,%%es"::"a"(nextSegment));

    uint8 readscts = readsect((char*)offset, activeBpb->SectPClust, clusterLBA);
    asm("popw %es");
    
    if(readscts == 0){
      return -1;
    }

    fileClust = fat[fileClust];
    nextSegment += ByPSeg;
    
  } while(fileClust != EOFMAGIC);
    
  return 0;
  

}
