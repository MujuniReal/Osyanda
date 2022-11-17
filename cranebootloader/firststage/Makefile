ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
CRANE_STAGE1DIR = `pwd`
CRANE_ROOT = $(CRANE_STAGE1DIR)/../
CRANE_INCLUDEDIR = $(CRANE_ROOT)/include/
endif


CC = gcc
CPP = cpp -nostdinc -I $(CRANE_INCLUDEDIR)
AS = as


ASFLAGS = --32
LD = ld

LDFLAGS = -m elf_i386 --oformat binary -Map=System.map

HFILES = $(CRANE_INCLUDEDIR)/fat/fat16mbr.h \
$(CRANE_INCLUDEDIR)/printer.h \
$(CRANE_INCLUDEDIR)/sreadsect.h

all: $(CONFIGURE) stage1.img


stage1.img: mbr1.bin mbr2.bin
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

mbr1.S: fat16_1.s
	$(CPP) $< -o $@

mbr2.S: fat16_2.s
	$(CPP) $< -o $@

config:
	echo "CRANE_STAGE1DIR="$(CRANE_STAGE1DIR) > config.txt
	echo "CRANE_ROOT="$(CRANE_ROOT) >> config.txt
	echo "CRANE_INCLUDEDIR="$(CRANE_INCLUDEDIR) >> config.txt

clean:
	rm -f *.S
	rm -f *.o
	rm -f *.bin
	rm -f *.img
	rm -f *.map
	rm -f config*

