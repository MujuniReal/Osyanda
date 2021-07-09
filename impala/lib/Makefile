ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
IMPALA_LIBDIR = `pwd`
IMPALA_ROOT = $(IMPALA_LIBDIR)/../
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include/
endif

CC = gcc -m32 -nostdinc -c 
AS = as --32 

CFLAGS = -nostdinc -m32 -I $(IMPALA_INCLUDEDIR) -fno-PIC -c 


all: $(CONFIGURE) mem.o port.o


mem.o: mem.s
	$(AS) mem.s -o $@

port.o: port.c
	$(CC) $(CFLAGS) port.c -o $@

#mem.o: mem.c
#	$(CC) -m32 -ggdb mem.c -o $@

config:
	echo "IMPALA_LIBDIR="$(IMPALA_LIBDIR) > config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt


clean:
	rm -f config*
	rm -f *.o
