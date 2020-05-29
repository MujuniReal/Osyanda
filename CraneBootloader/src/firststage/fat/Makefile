CC = gcc
CPP = cpp -nostdinc -I /home/box/Osyanda/CraneBootloader/include

AS = as
ASFLAGS = --32
LD = ld

LDFLAGS = -m elf_i386 --oformat binary -e main -Ttext 0x7c00 	#some of the things are gonna come automatically, from system arch

HFILES = /home/box/Osyanda/CraneBootloader/include/fat/fat12mbr.h \
/home/box/Osyanda/CraneBootloader/include/printer.h \
/home/box/Osyanda/CraneBootloader/include/readsect.h

all: Stage1.bin

fat12mbr: Stage1.bin

Stage1.bin: Stage1.o
	$(LD) $(LDFLAGS) $< -o $@

Stage1.o: Stage1.S
	$(AS) $(ASFLAGS) $< -o $@


Stage1.S: fat16_2.s $(HFILES)
	$(CPP) $< -o $@

	
clean:
	rm *.o
	rm *.bin
	rm *.S
