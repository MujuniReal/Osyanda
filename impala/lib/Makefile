
CC = gcc -m32 -nostdinc -c 
AS = as --32 

CFLAGS = -nostdinc -m32 -I ../include/ -fno-PIC -c 


all: mem.o port.o


mem.o: mem.s
	$(AS) mem.s -o $@

port.o: port.c
	$(CC) $(CFLAGS) port.c -o $@

#mem.o: mem.c
#	$(CC) -m32 -ggdb mem.c -o $@


clean:
	rm -f *.o