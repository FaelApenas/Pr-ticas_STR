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
int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

int __io_getchar()
{
	return uart_read();
}


void uart_int(uint32_t BaudRate)
{
	RCC->AHB1ENR |= (1U<<0);

	GPIOA->MODER &=~ (1U<<18);
	GPIOA->MODER |= (1U<<19);

	GPIOA->MODER &=~ (1U<<20);
	GPIOA->MODER |= (1U<<21);

	GPIOA->AFR[1] |=(1U<<8);
	GPIOA->AFR[1] |=(1U<<9);
	GPIOA->AFR[1] |=(1U<<10);
	GPIOA->AFR[1] &=~(1U<<11);

	GPIOA->AFR[1] |=(1U<<4);
	GPIOA->AFR[1] |=(1U<<5);
	GPIOA->AFR[1] |=(1U<<6);
	GPIOA->AFR[1] &=~(1U<<7);


	RCC->APB2ENR |= (1U<<4);

	USART1->BRR = compute_uart_bd(sys_freq, BaudRate);

	USART1-> CR1 |= (1U<<5);
	//NVIC_EnableIRQ(USART1_IRQn);

	USART1->CR1 = CR1_TE|(1U<<2);
	USART1->CR1|= CR1_UE;

}



static uint16_t compute_uart_bd(uint32_t periph_clock,uint32_t Baudrate)
{
	return ((periph_clock+(Baudrate/2U))/Baudrate);

}

void uart_write(int ch)
{
	while(!(USART1->SR & SR_TXE)){}

		USART1->DR = (ch & 0xFF);


}

char uart_read()
{
	while(!(USART1->SR & SR_RXNE)){}
	return USART1->DR;
}


