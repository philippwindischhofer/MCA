/*
 * LED1: idle
 * LED2: pulses
 * LED3: i2c-data
 */


#include <stdio.h>
#include <stdlib.h>
#include <p33Fxxxx.h>
#include <dsp.h>
#include <stdint.h>
#include "constants.h"
#include "config.h"
#include "adc.h"
#include "interrupts.h"
#include "LED.h"
#include "DBTimer.h"
#include "i2c.h"

//configuration bits
_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);
_FWDT(FWDTEN_OFF);
_FICD(JTAGEN_OFF & ICS_PGD3);

//function prototypes for ISRs:
void __attribute__((__interrupt__, __auto_psv__)) _INT0Interrupt(void);
void __attribute__((__interrupt__, __auto_psv__)) _ADC1Interrupt(void);
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);

void __attribute__((__interrupt__, __auto_psv__)) _MI2C1Interrupt(void);

//global variables
__eds__ uint16_t __attribute__((section("eds1"),space(eds))) spec [SPECTRUM_LENGTH];
uint16_t lastCounts = 0;
uint16_t lastPulseHeight = 0;

uint8_t INTStatus = ARMED_FIRST;

uint8_t rcvStatus = COMMAND_BYTE;
uint8_t rcvHLStatus = COMMAND;
uint8_t incomingByte = 0;
uint16_t incomingWord = 0;

uint8_t trnStatus = DATA_BYTE_HIGH;
uint8_t trnHLStatus = SEND_CHANNEL;
uint16_t outgoingWord = 0;

uint8_t RecHLReady = 0;        //data for high-level state machine ready (?)
uint8_t TrnHLReady = 0;

//general purpose
uint8_t done = 0;
uint8_t devnull = 0;        //trash
uint16_t i = 0;

//ISRs:
void __attribute__((__interrupt__, __auto_psv__)) _SI2C1Interrupt(void)
{
    IFS1bits.SI2C1IF = 0;
    
    SET_LED_3;

    //I2C recieve state machine
    if((I2C1STATbits.D_A == I2C_ADDRESS_REC) && (I2C1STATbits.R_W == I2C_WRITE))
    {
        //got address, do nothing but dummy read
        devnull = I2C1RCV;
    }
    else if((I2C1STATbits.D_A == I2C_DATA_REC) && (I2C1STATbits.R_W == I2C_WRITE))
    {
        RecHLReady = 0;
        
        //low level state machine for incoming bytes
        if(rcvStatus == COMMAND_BYTE)
        {
            RecHLReady = 1;    //request action of HL state machine
            incomingByte = I2C1RCV;
        }
        else if(rcvStatus == DATA_BYTE_LOW)
        {
            incomingWord |= I2C1RCV;
            rcvStatus = COMMAND_BYTE;
            RecHLReady = 1;    //full 16-bit word recieved
        }
        else if(rcvStatus == DATA_BYTE_HIGH)
        {
            incomingWord = I2C1RCV;
            incomingWord <<= 8;
            rcvStatus = DATA_BYTE_LOW;
        }

        //high level state machine does processing of data
        if(RecHLReady != 0)
        {
            RecHLReady = 0;
            
            if(rcvHLStatus == COMMAND)
            {
                //processing of command byte
                switch(incomingByte)
                {
                    case STOP_ACQ:
                        DISABLE_ACQ;   //disable external interrupt (INT0)
                        RESET_LINE = 0;
                        CLR_LED_2;
                        TICKOUT_LINE = 0;
                        break;
                    case START_ACQ:
                        ENABLE_ACQ;    //enable external interrupt (INT0)
                        break;
                    case RESET_LAST_CNTS:
                        lastCounts = 0;
                        break;
                    case GET_LAST_CNTS:
                        trnHLStatus = SEND_LAST_COUNTS;
                        TrnHLReady = 1;
                        break;
                    case GET_LAST_HEIGHT:
                        trnHLStatus = SEND_LAST_HEIGHT;
                        TrnHLReady = 1;
                        break;
                    case RESET_ALL_CHANNELS:
                        //reset spectrum array in slave transmitter mode:
                        trnHLStatus = SEND_SPEC_CLRD_DONE;
                        TrnHLReady = 1;
                        break;
                    case GET_CHANNEL:
                        rcvStatus = DATA_BYTE_HIGH;     //advise LL to get word
                        rcvHLStatus = GET_DATAPOINTER;  //wait for location of channel

                        break;
                    case GET_ALL_CHANNELS:
                        i = 0;      //loop variable for sending
                        trnHLStatus = SEND_ALL_CHANNELS;
                        RecHLReady = 1;
                        break;
                }
            }
            else if(rcvHLStatus == GET_DATAPOINTER)
            {
                rcvHLStatus = COMMAND;
                
                //location of channel stored in 'incomingword', invoke HL-recieve state machine
                trnHLStatus = SEND_CHANNEL;
                TrnHLReady = 1;
            }
        }
    }
    else if((I2C1STATbits.R_W == I2C_READ) && (I2C1CONbits.SCLREL == 0))
    {
        devnull = I2C1RCV;      //discard incoming data

        //high level state machine prepares data for sending
        if(TrnHLReady != 0)
        {
            TrnHLReady = 0;

            switch(trnHLStatus)
            {
                case SEND_CHANNEL:
                    outgoingWord = spec[incomingWord];
                    break;
                case SEND_ALL_CHANNELS:
                    if(i < SPECTRUM_LENGTH)
                    {
                        outgoingWord = spec[i];
                        i++;
                    }
                    break;
                case SEND_LAST_COUNTS:
                    outgoingWord = lastCounts;
                    break;
                case SEND_LAST_HEIGHT:
                    outgoingWord = lastPulseHeight;
                    break;
                case SEND_SPEC_CLRD_DONE:
                    outgoingWord = DONE_MSG;

                    //do spectrum clear in slave transmitter mode (takes time...)
                    for(i = 0; i < SPECTRUM_LENGTH; i++)
                    {
                        spec[i] = 0;
                    }
                    break;
            }
        }

        //low level state machine does actual sending of data
        if(trnStatus == DATA_BYTE_LOW)
        {
            I2C1TRN = (outgoingWord & 0x00FF);
            trnStatus = DATA_BYTE_HIGH;

            //reinvoke HL to fetch next byte (no problem if this is last byte sent)
            TrnHLReady = 1;
        }
        else if(trnStatus == DATA_BYTE_HIGH)
        {
             I2C1TRN = ((outgoingWord & 0xFF00) >> 8);   //send high byte first
             trnStatus = DATA_BYTE_LOW;
        }
        
        //wait for sending complete
        I2C1CONbits.SCLREL = 1;     //release clock line
        while(I2C1STATbits.TBF);
    }

    CLR_LED_3;
}

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;

    //stop timer
    RESET_TIMER;
    STOP_TIMER;

    //T1 interrupt occured, debouncing finished
    if(INTStatus == ARMED)
    {
        //debounced positive edge - new pulse started
        //switch ADC S/H to "sampling"
        AD1CON1bits.SAMP = 1;

        //change INT0 polarity to "falling" edge
        INTCON2bits.INT0EP = 1;

        INTStatus = SAMPLE;
    }
    else if(INTStatus == WAIT_PULSE)
    {
        //debounced negative edge - pulse finished

        //change INT0 polarity back to "rising" edge
        INTCON2bits.INT0EP = 0;
        INTStatus = ARMED_FIRST;
    }
}

