/*
 * EEPROM.c
 *
 * Created: 7/20/2021 9:41:36 PM
 *  Author: DELLL
 */ 

#include "EEPROM.h"
enuErrorStatus_t EEPROM_WRITE(uint16_t addr,uint8_t data)
{
	uint8_t var = (uint8_t)((0xA0)|((addr&0x0700)>>7));
	TWI_StartCondition();

	TWI_WriteToAddress(var);

	TWI_WriteData((uint8_t)addr);

	TWI_WriteData(data);

	TWI_StopCondition();
	return E_OK;
}

enuErrorStatus_t EEPROM_READ(uint16_t addr,uint8_t* ptr)
{
	uint8_t var = (uint8_t)((0xA0)|((addr&0x0700)>>7));
	TWI_StartCondition();

	TWI_WriteToAddress(var);

	TWI_WriteData((uint8_t)addr);

	TWI_RepeatedStart();

	var++;
	TWI_ReadFromAddress(var);

	_delay_ms(10);
	TWI_ReadData(ptr);

	TWI_StopCondition();
	
	return E_OK;
}
