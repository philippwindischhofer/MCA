/* 
 * File:   constants.h
 * Author: Philipp Windischhofer
 *
 * Created on August 3, 2014, 16:18
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

#define SPECTRUM_LENGTH 4096
#define RESET_LINE      LATBbits.LATB1
#define TICKOUT_LINE    LATBbits.LATB12

//pulse-height state machine
#define SAMPLE      1
#define ARMED       2
#define ARMED_FIRST 3
#define WAIT_PULSE  4

//low level i2c-recieve state machine
#define COMMAND_BYTE    1
#define DATA_BYTE_HIGH  2
#define DATA_BYTE_LOW   3

//high level i2c-recieve state machine
#define COMMAND         1
#define GET_CHANNEL         0x10
#define GET_ALL_CHANNELS    0x11
#define RESET_ALL_CHANNELS  0x12
#define GET_LAST_CNTS       0x20
#define RESET_LAST_CNTS     0x21
#define STOP_ACQ            0x22
#define START_ACQ           0x23
#define GET_LAST_HEIGHT     0x24

#define GET_DATAPOINTER     2

//high level i2c-transmit state machine
#define SEND_ALL_CHANNELS   1
#define SEND_CHANNEL        2
#define SEND_LAST_COUNTS    3
#define SEND_LAST_HEIGHT    4
#define SEND_SPEC_CLRD_DONE 5

#define DONE_MSG            0x1234

//low level i2c-transmit state machine

#define TMR1_PRELOAD_VALUE 0xFF00

#endif	/* CONSTANTS_H */

