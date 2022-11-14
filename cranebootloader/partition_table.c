#include <stdio.h>
#define PART_TABLE_OFFSET 446

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;

typedef struct _partble{
  uint8 bootSig;
  uint8 startHead;
  uint8 startSect;
  uint8 startCylinder;
  uint8 sysSig;
  uint8 endHead;
  uint8 endSect;
  uint8 endCylinder;
  uint32 sectsB4Partion;
  uint32 sectsInPartition;
}__attribute__((packed)) partTableEntry;



void read_partition_table(char *mbr){

  partTableEntry *patitionTable = (partTableEntry*)(mbr + PART_TABLE_OFFSET);

  printf("Boot signature: 0x%x\n",patitionTable[3].bootSig);
  printf("startHead  %d\n",patitionTable[3].startHead);
  printf("startSect  %d\n",patitionTable[3].startSect);
  printf("startCylinder  %d\n",patitionTable[3].startCylinder);
  printf("sysSig  %d\n",patitionTable[3].sysSig);
  printf("endHead  %d\n",patitionTable[3].endHead);
  printf("endSect  %d\n",patitionTable[3].endSect);
  printf("endCylinder  %d\n",patitionTable[3].endCylinder);
  printf("sectsB4Partion  %d\n",patitionTable[3].sectsB4Partion);
  printf("sectsInPartition  %d\n",patitionTable[3].sectsInPartition);
}
