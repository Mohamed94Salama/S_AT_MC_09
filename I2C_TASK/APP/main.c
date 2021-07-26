/*
 * I2C_TASK.c
 *
 * Created: 7/20/2021 5:20:41 PM
 * Author : DELLL
 */ 

#include "../ECUAL/EEPROM/EEPROM.h"
#include "../MCAL/UART/UART.h"

int main(void)
{
	/* TWI Initialization */
	TWI_MasterInit();
	
	/* A character the return the data to read */
	uint8_t c;
	
	/* UART Initialization */
	UART_Init();
	
	/* Strings to see on the terminal device */
	uint8_t* arr0="Enter a command (READ , WRITE): \r";
	uint8_t* arr1="Enter the address :\r";
	uint8_t* arr2="Enter the data: \r";
	uint8_t* arr_OK="OK\r";
	
	/* Array to get the addresses */
	uint8_t x[9];
	uint8_t x1[9];
	
	/* Array to get the data */
	uint8_t dat;
	
	/* The converted addresses from characters to integral form */
	uint8_t res=0;
	
    while (1) 
    {
	/* Array to get the command */	
	uint8_t cmnd[7];
	
	UART_SendString(arr0);
	UART_ReceiveString(cmnd,MAX_LEN);
	
	/* Write command is selected */
	if(!strcmp(cmnd,"WRITE\r"))
	{
	/* Getting the address from the user */	
	UART_SendString(arr_OK);
	UART_SendString(arr1);
	UART_ReceiveString(x,MAX_LEN);
	
	/* Convert the string of the address */
	uint8_t i=0;
	while(x[i] != '\r')
	{
		if(x[i]=='1')
		{
			if(i==0)
			{
				res=res+128;
			}else if(i==1)
			{
				res=res+64;
			}else if(i==2)
			{
				res=res+32;
			}else if(i==3)
			{
				res=res+16;
			}else if(i==4)
			{
				res=res+8;
			}else if(i==5)
			{
				res=res+4;
			}else if(i==6)
			{
				res=res+2;
			}else if(i==7)
			{
				res=res+1;
			}
		}
		i++;
	}
	
	/* Getting the data to write */
	UART_SendString(arr_OK);
	UART_SendString(arr2);
	UART_ReceiveData(&dat);
	EEPROM_WRITE(res,dat);
	_delay_ms(20);	
	UART_SendData('\r');
	res=0;
	/* Read command is selected */
	}else if(!strcmp(cmnd,"READ\r"))
	{
	/* Getting the address location of the data to read */	
	UART_SendString(arr_OK);
	UART_SendString(arr1);
	UART_ReceiveString(x1,MAX_LEN);
	uint8_t i=0;
	while(x1[i] != '\r')
	{
		if(x1[i]=='1')
		{
			if(i==0)
			{
				res=res+128;
			}else if(i==1)
			{
				res=res+64;
			}else if(i==2)
			{
				res=res+32;
			}else if(i==3)
			{
				res=res+16;
			}else if(i==4)
			{
				res=res+8;
			}else if(i==5)
			{
				res=res+4;
			}else if(i==6)
			{
				res=res+2;
			}else if(i==7)
			{
				res=res+1;
			}
		}
		i++;
	}
	
	/* Returning the data */	
	EEPROM_READ(res,&c);
	UART_SendData(c);

	UART_SendData('\r');
	res=0;
	}

		
    }
}
