# OBD2-SocktCan-Interface

This MATLAB/Simulink library/Add-On provides an OBD2 (On-board diagnostics) block for basic communication, data logging and vehicle diagnostics.

The block, included in this library, is intended to be used with SocketCan on a Linux target. For example, a RaspberryPi or a BeagleBone Black. 

### For Example:
To get e.g. the engine RPM, the "OBD2 SocketCan Interface" Block has to generate a request message and send it on to the vehicles CAN bus. To generate this request message, the appropriate OBD2/OBD-II Parameter IDs (PID) has to be provided to the input port (OBD2_PID) of the block. To show the current data (Mode 1) an additional parameter has to be provided on the OBD2_Mode input.

In this article: https://en.wikipedia.org/wiki/OBD-II_PIDs the Modes and PIDs are listed for the SAE J/1979 standard and the OBD2 protocol is further explained. The Formulas and PIDs can be used to calculate various different vehicle parameters. 

![Image of pid](/images/engine_rpm_pid.png)


![Image of example](/images/example.PNG)

#### In Summary:
* provide an OBD-II PID and a Mode for the "OBD2_PID" and "OBD2_Mode" input port.
* calculate the parameter you are expecting with the given formula and the appropriate output ports A, B, C and D.

### The "OBD2 SocketCan Interface"-Block
#### Inputs:
1. **OBD2_PID**: specific parameter ID for a vehicle status or parameter (e.g. 13 = vehicle speed),
2. **OBD2_Mode**: they are 10 different modes for OBD2 (e.g. 1 = current data, 2 = freeze frame data etc.).

#### Output:
1. **Identifier**: The identifier of the ecu response message,
2. **Returned_Bytes**: the number of returned data bytes,
3. **Mode**: the mode, the response message is in (e.g. Mode 1 = current data),
4. **A**: the first usable data byte,
5. **B**: the second usable data byte,
6. **C**: the third usable data byte,
7. **D**: the fourth usable data byte,
8. **Timestamp**: a Linux timestamp using *ioctl(s, SIOCGSTAMP, &tv)*,
9. **Raw_Date[8]**: the raw can message data vector,
10. **New_Message_Trigger**: this value is set to 1 if a new message has arrived in the current time step.

# How to:
### Prepare your Hardware

This example is for the Raspberry Pi 2.

#### 1. Install the Simulink Support Package for Raspberry Pi Hardware
Go to MATLAB -> HOME -> Add-Ons -> Get Hardware Support Packages

![Image of example](/images/matlab_1.PNG)

Install the following support packages for 
* MATLAB Support Package for Raspberry Pi Hardware
* Simulink Support Package for Raspberry Pi Hardware

![Image of example](/images/matlab_2.PNG)

Follow the instructions given by MATLAB to prepare your SD-Card

![Image of example](/images/matlab_4.PNG)

You can always put up the setup for the SD-Card using:

> `>> targetupdater`

in the MATLAB Command Window.

#### Connect to your hardware:
1. Connect the Raspi to your network and access it remotely using:
* putty.exe

or

* using MATLAB:

type:

> `>> p = raspi`

> `>> p.openShell`

You have now access to the Linux Command Shell and your output should look something like this:

![Image of example](/images/matlab_5.PNG)

If you have encountered problems the documentation is always a good place to go: 

https://www.mathworks.com/help/supportpkg/raspberrypiio/index.html

To have enough disk space on the Raspi for the Simulink applications, the file system has to be expanded:

In the Command Shell type:

> `$ sudo raspi-config`

this command opens up a dialog. Go to Advanced Options -> Expand Filesystem and reboot your Raspi.
By the way, changing the default 
* username: pi 

and the default 
* password: raspberry, 

is always a great idea.

#### Update your hardware:

Updating you Linux distro can solve a lot of problems.

> `$ sudo apt-get update`

#### Install can-utils:
> `$ sudo apt-get install can-utils`

FYI: https://github.com/linux-can/can-utils

#### CAN bus hardware:

In this example the PiCAN2 board is used to enable CAN communication with the vehicle.

![Image of PiCan](/images/PiCAN2.PNG)

Image source and supplier: http://skpang.co.uk/catalog/pican2-canbus-board-for-raspberry-pi-23-p-1475.html

It is very important to match the bitrate or baudrate of your hardware to the bitrate of your vehicle.
This should be done in the `/boot/config.txt` file:

Just add the following lines at the end of the File using:

> `$ sudo nano /boot/config.txt`

and then add 

`dtparam=spi=on`

`dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=25`

`dtoverlay=spi-bcm2835-overlay`

Additionally, to bring up the can interface with every reboot, the following lines have to be added to `/etc/network/interfaces`

> `$ sudo nano /etc/network/interfaces`

`allow-hotplug can0`

`iface can0 can static`

`bitrate 500000`

The bitrate should be changes to match the CAN bus bitrate of your vehicle.



