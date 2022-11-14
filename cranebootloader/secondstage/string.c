#include "types.h"

uint16 strlen(char *s){
  
  if(*s == '\0'){
    return 0;
  }
  
  return (1 + strlen(s+1));
}

int16 strcmp(char *s1, char *s2){
  
  if (*s1 == '\0' && *s2 == '\0'){  
    return 0;
  }
  
  else if (*s1 == *s2){
    return strcmp(s1+1, s2+1);
  }
  
  else if (*s1 > *s2){
    return 1;
  }
  
  else{
    return -1;
  }

}

char *strncpy(char *dest, char *src, int size){

  for(int i=0; i < size; i++){
    dest[i] = src[i];
  }
  return dest;
}
