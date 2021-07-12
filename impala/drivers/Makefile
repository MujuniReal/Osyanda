ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
IMPALA_DRIVERDIR = `pwd`
IMPALA_ROOT = $(IMPALA_DRIVERDIR)/../
IMPALA_INCLUDEDIR = IMPALA_ROOT/include
endif

AS = as --32 -I $(IMPALA_INCLUDEDIR)


all: $(CONFIGURE) monitor.o ps2.o keyboard.o 



ps2.o: ps2.s
	$(AS) $< -o $@

keyboard.o: keyboard.s
	$(AS) $< -o $@

monitor.o: monitor.s
	$(AS) $< -o $@

config:
	echo "IMPALA_DRIVERDIR="$(IMPALA_DRIVERDIR) > config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt

clean:
	rm -f *.S
	rm -f *.o
	rm -f config*
