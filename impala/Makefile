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

objs = kernel.o main.o idt.o isr.o isr_s.o  irq.o irq_s.o
libs = lib/port.o lib/mem.o
drivers = drivers/monitor.o

LINKSCRIPT = linkscript.ld

CFLAGS = -nostdinc -m32 -I $(IMPALA_INCLUDEDIR) -fno-PIC -c

LD = ld
AS = as --32 
CC = gcc 

LDFLAGS =  -m elf_i386 --oformat binary -e _start -Ttext 0x60000


all: $(CONFIGURE) impala.img


impala.img: $(objs) $(libs) $(drivers)
	$(LD) $(LDFLAGS)  $(objs) $(libs) $(drivers) -o $@


$(libs):
	$(MAKE) -C $(IMPALA_LIBDIR)

$(drivers):
	$(MAKE) -C $(IMPALA_DRIVERDIR)

io.o: io.c
	$(CC) $(CFLAGS) io.c -o $@

irq_s.o: irq_s.s
	$(AS) irq_s.s -o $@

irq.o: irq.c 
	$(CC) $(CFLAGS) irq.c -o $@

isr_s.o: isr_s.s
	$(AS) isr_s.s -o $@

isr.o: isr.c include/types.h include/system.h include/idt.h
	#$(CPP) isr.s -o isr.S
	#$(AS) isr.S -o $@
	$(CC) $(CFLAGS) isr.c -o $@

idt.o: idt.c include/system.h
	$(CC) $(CFLAGS) idt.c -o $@

main.o: main.c include/system.h
	$(CC) $(CFLAGS) main.c -o $@

kernel.o: kernel.s
	$(AS) kernel.s -o $@


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
	$(MAKE) -C $(IMPALA_LIBDIR) clean
	$(MAKE) -C $(IMPALA_DRIVERDIR) clean
