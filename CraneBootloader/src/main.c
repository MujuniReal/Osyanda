#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXFATBPBSIZE 90
#include <bpbsize.h>
/* this is the main caller of the bootloader loggedin user interface view */
/*How program is called -> crane prep-disk
 steps of working 
this program has to read the file made from the crane mkconfig program
1 read the MBR 
2 Dont edit the BIOS Parameter Block for some filesystems ie the FATS 
3 only edit the section required for us to drop the 

*/
/* this program shd be able to detect other operating systems on disks ie reading partitions too */
int initiate_fatprep(void*);


int main(int argc,char **argv){
    
    char *Fatbpb = (char*)malloc(MAXFATBPBSIZE);

    FILE *diskmbrPTR;
    diskmbrPTR = fopen(argv[1],"rb");

    fread(Fatbpb,1,MAXFATBPBSIZE,diskmbrPTR);
    fclose(diskmbrPTR);

    char* tmpf = "FAT";
    if(strncmp(tmpf,(Fatbpb+(MAXFATBPBSIZE - 8)),3)){
        initiate_fatprep(Fatbpb);
    }
    else if (strncmp(tmpf,(Fatbpb+(62 - 8)),3) ){ /*62 is the maximum that is bpb + jump instruction + nop + devOEM(8)  one for fat12 and 16 */
        initiate_fatprep(Fatbpb);
        }
    
/*    else{
         not fat 
    }*/


    free(Fatbpb);

    return 0;
}