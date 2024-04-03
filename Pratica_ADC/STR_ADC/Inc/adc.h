/*
 * adc.h
 *
 *  Created on: Mar 13, 2024
 *      Author: rafae
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"


void adc_init(void);
void start_conv(void);
uint32_t adc_read(void);



#endif /* ADC_H_ */
