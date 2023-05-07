#include "types.h"
#include "partable.h"
#define IMPALA_ADDR 0x100000
#define MBRSIZE 512

extern void clears();
extern void prints(char *s);
extern char *diskread(char*buf, uint8 numSects, uint32 lba);
extern int16 readPartitionTable(char* mbr);
extern uint32 (*findFile)(char* filename);
extern int16 (*readFile)(uint16 segment, uint16 offset, uint32 fstartClust);
extern void detectFs(char* mbr);
extern char *toasci10(int number, char *buff);
extern struct _partblentry *partitionTable;


//TObe dynamic from setup automatically because it prompts user to select partition at install
int16 osyandaPartition = 1;
uint32 osyandaStartSector;
uint16 sectsPerTrack;
uint16 totalHeads;


void crane_main(){

  clears();
  prints("CRANE BOOTLOADER\r\n");

 
  
  char mbr[MBRSIZE];
  if(diskread((char*)&mbr, 1, 0) == 0){
    prints("Error occured while attempting to read mbr.\r\n");
    goto hangKernel;
  }
  
  //Tobe read from a config file to locate partition impala is installed on
  int16 numPartitions = readPartitionTable((char*)&mbr);
  osyandaStartSector = 0;
  if(numPartitions > 0){
    osyandaStartSector = partitionTable[osyandaPartition-1].sectsB4Partion;
    
    char mbrPart[MBRSIZE];
    
    if(diskread((char*)&mbrPart, 1, osyandaStartSector) == 0){
      prints("Failed to read partition bpb\r\n");
      goto hangKernel;
    }
    detectFs((char*)&mbrPart);
  }
  else{
    detectFs((char*)&mbr);
  }

  char *kernelName = "IMPALA  IMG";
  
  uint32 fileStartClust = (uint32)findFile(kernelName);

  if(fileStartClust == 0){
    prints("Kernel not found\r\n");
    goto hangKernel;
  }

  if(readFile(IMPALA_ADDR, fileStartClust) != 0){
    prints("Error Occured while reading kernel.\r\n");
    goto hangKernel;
  }
  
hangKernel:
    goto hangKernel;
}
