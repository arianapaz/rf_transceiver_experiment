
# Defines the RPI variable which is needed by rc-switch/RCSwitch.h
CXXFLAGS=-DRPI

all: experiment2 experiment2_2

experiment2: ./sample/lib/rc-switch/RCSwitch.o ./sample/RFContext.o experiment2.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt
	
experiment2_2: ./sample/lib/rc-switch/RCSwitch.o ./sample/RFContext.o experiment2_2.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt

clean:
	$(RM) ./sample/lib/rc-switch/*.o *.o servo experiment2

