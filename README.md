# OBD2-SocktCan-Interface
A test repository
##
Getting Started with OBD2SocketCanInterface

Description
This Blockset is based on the OBD2 SAE J/1979 standard.
It is able to generate OBD2 request messages and listen to the appropriate response from the vehicle.

The CAN bus interface works with SocketCan, and e.g. Raspberry, Beaglebone etc.
SocketCan documentation can be found here:
https://en.wikipedia.org/wiki/SocketCAN

The outputs are based on the following OBD2 documentation:
https://en.wikipedia.org/wiki/OBD-II_PIDs

Example:
To get the engine RPM, the inputs should be:
OBD2_PID = 12 and OBD2_Mode = 1.

The Engine RPM can be calculated with the following outputs:
(256*A + B)/4. The formulars can be found in the wiki article.

Note: "not all vehicles will support all PIDs and there can be manufacturer-defined custom PIDs", as stated in the wiki.
Requires: Raspberry Pi Support from Simulink

Author: Vitali Rjasanzew-Frey

Good Intro: https://www.youtube.com/watch?v=OhShoU_E-0g

System Requirements
Toolboox: Raspberry Pi Support from Matlab and Simulink
https://www.mathworks.com/hardware-support/raspberry-pi-simulink.html
https://www.mathworks.com/hardware-support/raspberry-pi-matlab.html
Install it directly through Matlab:
https://www.mathworks.com/help/supportpkg/raspberrypi/ug/install-target-for-raspberry-pi-hardware.html

can-utils for your target: sudo apt-get install can-utils
https://en.wikipedia.org/wiki/SocketCAN
https://wiki.linklayer.com/index.php/SocketCAN
https://github.com/linux-can/can-utils/blob/master/README.md

Features
OBD2 communication with your vehicle.

Examples
See example in the library in the AddOn Folder.
