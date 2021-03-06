/*
 * i2c.h
 *
 *  Created on: 26 feb 2022
 *      Author: Mattia
 */

#ifndef I2C_H_
#define I2C_H_



#endif /* I2C_H_ */


#include <stdio.h>

void i2c_init(void);
void i2c_byteRead(char saddr, char maddr, char *data);
void i2c_burstRead(char saddr, char maddr, int n, char *data);
void i2c_WriteMulti(char saddr, char maddr, char *data,uint8_t length);
void i2c_writeByte(char saddr, char maddr, char data) ;

uint8_t i2c_bus_scan(void);
int ret1(void);
