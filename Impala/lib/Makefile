

CC = gcc -nostdinc -c 
AS = as


all: mem.o _mem.o


_mem.o: mem.s
	$(AS) --32 mem.s -o $@

mem.o: mem.c
	$(CC) -m32 -ggdb mem.c -o $@


clean:
	rm -f *.o