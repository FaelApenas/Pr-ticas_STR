/*
 * tim .c
 *
 *  Created on: Apr 10, 2024
 *      Author: rafae
 */

#include "tim.h"

#define TIM2EN (1U<<0)

void tim_init_interrupt()
{
	RCC->APB1ENR |=TIM2EN;

	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	TIM2->CNT =0 ;
	TIM2->CR1= (1U<<0);

	TIM2->DIER |= (1U<<0);

	NVIC_EnableIRQ(TIM2_IRQn);


}


