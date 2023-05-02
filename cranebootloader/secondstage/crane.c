#include "types.h"
#include "partable.h"
#define IMPALASEGMENT 0x6000
#define IMPALAOFFSET 0x0000
#define MBRSIZE 512

extern void prints(char *s);
extern uint8 readsect(char*buf, uint8 numSects, uint32 lba);
extern int16 readPartitionTable(char* mbr);
extern uint32 (*findFile)(char* filename);
extern int16 (*readFile)(uint16 segment, uint16 offset, uint32 fstartClust);
extern void detectFs(char* mbr);
extern void initialize_gdt();
extern void initialize_idt();
extern void load_gdt();
extern void load_idt();
extern int16 activate_a20pin();
extern char *toasci10(int number, char *buff);
extern struct _partblentry *partitionTable;


//TObe dynamic from setup automatically because it prompts user to select partition at install
int16 osyandaPartition = 1;
uint32 osyandaStartSector;


void crane_main(){

  prints("CRANE BOOTLOADER\r\n");

 
  
//   char mbr[MBRSIZE];
//   if(readsect((char*)&mbr, 1, 0) == 0){
//     prints("Error occured while attempting to read mbr.\r\n");
//     goto hangKernel;
//   }
  
//   //Tobe read from a config file to locate partition impala is installed on
//   int16 numPartitions = readPartitionTable((char*)&mbr);
//   osyandaStartSector = 0;
//   if(numPartitions > 0){
//     osyandaStartSector = partitionTable[osyandaPartition-1].sectsB4Partion;
    
//     char mbrPart[MBRSIZE];
    
//     if(readsect((char*)&mbrPart, 1, osyandaStartSector) == 0){
//       prints("Failed to read partition bpb\r\n");
//       goto hangKernel;
//     }
//     detectFs((char*)&mbrPart);
//   }
//   else{
//     detectFs((char*)&mbr);
//   }

//   char *kernelName = "IMPALA  IMG";
  
//   uint32 fileStartClust = (uint32)findFile(kernelName);

//   if(fileStartClust == 0){
//     prints("Kernel not found\r\n");
//     goto hangKernel;
//   }

//   if(readFile(IMPALASEGMENT, IMPALAOFFSET, fileStartClust) != 0){
//     prints("Error Occured while reading kernel.\r\n");
//     goto hangKernel;
//   }

//   if(activate_a20pin() != 0){
//     char *a20fail = "Failed to activate A20 pin.\r\n";
//     prints(a20fail);
//     //    return;
//   }
//   initialize_gdt();
//   // initialize_idt();
  
//   // load_idt();
//   load_gdt();
//   //  asm("int $0x16"::"a"(0x0));

//   asm("nop");

//   asm("xor %eax,%eax;\
//       mov %cr0,%eax;\
//       or $0x1,%eax;\
//       mov %eax,%cr0"
//       );

//   uint16 dataSelector = 0x10;

//   asm("mov %%ax, %%ds;\
// 	    mov %%ax,%%es;\
// 	    mov %%ax,%%gs;\
// 	    mov %%ax,%%fs;\
// 	    mov %%ax,%%ss;"
//       ::"a"(dataSelector));

//   asm("mov $0x2ffff,%esp");

//   goto clearPrefetchQue;
//   asm("nop; nop; nop;");

//  clearPrefetchQue:
 
//   asm(" .byte 0x66;\
//         .byte 0xea;\
//         .int 0x60000;\
//         .word 0x0008;"
//         );
  
hangKernel:
    goto hangKernel;
}
