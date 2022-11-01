
extern void printc(char c);
extern void prints(char *s);
extern void clears(void);
extern char read_kybd(void);
extern int lba;

//Syscall
extern void iread(char *block,int blocksize);


void terminal(){

  char *prompt = "impala> ";
  char *found_ent = "Enter Key found\n";
  char c;
  int command_index = 0;
  // char command[1024];
  char mbrdata[512];
  lba = 0;
  iread((char*)&mbrdata,512);
  asm("nop");

  //  clears();
  //prints(prompt);

  /* while(1){ */
  /*   c = read_kybd(); */
  /*   if(c == '\r'){ */
  /*     command[command_index] = '\0'; */
  /* 	//prints(found_ent); */
  /* 	prints((char*)&command); */
  /* 	command_index = -1; */
  /*   } */
  /*   else if(c == '\0'){ */
  /*     continue; */
  /*   } */
  /*   else{ */
  /*     command[command_index] = c; */
  /*   } */

  //    asm("nop");
  //   command_index++;
  //  }
  
  
}
