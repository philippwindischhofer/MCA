/* 
 * File:   DBTimer.h
 * Author: Philipp Windischhofer
 *
 * Created on August 3, 2014, 16:38
 */

#ifndef DBTIMER_H
#define	DBTIMER_H

#include <p33Fxxxx.h>
#include <dsp.h>

//makros:
#define START_TIMER T1CONbits.TON = 1
#define STOP_TIMER T1CONbits.TON = 0
#define RESET_TIMER STOP_TIMER;    TMR1 = TMR1_PRELOAD_VALUE;    START_TIMER

void initDebouncingTimer();

#endif	/* DBTIMER_H */

