CC:=cc
FRAMEWORKS=-framework IOKit -framework CoreFoundation

all: power_meter smcstat

power_meter: power_meter.o smc.o
	$(CC) -o power_meter $(FRAMEWORKS) power_meter.o smc.o

smcstat: smcstat.o smc.o
	$(CC) -o smcstat $(FRAMEWORKS) smcstat.o smc.o

clean:
	rm -rf *.o *.dSYM smcstat power_meter
