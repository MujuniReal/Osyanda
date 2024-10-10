#include "types.h"
#include "partable.h"
#include "display.h"
#define IMPALA_ADDR 0x100000
#define MBRSIZE 512

extern char *diskread(char *buf, uint8 numSects, uint32 lba);
extern void start_kernel();

//File system specific 
extern uint32 find_file(char*);
extern int16 read_file(char*, uint32);

typedef struct _partblentry partTableEntry;

uint32 osyandaStartSector;

int16 load_partable(char *mbr);

void crane_main() {

  // Tobe dynamic from setup automatically because it prompts user to select partition at install
  // // Tobe read from a config file to locate partition impala is installed on
  int osyandaPartition = 1;

  clears();
  printf("CRANE BOOTLOADER\n");

  char mbr[MBRSIZE];
  if ( !diskread((char *)&mbr, 1, 0) ) {
    printf("Error occured while attempting to read mbr.\n");
    goto hangKernel;
  }

  // osypart - 1 = osy_index
  // osy_index * part_entry_size = part_offset
  int partition_offset = (osyandaPartition - 1) * ENTRY_SIZE; 
  partTableEntry *entry = (partTableEntry*)(mbr + PART_TABLE_OFFSET + partition_offset);
  osyandaStartSector = entry->sectsB4Partion;

  printf("Start Sector: %d\n", osyandaStartSector);

  char *kernelName = "IMPALA  IMG";

  uint32 fileStartClust = find_file(kernelName);

  if (fileStartClust == 0) {
    printf("Kernel not found\n");
    goto hangKernel;
  }

  printf("LOADING THE KERNEL\n");

  if ( read_file((char *)IMPALA_ADDR, fileStartClust) != 0 ) {
    printf("Error Occured while reading kernel.\r\n");
    goto hangKernel;
  }

  start_kernel();

hangKernel:
  goto hangKernel;
}