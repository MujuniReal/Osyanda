OSYANDA_ROOT = `pwd`

CRANE_ROOT = $(OSYANDA_ROOT)/crane/
CRANE_INCLUDEDIR = $(CRANE_ROOT)/include/
CRANE_STAGE1DIR = $(CRANE_ROOT)/firststage/
CRANE_STAGE2DIR =$(CRANE_ROOT)/secondstage/


IMPALA_ROOT = $(OSYANDA_ROOT)/impala/
IMPALA_INCLUDEDIR = $(IMPALA_ROOT)/include/
IMPALA_LIBDIR = $(IMPALA_ROOT)/lib/
IMPALA_DRIVERDIR = $(IMPALA_ROOT)/drivers/


all:	config
	$(MAKE) -C $(CRANE_ROOT)
	$(MAKE) -C $(IMPALA_ROOT)


config:
	echo "OSYANDA_ROOT="$(OSYANDA_ROOT) > config.txt

	echo "CRANE_ROOT="$(CRANE_ROOT) >> config.txt
	echo "CRANE_INCLUDEDIR="$(CRANE_INCLUDEDIR) >> config.txt
	echo "CRANE_STAGE1DIR="$(CRANE_STAGE1DIR) >> config.txt
	echo "CRANE_STAGE2DIR="$(CRANE_STAGE2DIR) >> config.txt

	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	echo "IMPALA_INCLUDEDIR="$(IMPALA_INCLUDEDIR) >> config.txt
	echo "IMPALA_LIBDIR="$(IMPALA_LIBDIR) >> config.txt
	echo "IMPALA_DRIVERDIR="$(IMPALA_DRIVERDIR) >> config.txt

	cp $(OSYANDA_ROOT)/config.txt $(CRANE_ROOT)/config.txt
	cp $(OSYANDA_ROOT)/config.txt $(CRANE_STAGE1DIR)/config.txt
	cp $(OSYANDA_ROOT)/config.txt $(CRANE_STAGE2DIR)/config.txt

	cp $(OSYANDA_ROOT)/config.txt $(IMPALA_ROOT)/config.txt
	cp $(OSYANDA_ROOT)/config.txt $(IMPALA_LIBDIR)/config.txt
	cp $(OSYANDA_ROOT)/config.txt $(IMPALA_DRIVERDIR)/config.txt

clean:
	rm -f config*
	$(MAKE) -C $(CRANE_ROOT) clean
	$(MAKE) -C $(IMPALA_ROOT) clean
