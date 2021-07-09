CRANE_ROOT = $(PWD)
CRANE_INCLUDEDIR = $(CRANE_ROOT)/include/
CRANE_SRCDIR = $(CRANE_ROOT)/src/

all: cranebootloader crane-disk


crane-disk: cranebootloader
	cp $(CRANE_SRCDIR)/crane $(CRANE_ROOT)/$@


crane.mbr:
	$(MAKE) -C $(CRANE_SRCDIR) stage1
	cp $(CRANE_SRCDIR)/crane.mbr $(CRANE_ROOT)/$@

cranebl.img:
	$(MAKE) -C $(CRANE_SRCDIR) stage2
	cp $(CRANE_SRCDIR)/cranebl.img $(CRANE_ROOTDIR)/$@

cranebootloader:
	$(MAKE) -C $(CRANE_SRCDIR)

config:
	echo $(CRANE_ROOT) >> config.txt
	echo $(CRANE_INCLUDEDIR) >> config.txt

clean:
	rm -f *.o
	rm -f *.bin
	rm -f *.img
	rm -f config.txt
	$(MAKE) -C $(CRANE_SRCDIR) clean
