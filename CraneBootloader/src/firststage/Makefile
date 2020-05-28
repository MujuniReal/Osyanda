
CC = gcc
CPP = cpp

AS = as
ASFLAGS = --32
LD = ld

LDFLAGS = -m elf_i386 --oformat binary -e main -Ttext 0x7c00 	#some of the things are gonna come automatically, from system arch



fat12:
	$(MAKE) -C fat fat12mbr


clean:
	rm *.o
	rm *.bin
	rm *.S
