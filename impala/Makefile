
CPP = cpp 

objs = kernel.o main.o idt.o isr.o isr_s.o  irq.o irq_s.o
libs = lib/port.o lib/mem.o
drivers = drivers/monitor.o

LINKSCRIPT = linkscript.ld

CFLAGS = -nostdinc -m32 -I include/ -c

LD = ld
AS = as --32 
CC = gcc 

LDFLAGS =  -m elf_i386 --oformat binary -e _start -Ttext 0x60000

LIBDIR = lib/
DRV_DIR = drivers/

all: impala.img


impala.img: $(objs) $(libs) $(drivers)
	$(LD) $(LDFLAGS)  $(objs) $(libs) $(drivers) -o $@


$(libs):
	$(MAKE) -C $(LIBDIR)

$(drivers):
	$(MAKE) -C $(DRV_DIR)

io.o: io.c
	$(CC) $(CFLAGS) io.c -o $@

irq_s.o: irq_s.s
	$(AS) irq_s.s -o $@

irq.o: irq.c 
	$(CC) $(CFLAGS) irq.c -o $@

isr_s.o: isr_s.s
	$(AS) isr_s.s -o $@

isr.o: isr.c include/types.h include/system.h include/idt.h
	$(CC) $(CFLAGS) isr.c -o $@

idt.o: idt.c include/system.h
	$(CC) $(CFLAGS) idt.c -o $@

main.o: main.c include/system.h
	$(CC) $(CFLAGS) main.c -o $@

kernel.o: kernel.s
	$(AS) kernel.s -o $@


clean:
	rm -f *.o
	rm -f *.i
	rm -f *.img
	$(MAKE) -C $(LIBDIR) clean
	$(MAKE) -C $(DRV_DIR) clean