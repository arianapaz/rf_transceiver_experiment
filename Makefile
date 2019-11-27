
# Defines the RPI variable which is needed by rc-switch/RCSwitch.h
CXXFLAGS=-DRPI

all: experiment2 experiment2_2 experiment3 experiment3_THIEF crack

experiment2: ./sample/lib/rc-switch/RCSwitch.o ./sample/RFContext.o experiment2.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt
	
experiment2_2: ./sample/lib/rc-switch/RCSwitch.o ./sample/RFContext.o experiment2_2.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt

experiment3: ./sample/lib/rc-switch/RCSwitch.o ./sample/RFContext.o experiment3.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt

experiment3_THIEF: ./sample/lib/rc-switch/RCSwitch.o ./sample/RFContext.o experiment3_THIEF.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lwiringPiDev -lcrypt

clean:
	$(RM) ./sample/lib/rc-switch/*.o *.o servo experiment2 experiment2_2 experiment3 experiment3_THIEF crack

