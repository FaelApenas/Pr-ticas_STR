/*
 * i2c.c
 *
 *  Created on: Apr 8, 2024
 *      Author: rafae
 */

#include "i2c.h"

#define I2CEN 	(1U<<21)
#define GPIOCEN	(1U<<2)
#define GPIOBEN (1U<<1)


//Set the PB9 and PB8 as alternate funciton

void i2c_init()
{
	RCC->APB1ENR |= (1<<21);  // enable I2C CLOCK
	RCC->AHB1ENR |= (1<<1);  // Enable GPIOB CLOCK


	// Configure the I2C PINs for ALternate Functions
	GPIOB->MODER |= (2<<16) | (2<<18);  // Bits (17:16)= 1:0 --> Alternate Function for Pin PB8; Bits (19:18)= 1:0 --> Alternate Function for Pin PB9
	GPIOB->OTYPER |= (1<<8) | (1<<9);  //  Bit8=1, Bit9=1  output open drain
	GPIOB->OSPEEDR |= (3<<16) | (3<<18);  // Bits (17:16)= 1:1 --> High Speed for PIN PB8; Bits (19:18)= 1:1 --> High Speed for PIN PB9
	GPIOB->PUPDR |= (1<<16) | (1<<18);  // Bits (17:16)= 0:1 --> Pull up for PIN PB8; Bits (19:18)= 0:1 --> pull up for PIN PB9
	GPIOB->AFR[1] |= (4<<0) | (4<<4);  // Bits (3:2:1:0) = 0:1:0:0 --> AF4 for pin PB8;  Bits (7:6:5:4) = 0:1:0:0 --> AF4 for pin PB9


	// Reset the I2C
	I2C1->CR1 |= (1<<15);
	I2C1->CR1 &= ~(1<<15);

	// Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	I2C1->CR2 |= (45<<0);  // PCLK1 FREQUENCY in MHz

	// Configure the clock control registers
	I2C1->CCR = 225<<0;  // check calculation in PDF

	// Configure the rise time register
	I2C1->TRISE = 46;  // check PDF again

	// Program the I2C_CR1 register to enable the peripheral
	I2C1->CR1 |= (1<<0);  // Ena

}

void i2c_start()
{
	I2C1->CR1 |= (1<<10);  // Enable the ACK
	I2C1->CR1 |= (1<<8);  // Generate START
	while (!(I2C1->SR1 & (1<<0)));  // Wait fror SB bit to set

}

void i2c_write(uint8_t data)
{
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
	I2C1->DR = data;
	while (!(I2C1->SR1 & (1<<2)));


}

void i2c_address(uint8_t addr)
{
	I2C1->DR=addr;
	while(!(I2C1->SR1 & (1U<<1)));
	uint8_t temp= I2C1->SR1 | I2C1->SR2;

}
void i2c_stop()
{
	I2C1->CR1 |= (1U<<9);
}

void i2c_write_mult(uint8_t *data, uint size)
{
	while(!(I2C1->SR1 & (1U<<7)));
	while(size)
	{
		while(!(I2C1->SR1 & (1U<<7)));
		I2C1->DR=(volatile uint32_t) data++;
		size--;

	}
	while(!(I2C1->SR1 & (1U<<2)));



}

