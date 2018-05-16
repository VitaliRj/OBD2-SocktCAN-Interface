# OBD2-SocktCan-Interface

This Simulink library/Add-On provides an OBD2 (On-board diagnostics) block for basic communication, data logging and vehicle diagnostics.

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
1. **OBD2_PID**: specific parameter ID for a vehicle status or parameter or information (e.g. 13 = vehicle speed)
2. **OBD2_Mode**: they are 10 different modes for OBD2 (e.g. 1 = current data, 2 = freeze frame data etc.)

#### Output:
1. **Identifier**: The identifier of the ecu response message
2. **Returned_Bytes**: the number of returned data bytes
3. **Mode**: the mode the response message is in (e.g. Mode 1 = current data)
4. **A**: the first usable data byte.
5. **B**: the second usable data byte.
6. **C**: the third usable data byte.
7. **D**: the fourth usable data byte.
8. **Timestamp**: a Linux timestamp using *ioctl(s, SIOCGSTAMP, &tv)*
9. **Raw_Date[8]**: the raw can message data vector
10. **New_Message_Trigger**: this value is set to 1 if a new message has arrived in the current time step.
