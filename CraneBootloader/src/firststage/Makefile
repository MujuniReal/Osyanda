
CC = gcc
CPP = cpp

AS = as
ASFLAGS = --32
LD = ld

LDFLAGS = -m elf_i386 --oformat binary -e main -Ttext 0x7c00 	#some of the things are gonna come automatically, from system arch

all: Stage1.img

Stage1.img: stage1_a.o stage1_b.o
	ld --oformat binary -e main -Ttext 0x7c00 $^ -o $@

stage1_a.o: stage1_a.S
	as $^ -o $@

stage1_a.S: stage1_a.s
	cpp -I $(PWD)/../../include $^ -o $@

stage1_b.o: stage1_b.S
	as $^ -o $@

stage1_b.S: stage1_b.s
	cpp -I $(PWD)/../../include $^ -o $@


clean:
	rm -f *.S
	rm -f *.o
	rm -f *.bin
	rm -f *.img
	
