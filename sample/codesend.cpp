/*
Usage: ./codesend decimalcode [protocol] [pulselength]
decimalcode - As decoded by RFSniffer
protocol    - According to rc-switch definitions
pulselength - pulselength in microseconds

 'codesend' hacked from 'send' by @justy
 
 - The provided rc_switch 'send' command uses the form systemCode, unitCode, command
   which is not suitable for our purposes.  Instead, we call 
   send(code, length); // where length is always 24 and code is simply the code
   we find using the RF_sniffer.ino Arduino sketch.

(Use RF_Sniffer.ino to check that RF signals are being produced by the RPi's transmitter 
or your remote control)
*/
#include "./433utils/rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

// GPIO pin to be used for transmission (note: 0 -> GPIO 27 implicitly)
int PIN = 0;

struct TransmitParams{
    // Indicates if params are valid. If false, program should terminate
    bool valid = true;
    // Code to be sent via RF
    int code = 0;
    // Parse the first parameter to this command as an integer
    int pulseLength = 0;
    // RF Protocol
    int protocol = 0;
};

/**
 * Parses CLI arguments, sets up TransmitParams for program
 * 
 * @param argc number of CLI arguments (length of argv)
 * @param argv CLI arguments in raw string form
 * @return TransmitParams struct instance built from CLI arguments
 */
TransmitParams setup(int argc, char *argv[]){
    TransmitParams tParams;

    // If no command line argument is given, print the help text
    if (argc == 1) {
        printf("Usage: %s decimalcode [protocol] [pulselength]\n", argv[0]);
        printf("decimalcode\t- As decoded by RFSniffer\n");
        printf("protocol\t- According to rc-switch definitions\n");
        printf("pulselength\t- pulselength in microseconds\n");
        tParams.valid = false;
        return tParams;
    }
    
    
    tParams.code = atoi(argv[1]);
    
    // Optional arguments, only add if they exist
    if (argc >= 3) tParams.protocol = atoi(argv[2]);
    if (argc >= 4) tParams.pulseLength = atoi(argv[3]);
    
    // Ensure that wiringpi setup routine succeeds
    if (wiringPiSetup () == -1){
         printf("Wiring Pi setup failed. Exiting...\n");
         tParams.valid = false;
         return tParams;
    }
    return tParams;
}

/**
 * Sends an integer via RF transmitter
 * 
 * @param mySwitch RCSwitch object, contains logic for RF transmission
 * @param code numeric code to be sent via RF transmitter
 */
void send_code(RCSwitch& mySwitch, int code){
    printf("sending code[%i]\n", code);
    mySwitch.send(code, 24);
}

int main(int argc, char *argv[]) {
    TransmitParams tParams = setup(argc, argv);
    // If parameters are invalid, break program
    if(!tParams.valid){
        return -1;
    }
    
    RCSwitch mySwitch = RCSwitch();
    if (tParams.protocol != 0) mySwitch.setProtocol(tParams.protocol);
    if (tParams.pulseLength != 0) mySwitch.setPulseLength(tParams.pulseLength);
    mySwitch.enableTransmit(PIN);
    
    send_code(mySwitch, tParams.code);
    
    
    return 0;

}
