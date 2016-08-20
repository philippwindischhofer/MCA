#include "adc.h"

void initADC()
{
    //switch AN0 to analog functionality:
    AD1PCFGLbits.PCFG0 = 0;

    // select reference voltage source (AVDD / AVSS)
    AD1CON2bits.VCFG = 0b000;

    // select 12bit operating mode
    AD1CON1bits.AD12B = 1;

    // set appropriate output data format (unsigned integer)
    AD1CON1bits.FORM = 0b00;

    // set CH0 positive input to AN0, negative input is VREF- (AVSS)
    AD1CHS0bits.CH0SB = 0b00000;
    AD1CHS0bits.CH0NB = 0;
    AD1CHS0bits.CH0SA = 0b00000;
    AD1CHS0bits.CH0NA = 0;
    
    AD1CON1bits.SSRC = 0b000;

    //manual mode
    AD1CON1bits.ASAM = 0;

    //clock settings
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.ADCS = 0b00111111;

    //switch on adc:
    AD1CON1bits.ADON = 1;
}

uint16_t getSample()
{
    //start conversion; switch to hold
    AD1CON1bits.DONE = 0;
    AD1CON1bits.SAMP = 0;
    while(AD1CON1bits.DONE == 0);

    return(ADC1BUF0);
}

void startADConversion()
{
    AD1CON1bits.DONE = 0;
    AD1CON1bits.SAMP = 0;
}