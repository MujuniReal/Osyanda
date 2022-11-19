ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
CRANE_ROOT = `pwd`
CRANE_INCLUDEDIR = $(CRANE_ROOT)/include/
CRANE_STAGE1DIR = $(CRANE_ROOT)/firststage/
CRANE_STAGE2DIR = $(CRANE_ROOT)/secondstage/
endif


CC = gcc -m32 -Wall
#todo: -Wno-sizeof-pointer-memaccess
CFLAGS = -I $(CRANE_INCLUDEDIR) -c

objs = main.o partition_table.o fs.o fat.o

SFILES = ptable.s fatbpb.s

all: $(CONFIGURE) crane-disk asmfiles bootdisk.img

bootdisk.img: mbr.img cranebl.bin
	cat $(word 1, $^) > $@
	cat $(word 2, $^) >> $@


mbr.img: crane-disk $(SFILES)
	cp $(word 1, $(SFILES)) $(CRANE_STAGE1DIR)
	cp $(word 2, $(SFILES)) $(CRANE_STAGE1DIR)
	$(MAKE) -C $(CRANE_STAGE1DIR)
	cp $(CRANE_STAGE1DIR)/mbr.img  $(CRANE_ROOT)/$@

cranebl.bin: crane-disk
	$(MAKE) -C $(CRANE_STAGE2DIR)
	cp $(CRANE_STAGE2DIR)/$@ $(CRANE_ROOT)/$@

asmfiles: crane-disk
	$(CRANE_ROOT)/$^

crane-disk: $(objs)
	$(CC) $^ -o $@


%.o: %.c
	$(CC) $(CFLAGS) $< -o $@


config:
	echo "CRANE_ROOT="$(CRANE_ROOT) > config.txt
	echo "CRANE_INCLUDEDIR="$(CRANE_INCLUDEDIR) >> config.txt
	echo "CRANE_STAGE1DIR="$(CRANE_STAGE1DIR) >> config.txt
	echo "CRANE_STAGE2DIR="$(CRANE_STAGE2DIR) >> config.txt
	cp $(CRANE_ROOT)/config.txt $(CRANE_STAGE1DIR)/config.txt
	cp $(CRANE_ROOT)/config.txt $(CRANE_STAGE2DIR)/config.txt

clean:
	rm -f *.o
	rm -f *.bin
	rm -f *.img
	rm -f config*
	rm -f *.mbr
	rm -f crane-disk
	rm -f $(SFILES)
	$(MAKE) -C $(CRANE_STAGE1DIR) clean
	$(MAKE) -C $(CRANE_STAGE2DIR) clean

