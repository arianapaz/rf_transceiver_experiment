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
    rcSwitch = RCSwitch();
    if (protocol != 0) rcSwitch.setProtocol(protocol);
    if (pulselength != 0) rcSwitch.setPulseLength(pulselength);
    rcSwitch.enableTransmit(PIN_SEND);
    rcSwitch.enableReceive(PIN_RECEIVE);
}

void RFContext::send_code(int code){
    printf("Sending %i...\n", code);
    rcSwitch.send(code, 24);
}

bool RFContext::available(){
    return rcSwitch.available();
}

int RFContext::getReceivedValue(){
    return rcSwitch.getReceivedValue();
}

void RFContext::resetAvailable(){
    rcSwitch.resetAvailable();
}
