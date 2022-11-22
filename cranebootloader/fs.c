#include <stdio.h>
#include <string.h>
#include "fat.h"
/* #include "partable.h" */

typedef struct _fatbpb1216 fatbpb1216;
typedef struct _fatbpb32 fatbpb32;
//typedef struct _partblentry partTableEntry;
//extern partTableEntry *partitionTable;
extern int numberOfPartitions;
extern void handleFat(char *mbr);

char *detectFs(char *mbr){

  //Returns FSname
  char fsName[10];

  //Disk has no partitions
  //Known file systems FAT first
  fatbpb1216 *bpb = (fatbpb1216*)(mbr + FATBPBOFFSET);
  fatbpb32 *bpb32 = (fatbpb32*)(mbr + FATBPBOFFSET);

  if(strncmp(bpb->FSType, "FAT", 3) == 0){

    //prepare fat bpb structure src file
    handleFat(mbr);
    strncpy((char*)&fsName, bpb->FSType, 5);
    return (char*)bpb->FSType;
  }
  else if(strncmp(bpb32->FSType, "FAT", 3) == 0){

    handleFat(mbr);
    return (char*)bpb32->FSType;
  }
  else{
    //Just Create the bpb file as its necessary in the build process
    FILE *bpbSrcPtr;
    bpbSrcPtr = fopen("./fatbpb.s","w");
    fclose(bpbSrcPtr);
  }
  
  
}
