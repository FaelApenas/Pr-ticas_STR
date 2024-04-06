/*
 * adc.c
 *
 *  Created on: Mar 13, 2024
 *      Author: rafae
 */

#include "adc.h"


void adc_init()
{
	RCC->AHB1ENR |= (1U<<0);

	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	RCC->APB2ENR |= (1U<<8); // habilita o clock no adc

	ADC1->CR1 |= (1U<<5);
	NVIC_EnableIRQ(ADC_IRQn);

	ADC1->SQR3    = (1U<<0); // inicia a sequencia de conversã
	ADC1->SQR1	= 0x00;


	ADC1-> CR2 |=(1U<<0); // HABILITA O MODULO ADC




}


void start_conv()
{
	ADC1-> CR2 |= (1U<<1);
	ADC1-> CR2 |= (1U<<30);


}

uint32_t adc_read()
{
	while(!(ADC1->SR & (1U<<1)))
	{

	}
	return (ADC1->SR);
}
