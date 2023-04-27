ifeq (config.txt, $(wildcard config.txt))
include config.txt
else
CONFIGURE = config
IMPALA_ROOT = `pwd`
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include/
IMPALA_LIBDIR = $(IMPALA_ROOT)/lib/
IMPALA_DRIVERDIR = $(IMPALA_ROOT)/drivers/

endif

CPP = cpp 

objs = kernel.o main.o idt.o isr.o isr_s.o  irq.o irq_s.o loader.o
lib = lib/lib.o
drivers = drivers/drivers.o

LINKSCRIPT = linkscript.ld



LD = ld
AS = as 
CC = gcc 

ASFLAGS =  --32 --gen-debug -I $(IMPALA_INCLUDEDIR)
CFLAGS = -nostdinc -nostdlib -m32 -I $(IMPALA_INCLUDEDIR) -fno-PIC -ggdb -c
LDFLAGS =  -m elf_i386 --oformat binary -T linkscript.ld -Map=System.map


all: $(CONFIGURE) impala.img


impala.img: $(objs) $(drivers) $(lib) $(progs)
	$(LD)  $^ $(LDFLAGS)   -o $@

impala.o: $(objs) $(libs) $(drivers) $(progs)
	$(LD) -m elf_i386 -r $^ -T linkscript.ld -Map=System.map -o $@

$(lib):
	$(MAKE) -C $(IMPALA_LIBDIR)

$(drivers):
	$(MAKE) -C $(IMPALA_DRIVERDIR)

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

config:
	echo "IMPALA_ROOT="$(IMPALA_ROOT) > config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt
	echo "IMPALA_LIBDIR="$(IMPALA_LIBDIR) >> config.txt
	echo "IMPALA_DRIVERDIR="$(IMPALA_DRIVERDIR) >> config.txt
	cp $(IMPALA_ROOT)/config.txt $(IMPALA_LIBDIR)/config.txt
	cp $(IMPALA_ROOT)/config.txt $(IMPALA_DRIVERDIR)/config.txt

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.img
	rm -f *.S
	rm -f config*
	rm -f *.map
	$(MAKE) -C $(IMPALA_LIBDIR) clean
	$(MAKE) -C $(IMPALA_DRIVERDIR) clean
	$(MAKE) -C programs clean
