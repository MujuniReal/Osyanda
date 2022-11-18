#include "types.h"

#ifndef PARTABLE_H
#define PARTABLE_H

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
