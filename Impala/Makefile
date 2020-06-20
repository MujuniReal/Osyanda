
all: Impala.img


Impala.img: kernel.o main.o
	ld -m elf_i386 -r $^ -o Impala.o
	ld -m elf_i386 --oformat binary -e impala_start Impala.o -o $@

kernel.o: kernel.s
	as --32 kernel.s -o $@

main.o:main.c
	gcc -m32 -nostdlib -nostdinc -fPIC -c main.c -o $@
