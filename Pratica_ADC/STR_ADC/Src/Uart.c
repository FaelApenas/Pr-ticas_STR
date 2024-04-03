/*
 * Uart.c
 *
 *  Created on: Mar 11, 2024
 *      Author: rafae
 */

#include "Uart.h"

/*
 * PA9 Alternate functiom
 * PA9 -> |()
 */




void uart_int(uint32_t BaudRate)
{
	RCC->AHB1ENR |= (1U<<0);

	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);

	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |=(1U<<7);



	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	GPIOA->AFR[0] |=(1U<<12);
	GPIOA->AFR[0] |=(1U<<13);
	GPIOA->AFR[0] |=(1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);


	RCC->APB1ENR |= (1U<<17);


	USART2->BRR = compute_uart_bd(sys_freq, BaudRate);
	USART2->CR1 = (CR1_TE|CR1_RE);
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
char uart_read()
{
	while(USART2->SR & SR_RXE){}
	return USART2->DR;
}


