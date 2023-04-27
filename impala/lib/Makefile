ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
IMPALA_LIBDIR = `pwd`
IMPALA_ROOT = $(IMPALA_LIBDIR)/../
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include/
endif

CC = gcc
AS = as 
LD = ld -m elf_i386 -r
objs = iread.o string.o port.o

ASFLAGS = --32 --gen-debug -I $(IMPALA_INCLUDEDIR) 
CFLAGS = -nostdinc -nostdlib -m32 -I $(IMPALA_INCLUDEDIR) -fno-PIC -ggdb -c 


all: $(CONFIGURE) lib.o

lib.o:	$(objs)
	$(LD) $^ -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

config:
	echo "IMPALA_LIBDIR="$(IMPALA_LIBDIR) > config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt


clean:
	rm -f config*
	rm -f *.o
	rm -f *.i
	rm -f *.S
