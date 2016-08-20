#include "config.h"

void initOSC()
{
    // switch device to internal oscillator, activate PLL to get 40 MIPS
    PLLFBD = 41;
    CLKDIVbits.PLLPOST = 0;
    CLKDIVbits.PLLPRE = 0;

    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);
    while(OSCCONbits.COSC != 0b001);
    while(OSCCONbits.LOCK != 1);
}