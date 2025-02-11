# Basic Rocketry System

This repo will be used to develop a basic system for rocketry avionics. Development is still in initial phase, as described below, and will most definetly go under many changes and tweeks as the project evolves.

For updated project information, please refer to the [**General Requirements document**](Documentation/General_Requirements.pdf). The images and descriptions in this README may be out of date.

# Rocketry Overview
## My Background
I am a recently graduated Electronics Engineer and a space/rocketry enthusiast. For 3 years during graduation, I participated on a student rocketry team (at the time called Beyond Rocket Design, now Beyond Aerospace Department) where I helped to design and build model rockets for competitions like LASC, FBMF and so many others.

The problem is I knew nothing about rocketry back then (I still don't for the most part but hey, at least I have some xp now) and I was just starting to learn electronics, so although I knew how to code a little bit, I had never even heard of things like RTOS, threads, drivers and many many other things. Back then we used to program on Arduino IDE and created some really basic pcbs with ATmega328 and, later, ESP32 DevKit. Nothing wrong with that, we were able get somethings working, but of course my imagination never stops thinking about how much faster, reliable and efficient I could make those systems had I implemented them with some fancier techniques.

So, this is my main motivation for this project. I will be trying to implement an avionics system that does the basic but does it well. And obviously, if it works I will also try to convince the current team members to let me fly this thing on one of their rockets.

## Flight Behavior
Suborbital model rockets tend to (although, more often than desired, they don't) go through these 6 main stages during flight:
- Lift off
- Powered Ascent
- Coasting / Unpowered Ascent
- Parachute / Recovery system deployment
- Slow Descent
- Landing

<p align="center">
  <img src="https://github.com/user-attachments/assets/89e4ac4f-ced1-4a4b-8422-af78ff70ac67" alt="Flight Stages (NASA)" width="500">
  <br>Source: NASA's <a href="https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/flight-of-a-model-rocket/" target="_blank">Beginners Guide to Aeronautics</a>
</p>
<!-- ![rktflight](https://github.com/user-attachments/assets/89e4ac4f-ced1-4a4b-8422-af78ff70ac67) -->

<p align="center">
  <br><img src="https://github.com/user-attachments/assets/95ef7178-a636-40cd-b9dc-83a80c350e83" alt="Flight Stages Resultant Analysis" width="500">
</p>
<!-- ![flight_stages](https://github.com/user-attachments/assets/95ef7178-a636-40cd-b9dc-83a80c350e83) -->

Notice that the most important events that happen during a flight - as far as software development goes - are the transitions between stages:
- Launch: transition from being still and moving, hopefully, upwards
- MECO: transition from Powered to Unpowered Ascent
- Apogee: transition from moving upwards to downwards
- Parachute: transition from descending almost on free fall to descending slowly
- Landing: transition from descending to - we expect - softly stopping on the ground

Consider that the avionics system will have some kind of IMU (Inertial Measurement Unit), which basically tells us the instantaneous acceleration along its 3 axes. It will also feature a barometric sensor to measure the air pressure during flight. Now, let's imagine a rocket flying without any rotation, so that the Z-axis is always pointing up (this will never actually happen, but it's good for demonstration purposes). We can plot a graph with the approximate resultant acceleration (in red) and the corresponding velocity (in green) during this flight.

<p align="center">
  <img src="https://github.com/user-attachments/assets/daaf0ec1-653c-4937-aa67-dafecf62db17" alt="Flight Behavior" width="500">
</p>
<!-- ![desmos-graph](https://github.com/user-attachments/assets/daaf0ec1-653c-4937-aa67-dafecf62db17) -->

As we can see in this simplified example, the resultant acceleration starts at 0g (1g = 9.8 m/s^2). It rises up to about 5g and then falls back down to 0g. This period where the acceleration is positive corresponds to the powered ascent, as illustrated on the previous image. Note that the rocket hits its maximum velocity when the acceleration is 0 (of course, since a=dv/dt). Then, the vehicle experiences free fall for some time (a = -1g) until the parachutes are deployed, at around T+28 seconds. From this point, the rocket falls at a constant speed only to hit the ground at T+41 seconds.

Just to be very clear, this example is absolutely, completely inaccurate and overly simplified. In practice, the acceleration curve of the motor during powered ascent stage is much steeper and shorter and the free fall period should be significantly smaller. Also, this example ignores any kind of air resistance, which is definetely not a great idea when studying rockets. However, I hope the example helps us understand the overall behavior of a model rocket during flight.

# Project Requirements and definitions

For updated project information, please refer to the [**General Requirements document**](Documentation/General_Requirements.pdf). The images and descriptions in this README may be out of date.

## Hardware
The main objective with this project is to develop the device firmware, so hardware requirements are being defined based on components I have easy access to, mainly some off-the-shelf modules. If everything goes well after prototyping, I might review the project and design some proper hardware for it, but for now it is what it is.

## Firmware
First of all, I defined a state machine to control the system behavior based on rockect flight phases. For this project, I considered that the parachute shall be deployed on apogee detection in order to simplify things a little.

<p align="center">
  <img src="https://github.com/user-attachments/assets/31c2614a-2e3a-4176-8dae-46d438cfd16f" alt="FW State Machine" width="800">
</p>
<!-- ![FW State Machine](https://github.com/user-attachments/assets/31c2614a-2e3a-4176-8dae-46d438cfd16f) -->

Basically, the system is initialized on the first state and, if everything is working properly, moves to S1 where the operation mode is selected based on some system data stored in flash memory. There are only 2 modes: Data Log is used to read the stored data after a flight and Flight mode is where the magic happens.

A flight only starts after the Remove Before Flight tag is removed. This has many reasons, in this case the most important being reliability, since this helps prevent a false flight start. After that, the system has 4 detection states, one for each flight stage transition. For example, S3 keeps trying to detect lift off stage by analyzing IMU and barometric sensor data or after a certain period of time has passed since the machine entered this state.

Finally, after landing has been detected (and if the rocket is still a rocket) the system tries to backup the data to a secondary storage unit, which may be a microSD card or another flash chip (still to be defined).

All of this is operation is illustrated in the following flowchart (also under development).

<p align="center">
  <img src="https://github.com/user-attachments/assets/172260db-716e-4f8e-a2d3-e177a55b31c4" alt="FW Flowchart" width="800">
</p>
<!-- ![FW Flowchart](https://github.com/user-attachments/assets/172260db-716e-4f8e-a2d3-e177a55b31c4) -->

Lastly, the system will be roughly organized as follows (yes, you guessed it, this is also not the final version).

<p align="center">
  <img src="https://github.com/user-attachments/assets/1cfd1d3e-59c2-4a47-b8ed-0f1b9415cbda" alt="FW Architecture" width="800">
</p>
<!-- ![FW Architecture](https://github.com/user-attachments//assets/1cfd1d3e-59c2-4a47-b8ed-0f1b9415cbda) -->

## Tests and Validation
Untested rocket code is bad rocket code. So, I need a good way of testing this firmware to validate individual blocks and also the complete system working together. Of course, the biggest issue here is that I don't have multiple rockets to fire up and watch what happens. I am still not sure how to do this (if you have any ideas or advices, please tell me), but I fell like what I need is a combination of these 2 things:
1. Simulated flight data: a piece of code that simulates a flight by generating coherent sensor data and feeds it into the system firmware as inputs.
2. Small scale test flight: some sort of physical structure tied to my device/pdb that allows me to through it up the air and control the descent phase so that it doesn't crash onto the ground.

First method is clearly safer, but doesn't provide a "real world" condition. Second method allows me to test things in conditions closer to a real flight, but may lead to a lot of frustration, electronic waste and emptiness in my wallet. For now though, I will focus on developing the main firmware and some sort of flight simulation function.
