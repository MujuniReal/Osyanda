#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
int fat1216prep_disk(char*);


int main(int argc,char **argv){

	if(argc == 1){
	  printf("Usage: %s path-to-disk-image ",argv[0]);
		return 1;
	}
    
	char *Fatbpb = (char*)malloc(FAT1216_BPBSIZE);

	FILE *diskmbrPTR;
	diskmbrPTR = fopen(argv[1],"r");

	fread(Fatbpb,1,FAT1216_BPBSIZE,diskmbrPTR);
	fclose(diskmbrPTR);

	fat1216prep_disk(Fatbpb);


	free(Fatbpb);

    return 0;
}
