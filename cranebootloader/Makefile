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
CFLAGS = -I $(CRANE_INCLUDEDIR) -c


all: $(CONFIGURE) crane-disk crane.mbr cranebl.img


crane.mbr:
	$(MAKE) -C $(CRANE_STAGE1DIR)
	cp $(CRANE_STAGE1DIR)/stage1.img  $(CRANE_ROOT)/$@

cranebl.img:
	$(MAKE) -C $(CRANE_STAGE2DIR)
	cp $(CRANE_STAGE2DIR)/stage2.img $(CRANE_ROOT)/$@

crane-disk: main.o crane_prep-disk.o
	$(CC) $^ -o $@


main.o: main.c
	$(CC) $(CFLAGS) $< -o $@

crane_prep-disk.o: crane_prep-disk.c
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
	$(MAKE) -C $(CRANE_STAGE1DIR) clean
	$(MAKE) -C $(CRANE_STAGE2DIR) clean

