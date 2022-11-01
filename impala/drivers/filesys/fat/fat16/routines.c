#include <string.h>
#include <fs/rootdir_struct.h>

typedef struct dirEntry dirEntryStruct;

extern short int *fat_tab;
extern dirEntryStruct *rootdir_mem;
extern int rootdir_start;

int find_file_startcluster(char *filename){
  
}
