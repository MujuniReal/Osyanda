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

typedef struct _monitorAxis{
  uint8 x;
  uint8 y;
} monitorAxis;

monitorAxis cursrPos = {x: 0, y: 0};     //Cursor positiion

void memsetw(void *s, short int, int size);

void clears(void){

  //clear screen fills the screen with spaces
  //TOTALPIXEL = 2000 divided by 2 1000
  memsetw((uint16*)VGA, ATTRIBSPACE, 1000);

  //Set cursor position
  cursrPos.x = 0;
  cursrPos.y = 0;
  
  setcursor();
}

void setcursor(){

  
}
