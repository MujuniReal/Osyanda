#include "types.h"

#ifndef STRING_H

#define STRING_H

extern int strlen(char *s);
extern int strcmp(char *s1, char *s2);
extern char *strncpy(char *dest, char *src, uint32 size);
extern int16 strncmp(char *s1, char *s2, uint32 size);
extern char *memset(void *s, char c, uint32 size);
extern uint16 *memsetw(uint16 *ss, uint16 cc, uint32 size);
extern void *memcpy(void *dest, void *src, uint32 size);
#endif
