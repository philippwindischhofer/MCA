#include "UART.h"

uint8_t incoming = 0;
uint8_t inputBuffer[10] = {0};
uint8_t outputBuffer[10] = {0};

uint8_t* outputPtr = outputBuffer;
uint8_t* inputPtr = inputBuffer;

uint16_t cmdVal = 0;
uint16_t i = 0;

uint8_t busy = 0;

void initUART()
{
	//init baud rate generator
	UBRRH = UBRRVAL >> 8;
    UBRRL = UBRRVAL & 0xff;
    
    //other settings
    UCSRB = (1 << RXEN) | (1 << TXEN);
    //UCSRC = (1 << URSEL)|(1 << USBS)|(3 << UCSZ0);
    
    //interrupts
    UCSRB |= (1 << RXCIE) | (1 << TXCIE);
    
    sei();	
}

ISR(USART_RXC_vect)
{
	//recieve state machine comes here:
	incoming = UDR;
	
	//put byte in input buffer:
	if(incoming != ' ')
	{
		*inputPtr = incoming;
		inputPtr++;
	}
	else
	{
		inputPtr--;
		//pointer now points to last recieved digit
		//convert string
		i = 1;
		cmdVal = 0;
		do
		{
			cmdVal += (*inputPtr - 48) * i;
			inputPtr--;
			i *= 10;
		}
		while(inputPtr >= inputBuffer);
		
		//reset pointer for next command
		inputPtr = inputBuffer;
	}
	
	//resetting flag is done automatically once no more bytes in input buffer
}

void sendOutputBuffer()
{
	while(busy != 0);
	UDR = *outputPtr;
	outputPtr++;
}

ISR(USART_TXC_vect)
{
	if(*outputPtr != 0)
	{
		UDR = *outputPtr;
		outputPtr++;
	}
	else
	{
		outputPtr = outputBuffer;
	}
		
	//flag cleared automatically
}