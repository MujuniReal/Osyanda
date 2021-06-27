
CPP = cpp 

objs = kernel.o main.o idt.o isr.o isr_s.o lib/mem.o

LINKSCRIPT = linkscript.ld

CFLAGS = -nostdinc -m32 -I include/ -c

LD = ld
AS = as --32 
CC = gcc 

LDFLAGS =  -m elf_i386 --oformat binary -e _start -Ttext 0x60000

LIBDIR = lib/

all: impala.img


impala.img: $(objs)
	$(LD) $(LDFLAGS)  $(objs) -o $@


lib/mem.o: $(LIBDIR)/mem.s
	$(MAKE) -C $(LIBDIR)

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