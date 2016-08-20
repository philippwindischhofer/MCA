/* 
 * File:   interrupts.h
 * Author: Philipp Windischhofer
 *
 * Created on August 3, 2014, 15:41
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include <p33Fxxxx.h>
#include <dsp.h>

//macros:
#define DISABLE_INT0    IEC0bits.INT0IE = 0
#define ENABLE_INT0     IFS0bits.INT0IF = 0;    IEC0bits.INT0IE = 1

#define DISABLE_ADC     IEC0bits.AD1IE = 0
#define ENABLE_ADC      IFS0bits.AD1IF = 0;     IEC0bits.AD1IE = 1

#define DISABLE_TMR0    IEC0bits.T1IE = 0
#define ENABLE_TMR0     IFS0bits.T1IF = 0;      IEC0bits.T1IE = 1

#define DISABLE_ACQ     DISABLE_INT0;   DISABLE_TMR0;   DISABLE_ADC;
#define ENABLE_ACQ      ENABLE_INT0;    ENABLE_TMR0;    ENABLE_ADC;

//function prototypes
void initInterrupts();

#endif	/* INTERRUPTS_H */

