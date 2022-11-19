#include <stdio.h>
#include "types.h"
#include "partable.h"

typedef struct _partblentry partTableEntry;

partTableEntry *partitionTable;
int numberOfPartitions;

int readPartitionTable(char *mbr){

  numberOfPartitions = 0;

  partitionTable = (partTableEntry*)(mbr + PART_TABLE_OFFSET);

  
  for(int i=0; i < MAXTABLENTRIES; i++){

    if(partitionTable[i].sectsInPartition != 0){
      //If there are sectors in the partition means the partition exists
      numberOfPartitions += 1;
    }
    
  }

  return numberOfPartitions;

  

  /* printf("Boot signature: 0x%x\n",patitionTable[3].bootSig); */
  /* printf("startHead  %d\n",patitionTable[3].startHead); */
  /* printf("startSect  %d\n",patitionTable[3].startSect); */
  /* printf("startCylinder  %d\n",patitionTable[3].startCylinder); */
  /* printf("sysSig  %d\n",patitionTable[3].sysSig); */
  /* printf("endHead  %d\n",patitionTable[3].endHead); */
  /* printf("endSect  %d\n",patitionTable[3].endSect); */
  /* printf("endCylinder  %d\n",patitionTable[3].endCylinder); */
  /* printf("sectsB4Partion  %d\n",patitionTable[3].sectsB4Partion); */
  /* printf("sectsInPartition  %d\n",patitionTable[3].sectsInPartition); */
}

void createPartSrcFile(){

  FILE *srcFilePtr;
  srcFilePtr = fopen("./ptable.s","w");

  for(int i=0; i < MAXTABLENTRIES; i++){
    fprintf(srcFilePtr, "\nbootSig%d:\t.byte 0x%x\n",i , partitionTable[i].bootSig);
    fprintf(srcFilePtr, "startHead%d:\t.byte 0x%x\n",i , partitionTable[i].startHead);
    fprintf(srcFilePtr, "startSect%d:\t.byte 0x%x\n",i , partitionTable[i].startSect);
    fprintf(srcFilePtr, "startCylinder%d:\t.byte 0x%x\n",i , partitionTable[i].startCylinder);
    fprintf(srcFilePtr, "sysSig%d:\t.byte 0x%x\n",i , partitionTable[i].sysSig);
    fprintf(srcFilePtr, "endHead%d:\t.byte 0x%x\n",i , partitionTable[i].endHead);
    fprintf(srcFilePtr, "endSect%d:\t.byte 0x%x\n",i , partitionTable[i].endSect);
    fprintf(srcFilePtr, "endCylinder%d:\t.byte 0x%x\n",i , partitionTable[i].endCylinder);
    fprintf(srcFilePtr, "sectsB4Partion%d:\t.int 0x%x\n",i , partitionTable[i].sectsB4Partion);
    fprintf(srcFilePtr, "sectsInPartition%d:\t.int 0x%x\n",i , partitionTable[i].sectsInPartition);
    
  }

  fclose(srcFilePtr);
  return;
}
