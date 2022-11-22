#include "types.h"
#include "string.h"
#include "partable.h"
#include "fat.h"
#define MBRSIZE 512

extern uint8 readsect(char*buf, uint8 numSects, uint32 lba);
typedef struct _fatbpb1216 fatbpb1216;
typedef struct _partblentry partTableEntry;
extern void loadFatDependancies(fatbpb1216*);
partTableEntry *partitionTable;
char mbr[MBRSIZE];
int16 numberOfPartitions;

typedef uint32 (*findFileFunc)(char*);
findFileFunc findFile;
typedef int16 (*readFileFunc)(uint16, uint16, uint32);
readFileFunc readFile;

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

  fatbpb1216 *bpb;
  if(numberOfPartitions == 0){
    //Disk has no partitions
    bpb = (fatbpb1216*)(mbr + FATBPBOFFSET);
  }
  //If it has partitions the file system identifier wont be in the bpb
  else{
    //Calculate the offset to the partition containing the fs
    //Read the bpb of the start of the bpb containing FS info
    //and update the bpb variable
  }
  //Known file systems FAT first
  

  if(strncmp(bpb->FSType, "FAT", 3) == 0){
    loadFatDependancies(bpb);
  }
  else{
    //not a FAT fs
  }

}

//This function below is to setup functions that read the selected partition
//Common necessary functions like reading a file from the filesystem of the selected partition
//It takes in pointers to those functions of the selected file system
void initializeSubRoutines(){

}
