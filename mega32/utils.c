#include "utils.h"

void convertToString(uint16_t inval, uint8_t* buffer)
{
	uint16_t i = 1;
	uint16_t tmp = 1;
	uint8_t mag = 1;
	
	if(inval != 0)
	{
		//first get magnitude of number
		while(inval >= tmp)
		{
			tmp *= 10;
		}
	
		tmp /= 10;
		
		for(i = tmp; i > 0; i /= 10)
		{
			tmp = inval / i;
			*buffer = tmp + 48;
			buffer++;		
			inval -= tmp * i;
		}
	}
	else
	{
		*buffer = 48;
		buffer++;
	}
	
	*buffer = ' ';
	buffer++;
	*buffer = 0;
}