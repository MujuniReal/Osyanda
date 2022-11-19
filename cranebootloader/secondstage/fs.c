#include "types.h"
#include "string.h"
#include "partable.h"
#include "fat.h"
#define MBRSIZE 512

extern uint8 readsect(char*buf, uint8 numSects, uint32 lba);
typedef struct _partblentry partTableEntry;
partTableEntry *partitionTable;
char mbr[MBRSIZE];
int16 numberOfPartitions;

int16 readPartitionTable(){
  //Read the first Sector of the disk the mbr
  readsect((char*)&mbr, 1, 0);
  numberOfPartitions = 0;

  partitionTable = (partTableEntry*)(mbr + PART_TABLE_OFFSET);
  
  for(uint16 i=0; i < MAXTABLENTRIES; i++){

    if(partitionTable[i].sectsInPartition != 0){
      //If there are sectors in the partition means the partition exists
      numberOfPartitions += 1;
    }
    
  }

  return numberOfPartitions;
}

void detectFs(){

  readPartitionTable();

  if(numberOfPartitions == 0){
    //Disk has no partitions
  }

  //Known file systems FAT first
  fatbpb1216 *bpb = (fatbpb1216*)(mbr + FATBPBOFFSET);

  if(strncmp(bpb->FSType, "FAT", 3) == 0){
    //prepare fat bpb structure src file
    loadFatDependancies(bpb);
  }
  else{
    //Just Create the bpb file as its necessary in the build process
    FILE *bpbSrcPtr;
    bpbSrcPtr = fopen("./fatbpb.s","w");
    fclose(bpbSrcPtr);
  }

}

//This function below is to setup functions that read the selected partition
//Common necessary functions like reading a file from the filesystem of the selected partition
//It takes in pointers to those functions of the selected file system
void initializeSubRoutines(){

}
