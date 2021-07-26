/*
 * I2C.c
 *
 * Created: 7/17/2021 1:39:18 PM
 *  Author: DELLL
 */ 

#include "I2C.h"

/************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : I2C Master initialization
*************************************************************/
enuErrorStatus_t TWI_MasterInit(void)
{
	uint8_t prescale=PRESCALE;
	if(prescale == 1)
	{
		TWSR_R=(0<<TWPS1_B)|(0<<TWPS0_B);
	
	}else if(prescale == 4)
	{
		TWSR_R=(0<<TWPS1_B)|(1<<TWPS0_B);
		
	}else if(prescale == 16)
	{
		TWSR_R=(1<<TWPS1_B)|(0<<TWPS0_B);	
	}else if(prescale == 64)
	{
		TWSR_R=(1<<TWPS1_B)|(1<<TWPS0_B);		
	}
	
	TWBR_R = ((F_CPU/TWI_FREQ)-16)/(2L*prescale);

	TWCR_R|=(1<<TWEN_B);
	return E_OK;
}

/************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Start condition
*************************************************************/
enuErrorStatus_t TWI_StartCondition(void)
{
	TWCR_R = (1<<TWINT_B)|(1<<TWSTA_B)|(1<<TWEN_B);
	while(!GET_BIT(TWCR_R,TWINT_B));
	if(TWI_GetStatus()!=START)
	{
		return E_ERROR;
	}
	return E_OK;
}

/************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Stop condition
*************************************************************/
enuErrorStatus_t TWI_StopCondition(void)
{
	TWCR_R=(1<<TWINT_B)|(1<<TWEN_B)|(1<<TWSTO_B);
	
	return E_OK;
}

/************************************************************
* Parameters (in) : uint8_t address
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Master send the address to write to
*************************************************************/
enuErrorStatus_t TWI_WriteToAddress(uint8_t address)
{
	TWDR_R = (address);
	TWCR_R = (1<<TWINT_B)|(1<<TWEN_B);
	while(!GET_BIT(TWCR_R,TWINT_B));
	if(TWI_GetStatus()!=MT_SLA_W_ACK)
	{
		return E_ERROR;
	}
	return E_OK;	
}

/************************************************************
* Parameters (in) : uint8_t address
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Master send the address to read from
*************************************************************/
enuErrorStatus_t TWI_ReadFromAddress(uint8_t address)
{
	TWDR_R = (address);
	TWCR_R = (1<<TWINT_B)|(1<<TWEN_B);
	while(!GET_BIT(TWCR_R,TWINT_B));
	if(TWI_GetStatus()!=MT_SLA_R_ACK)
	{
		return E_ERROR;
	}
	return E_OK;	
}

/************************************************************
* Parameters (in) : uint8_t data
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Sending the data
*************************************************************/
enuErrorStatus_t TWI_WriteData(uint8_t data)
{
	TWDR_R = data;
	TWCR_R = (1<<TWINT_B)|(1<<TWEN_B);
	while(!GET_BIT(TWCR_R,TWINT_B));
	if(TWI_GetStatus()!=MT_DATA_ACK)
	{
		return E_ERROR;
	}
	return E_OK;	
}

/************************************************************
* Parameters (in) : uint8_t* pu8data
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Reading the data
*************************************************************/
enuErrorStatus_t TWI_ReadData(uint8_t* pu8data)
{
	TWCR_R = (1<<TWINT_B)|(1<<TWEN_B);
	while(!GET_BIT(TWCR_R,TWINT_B));
	*pu8data = TWDR_R;
	if(TWI_GetStatus()!=MT_R_DATA_NACK)
	{
		return E_ERROR;
	}
	return E_OK;	
}

/************************************************************
* Parameters (in) : uint8_t addr
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Slave initialization
*************************************************************/
enuErrorStatus_t TWI_SlaveInit(uint8_t addr)
{
	TWAR_R = (addr<<1);
	
	return E_OK;
}

/************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Slave match the read by looping till an ack 
					is received
*************************************************************/
enuErrorStatus_t TWI_SlaveReadMatch(void)
{
	while((TWSR_R&0xF8) != 0x60) //loop till the correct ack received
	{

		/*Get ack */
		TWCR_R=(1<<TWEA_B)|(1<<TWEN_B)|(1<<TWINT_B);
		while(!GET_BIT(TWCR_R,TWINT_B));
	}
	return E_OK;
}

/************************************************************
* Parameters (in) : uint8_t* pu8data
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Slave reads the data
*************************************************************/
enuErrorStatus_t TWI_SlaveRead(uint8_t* pu8data)
{
	TWCR_R=(1<<TWINT_B)|(1<<TWEA_B)|(1<<TWEN_B);
	while(!GET_BIT(TWCR_R,TWINT_B));
	while((TWSR_R&0xF8) != 0x80);
	*pu8data=TWDR_R;
	return E_OK;
}

/************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Slave match the write by looping till an ack 
					is received
*************************************************************/
enuErrorStatus_t TWI_SlaveWriteMatch(void)
{
	while((TWSR_R&0xF8) != 0xA8) //loop till the correct ack received
	{
		/*Get ack */
		TWCR_R=(1<<TWEA_B)|(1<<TWEN_B)|(1<<TWINT_B);
		while(!GET_BIT(TWCR_R,TWINT_B));
	}
	return E_OK;
}

/************************************************************
* Parameters (in) : uint8_t data
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Slave writes the data
*************************************************************/
enuErrorStatus_t TWI_SlaveWriteData(uint8_t data)
{
	TWDR_R = data;
	TWCR_R = (1<<TWINT_B)|(1<<TWEN_B);
	while(!GET_BIT(TWCR_R,TWINT_B));
	while((TWSR_R&0xF8) != 0xC0);
	return E_OK;
}

/************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : enuErrorStatus_t - For error handling
* Description     : Repeated start for changing the data direction
*************************************************************/
enuErrorStatus_t TWI_RepeatedStart(void)
{
	TWCR_R = (1<<TWINT_B)|(1<<TWSTA_B)|(1<<TWEN_B);
	while(!GET_BIT(TWCR_R,TWINT_B));
	if(TWI_GetStatus()!=REPEATED_S)
	{
		return E_ERROR;
	}
	return E_OK;
}

/************************************************************
* Parameters (in) : None
* Parameters (out): None
* Return Value    : uint8_t - for the status of the TWSR
* Description     : Get the status by checking the TWSR
*************************************************************/
uint8_t TWI_GetStatus(void)
{
	uint8_t status = TWSR_R&0xF8;
	return status;
}
