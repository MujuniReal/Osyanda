INCLUDE_DIR = /home/box/Osyanda/CraneBootloader/include


CC = gcc -m32 -Wall
CFLAGS = -I $(INCLUDE_DIR)


all: crane


crane: main.o crane_prep-disk.o
	$(CC) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

crane_prep-disk.o: crane_prep-disk.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o
