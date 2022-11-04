#define PRINTS 0x0
#define READKYBD 0x1


typedef char (*charFunc)(void);
typedef void (*voiFunc)(void);



void terminal(){

  char(*read_kybd)(void) = (charFunc)READKYBD;
  void(*prints)(void) = (voiFunc)PRINTS;
  
  char *prompt = "impala> ";
  char *found_ent = "Enter Key found\n";
  char c;
  int command_index = 0;
  // char command[1024]

  asm("nop");
}
