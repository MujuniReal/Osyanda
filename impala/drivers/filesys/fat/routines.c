#include <string.h>
#include <types.h>
#include <fs/dirstruct.h>

//This below should come from a header file of fat16bpb
#define MAXROOTENTRIES 512


extern void rdsk(void *buf, int size);

typedef struct dirEntry dirEntryStruct;

short int fat_tab[65536];
dirEntryStruct rootdir_mem[MAXROOTENTRIES];
uint32 rootdir_start;
uint32 firstDataClust;

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
