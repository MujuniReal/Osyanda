ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
CRANE_STAGE1DIR = `pwd`
CRANE_ROOT = $(CRANE_STAGE1DIR)/../
CRANE_INCLUDEDIR = $(CRANE_ROOT)/include/
endif


AS = as
ASFLAGS = --32
LD = ld

LDFLAGS = -m elf_i386 --oformat binary -e main -Ttext 0x7c00 -Map=MBR.map

objs = mbr.o
SFILES = ptable.s fatbpb.s

all: $(CONFIGURE) $(objs) mbr.img


%.img: %.o
	$(LD) $(LDFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $^ -o $@

config:
	echo "CRANE_STAGE1DIR="$(CRANE_STAGE1DIR) > config.txt
	echo "CRANE_ROOT="$(CRANE_ROOT) >> config.txt
	echo "CRANE_INCLUDEDIR="$(CRANE_INCLUDEDIR) >> config.txt

clean:
	echo "" > $(word 1, $(SFILES))
	echo "" > $(word 2, $(SFILES))
	rm -f *.S
	rm -f *.o
	rm -f *.bin
	rm -f *.img
	rm -f *.map
	rm -f config*

