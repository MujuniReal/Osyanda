CRANEMBR_DIR = $(PWD)
CRANE_INCLUDEDIR = $(CRANEMBR_DIR)/../../include


CC = gcc
CPP = cpp -nostdinc -I $(CRANE_INCLUDEDIR)
AS = as


ASFLAGS = --32
LD = ld

LDFLAGS = -m elf_i386 --oformat binary

HFILES = $(CRANE_INCLUDEDIR)/fat/fat16mbr.h \
$(CRANE_INCLUDEDIR)/printer.h \
$(CRANE_INCLUDEDIR)/sreadsect.h

all: Stage1.img


Stage1.img: mbr1.bin mbr2.bin
	cat mbr1.bin > $@
	cat mbr2.bin >> $@


mbr1.bin: mbr1.o
	$(LD) $(LDFLAGS) -e main -Ttext 0x7c00 $< -o $@

mbr2.bin: mbr2.o
	$(LD) $(LDFLAGS) -e main_mbr2 -Ttext 0x0 $< -o $@

mbr1.o: mbr1.S
	$(AS) $(ASFLAGS) $< -o $@

mbr2.o: mbr2.S
	$(AS) $(ASFLAGS) $< -o $@

mbr1.S: fat16_1.s $(HFILES)
	$(CPP) $< -o $@

mbr2.S: fat16_2.s $(HFILES)
	$(CPP) $< -o $@
	
clean:
	rm *.S
	rm *.o
	rm *.bin
	rm *.img
