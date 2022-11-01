

int strlen(char *s){
  if(*s == '\0'){
    return 1;
  }
  int size = 1 + strlen(s+1);

  return size;
}

int strcmp(char *s1, char *s2){
  if(*s1 != *s2){
    return 0;
  }
  

}
