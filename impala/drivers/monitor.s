#define VGA_ADDRESS 0xb8000
#define VIDEO_CMD_PORT 0x3d4
#define VIDEO_DATA_PORT 0x3d5
#define MAX_COLUMNS 80              /* maximum number of columns is 80 x axis */
#define MAX_ROWS 25                 /* maximum number of rows 25 y axis */
#define TOTAL_PIXEL (MAX_COLUMNS*MAX_ROWS)
#define DEFAULT_ATTRIBUTE 0x0f      /* white on black, ie higher 4bits->background, lower 4bits-> text/cursor color */
#define SPACEBAR 0x20
#define ATTRIB_SPACE 0x0f20         /* attribute and character 2bytes */
.code32
.text
.global clears
//memsetw(uint16*, )
//void clears(void);   clearscreen
//function(3,2,1) -- calling convention
clears:
    xor %eax,%eax
    push $TOTAL_PIXEL
    movw $ATTRIB_SPACE,%ax   /* fill screen with spaces spaces is 0x20 thus clearing screen*/                       
    push %eax  
    push $VGA_ADDRESS
    call memsetw
    add $0xc,%esp

    movw $0x0000,(cursr_pos)               /* After clearing screen, set cursor to 0,0 top left */
    call setcursor
    pop
    ret

//void setcursor();
setcursor:
    movw cursr_pos,%ax
    out %ah,$VIDEO_CMD_PORT         /* high byte for cursor location */
    out %al,$VIDEO_DATA_PORT        /* low byte for cursor location */
    ret                                /* cursor location y = overall location / 80, x = overall location mod 80 */



.data

cursr_pos:
    x: .byte 0x0    /* lower byte for cursor location */
    y: .byte 0x0    /* higher byte for cursor location */