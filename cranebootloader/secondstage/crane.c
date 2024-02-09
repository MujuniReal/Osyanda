#include "types.h"
#include "partable.h"
#define IMPALA_ADDR 0x100000
#define MBRSIZE 512

extern void clears();
extern void prints(char *s);
extern char *diskread(char *buf, uint8 numSects, uint32 lba);
extern int16 readPartitionTable(char *mbr);
extern uint32 (*findFile)(char *filename);
extern int16 (*readFile)(uint32 *dest, uint32 fstartClust);
extern void detectFs(char *mbr);
extern char *toasci10(int number, char *buff);
extern void start_kernel();

uint32 osyandaStartSector;
uint16 sectsPerTrack;
uint16 totalHeads;
typedef struct _partblentry partTableEntry;
typedef struct _fatbpb1216 fatbpb1216;
extern void loadFatDependancies(fatbpb1216 *);
extern partTableEntry **partitionTable;

void crane_main()
{

  // TObe dynamic from setup automatically because it prompts user to select partition at install
  int osyandaPartition = 1;

  clears();
  prints("CRANE BOOTLOADER\n");

  char mbr[MBRSIZE];
  if (diskread((char *)&mbr, 1, 0) == 0)
  {
    prints("Error occured while attempting to read mbr.\n");
    goto hangKernel;
  }

  // Tobe read from a config file to locate partition impala is installed on
  int16 numPartitions = readPartitionTable((char *)&mbr);
  osyandaStartSector = 0;
  if (numPartitions > 0)
  {
    // partTableEntry *entry = mbr + ((osyandaPartition - 1 * ENTRY_SIZE) + PART_TABLE_OFFSET);
    int part_index = osyandaPartition - 1;
    partTableEntry *entry = (partTableEntry *)&partitionTable[0];
    osyandaStartSector = entry->sectsB4Partion;

    char mbrPart[MBRSIZE];
    diskread((char *)&mbrPart, 1, osyandaStartSector);
    loadFatDependancies((char *)&mbrPart);

    // if (diskread((char *)&mbrPart, 1, osyandaStartSector) == 0)
    // {
    //   prints("Failed to read partition bpb\r\n");
    //   goto hangKernel;
    // }
    // detectFs((char *)&mbrPart);
  }
  // else
  // {
  //   detectFs((char *)&mbr);
  // }

  char *kernelName = "IMPALA  IMG";

  uint32 fileStartClust = (uint32)findFile(kernelName);

  if (fileStartClust == 0)
  {
    prints("Kernel not found\n");
    goto hangKernel;
  }

  prints("READING THE KERNEL\n");

  if (readFile((char *)IMPALA_ADDR, fileStartClust) != 0)
  {
    prints("Error Occured while reading kernel.\r\n");
    goto hangKernel;
  }

  asm("nop");
  asm("nop");
  asm("sti");
  asm("nop");
  asm("nop");
  asm("nop");
  start_kernel();

hangKernel:
  goto hangKernel;
}
