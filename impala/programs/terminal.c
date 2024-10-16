#define PRINTC 0x609a4
#define PRINTF 0x60a30
#define READKYBD 0x60bc1
#define CLEARS 0x6085e
#define FINDFILESTART 0x60d42


typedef char (*charFunc)(void);
typedef void (*voiFunc)(void);
typedef void (*voiFuncArg)(char*);
typedef void (*printcTy)(char);
typedef unsigned int (*findF)(char*);

char(*read_kybd)(void) = (charFunc)READKYBD;
void(*printf)(char *fmt, ...) = (voiFuncArg)PRINTF;
void(*printc)(char) = (printcTy)PRINTC;
void(*clears)(void) = (voiFunc)CLEARS;
unsigned int (*find_file_startcluster)(char*) = (findF)FINDFILESTART;

void terminal(){
  
  char *prompt = "impala> ";
  char *cmdNtF = "Command not found.";
  char c;
  int command_index = 0;
  char command[1024];

  clears();
  printf(prompt);

  while(1){
    c = read_kybd();
    if(c == '\r'){
      command[command_index] = '\0';
 	//printf(found_ent);
      printf((char*)&command);
      //unsigned int startCl = find_file_startcluster((char*)&command);
	
      //	if(startCl == 0){
      //  printf(cmdNtF);
      //  asm("nop");
      //	}
	printc('\n');
	printf(prompt);
 	command_index = -1;
   } 
   else if(c == '\0'){ 
     continue;
   } 
  else{ 
     command[command_index] = c;
   } 

     command_index++;
    }
}
