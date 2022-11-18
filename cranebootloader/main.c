#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MBRSIZE 512
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
extern int readPartitionTable(char* mbr);


int main(int argc,char **argv){

  char *filePath;
  char fpath[256];

  if(argc == 1){
    printf("Usage: %s path-to-disk-image \n",argv[0]);
    printf("Enter disk path (eg: /dev/sda or disk.img): ");
    scanf("%s",&fpath);
    filePath = (char*)&fpath;
  }
  else{
    filePath = argv[1];
  }
  
  FILE *diskmbrPtr;
  diskmbrPtr = fopen(filePath,"r");
  
  char *mbr = (char*)malloc(MBRSIZE);
  
  fread(mbr, 1, MBRSIZE, diskmbrPtr);

  fclose(diskmbrPtr);

  readPartitionTable(mbr);
  createPartSrcFile();

  detectFs();
  //char *Fatbpb = (char*)malloc(FAT1216_BPBSIZE);
  //check for partition table
  //Detect Fs
  //detect_fs();
  //fread(mbr,1,512,diskmbrPTR);


  //  fat1216prep_disk(Fatbpb+3);
  //read_partition_table(mbr);


  free(mbr);

  return 0;
}
