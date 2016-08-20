#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "MCA.h"
#include "UART.h"
#include "I2C.h"
#include "utils.h"
#include "Timer.h"
#include "ADC.h"
#include "commands.h"

extern uint8_t outputBuffer[];
extern uint16_t cmdVal;

// -----------
// global storage for measurement values, to be sent on request
// -----------
uint16_t mca_pmt_volts = 0;
uint16_t mca_cps = 0;
// -----------

uint8_t postscaler = 0;

ISR(ADC_vect)
{
	mca_pmt_volts = ADCL;
	mca_pmt_volts |= (ADCH << 8);

	//conversion to volts is done on PC!
}

ISR(TIMER0_OVF_vect)
{
	//ADC is triggered at this frequency (about 60Hz)
	
	//postscaler for higher-level data gathering	
	postscaler++;
	if(postscaler > 60)
	{	
		// 1Hz-loop (temporary)
		mca_cps = getLastCounts();
		sendCMD(RESET_LAST_CNTS);

		postscaler = 0;
	}
}

int main(void)
{
	uint8_t test = 0;
	uint16_t tmp = 0;
	uint16_t i = 0;
	uint16_t j = 0;
	
	uint8_t specCnt = 0;
	
	initUART();
	initADC();
	initTimer();
	initScintillator();
	
	//sendCMD(START_ACQ);

	while(1)
	{
		//wait for new commands
		while(cmdVal == 0);
		
		cli();
		//parse command
		if(cmdVal == SERIAL_STAT)
		{
			convertToString(OK_MSG, outputBuffer);
			sendOutputBuffer();
		}
		else if(cmdVal == MCA_PMT_VOLTS)
		{
			convertToString(mca_pmt_volts, outputBuffer);
			sendOutputBuffer();
		}
		else if(cmdVal == MCA_CPS)
		{
			convertToString(mca_cps, outputBuffer);
			sendOutputBuffer();
		}
		else if(cmdVal == MCA_START_ACQ)
		{
			sendCMD(START_ACQ);
			convertToString(OK_MSG, outputBuffer);
			sendOutputBuffer();
		}
		else if(cmdVal == MCA_STOP_ACQ)
		{
			sendCMD(STOP_ACQ);
			convertToString(OK_MSG, outputBuffer);
			sendOutputBuffer();
		}
		else if(cmdVal == MCA_RESET)
		{
			clearSpectrum();
			convertToString(OK_MSG, outputBuffer);
			sendOutputBuffer();
		}
		else if(cmdVal >= MCA_CH_OFFSET)
		{			
			convertToString(getChannel(cmdVal - MCA_CH_OFFSET), outputBuffer);
			sendOutputBuffer();
		}
		sei();
		
		//reset
		cmdVal = 0;
	}

	while(1);
}
