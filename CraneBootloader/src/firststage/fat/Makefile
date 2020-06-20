
#INCLUDE_DIR = $(TOPDIR)/include

CC = gcc

CPP = cpp -nostdinc -I /home/box/Osyanda/CraneBootloader/include
AS = as


ASFLAGS = --32
LD = ld

LDFLAGS = -m elf_i386 --oformat binary 	#some of the things are gonna come automatically, from system arch

HFILES = /home/box/Osyanda/CraneBootloader/include/fat/fat32mbr.h \
/home/box/Osyanda/CraneBootloader/include/printer.h \
/home/box/Osyanda/CraneBootloader/include/sreadsect.h \
/home/box/Osyanda/CraneBootloader/include/lreadsect.h

all: Stage1.img


Stage1.img: mbr1.bin mbr2.bin fat32reserved
	cat mbr1.bin > $@
	cat fat32reserved >> $@
	cat mbr2.bin >> $@


mbr1.bin: mbr1.o
	$(LD) $(LDFLAGS) -e main -Ttext 0x7c00 $< -o $@

mbr2.bin: mbr2.o
	$(LD) $(LDFLAGS) -e main_mbr2 -Ttext 0x0 $< -o $@

fat32reserved:
	dd if=/dev/loop15 of=./fat32reserved skip=1 bs=512 count=1

mbr1.o: mbr1.S
	$(AS) $(ASFLAGS) $< -o $@

mbr2.o: mbr2.S 
	$(AS) $(ASFLAGS) $< -o $@

mbr1.S: fat32_1.s $(HFILES)
	$(CPP) $< -o $@

mbr2.S: fat32_2.s $(HFILES)
	$(CPP) $< -o $@
	
clean:
	rm -f *.S
	rm -f *.o
	rm -f *.bin
	rm -f *.img
	rm -f fat32reserved
