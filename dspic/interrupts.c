#include "interrupts.h"

void initInterrupts()
{
    //general settings
    //no interrupt nesting:
    INTCON1bits.NSTDIS = 1;

    //set up EXINT0
    TRISBbits.TRISB7 = 1;   //Pin is Input
    INTCON2bits.INT0EP = 0;    //rising edge triggers interrupt

    DISABLE_INT0;   //don't count impulses on default

    //set up ADC-Interrupt
    DISABLE_ADC;

    //set up TMR1-interrupt
    DISABLE_TMR0;
}
