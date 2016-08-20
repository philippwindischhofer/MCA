#include "DBTimer.h"

void initDebouncingTimer()
{
    //init Timer 1
    T1CONbits.TCS = 0;  //internal clock
    T1CONbits.TGATE = 0; //no clock gating

    T1CONbits.TCKPS = 0b00; //1:256 prescaling
}
