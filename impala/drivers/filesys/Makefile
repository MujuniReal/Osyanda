
dirs = fat 

FILE_SYSTEMS = fat/fat.o

all: filesys.o


LD = ld -m elf_i386 -r


filesys.o: $(FILE_SYSTEMS)
	$(LD) $^ -o $@

fat/fat.o:
	$(MAKE) -C fat/

clean:
	rm -f *.S
	rm -f *.o
	rm -f config*
	$(MAKE) -C fat/ clean
