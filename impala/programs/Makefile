
objs = terminal.o
programs = terminal

all: $(objs) $(programs)

AS = as --32 

%.o: %.s
	$(AS) $^ -o $@

%.o: %.c
	gcc -m32 -nostdinc -nostdlib -e terminal -fno-PIC -c $^ -o $@
%: %.o
	ld -m elf_i386 --oformat binary -T linkscript.ld $^ -o $@
clean:
	rm -f *.o
	rm -f *.i
	rm -f *.img
	rm -f *.S
	rm -f terminal
	rm -f config*
	rm -f *.map
