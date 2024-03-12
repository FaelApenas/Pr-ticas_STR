/*
 * Uart.c
 *
 *  Created on: Mar 11, 2024
 *      Author: rafae
 */

#include "Uart.h"



void uart_int(uint32_t BaudRate)
{
	RCC->AHB1ENR |= (1U<<0);

	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);

	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0]&=~(1U<<11);


	RCC->APB1ENR |= (1U<<17);

	USART2->BRR = compute_uart_bd(sys_freq, BaudRate);

	USART2->CR1 = CR1_TE;
	USART2->CR1|= CR1_UE;



}



static uint16_t compute_uart_bd(uint32_t periph_clock,uint32_t Baudrate)
{
	return ((periph_clock+(Baudrate/2U))/Baudrate);

}

void uart_write(int ch)
{
	while(!(USART2->SR & SR_TXE)){}

		USART2->DR = (ch & 0xFF);




}
