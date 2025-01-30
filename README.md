# Basic Rocketry System

This repo will be used to develop a basic system for rocketry avionics. Development is still in initial phase, as described below, and will most definetly go under many changes and tweeks as the project evolves.

# Rocketry Overview
## My Experience
/*! TODO */

## Flight Behavior
Suborbital model rockets tend to (although, more often than desired, they don't) go through these 6 main phases during flight:
- Lift off
- Powered Ascent
- Coasting / Unpowered Ascent
- Parachute / Recovery system deployment
- Slow Descent
- Landing

![rktflight](https://github.com/user-attachments/assets/89e4ac4f-ced1-4a4b-8422-af78ff70ac67)

Notice that the most important events that happen during a flight - as far as software development goes - are the transitions between phases:
- Launch: transition from being still and moving, hopefully, upwards
- MECO: transition from Powered to Unpowered Ascent
- Apogee: transition from moving upwards to downwards
- Parachute: transition from descending almost on free fall to descending slowly
- Landing: transition from descending to - we expect - softly stopping on the ground

Now, consider that the avionics system will have some kind of IMU (Inertial Measurement Unit), which basically tells us the instant acceleration in its 3 axis. Lets imagine a rocket flying without any rotation, so that the Z-axe is always pointing up (this will never actually happen, but it's good for demonstration purposes). We can plot a graph with the approximate acceleration in this case.

// graph

/*! TODO */

# Project Requirements and definitions

## Hardware
The main objective with this project is to develop the device firmware, so hardware requirements are being defined based on components I have easy access to, mainly some off-the-shelf modules. If everything goes well after prototyping, I might review the project and design some proper hardware for it, but for now it is what it is.

## Firmware
First of all, I defined a state machine to control the system behavior based on rockect flight phases. 

For this project, I considered that the parachute will be deployed on apogee detection in order to simplify things a little. Based on all of this, I defined the following state machine:

/*! TODO */

![FW State Machine](https://github.com/user-attachments/assets/309f61ed-bc05-4bf5-9b9c-621f50178c9a)
![FW Flowchart](https://github.com/user-attachments/assets/6e1fbad9-d223-4e75-9106-50fbe2ec781a)
![FW Architecture](https://github.com/user-attachments/assets/4a856157-59f2-4fc2-b26b-c7480194d388)

