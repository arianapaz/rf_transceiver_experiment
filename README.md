# Exploring Vulnerabilities of PKE Systems with Simulated RF Devices

## Description
This project aims to replicate vulnerabilities of modern RFID security systems, more specifically, those used for passive keyless entry (PKE) in modern vehicles. The goal is to conduct several experiments to demonstrate the existing flaws of PKE systems. Hence, we will emulate PKE systems by building RFID devices using: Raspberry Pis, RF-433-MHZ, F/F cables, and some code in Python for creating the encryption protocol.

## Table of Contents
Below you can find a list of the experiments that will be performed and documented here.

|Task | Description|
|--|--|
|[Hardware](#Hardware)| Description of the hardware to be used (Raspberry Pis, RF-433-MHZ, and cables)|
|[Hardware Setup](#Hardware-Setup) | Description of how the hardware components will be put together|
|[Software Setup](#Software-Setup) | Description of the software needed and how to install it |
|Experiment 1 | Sanity check. Prove that we can put the hardware together and recreate an RFID|
|Experiment 2 | Simulation of an replay attack|
|Experiment 3 | Simulation of a relay attack (with basic  encryption)|
|Experiment 4 | Simulation of a relay attack (with more advanced encryption)|

## Hardware
To recreate a PKE system we will need the following hardware:
- Raspberry Pi 3
- Power Adapter
- Micro SD (with at least 16GB)
- Female to Female jumper cables (6 cables total)
- 433 MHz Transceiver

## Hardware Setup

## Software
[rpi-rf](https://pypi.org/project/rpi-rf/): Python module for sending and receiving signals on Raspberry Pi.


## Usage

## Credits
This project was developed by Ariana Paz, Cameron Bost, and Cody Standridge.
