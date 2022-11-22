#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "partable.h"
#define MBRSIZE 512
#define BYTESPSECT 512
/* this is the main caller of the bootloader loggedin user interface view */
/*How program is called -> crane prep-disk
 steps of working 
this program has to read the file made from the crane mkconfig program
1 read the MBR 
2 Dont edit the BIOS Parameter Block for some filesystems ie the FATS 
3 only edit the section required for us to drop the 

*/
/* this program shd be able to detect other operating systems on disks ie reading partitions too */

extern struct _partblentry *partitionTable;
extern int readPartitionTable(char* mbr);
extern char *detectFs(char *mbr);

int main(int argc,char **argv){

  char *filePath;
  char fpath[256];

  if(argc == 1){
    printf("Usage: %s path-to-disk-image \n",argv[0]);
    printf("Enter disk path (eg: /dev/sda or disk.img): ");
    scanf("%s",(char*)&fpath);
    filePath = (char*)&fpath;
  }
  else{
    filePath = argv[1];
  }
  
  FILE *diskmbrPtr;
  diskmbrPtr = fopen(filePath,"r");
  
  char *mbr = (char*)malloc(MBRSIZE);
  
  fread(mbr, 1, MBRSIZE, diskmbrPtr);
  
  int numPartitions = readPartitionTable(mbr);
  createPartSrcFile();

  if(numPartitions == 0){
    //No partition, use mbr to predict filesystem

    detectFs(mbr);
    fclose(diskmbrPtr);  

    free(mbr);
    return 0;
  }
  
  char *allocMem[4];

  printf("Choose Osyanda partition:\n\n");
  for(int i=0; i < numPartitions; i++){
    
    char *mbrBpb = (char*)malloc(MBRSIZE);
    allocMem[i] = mbrBpb;
    long position = partitionTable[i].sectsB4Partion * BYTESPSECT ;
    fseek(diskmbrPtr, position, SEEK_SET);
    fread(mbrBpb, 1, MBRSIZE, diskmbrPtr);
    char fsName[11];
    char *fsname = detectFs(mbrBpb);
    snprintf(fsName, 6, "%s\n", fsname);
    printf("*%i. %s\n",(i+1), fsName);
    //    printf("*%i. %s\n",(i+1), fsName);
    
  }
  
  
  fclose(diskmbrPtr);  

  //Free allocatedMemory
  for(int m=0; m < numPartitions; m++){
    free(allocMem[m]);
  }
  free(mbr);

  return 0;
}
