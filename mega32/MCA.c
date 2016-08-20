#include "MCA.h"

void initScintillator()
{
	initI2C();
	sendCMD(STOP_ACQ);
	sendCMD(RESET_LAST_CNTS);
	sendCMD(RESET_ALL_CHANNELS);
}

void prepareSpectrumTransfer()
{
	I2CStart();
	I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_WRITE);
	I2CSendByte(GET_ALL_CHANNELS);

	I2CStart();
	I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_READ);
}

uint16_t getNextChannel()
{
	return I2CRecieveWord(ACK);
}

uint16_t getLastChannel()
{
	return I2CRecieveWord(NAK);
}

uint16_t getChannel(uint16_t channel_nr)
{
	uint16_t retval = 0;
	
	I2CStart();
	I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_WRITE);
	I2CSendByte(GET_CHANNEL);
	
	//send channel number:
	I2CSendWord(channel_nr);

	I2CStart();
	I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_READ);
	retval = I2CRecieveWord(NAK);
	
	I2CStop();
	
	return retval;
}

uint16_t getLastCounts()
{
	uint16_t retval = 0;
	
	I2CStart();
	I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_WRITE);
	I2CSendByte(GET_LAST_CNTS);
	
	I2CStart();
	I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_READ);
	retval = I2CRecieveWord(NAK);

	I2CStop();
	
	return retval;
}

uint16_t getLastHeight()
{
	uint16_t retval = 0;
	
	I2CStart();
	I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_WRITE);
	I2CSendByte(GET_LAST_HEIGHT);
	
	I2CStart();
	I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_READ);
	retval = I2CRecieveWord(NAK);

	I2CStop();
	
	return retval;
}

void clearSpectrum()
{
	uint16_t retval = 0;
	
	do
	{
		I2CStart();
		I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_WRITE);
		I2CSendByte(RESET_ALL_CHANNELS);
	
		I2CStart();
		I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_READ);
		retval = I2CRecieveWord(NAK);

		I2CStop();
	}
	while(retval != DONE_MSG);	
}

//for simple commands with no data sent back
void sendCMD(uint8_t cmd_val)
{
	I2CStart();
	I2CSendByte((SCINTILLATOR_ADDRESS << 1) + I2C_WRITE);
	I2CSendByte(cmd_val);
	I2CStop();
}
