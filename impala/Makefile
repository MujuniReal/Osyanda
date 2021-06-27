
CPP = cpp 

objs = kernel.o main.o idt.o except_handlers.o except_handls.o lib/mem.o

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

except_handls.o: except_handls.s
	$(AS) except_handls.s -o $@

except_handlers.o: except_handlers.c include/types.h include/system.h include/idt_exceptions.h
	$(CC) $(CFLAGS) except_handlers.c -o $@

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