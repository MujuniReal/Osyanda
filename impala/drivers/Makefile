ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
IMPALA_DRIVERDIR = `pwd`
IMPALA_ROOT = $(IMPALA_DRIVERDIR)/../
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include
endif

AS = as --32 -I $(IMPALA_INCLUDEDIR)
CC = gcc
LD = ld -m elf_i386 -r
CFLAGS = -nostdinc -nostdlib -m32 -I $(IMPALA_INCLUDEDIR) -fno-PIC -c 
objs = monitor.o ps2.o kbd/kbd.o hd/hd.o fs/fs.o

all: $(CONFIGURE) drivers.o

drivers.o: $(objs)
	$(LD) $^ -o $@

%.o: %.s
	$(AS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

hd/hd.o:
	$(MAKE) -C hd

kbd/kbd.o:
	$(MAKE) -C kbd

fs/fs.o:
	$(MAKE) -C fs

config:
	echo "IMPALA_DRIVERDIR="$(IMPALA_DRIVERDIR) > config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt
	echo "IMPALA_DRIVERDIR="$(IMPALA_DRIVERDIR) >> config.txt

clean:
	rm -f *.S
	rm -f *.o
	rm -f *.i
	rm -f config*
	$(MAKE) -C hd clean
	$(MAKE) -C kbd clean
	$(MAKE) -C fs clean
