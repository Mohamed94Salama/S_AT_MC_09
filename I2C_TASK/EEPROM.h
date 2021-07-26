/*
 * EEPROM.h
 *
 * Created: 7/20/2021 9:41:58 PM
 *  Author: DELLL
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C.h"

enuErrorStatus_t EEPROM_WRITE(uint16_t addr,uint8_t data);
enuErrorStatus_t EEPROM_READ(uint16_t addr,uint8_t* ptr);



#endif /* EEPROM_H_ */
