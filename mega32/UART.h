/* 
 * File:   UART.h
 * Author: Philipp Windischhofer
 *
 * Created on February 2, 2014
 */

#ifndef __UART_H
#define __UART_H

#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define F_CPU 16000000L
#define BAUD 9600UL
#define UBRRVAL (F_CPU / (BAUD * 16) - 1)

//function prototypes
void initUART();
void UART_puts(char*);
void sendOutputBuffer();

#endif
