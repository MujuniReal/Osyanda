#include <string.h>
#include <types.h>
#include <fat.h>

//This below should come from a header file of fat16bpb
#define MAXROOTENTRIES 512


extern void rdsk(void *buf, int size);
// extern void memset(void *buf, char c, int size);

typedef struct _dirEntry dirEntryStruct;

uint32 first_datacluster;


uint32 find_file_startcluster(char *filename){


  return 0;
  
}


void *readfatfile(uint32 startClust, void *buf, uint32 size){
  //This function sets the firstDataClust variable
}
