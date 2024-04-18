
#include "Systick.h"


void sys_delay_ms(int delay)
{
	SysTick->LOAD= SYSTICK_LOAD_VAL_MS;
	SysTick->VAL=0;
	SysTick->CTRL= CTRL_ENABLE|CTRL_CLKSRC;

	for(int i= 0 ; i<delay;i++)
	{
		while((SysTick->CTRL & CTRL_COUNTFLAG)==0){}
	}
	SysTick->CTRL=0;

}


void sys_delay_us(int delay)
{
	SysTick->LOAD= SYSTICK_LOAD_VAL_US;
	SysTick->VAL=0;
	SysTick->CTRL= CTRL_ENABLE|CTRL_CLKSRC;

	for(int i= 0 ; i<delay;i++)
	{
		while((SysTick->CTRL & CTRL_COUNTFLAG)==0){}
	}
	SysTick->CTRL=0;


}


