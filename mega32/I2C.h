/* 
 * File:   i2c.h
 * Author: Philipp Windischhofer
 *
 * Created on February 2, 2016
 */

#ifndef _I2C_h
#define _I2C_h

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define I2C_WRITE   0x00
#define I2C_READ    0x01

#define ACK		1
#define NAK		0

//function prototypes:
void initI2C();
void I2CStart();
void I2CStop();

void I2CSendByte(uint8_t val);
uint8_t I2CRecieveByte(uint8_t ack);

void I2CSendWord(uint16_t sendval);
uint16_t I2CRecieveWord(uint8_t val);

#endif
