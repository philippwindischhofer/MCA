#include "i2c.h"

void initI2C()
{
    //use 7-bit addressing:
    I2C1CONbits.A10M = 0;

    //set slave adress:
    I2C1ADD = I2C_ADDRESS;

    //no clock stretching:
    I2C1CONbits.SCLREL = 0;

    //enable I2C control module:
    I2C1CONbits.I2CEN = 1;

    //Interrupt:
    IFS1bits.SI2C1IF = 0;
    IEC1bits.SI2C1IE = 1;
}


