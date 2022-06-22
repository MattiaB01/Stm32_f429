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


void p (void);
#endif /* UART_H_ */
