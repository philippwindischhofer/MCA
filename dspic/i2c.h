/* 
 * File:   i2c.h
 * Author: Philipp Windischhofer
 *
 * Created on August 6, 2014, 17:09
 */

#ifndef I2C_H
#define	I2C_H

#include <p33Fxxxx.h>
#include <dsp.h>
#include "constants.h"

#define I2C_ADDRESS 0x10
#define I2C_WRITE   0x00
#define I2C_READ    0x01

#define I2C_ADDRESS_REC 0x0
#define I2C_DATA_REC    0x1

void initI2C();

#endif	/* I2C_H */

