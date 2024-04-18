#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL_MS	16000 - 1
#define SYSTICK_LOAD_VAL_US 16 - 1
#define CTRL_ENABLE 		(1U<<0)
#define CTRL_CLKSRC			(1U<<2)
#define CTRL_COUNTFLAG		(1U<<16)


void sys_delay_ms(int delay);
void sys_delay_us(int delay);

#endif /* SYSTICK_H_ */
