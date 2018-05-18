/*
 * Copyright (c) 2018 Vitali Rjasanzew-Frey
 * Licensed under the MIT License (see LICENSE for details)
 *
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>

# ifndef MATLAB_MEX_FILE
	#include <stdio.h>
	#include <string.h>
	#include <linux/can.h>
	#include <net/if.h>
	#include <sys/ioctl.h>
	#include <sys/types.h>
       	#include <sys/socket.h>
	#include <sys/time.h>
# endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/*Global variables:*/
int socket0;
int interfaceNumber = 0;
//masks:
#ifndef CAN_MASK
#define maskExtended 	0x80000000U //extended
#define maskRemote      0x40000000U //remote
#define maskError       0x20000000U //error

#define maskId          0x1FFFFFFFU //Data
#define maskIdStd       0x000007FFU //Data std_ID "not used"

#define obd2requestPid  0x7DF      //OBD2 Request ID
#endif
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start functions
 *
 */
void obd2RawJ1979_Start_wrapper(const real_T *sampleTime, const int_T p_width0)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
/*
 * Custom Start code goes here.
 */
# ifndef MATLAB_MEX_FILE
    
    // build interface name example: "can0" 
    char interfaceName[7];
    sprintf(interfaceName, "can%d\0", interfaceNumber);
    
    // as defined in Readme file of SocketCAN
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;

    //open a socket for communicating over a CAN network
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    // as defined in Readme file of SocketCAN
    // fill the sockaddr_can struct:
    strcpy(ifr.ifr_name, interfaceName);
    ioctl(s, SIOCGIFINDEX, &ifr);
    
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    
    bind(s, (struct sockaddr *)&addr, sizeof(addr));
    socket0 = s; // Global
# endif
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output functions
 *
 */
void obd2RawJ1979_Outputs_wrapper(const uint8_T *obd2PID,
			const uint8_T *obd2Mode,
			uint32_T *Identifier,
			uint8_T *ReturnedBytes,
			uint8_T *Mode,
			uint8_T *PID,
			uint8_T *A,
			uint8_T *B,
			uint8_T *C,
			uint8_T *D,
			real_T *Timestamp,
			uint8_T *RawData,
			uint32_T *NewMessage,
			const real_T *sampleTime, const int_T p_width0)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
 */

# ifndef MATLAB_MEX_FILE
    struct can_frame frame; // struct can_frame - basic CAN frame struct
    struct can_frame frameRequest;
    int receivedBytes;
    uint32_T msgIDRaw;
    uint32_T msgID;  
    int i;  
    struct timeval tv;

    // Request Generator
    frameRequest.can_id = 0x7DF;
    frameRequest.can_dlc = 8;
    
    // Request Data
    frameRequest.data[0] = 2;
    frameRequest.data[1] = obd2Mode[0];
    frameRequest.data[2] = obd2PID[0];
    frameRequest.data[3] = 0;
    frameRequest.data[4] = 0;
    frameRequest.data[5] = 0;
    frameRequest.data[6] = 0;
    frameRequest.data[7] = 0;
    
    //send frame to socket
    int bytes_sent = write( socket0, &frameRequest, sizeof(frameRequest) );
    
    // One easy but non-standard way to do a non-blocking read would be to use
    receivedBytes = recv(socket0, &frame, sizeof(struct can_frame),MSG_DONTWAIT );
    // and not: receivedBytes = read(socket0, &frame, sizeof(struct can_frame));
    
    /* Check for new messages */
    if (receivedBytes != sizeof(struct can_frame) ) {
        NewMessage[0] = 0;
    }else{
        // get the last one
        while (receivedBytes == sizeof(struct can_frame)) {
            msgIDRaw    = (uint32_T)frame.can_id;  //can_ID
            if (msgIDRaw >= 0x7E8 && msgIDRaw <= 0x7EF) {
                ioctl(socket0, SIOCGSTAMP, &tv);        // Timestamp

                /* Apply mask to extract further information from ID */
                msgID       = msgIDRaw & maskId;    

                // Output
                Identifier[0]   = msgID;
                Timestamp[0]    = tv.tv_sec + tv.tv_usec * 1e-6;
                NewMessage[0]   = 1;
                
                ReturnedBytes[0] = (uint8_T)frame.data[0];
                Mode[0] = (uint8_T)frame.data[1];
                PID[0] = (uint8_T)frame.data[2];
                A[0] = (uint8_T)frame.data[3];
                B[0] = (uint8_T)frame.data[4];
                C[0] = (uint8_T)frame.data[5];
                D[0] = (uint8_T)frame.data[6];
                
                // Fill RawData
                for(i=0; i<8; i++) {
                    RawData[i] = (uint8_T)frame.data[i];
                }  
            } 
            // check again
            receivedBytes = recv(socket0, &frame, sizeof(struct can_frame),MSG_DONTWAIT );
        }
    }
# endif
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


