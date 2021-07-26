/*
 * I2C.h
 *
 * Created: 7/17/2021 1:39:34 PM
 *  Author: DELLL
 */ 


#ifndef I2C_H_
#define I2C_H_

/* Includes */
#include <util/delay.h>
#include "../../LIB/BIT_MANIPULATE.h"
#include "../../LIB/Register.h"
#include "../../LIB/Register_Cont.h"
#include "I2C_Cfg.h"
//#include "STD_TYPES.h"

/* Functions prototypes */
enuErrorStatus_t TWI_MasterInit(void);
enuErrorStatus_t TWI_StartCondition(void);
enuErrorStatus_t TWI_StopCondition(void);

enuErrorStatus_t TWI_WriteToAddress(uint8_t address);
enuErrorStatus_t TWI_ReadFromAddress(uint8_t address);

enuErrorStatus_t TWI_WriteData(uint8_t data);
enuErrorStatus_t TWI_ReadData(uint8_t* pu8data);

enuErrorStatus_t TWI_SlaveInit(uint8_t addr);
enuErrorStatus_t TWI_SlaveReadMatch(void);
enuErrorStatus_t TWI_SlaveRead(uint8_t* pu8data);
enuErrorStatus_t TWI_SlaveWriteMatch(void);
enuErrorStatus_t TWI_SlaveWriteData(uint8_t data);

enuErrorStatus_t TWI_RepeatedStart(void);


uint8_t TWI_GetStatus(void);

#endif /* I2C_H_ */
