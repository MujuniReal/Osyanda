#include "types.h"
#include "string.h"
#include "partable.h"
#include "fat.h"
#define MBRSIZE 512

typedef struct _fatbpb1216 fatbpb1216;
typedef struct _partblentry partTableEntry;
typedef int16 (*readFileFunc)(uint32*, uint32);
typedef uint32 (*findFileFunc)(char*);

extern uint8 diskread(char*buf, uint8 numSects, uint32 lba);
extern void loadFatDependancies(fatbpb1216*);

partTableEntry *partitionTable;

int16 numberOfPartitions;

findFileFunc findFile;

readFileFunc readFile;

int16 readPartitionTable(char *mbr){
  //Read the first Sector of the disk the mbr
  //diskread((char*)&mbr, 1, 0);
  numberOfPartitions = 0;

  partitionTable = (partTableEntry*)(mbr + PART_TABLE_OFFSET);
  
  for(uint16 i=0; i < MAXTABLENTRIES; i++){

    if(partitionTable[i].sectsInPartition != 0){
      //If there are sectors in the partition means the partition exists
      numberOfPartitions += 1;
    } else{
      return 0;
    }
    
  }

  return numberOfPartitions;
}

void detectFs(char *mbr){

  //readPartitionTable(mbr);

  fatbpb1216 *bpb = (fatbpb1216*)(mbr + FATBPBOFFSET);
//  if(numberOfPartitions == 0){
    //Disk has no partitions
    //    bpb
//  }
  //If it has partitions the file system identifier wont be in the bpb
//  else{
    //Calculate the offset to the partition containing the fs
    //Read the bpb of the start of the bpb containing FS info
    //and update the bpb variable
//  }
  //Known file systems FAT first
  

  if(strncmp(bpb->FSType, "FAT", 3) == 0){
    loadFatDependancies(bpb);
  }
  else{
    //not a FAT fs
  }

}