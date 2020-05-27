
CC = gcc
CPP = cpp

AS = as
LD = ld

LDFLAGS = --oformat binary

all: Stage2.bin

stage2: Stage2.bin

Stage2.bin: Stage2.o
	$(LD) $(LDFLAGS) -e mainSecond -Ttext 0x0 Stage2.o -o $@

Stage2.o: Stage2.S
	$(AS)  Stage2.S -o $@

Stage2.S: Stage2.s check_a20.s  g_idts.s
	$(CPP) Stage2.s -o $@


clean:
	rm *.o
	rm *.bin
	rm *.S
