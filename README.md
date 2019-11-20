# Exploring Vulnerabilities of PKE Systems with Simulated RF Devices

## Description
This project aims to replicate vulnerabilities of modern RFID security systems, more specifically, those used for passive keyless entry (PKE) in modern vehicles. The goal is to conduct several experiments to demonstrate the existing flaws of PKE systems. Hence, we will emulate PKE systems by building RFID devices using: Raspberry Pis, RF-433-MHZ, F/F cables, and code in Python and C for creating the encryption protocol.

## Table of Contents
Below you can find a list of the experiments that will be performed and documented here.

|Task | Description|
|--|--|
|[Hardware](#Hardware)| Description of the hardware to be used|
|[Hardware Setup](#Hardware-Setup) | Description of how the hardware components will be put together|
|[Software](#Software) | Description of the software needed and how to install it |
|[Experiments](#Experiments) | <li> Sanity check. Prove that we can put the hardware together and recreate an RFID </li> <li>Simulation of an replay attack</li><li>Simulation of a relay attack (with basic  encryption)</li><li>Simulation of a relay attack (with more advanced encryption)</li>|
|[Problems Encountered](#Problems-Encountered) | List of modifications to hardware and software encountered |
|[Credits](#Credits) | People that contributed to this project|

## Hardware
To recreate a PKE system we will need the following hardware:
- Raspberry Pi 2 or 3 (3 of them)
  - https://www.raspberrypi.org/products/
  - https://www.amazon.com/s?k=raspberry+pi
  <img src="/images/raspberry_pi.jpg" width="360">
- 4 Amp Power Adapter (3 of them)
  - https://www.amazon.com/s?k=4A+power+adapter+raspberry+pi
  <img src="/images/adapter.jpg" width="360">
- Micro SD (3 of them with at least 16GB)
  - https://www.amazon.com/s?k=micro+sd+card
  <img src="/images/sd_card.jpg" width="360">
- Female to Female jumper cables (18 cables total)
  - https://www.amazon.com/s?k=female+to+female+cables
  <img src="/images/cables.jpg" width="360">
- 433 MHz Transceiver (3 of them)
  - https://www.amazon.com/s?k=433mhz+transceiver+raspberry+pi
  <img src="/images/transceiver.png" width="360">
- Antennas (6 of them)

  <img src="/images/cable.jpg" width="360">

## Hardware Setup
To set up the hardware follow the instructions:
- You will need to get wire the transmitter and receiver to the Raspberry Pi
  - **Raspberry Pi pin locations**:
  ![image](/images/gpio_pins.png)
  - **Wiring**:
  ![image](/images/wiring.png)


## Software
- [rpi-rf](https://pypi.org/project/rpi-rf/): Python module for sending and receiving signals with Raspberry Pi.
- [433Utils](https://github.com/ninjablocks/433Utils): C module for sending and receiving signals with Raspberry Pi.

## Experiments
- Experiment 1:

## Problems Encountered

## Credits
This project was developed by Ariana Paz, Cameron Bost, and Cody Standridge.
