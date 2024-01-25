#include "types.h"

#ifndef PARTABLE_H
#define PARTABLE_H

#define PART_TABLE_OFFSET 446
#define MAXTABLENTRIES 4
#define ENTRY_SIZE 16
#define MAX_TABLE_SIZE 64


struct _partblentry{
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
}__attribute__((packed));

#endif
