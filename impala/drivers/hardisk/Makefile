ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
HARDISK_DRIVERDIR = `pwd`
IMPALA_ROOT = $(HARDISK_DRIVERDIR)/../../
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include
IMPALA_DRIVERDIR = $(IMPALA_ROOT)/drivers/
endif

AS = as --32 -I $(IMPALA_INCLUDEDIR)
LD = ld -m elf_i386 -r
objs = ide/rdsk.o ide/wrtdsk.o

all: $(CONFIGURE) $(objs) hardisk.o


%.o: %.s
	$(AS) $< -o $@


hardisk.o: $(objs)
	cp ide/rdsk.o $(HARDISK_DRIVERDIR)
	cp ide/wrtdsk.o $(HARDISK_DRIVERDIR)
	$(LD) $^ -o $@


config:
	echo "HARDISK_DRIVERDIR="$(HARDISK_DRIVERDIR) > config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt
	echo "IMPALA_DRIVERDIR="$(IMPALA_DRIVERDIR) >> config.txt

clean:
	rm -f *.S
	rm -f *.o
	rm -f *.i
	rm -f config*
	$(MAKE) -C ide/ clean
	$(MAKE) -C sata/ clean
