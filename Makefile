OSYANDA_ROOT = $(PWD)
CRANE_ROOT = $(OSYANDA_ROOT)/cranebootloader/
IMPALA_ROOT = $(OSYANDA_ROOT)/impala/



all:	config
	#$(MAKE) -C $(CRANE_ROOT)
	#$(MAKE) -C $(IMPALA_ROOT)


config:
	echo "OSYANDA_ROOT="$(OSYANDA_ROOT) > config.txt
	echo "CRANE_ROOT="$(CRANE_ROOT) >> config.txt
	echo "IMPALA_ROOT="$(IMPALA_ROOT) >> config.txt
	cp $(OSYANDA_ROOT)/config.txt $(CRANE_ROOT)
	cp $(OSYANDA_ROOT)/config.txt $(IMPALA_ROOT)

clean:
	rm config.txt
	$(MAKE) -C $(CRANE_ROOT) clean
	$(MAKE) -C $(IMPALA_ROOT) clean
