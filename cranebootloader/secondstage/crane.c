#include <types.h>
#define IMPALASEGMENT 0x6000
#define IMPALAOFFSET 0x0000

extern void prints(char *s);
extern uint8 readsect(char*buf, uint8 numSects, uint32 lba);

extern void initialize_gdt();
extern void initialize_idt();
extern void load_gdt();
extern void load_idt();
extern int16 activate_a20pin();
extern uint16 find_file(char* filename);
extern int16 read_file(uint16 segment, uint16 offset, uint32 fstartClust);

void crane_main(){

  char *welcome = "CRANE BOOTLOADER\r\n";

  prints(welcome);


  char *kernelName = "IMPALA  IMG";
  
  uint32 fileStartClust = find_file(kernelName);

  if(fileStartClust == 0){
    char *knfound = "Kernel not found\r\n";
    prints(knfound);
    return;
  }

  if(read_file(IMPALASEGMENT, IMPALAOFFSET, fileStartClust) != 0){
    char *eReadkern = "Error Occured while reading kernel\r\n";
    prints(eReadkern);
    return;
  }

  if(activate_a20pin() != 0){
    char *a20fail = "Failed to activate A20 pin.\r\n";
    prints(a20fail);
    return;
  }
  initialize_gdt();
  initialize_idt();
  
  load_idt();
  load_gdt();

  asm("nop");

  asm("xor %eax,%eax;\
mov %cr0,%eax;\
or $0x1,%eax;\
mov %eax,%cr0");

  uint16 dataSelector = 0x10;

  asm("mov %%ax, %%ds;\
	mov %%ax,%%es;\
	mov %%ax,%%gs;\
	mov %%ax,%%fs;\
	mov %%ax,%%ss;"
      ::"a"(dataSelector));
  asm("mov $0x2ffff,%esp");

  goto clearPrefetchQue;
  asm("nop; nop; nop;");

 clearPrefetchQue:
 
  asm(" .byte 0x66;\
.byte 0xea;\
.int 0x60000;\
.word 0x0008;");
  
  
}
