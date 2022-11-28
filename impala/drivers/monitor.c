#include <types.h>

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

uint16 cursorLocation;

extern void memsetw(void *s, short int, int size);
extern void outportb(uint8 data, uint16 port);
extern void scroll();
extern void prints(char *str);

void clears(void){

  //clear screen fills the screen with spaces
  //TOTALPIXEL = 2000 divided by 2 1000
  memsetw((uint16*)VGA, ATTRIBSPACE, 1000);

  //Set cursor position
  setcursor(0);
}

void setcursor(uint16 newCursorLocation){

  cursorLocation = newCursorLocation;
  uint8 hi = 0xf & cursorLocation >> 8 ;
  uint8 lo = 0xf & cursorLocation;


  outportb(CURSORHI, VGACMD);

  outportb(hi, VGADATA);

  outportb(CURSORLO, VGACMD);

  outportb(lo, VGADATA);
  
}

void printc(char c){

  if(cursorLocation == TOTALPIXEL){
    //Scroll
    scroll();
  }
  if(c <= 0x1f){
    // prints("")
    uint32 yAxis;
    yAxis = cursorLocation / MAXCOLUMNS;   //yaxis = cursorLocation / 80, xaxis = cursorLocation mod 80
        yAxis += 1;   //Advance it to the next line on the y axis
        yAxis *= MAXCOLUMNS;
        setcursor((uint16)yAxis);
    // switch(c){
    //   case '\n':
    //     yAxis = cursorLocation / MAXCOLUMNS;   //yaxis = cursorLocation / 80, xaxis = cursorLocation mod 80
    //     yAxis += 1;   //Advance it to the next line on the y axis
    //     yAxis *= MAXCOLUMNS;
    //     setcursor((uint16)yAxis);
    //     break;
      
    //   default:
    //     break;
    // }
  }
  uint32 newCursPos = cursorLocation * 2;
  uint16 *vgaPtr = (uint16*)(VGA + newCursPos);

  //Print the character
  *vgaPtr = DEFAULTATTRIB << 8 | c;

  cursorLocation += 1;
  setcursor(cursorLocation);
}