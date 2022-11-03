#include <string.h>
#include <types.h>
#include <fs/dirstruct.h>

//This below should come from a header file of fat16bpb
#define MAXROOTENTRIES 512


extern void rdsk(void *buf, int size);

typedef struct dirEntry dirEntryStruct;

uint16 fat_tab[65536];
dirEntryStruct rootdir_mem[MAXROOTENTRIES];
uint32 rootdir_start;
uint32 firstDataClust;


struct fat16bpb {
  char devOEM[8];
  uint16 byPsect;
  uint8 sectPclust;
  uint16 resSects;
  uint8 fatTabs;
  uint16 nRootDirEs;
  uint16 totSects;
  uint16 medDescr;
  uint16 sectsPfat;
  uint16 sectsPtrck;
  uint16 nHeads;
  uint16 nHiddenSects;
  uint16 nHiddenSectsHi;
  uint32 totSectsFs;
  uint8 drvNo;
  uint8 resrvd;
  uint8 extSig;
  uint32 drvSerNum;
  char volLabel[11];
  char fsType[8];
  
}__attribute__((packed));

void readfat(void){

  
}

uint32 find_file_startcluster(char *filename){

  int i = 0;
  
  for(i ; i < MAXROOTENTRIES; i++){

    dirEntryStruct entry = rootdir_mem[i];
    //TODO add in formatters to handle file.extension ie. file.txt
    if(strcmp(filename, (char*)&entry.dirName) == 0){
     
      uint32 startCluster = entry.dirFirstClustHi << 16 | entry.dirFirstClustLo;
      
      return startCluster;
    }
  }

  return 0;
  
}


void *readfatfile(uint32 startClust, void *buf, uint32 size){
  //This function sets the firstDataClust variable
}
