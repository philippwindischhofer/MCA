#include "LED.h"

void initLEDs()
{
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
}

void setLED1()
{
    LATBbits.LATB2 = 1;
}

void clearLED1()
{
    LATBbits.LATB2 = 0;
}

void toggleLED1()
{
    if(LATBbits.LATB2 == 1)
        LATBbits.LATB2 = 0;
    else
        LATBbits.LATB2 = 1;
}

void setLED2()
{
    LATBbits.LATB3 = 1;
}

void clearLED2()
{
    LATBbits.LATB3 = 0;
}

void toggleLED2()
{
    if(LATBbits.LATB3 == 1)
        LATBbits.LATB3 = 0;
    else
        LATBbits.LATB3 = 1;
}

void setLED3()
{
    LATBbits.LATB4 = 1;
}

void clearLED3()
{
    LATBbits.LATB4 = 0;
}

void toggleLED3()
{
    if(LATBbits.LATB4 == 1)
        LATBbits.LATB4 = 0;
    else
        LATBbits.LATB4 = 1;
}