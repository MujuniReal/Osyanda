
CC = gcc
CPP = cpp

AS = as
ASFLAGS = --32
LD = ld

LDFLAGS = -m elf_i386 --oformat binary -e main -Ttext 0x7c00 	#some of the things are gonna come automatically, from system arch

all: boot.bin

boot.bin: _main.o
	$(LD) $(LDFLAGS) $< -o $@

_main.o: _main.S
	$(AS) $(ASFLAGS) $< -o $@


_main.S: _main.s fatstruct.h printer.h readsect.h
	$(CPP) $< -o $@



clean:
	rm *.o
	rm *.bin
	rm *.S
