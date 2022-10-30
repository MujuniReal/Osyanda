
objs = terminal.o

all: $(objs)

AS = as --32 

%.o: %.s
	$(AS) $^ -o $@

%.o: %.c
	gcc -m32 -c -nostdinc -nostdlib -fno-PIC $^ -o $@

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.img
	rm -f *.S
	rm -f config*
	rm -f *.map
