CC = gcc
CPP = cpp

AS = as
ASFLAGS = --32
LD = ld

LDFLAGS = -m elf_i386 --oformat binary -e main -Ttext 0x7c00 	#some of the things are gonna come automatically, from system arch

all: boot.bin

fat12mbr: Stage1.bin

Stage1.bin: Stage1.o
	$(LD) $(LDFLAGS) $< -o $@

Stage1.o: Stage1.S
	$(AS) $(ASFLAGS) $< -o $@


Stage1.S: fat12.s fatstruct.h printer.h readsect.h
	$(CPP) $< -o $@
