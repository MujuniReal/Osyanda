ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
IMPALA_DRIVERDIR = `pwd`
IMPALA_ROOT = $(IMPALA_DRIVERDIR)/../
IMPALA_INCLUDEDIR = IMPALA_ROOT/include
endif

AS = as --32
CPP = cpp -nostdinc 


all: $(CONFIGURE) monitor.o


monitor.o: monitor.S
	$(AS) monitor.S -o $@

monitor.S: monitor.s
	$(CPP) monitor.s -o $@

config:
	echo "IMPALA_DRIVERDIR="$(IMPALA_DRIVERDIR) > config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt

clean:
	rm -f *.S
	rm -f *.o
	rm -f config*
