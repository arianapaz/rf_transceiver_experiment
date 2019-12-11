# Exploring Vulnerabilities of PKE Systems with Simulated RF Devices

## Description
This project aims to replicate vulnerabilities of modern RFID security systems, more specifically, those used for passive keyless entry (PKE) in modern vehicles. The goal is to conduct several experiments to demonstrate the existing flaws of PKE systems. Hence, we will emulate PKE systems by building RFID devices using: Raspberry Pis, RF-433-MHZ, F/F cables, and code in Python and C for creating the encryption protocol.

For an full explanation on the hardwar, software, and experiments please refer to the [wiki page](../../wiki)

## Disclaimer
This project used [433Utils](https://github.com/ninjablocks/433Utils) to help with the implementation of the communication protocol. Also, [rpi-rf](https://github.com/milaq/rpi-rf) was also used to test the hardware without having to run any of the experiment scripts.

## How To Test The Project
### Set up the Hardware and Software
Check out the hardware and hardware setup sections in the [wiki page](../../wiki)

### Run the Code
From the command line on the Raspberry Pi:
- Clone this repo: `git clone https://github.com/arianapaz/rf_transceiver_experiment.git`
- Go into the `sample` folder: `cd sample`
- Run a make all command: `make all`
- Go back to the original folder: `cd ..`
- Run a make all command: `make all`

Now you can do one of two things: 
* Test our scripts by running the experiment executables:
  - To simulate the car or the key (without rolling codes) `./experiment2 [car or key]`
  - To simulate an attacker that copies/sends the car/key codes `./experiment2_2`
  - To simulate the car (with rolling codes) `./experiment3_car`
  - To simulate the key (with rolling codes) `./experiment3_key`
  - To simulate the person trying to crack the rolling codes`./experiment3_THIEF`
  - To understand the experiments better go to the software section in the [wiki page](../../wiki)
  
* You can test your hardware using the more simple libraries under the `sample` folder
  - Send codes with the C++ library `./codesend [decimalcode]`
  - Sniff codes with the C++ library `./RFSniffer`
  - Send codes with the Python library `python3 send.py [decimalcode]`
  - Sniff codes with the Python library `python3 receive.py`

## Credits
This project was developed by Ariana Paz, Cameron Bost, and Cody Standridge.
