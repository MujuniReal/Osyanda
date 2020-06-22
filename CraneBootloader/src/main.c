#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXFATBPBSIZE 90
#define PARTITIONTABLEOFFSET 446
#define MBRSIZE 512

//#include <bpbsize.h>
/* this is the main caller of the bootloader loggedin user interface view */
/*How program is called -> crane prep-disk
 steps of working 
this program has to read the file made from the crane mkconfig program
1 read the MBR 
2 Dont edit the BIOS Parameter Block for some filesystems ie the FATS 
3 only edit the section required for us to drop the 

*/
/* this program shd be able to detect other operating systems on disks ie reading partitions too */

/* make partiotion table header */
int initiate_partitiontblehdr(void*);

int initiate_fatprep(void*);


int main(int argc,char **argv){
    
    char *mbr512 = (char*)malloc(MBRSIZE);

    FILE *diskmbrPTR;
    diskmbrPTR = fopen(argv[1],"rb");

    fread(mbr512,1,MBRSIZE,diskmbrPTR);
    fclose(diskmbrPTR);

    /* Step 1 Make Partion table header */
    int partitions_on_disk;

    partitions_on_disk = initiate_partitiontblehdr((mbr512+PARTITIONTABLEOFFSET));
    /* for each partition, check its filesystem and check its root directory, scan for Operating systems installed on the
    partitions by checking in their root directory for known operating system files */

    printf("\n\nThe disk has %d Partitions\n\n",partitions_on_disk);

/* *********************************************************
        this joint below here is to prepare the FATs       *
********************************************************** */
    /* Step 2 Prepare fat bpb header */
    char* tmpf = "FAT";
    char tmpf32[4];
    char tmpf126[4];

    memset(tmpf32,'\0',sizeof(tmpf32));
    memset(tmpf126,'\0',sizeof(tmpf126));
    
    strncpy(tmpf32,(mbr512+(MAXFATBPBSIZE - 8)),3);
    strncpy(tmpf126,(mbr512+(62 - 8)),3);

    if( strcmp(tmpf32,tmpf) == 0 ){
        int statusf;
        statusf = initiate_fatprep(mbr512);
        if (statusf != 0){
            printf("An Error Occured....\n");
        }
        free(mbr512);
        return 0;
    }
    else if ( strcmp(tmpf126,tmpf) == 0 ){ /*62 is the maximum that is bpb + jump instruction + nop + devOEM(8)  one for fat12 and 16 */
        int statusf;
        statusf = initiate_fatprep(mbr512);
        if (statusf != 0){
            printf("An Error Occured....\n");
        }
        free(mbr512);
        return 0;
        }
    
/*    else{
         not fat 
    }*/


    free(mbr512);

    return 0;
}