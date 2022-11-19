#include "types.h"

#ifndef STRING_H

#define STRING_H

extern int strlen(char *s);
extern int strcmp(char *s1, char *s2);
extern char *strncpy(char *dest, char *src, uint32 size);
extern int16 strncmp(char *s1, char *s2, uint32 size);
extern char *memset(char *s, char c, uint32 size);
#endif
