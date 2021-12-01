ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
FATFS_DRIVERDIR = `pwd`
IMPALA_ROOT = $(FATFS_DRIVERDIR)/../../../
OSYANDA_ROOT = $(IMPALA_ROOT)/../
CRANE_ROOT = $(OSYANDA_ROOT)/cranebootloader/
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include
IMPALA_DRIVERDIR = $(IMPALA_ROOT)/drivers/
endif

HFILES = fs/fat16bpb.h

#ifneq ( $(IMPALA_INCLUDEDIR)/$(HFILES), $(wildcard $(IMPALA_INCLUDEDIR)/$(HFILES)))
#MKHFILES = mkhfiles
#endif

AS = as --32 -I $(IMPALA_INCLUDEDIR)
LD = ld -m elf_i386 -r

objs = fat16/r_fat.o fat16/r_fatfile.o fat16/r_rootdir.o

all: $(CONFIGURE) $(objs) fat.o

%.o: %.s
	$(AS) $< -o $@

fat.o: $(objs)
	cp fat16/r_fat.o  $(FATFS_DRIVERDIR)
	cp fat16/r_fatfile.o $(FATFS_DRIVERDIR)
	cp fat16/r_rootdir.o $(FATFS_DRIVERDIR)
	$(LD) $^ -o $@

mkhfiles:
	$(MAKE) -C $(CRANE_ROOT)
	$(CRANE_ROOT)/crane-disk

config:
	echo "FATFS_DRIVERDIR="$(FATFS_DRIVERDIR) > config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "OSYANDA_ROOT="$(OSYANDA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt
	echo "IMPALA_DRIVERDIR="$(IMPALA_DRIVERDIR) >> config.txt

clean:
	rm -f *.S
	rm -f *.o
	rm -f config*
	$(MAKE) -C fat16/ clean
	$(MAKE) -C fat32/ clean
