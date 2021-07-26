/*
 * I2C_Cfg.h
 *
 * Created: 7/17/2021 1:39:48 PM
 *  Author: DELLL
 */ 


#ifndef I2C_CFG_H_
#define I2C_CFG_H_

#define TWI_FREQ	100000ul

/* 0 ---> prescale by 1 , 1 ---> prescale by 4 , 2 ---> prescale by 16 , 3 ---> prescale by 64 */
#define PRESCALE	0

#define START				0x08
#define REPEATED_S			0x10
#define MT_SLA_W_ACK		0x18
#define MT_SLA__W_NACK		0x20
#define MT_DATA_ACK			0x28
#define	MT_DATA_NACK		0x30
#define MT_SLA_R_ACK		0x40
#define MT_SLA_R_NACK		0x48
#define MT_R_DATA_ACK		0x50
#define MT_R_DATA_NACK		0x58



#endif /* I2C_CFG_H_ */
