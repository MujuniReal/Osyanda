

CC = gcc -m32 -nostdinc -c 
AS = as --32 


all: mem.o 


mem.o: mem.s
	$(AS) mem.s -o $@

#mem.o: mem.c
#	$(CC) -m32 -ggdb mem.c -o $@


clean:
	rm -f *.o