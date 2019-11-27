#ifndef RFCONTEXT
#define RFCONTEXT

#include "./lib/rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include "Exceptions.h"

class RFContext{
private:
	// GPIO pin to be used for transmission (note: 0 -> GPIO 27 implicitly)
	int PIN_SEND = 0, PIN_RECEIVE = 2;
	RCSwitch rcSwitchSend, rcSwitchReceive;
public:
	RFContext(int protocol=0, int pulselength=0);
	void send_code(int code);
	int getReceivedValue();
	bool available();
	void resetAvailable();
};
#endif
