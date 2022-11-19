#include <stdio.h>
#include <string.h>
#include "fat.h"
/* #include "partable.h" */

typedef struct _fatbpb1216 fatbpb1216;
//typedef struct _partblentry partTableEntry;
//extern partTableEntry *partitionTable;
extern int numberOfPartitions;
extern void handleFat(char *mbr);

void detectFs(char *mbr){

  if(numberOfPartitions == 0){
    //Disk has no partitions
  }

  //Known file systems FAT first
  fatbpb1216 *bpb = (fatbpb1216*)(mbr + FATBPBOFFSET);

  if(strncmp(bpb->FSType, "FAT", 3) == 0){
    //prepare fat bpb structure src file
    handleFat(mbr);
  }
  else{
    //Just Create the bpb file as its necessary in the build process
    FILE *bpbSrcPtr;
    bpbSrcPtr = fopen("./fatbpb.s","w");
    fclose(bpbSrcPtr);
  }
  
}
