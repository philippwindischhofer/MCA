/* 
 * File:   MCA.h
 * Author: Philipp Windischhofer
 *
 * Created on February 2, 2014
 */

#ifndef _MCA_h
#define _MCA_h

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C.h"

//I2C:
#define SCINTILLATOR_ADDRESS		0x10

//commands:
#define GET_CHANNEL         0x10
#define GET_ALL_CHANNELS    0x11
#define RESET_ALL_CHANNELS  0x12
#define GET_LAST_CNTS       0x20
#define RESET_LAST_CNTS     0x21
#define STOP_ACQ            0x22
#define START_ACQ           0x23
#define GET_LAST_HEIGHT     0x24

#define DONE_MSG            0x1234

//function prototypes:
void initScintillator();

void prepareSpectrumTransfer();
uint16_t getNextChannel();
uint16_t getLastChannel();
void clearSpectrum();

uint16_t getChannel(uint16_t channel_nr);
uint16_t getLastCounts();
uint16_t getLastHeight();
void sendCMD(uint8_t cmd_val);

#endif
