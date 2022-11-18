ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
KEYBOARD_DRIVERDIR = `pwd`
IMPALA_ROOT = $(KEYBOARD_DRIVERDIR)/../../
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include
IMPALA_DRIVERDIR = $(IMPALA_ROOT)/drivers/
endif

AS = as --32 -I $(IMPALA_INCLUDEDIR)
LD = ld -m elf_i386 -r
objs = ps2_kbd.o

all: $(CONFIGURE) $(objs) keyboard.o


%.o: %.s
	$(AS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

keyboard.o: $(objs)
	$(LD) $^ -o $@


config:
	echo "KEYBOARD_DRIVERDIR="$(KEYBOARD_DRIVERDIR) > config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt
	echo "IMPALA_DRIVERDIR="$(IMPALA_DRIVERDIR) >> config.txt












clean:
	rm -f *.S
	rm -f *.o
	rm -f config*
