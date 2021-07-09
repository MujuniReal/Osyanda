CRANE_SRCDIR = $(PWD)
CRANE_INCLUDEDIR = $(CRANE_SRCDIR)/../include/
CRANE_STAGE1DIR = $(CRANE_SRCDIR)/firststage/
CRANE_STAGE2DIR = $(CRANE_SRCDIR)/secondstage/

CC = gcc -m32 -Wall
CFLAGS = -I $(CRANE_INCLUDEDIR)


all: crane.mbr cranebl.img crane


crane.mbr:
	$(MAKE) -C $(CRANE_STAGE1DIR)

cranebl.img:
	$(MAKE) -C $(CRANE_STAGE2DIR)

crane-disk: main.o crane_prep-disk.o
	$(CC) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

crane_prep-disk.o: crane_prep-disk.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f crane-disk
	$(MAKE) -C $(CRANE_STAGE1DIR) clean
	$(MAKE) -C $(CRANE_STAGE2DIR) clean
