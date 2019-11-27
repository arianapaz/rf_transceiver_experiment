
# Defines the RPI variable which is needed by rc-switch/RCSwitch.h
CXXFLAGS=-DRPI

all: experiment2 experiment2_2 experiment3 experiment3_THIEF

experiment2: ./lib/rc-switch/RCSwitch.o ./lib/RFContext.o experiment2.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt
	
experiment2_2: ./lib/rc-switch/RCSwitch.o ./lib/RFContext.o experiment2_2.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt

experiment3: ./lib/rc-switch/RCSwitch.o ./lib/RFContext.o experiment3.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt

experiment3_THIEF: ./lib/rc-switch/RCSwitch.o ./lib/RFContext.o experiment3_THIEF.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt

clean:
	$(RM) ./lib/rc-switch/*.o *.o servo experiment2 experiment2_2 experiment3 experiment3_THIEF

