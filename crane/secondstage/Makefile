ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
CRANE_STAGE2DIR = `pwd`
CRANE_ROOT = $(CRANE_STAGE2DIR)/../
CRANE_INCLUDEDIR = $(CRANE_ROOT)/include/
endif

CC = gcc
LD = ld
objs = crane.o start_kernel.o string.o diskread.o fs.o fat.o display.o ascii.o port.o
SFILES = ptable.s fatbpb.s
CFLAGS = -m32 -Wno-builtin-declaration-mismatch -fno-builtin -nostartfiles -nostdlib -nolibc -nodefaultlibs -nostdinc -nostartfiles -I $(CRANE_INCLUDEDIR) -fno-PIC -ggdb -c
LDFLAGS = -m elf_i386 --oformat binary -nostdlib  -T linkscript.ld -Map=Map.map
AS = as --32 --gen-debug

all: cranebl.bin

cranebl.bin: $(objs)
	$(LD) $(LDFLAGS) $^ -o $@

debug: $(objs)
	$(LD) -m elf_i386 -r -nostdlib  -T linkscript.ld -Map=Map.map $^ -o stage2sym.o

stage2.o: stage2.s
	$(AS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

config:
	echo "CRANE_STAGE2DIR="$(CRANE_STAGE2DIR) > config.txt
	echo "CRANE_ROOT="$(CRANE_ROOT) >> config.txt
	echo "CRANE_INCLUDEDIR="$(CRANE_INCLUDEDIR) >> config.txt

clean:
	echo "" > $(word 1, $(SFILES))
	echo "" > $(word 2, $(SFILES))
	rm -f *.o
	rm -f *.i
	rm -f *.img
	rm -f *.S
	rm -f *.bin
	rm -f config*
	rm -f *.map
