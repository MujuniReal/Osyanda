
TOPDIR = $(PWD)
INCLUDE_DIR = $(TOPDIR)/include



CC = gcc -Wall -ggdb
CFLAGS = -I $(INCLUDE_DIR)


all: initdirs crane


crane: main.o crane_partitiontble.o crane_prep-disk.o
	$(CC)  $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

crane_partitiontble.o: crane_partitiontble.c
	$(CC) $(CFLAGS) -c $< -o $@

crane_prep-disk.o: crane_prep-disk.c
	$(CC) $(CFLAGS) -c $< -o $@

initdirs:

clean:
	rm -f *.o
	rm -f crane