void __attribute__((__interrupt__, __auto_psv__)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0;

    //AD conversion finished, add new value to histogram
    spec[ADC1BUF0] += 1;
    lastPulseHeight = ADC1BUF0;
    lastCounts++;

    //reset holding capacitor:
    RESET_LINE = 1;

    //tickout signal
    TICKOUT_LINE = 1;

    CLR_LED_2;
}

void __attribute__((__interrupt__, __auto_psv__)) _INT0Interrupt(void)
{
    SET_LED_2;

    IFS0bits.INT0IF = 0;    //reset interrupt flag

    //state machine
    if(INTStatus == ARMED_FIRST)
    {
        //this is the first positive edge, start debouncing timer:
        RESET_LINE = 0;
        TICKOUT_LINE = 0;
        START_TIMER;
        INTStatus = ARMED;
    }
    else if(INTStatus == ARMED)
    {
        //waiting for next pulse; debounce INT-Signal and swith internal ADC to "sampling"
        //reset Time when new positive edge occurs, when timer overflows, debouncing completed
        RESET_TIMER;
    }
    else if(INTStatus == SAMPLE)
    {
        //this is the first negative edge, sample peak value and wait for pulse to decay
        START_AD_CONVERSION;
        START_TIMER;
        INTStatus = WAIT_PULSE;
    }
    else if(INTStatus == WAIT_PULSE)
    {
        //negative edge, reset debouncing timer
        RESET_TIMER;
    }
}

int main()
{
    initOSC();  //40MIPS
    initADC();
    initLEDs();
    initDebouncingTimer();
    initI2C();
    initInterrupts();

    TRISBbits.TRISB1 = 0;   //reset-pin
    RESET_LINE = 0;

    TRISBbits.TRISB12 = 0;  //tickout
    TICKOUT_LINE = 0;
    
    uint16_t i = 0;
    uint16_t j = 0;

    while(1)
    {      
        //idle-loop LED blinking:
        setLED1();
        for(i = 0; i < 20000; i++)
        {
            for(j = 0; j < 50; j++)
            {
                
            }
        }

        clearLED1();
        for(i = 0; i < 50000; i++)
        {
            for(j = 0; j < 150; j++)
            {

            }
        }
    }

    while(1);
}

