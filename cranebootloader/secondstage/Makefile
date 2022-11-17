CC = gcc
objs = stage2.o crane.o printer.o string.o printer.o sreadsect.o idt.o gdt.o a20.o fs.o
CFLAGS = -m16 -Wno-builtin-declaration-mismatch -nostdinc -nostdlib -fno-PIC -c

all: cranebl.img

cranebl.img: $(objs)
	ld -m elf_i386 --oformat binary -nostdlib  -T linkscript.ld -Map=Map.map $^ -o $@

AS = as --32 

stage2.o: stage2.s
	$(AS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.img
	rm -f *.S
	rm -f *~
	rm -f config*
	rm -f *.map
