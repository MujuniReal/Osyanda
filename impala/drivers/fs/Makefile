ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
IMPALA_FSDIR = `pwd`
IMPALA_ROOT = $(IMPALA_FSDIR)/../../
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include
endif

dirs = fat 

FILE_SYSTEMS = fat.o

all: fs.o
CC = gcc
CFLAGS = -nostdinc -nostdlib -m32 -I $(IMPALA_INCLUDEDIR) -fno-PIC -ggdb -c 

LD = ld -m elf_i386 -r

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

fs.o: $(FILE_SYSTEMS)
	$(LD) $^ -o $@

config:
	echo "IMPALA_FSDIR="$(IMPALA_FSDIR) > config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt
	echo "IMPALA_FSDIR="$(IMPALA_FSDIR) >> config.txt

clean:
	rm -f *.S
	rm -f *.o
	rm -f *.i
	rm -f config*
