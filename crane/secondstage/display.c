#include <types.h>
#include <string.h>
#include <port.h>

#define VGA 0xb8000
#define VGACMD 0x3d4
#define VGADATA 0x3d5
#define MAXCOLUMNS 80
#define MAXROWS 25
#define TOTALPIXEL 2000
#define DEFAULTATTRIB 0x0f //White on black screen
#define SPACEBAR 0x20
#define ATTRIBSPACE 0x0f20
#define CURSORHI 14
#define CURSORLO 15

extern char *toasci10(uint32, char*);
extern char *toasci16(uint32, char*);

uint16 cursorLocation;

void setcursor(uint16 newCursorLocation) {

  cursorLocation = newCursorLocation;
  uint8 hi = cursorLocation >> 8 ;
  uint8 lo = (uint8)cursorLocation;


  outportb(CURSORHI, VGACMD);

  outportb(hi, VGADATA);

  outportb(CURSORLO, VGACMD);

  outportb(lo, VGADATA);
  
}

void scroll() {

  uint16 *oldText = (uint16*)VGA;
  uint16 *newArea = (uint16*)(VGA + 160);     /* since we are adding one row down,, it might as well be adding one full line of empty columns,just line a new line */
  uint32 movedTextSize = (TOTALPIXEL * 2)- 160;
  memcpy(oldText, newArea, (movedTextSize * 2));

  //Create Empty row for adding text just below
  memsetw((uint16*)(VGA + movedTextSize), ATTRIBSPACE, MAXCOLUMNS);

  //Set Cursor on the new empty line
  setcursor(1920);
}

void clears(void) {

  //clear screen fills the screen with spaces
  memsetw((uint16*)VGA, ATTRIBSPACE, 2000);

  //Set cursor position
  setcursor(0);
}

void handleSpecialChars(char c) {
  //To cater for the ones that advance you to the next line eg: \n \r
  uint32 yAxis;

  if(c == '\n' || c == '\r'){
    yAxis = cursorLocation / MAXCOLUMNS;   //yaxis = cursorLocation / 80, xaxis = cursorLocation mod 80
    yAxis += 1;                            //Advance it to the next line on the y axis
    yAxis *= MAXCOLUMNS;
    setcursor((uint16)yAxis);

    //Create lower empty line and move back the cursor to the begining
    printc(' ');
    cursorLocation -= 1;
    setcursor(cursorLocation);
    
    return;
  }

  switch(c) {
    //TAB
    case '\t':
      prints("    ");                         //4 Spaces
      break;

    //Backspace
    //Takes back cursor, printf a space takes back cursor  
    case '\b':
      cursorLocation -= 1;
      setcursor(cursorLocation);
      printc(' ');
      cursorLocation -= 1;
      setcursor(cursorLocation);
      break;

    default:
      break;
  }
}

void printc(char c) {

  if(c <= 0x1f) {
    handleSpecialChars(c);
    return;
  }

  if(cursorLocation >= TOTALPIXEL) {
    //Scroll
    scroll();
  }
  
  uint32 newCursPos = cursorLocation * 2;
  uint16 *vgaPtr = (uint16*)(VGA + newCursPos);

  //Print the character
  *vgaPtr = DEFAULTATTRIB << 8 | c;

  
  cursorLocation += 1;
  setcursor(cursorLocation);
}

void prints(char *str) {

  for(int i=0; *(str+i) != '\0' ; i++){
    printc((char) *(str + i));
  }
}

void printf(char *fmt, ...) {
    
    int **argptr;
    //Locating parsed args on function call
    asm("mov %%ebp, %0;":"=r"(argptr):);

    // Old ebp, of main
    // ebp             argptr[0]
    // eip of caller   argptr[1]
    // fmt             argptr[2]
    // arg1 of ...     argptr[3]
    // arg2 of ...     argptr[4]

    char buff[1024];
    memset((char*)&buff, '\0', 1024);

    uint32 fmt_i = 0;
    //Choose the next argument after the *fmt
    uint32 arg_i = 3;
    uint32 buff_i = 0;
    char c = fmt[fmt_i];

    asm("nop");
    uint32 lastaddr;
    while(c != '\0'){
        if (c != '%') {
            buff[buff_i] = c;
            fmt_i++;
            buff_i++;
        }
        else {
            // c = %
            // c + 1 = 
            char f = fmt[fmt_i + 1];
            uint32 len;
            switch(f) {
                case 'i':
                    //Integer, todo: check for negative
                    lastaddr = (uint32)toasci10(*&argptr[arg_i] ,(char*)&buff[buff_i]);
                    //calculate address of next position in buff depending on the length of the ascii representation of the converted number
                    buff_i = lastaddr - (uint32)&buff;
                    //Next arg
                    arg_i++;
                    break;
                case 'd':
                    //Decimal base
                    lastaddr = (uint32)toasci10(argptr[arg_i] ,(char*)&buff[buff_i]);
                    buff_i = lastaddr - (uint32)&buff;
                    //Next arg
                    arg_i++;
                    break;
                case 'x':
                    //Hexadecimal
                    lastaddr = (uint32)toasci16(argptr[arg_i] ,(char*)&buff[buff_i]);
                    buff_i = lastaddr - (uint32)&buff;
                    //Next arg
                    arg_i++;
                    break;
                case 's':
                    // char*
                    len = strlen(argptr[arg_i]);
                    strncpy(&buff[buff_i], argptr[arg_i], len);
                    buff_i += len;
                    arg_i++;
                    break;
                default:
                    break;
            }
            fmt_i += 2;
        }
        
        c = fmt[fmt_i];
    }

    prints((char*)&buff);
}
