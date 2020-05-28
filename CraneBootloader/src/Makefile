
#PWD = `$$HOME`
TOPDIR = /home/box/Osyanda/CraneBootloader/			#Soon we will fetch this from the main Makefile present in the Topdirectory
IMG = /home/box/blank_floppy.img
MOUNTDIR = /home/box/mount/

CC = gcc
CPP = cpp -nostdinc -I /home/box/Osyanda/CraneBootloader/include


AS = as
LD = ld

LDFLAGS = --oformat binary

all: Stage2.bin

stage1:
	$(MAKE) -C firststage

stage2: Stage2.bin

disk: Stage2.bin
	mount -o rw $(IMG) $(MOUNTDIR)
	cp Stage2.bin $(MOUNTDIR)
	umount $(MOUNTDIR)

Stage2.bin: Stage2.o
	$(LD) $(LDFLAGS) -e mainSecond -Ttext 0x0 Stage2.o -o $@

Stage2.o: Stage2.S
	$(AS)  Stage2.S -o $@

Stage2.S: Stage2.s /home/box/Osyanda/CraneBootloader/include/check_a20.s  /home/box/Osyanda/CraneBootloader/include/g_idts.s
	# the above will too need to benefit from TOPDIR stuff 
	$(CPP)  Stage2.s -o $@


clean:
	rm *.o
	rm *.bin
	rm *.S
