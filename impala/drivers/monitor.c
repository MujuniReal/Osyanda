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

uint16 cursorLocation;

void setcursor(uint16 newCursorLocation){

  cursorLocation = newCursorLocation;
  uint8 hi = 0xf & cursorLocation >> 8 ;
  uint8 lo = 0xf & cursorLocation;


  outportb(CURSORHI, VGACMD);

  outportb(hi, VGADATA);

  outportb(CURSORLO, VGACMD);

  outportb(lo, VGADATA);
  
}

void scroll(){

  uint16 *oldText = (uint16*)VGA;
  uint16 *newArea = (uint16*)(VGA + 160);     /* since we are adding one row down,, it might as well be adding one full line of empty columns,just line a new line */
  uint32 movedTextSize = TOTALPIXEL - 160;
  memcpy(oldText, newArea, movedTextSize);

  //Create Empty row for adding text just below
  memsetw((uint16*)(VGA + movedTextSize), ATTRIBSPACE, MAXCOLUMNS);

  //Set Cursor on the new empty line
  setcursor(1920);
}

void clears(void){

  //clear screen fills the screen with spaces
  //TOTALPIXEL = 2000 divided by 2 1000
  memsetw((uint16*)VGA, ATTRIBSPACE, TOTALPIXEL);

  //Set cursor position
  setcursor(0);
}

void handleSpecialChars(char c){
  //To cater for the ones that advance you to the next line eg: \n \r
  uint32 yAxis;

  switch(c){
    case '\n':
      yAxis = cursorLocation / MAXCOLUMNS;   //yaxis = cursorLocation / 80, xaxis = cursorLocation mod 80
      yAxis += 1;                            //Advance it to the next line on the y axis
      yAxis *= MAXCOLUMNS;
      setcursor((uint16)yAxis);
      break;
      
    default:
      break;
  }
}

void printc(char c){

  if(cursorLocation == TOTALPIXEL){
    //Scroll
    scroll();
  }
  if(c <= 0x1f){
    handleSpecialChars(c);
    return;
  }
  uint32 newCursPos = cursorLocation * 2;
  uint16 *vgaPtr = (uint16*)(VGA + newCursPos);

  //Print the character
  *vgaPtr = DEFAULTATTRIB << 8 | c;

  cursorLocation += 1;
  setcursor(cursorLocation);
}

void prints(char *str){

  for(int i=0; *(str+i) != '\0' ; i++){
    printc((char) *(str + i));
  }
}

