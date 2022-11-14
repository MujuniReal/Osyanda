ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
CRANE_STAGE2DIR = `pwd`
CRANE_ROOT = $(CRANE_STAGE2DIR)/../
CRANE_INCLUDEDIR = $(CRANE_ROOT)/include/
endif

CPP = cpp -nostdinc -I $(CRANE_INCLUDEDIR)


AS = as --32
LD = ld

LDFLAGS = --oformat binary -Map=System.map

HFILES = $(CRANE_INCLUDEDIR)/check_a20.s \
$(CRANE_INCLUDEDIR)/g_idts.s

all: $(CONFIGURE) stage2.img


stage2: stage2.img


stage2.img: stage2.o
	$(LD) $(LDFLAGS) -e mainSecond -Ttext 0x0 $< -o $@

stage2.o: stage2.S
	$(AS)  $< -o $@

stage2.S: stage2.s
	$(CPP)  $< -o $@

config:
	echo "CRANE_STAGE2DIR="$(CRANE_STAGE2DIR) > config.txt
	echo "CRANE_ROOT="$(CRANE_ROOT) >> config.txt
	echo "CRANE_INCLUDEDIR="$(CRANE_INCLUDEDIR) >> config.txt


clean:
	rm -f *.o
	rm -f *.bin
	rm -f *.S
	rm -f *.img
	rm -f config*
