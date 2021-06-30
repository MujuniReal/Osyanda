
AS = as --32
CPP = cpp -nostdinc 


all: monitor.o


monitor.o: monitor.S
	$(AS) monitor.S -o $@
	
monitor.S: monitor.s
	$(CPP) monitor.s -o $@

clean:
	rm -f *.S
	rm -f *.o
