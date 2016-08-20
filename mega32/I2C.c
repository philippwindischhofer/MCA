#include "I2C.h"

void initI2C()
{
	//SCL frequency about 400kHz
	TWSR &= ~(1 << TWPS0);	//TWPS = 0; (Prescaler = 1)
	TWSR &= ~(1 << TWPS1);

	TWBR = 10;	//10 --> 400kHz
}

void I2CStart()
{
	//start condition:
	TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void I2CStop()
{
	//stop condition
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void I2CSendByte(uint8_t sendval)
{
	//load data into register and send
	TWDR = sendval;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1<<TWINT)));
}

uint8_t I2CRecieveByte(uint8_t val)
{
	if(val == ACK)
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	else
		TWCR = (1 << TWINT) | (1 << TWEN);
			
	while (!(TWCR & (1<<TWINT)));
	
	return TWDR;
}

void I2CSendWord(uint16_t sendval)
{
	I2CSendByte((sendval >> 8) & 0x00FF);
	I2CSendByte(sendval & 0x00FF);
}

uint16_t I2CRecieveWord(uint8_t val)
{
	uint16_t retval = 0;
	
	retval = I2CRecieveByte(ACK);
	retval <<= 8;
	retval |= ((I2CRecieveByte(val)) & 0x00FF);
	
	return retval;
}