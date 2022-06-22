/*
 * uart.h
 *
 *  Created on: 31 ott 2021
 *      Author: Mattia
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>

void usart_init (void);
void uart_rx_init(void);
char read_usart(void);
void uart2(void);
void dma2_stream7_init(uint32_t src, uint32_t dest,  uint32_t len);

#endif /* UART_H_ */
