#include "types.h"
#include "string.h"
#include "fat.h"
#define ROOTDIRENTRYSIZE 32
#define EOFMAGIC 0xffff

extern void prints(char *s);
extern uint8 readsect(char *buf, uint8 numSects, uint32 lba);
char activeFat[6]; //Active FAT String
/* extern uint16 ResSects; */
/* extern uint16 SectsPFat; */
/* extern uint8 FatTabs; */
/* extern uint16 NRootDirEs; */
/* extern uint16 ByPSect; */
/* extern uint8 SectPClust; */

typedef struct _dirEntry dirEntry;

uint16 *load_fat(uint16 *fat);

loadFatDependancies(char *fatbpb){

  //Detect which FAT is Exactly
  //Initialize Rootdir
  //Initialize FAT
  //Initialize required variables
  
  
}


//Returns 0 if file not found, returns file start Cluster number if file found
uint32 find_file(char *filename){

  char rootdirSect[ByPSect];

  uint32 rootdirStart = ResSects + (SectsPFat * FatTabs);
  uint32 rootdirSectors = (NRootDirEs * ROOTDIRENTRYSIZE) / ByPSect;
  uint16 dirEntriesInSect = ByPSect / ROOTDIRENTRYSIZE;


  uint16 i = 0;
  for(i; i < rootdirSectors; i++){
    uint32 dirSectLba = rootdirStart + i;

    if(readsect((char*)&rootdirSect, 1, dirSectLba) == 0){
      //Failed to read sector
      break;
    };
    
    dirEntry *rootdirMem = (dirEntry*)&rootdirSect;

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

int16 read_file(uint16 segment, uint16 offset, uint32 fstartClust){

  uint32 fatSize = SectsPFat * ByPSect;
  uint32 rootdirStart = ResSects + (SectsPFat * FatTabs);
  uint32 rootdirSectors = (NRootDirEs * ROOTDIRENTRYSIZE) / ByPSect;
  uint32 firstDataSect = rootdirStart + rootdirSectors;
  uint32 ByPClust = SectPClust * ByPSect;
  uint16 ByPSeg = ByPClust / 16;     //Real address / 16 = segment
  
  //Because fat16 entry in fat is 2bytes
  //Load Just one sector of the FAT for now
  uint16 fat[ByPSect];

  if(load_fat(fat) == 0){
    char *errFat = "Error reading FAT sector.\r\n";
    prints(errFat);
    return -1;
  };
  
  uint16 fileClust = fstartClust;
  uint16 nextSegment = segment;
  do {
    //Read file cluster into memory
    uint32 clusterLBA = firstDataSect + ((fileClust - 2) * SectPClust);  //Minus 2

    //Since we are reading the file to a special segment
    asm("pushw %es");

    asm("mov %%ax,%%es"::"a"(nextSegment));

    uint8 readscts = readsect((char*)offset, SectPClust, clusterLBA);
    asm("popw %es");
    
    if(readscts == 0){
      return -1;
    }

    fileClust = fat[fileClust];
    nextSegment += ByPSeg;
    
  } while(fileClust != EOFMAGIC);
    
    return 0;
  

}


uint16 *load_fat(uint16 *fat){
  
  uint32 fatStartSect = ResSects + 0;

  if(readsect((char*)fat, 1, fatStartSect) == 0){
    uint16 *nullPtr = 0;
    return nullPtr;
  }

  return fat;
  
}
