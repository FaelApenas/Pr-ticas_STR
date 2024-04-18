/*
 * i2c.h
 *
 *  Created on: Apr 8, 2024
 *      Author: rafae
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"
#include <stdio.h>

void i2c_init();
void i2c_start();
void i2c_write(uint8_t data);
void i2c_address(uint8_t addr);
void i2c_stop();



#endif /* I2C_H_ */
