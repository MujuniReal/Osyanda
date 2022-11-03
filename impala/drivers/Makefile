ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
IMPALA_DRIVERDIR = `pwd`
IMPALA_ROOT = $(IMPALA_DRIVERDIR)/../
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include
endif

AS = as --32 -I $(IMPALA_INCLUDEDIR)

objs = monitor.o ps2.o keyboard/keyboard.o hardisk/hardisk.o filesys/filesys.o

all: $(CONFIGURE) $(objs)


%.o: %.s
	$(AS) $< -o $@


hardisk/hardisk.o:
	$(MAKE) -C hardisk

keyboard/keyboard.o:
	$(MAKE) -C keyboard

filesys/filesys.o:
	$(MAKE) -C filesys

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
	$(MAKE) -C hardisk clean
	$(MAKE) -C keyboard clean
	$(MAKE) -C filesys clean
