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
objs = stage2.o crane.o printer.o string.o printer.o readsect.o idt.o gdt.o a20.o fs.o
SFILES = ptable.s fatbpb.s
CFLAGS = -m16 -Wno-builtin-declaration-mismatch -nostdinc -nostdlib -I $(CRANE_INCLUDEDIR) -fno-PIC -c
LDFLAGS = -m elf_i386 --oformat binary -nostdlib  -T linkscript.ld -Map=Map.map

all: cranebl.bin

cranebl.bin: $(objs)
	$(LD) $(LDFLAGS) $^ -o $@

AS = as --32 

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
