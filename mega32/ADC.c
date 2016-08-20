#include "ADC.h"

void initADC()
{
	//use 5V-reference & AD0
	ADMUX |= (1 << REFS0);
	
	ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADATE);
	ADCSRA |= (1 << ADPS2);	//prescaler
	SFIOR |= (1 << ADTS2); 	//T0 OVF as trigger
}