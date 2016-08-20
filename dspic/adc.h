/* 
 * File:   adc.h
 * Author: Philipp Windischhofer
 *
 * Created on July 26, 2014, 18:03
 */

#ifndef ADC_H
#define ADC_H

#include <p33Fxxxx.h>
#include <dsp.h>
#include <stdint.h>

//makros:
#define START_AD_CONVERSION     AD1CON1bits.DONE = 0;    AD1CON1bits.SAMP = 0

void initADC();
uint16_t getSample();
void startADConversion();

#endif	/* ADC_H */

