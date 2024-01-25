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

// TObe dynamic from setup automatically because it prompts user to select partition at install
int16 osyandaPartition = 1;
uint32 osyandaStartSector;
uint16 sectsPerTrack;
uint16 totalHeads;
typedef struct _partblentry partTableEntry;

void crane_main()
{

  clears();
  prints("CRANE BOOTLOADER\r\n");

  char mbr[MBRSIZE];
  if (diskread((char *)&mbr, 1, 0) == 0)
  {
    prints("Error occured while attempting to read mbr.\r\n");
    goto hangKernel;
  }

  // Tobe read from a config file to locate partition impala is installed on
  int16 numPartitions = readPartitionTable((char *)&mbr);
  osyandaStartSector = 0;
  if (numPartitions > 0)
  {
    partTableEntry *entry = mbr + ((osyandaPartition - 1 * ENTRY_SIZE) + PART_TABLE_OFFSET);
    osyandaStartSector = entry->sectsB4Partion;

    char mbrPart[MBRSIZE];

    if (diskread((char *)&mbrPart, 1, osyandaStartSector) == 0)
    {
      prints("Failed to read partition bpb\r\n");
      goto hangKernel;
    }
    detectFs((char *)&mbrPart);
  }
  else
  {
    detectFs((char *)&mbr);
  }

  char *kernelName = "IMPALA  IMG";

  uint32 fileStartClust = (uint32)findFile(kernelName);

  if (fileStartClust == 1343488)
  {
    asm("nop");
  }

  if (fileStartClust == 0)
  {
    prints("Kernel not found\r\n");
    goto hangKernel;
  }

  prints("READING THE KERNEL\r\n");
  char charb[1024];
  toasci10(fileStartClust, (char *)&charb);
  prints("Kernel starts on: ");
  prints((char *)&charb);
  prints("\r\n");

  if (readFile((char *)IMPALA_ADDR, fileStartClust) != 0)
  {
    prints("Error Occured while reading kernel.\r\n");
    goto hangKernel;
  }

  asm("nop");

  start_kernel();

hangKernel:
  goto hangKernel;
}
