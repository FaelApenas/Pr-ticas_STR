#ifndef UART_H
#define UART_H

#include "stm32f4xx.h"
#include <stdint.h>

#define sys_freq	 16000000

#define CR1_TE 			(1U<<3)
#define CR1_UE			(1U<<13)
#define CR1_RE 			(1U<<2)
#define SR_TXE			(1U<<7)
#define SR_RXE			(1U<<5)

void uart_int(uint32_t BaudRate);

static uint16_t compute_uart_bd(uint32_t periph_clock,uint32_t Baudrate);
void uart_write(int ch);
char uart_read();




#endif
