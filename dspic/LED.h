/* 
 * File:   LED.h
 * Author: Philipp Windischhofer
 *
 * Created on August 3, 2014, 15:57
 */

#ifndef LED_H
#define	LED_H

#include <p33Fxxxx.h>
#include <dsp.h>

//makros:
#define SET_LED_1   LATBbits.LATB2 = 1
#define CLR_LED_1   LATBbits.LATB2 = 0

#define SET_LED_2   LATBbits.LATB3 = 1
#define CLR_LED_2   LATBbits.LATB3 = 0

#define SET_LED_3   LATBbits.LATB4 = 1
#define CLR_LED_3   LATBbits.LATB4 = 0

void initLEDs();

void setLED1();
void clearLED1();
void toggleLED1();

void setLED2();
void clearLED2();
void toggleLED2();

void setLED3();
void clearLED3();
void toggleLED3();

#endif	/* LED_H */

