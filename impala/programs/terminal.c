#define PRINTC 0x60a08
#define PRINTS 0x60a58
#define READKYBD 0x60b07
#define CLEARS 0x60975

typedef char (*charFunc)(void);
typedef void (*voiFunc)(void);
typedef void (*voiFuncArg)(char*);
typedef void (*printcTy)(char);

char(*read_kybd)(void) = (charFunc)READKYBD;
void(*prints)(char*) = (voiFuncArg)PRINTS;
void(*printc)(char) = (printcTy)PRINTC;
void(*clears)(void) = (voiFunc)CLEARS;

void terminal(){
  
  char *prompt = "impala> ";
  char *found_ent = "Enter Key found\n";
  char c;
  int command_index = 0;
  char command[1024];

  asm("nop");

  clears();
  prints(prompt);

  while(1){
    c = read_kybd();
    if(c == '\r'){
      command[command_index] = '\0';
 	//prints(found_ent);
	prints((char*)&command);
	printc('\n');
	prints(prompt);
 	command_index = -1;
   } 
   else if(c == '\0'){ 
     continue;
   } 
  else{ 
     command[command_index] = c;
   } 

     asm("nop");
     command_index++;
    }
}
