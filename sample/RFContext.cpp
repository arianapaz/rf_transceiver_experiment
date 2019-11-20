/*
Usage: ./codesend decimalcode [protocol] [pulselength]
decimalcode - As decoded by RFSniffer
protocol    - According to rc-switch definitions
pulselength - pulselength in microseconds

 Loosely based on ninjablocks/433utils
*/

#include "RFContext.h"

RFContext::RFContext(int protocol, int pulselength){
    // Ensure that wiringpi setup routine succeeds
    if (wiringPiSetup () == -1){
         printf("Wiring Pi setup failed. Exiting...\n");
         throw new WiringPiException();
    }
    rcSwitchSend = RCSwitch();
    rcSwitchReceive = RCSwitch();
    if (protocol != 0) {
        rcSwitchSend.setProtocol(protocol);
        rcSwitchReceive.setProtocol(protocol);
    }
    if (pulselength != 0){
         rcSwitchSend.setPulseLength(pulselength);
         rcSwitchReceive.setPulseLength(pulselength);
     }
    rcSwitchSend.enableTransmit(PIN_SEND);
    rcSwitchReceive.enableReceive(PIN_RECEIVE);
}

void RFContext::send_code(int code){
    printf("Sending %i...\n", code);
    rcSwitchSend.send(code, 24);
}

bool RFContext::available(){
    return rcSwitchReceive.available() || rcSwitchSend.available();
}

int RFContext::getReceivedValue(){
    return rcSwitchReceive.getReceivedValue();
}

void RFContext::resetAvailable(){
    rcSwitchReceive.resetAvailable();
    rcSwitchSend.resetAvailable();
}
