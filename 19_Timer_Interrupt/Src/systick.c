/*
 * systick.c
 *
 *  Created on: 4 nov 2021
 *      Author: Mattia
 */

#include "stm32f4xx.h"

#define SYSTICK_VALUE 	16000    //indica il numero di cicli clock per millisecondo con freq 16Mhz
#define SYSTICK_EN 		(1U<<0)  //per abiitare systick
#define SYS_CLOCK_SRC   (1U<<2)   //per la scelta di utilizzare un clock interno o esterno
#define SYS_CLK_COUNT 	(1U<<16)

void systick_Delay_Ms (int delay)
{
	SysTick->LOAD = SYSTICK_VALUE;

	//forza l'inizio a 0
	SysTick->VAL =0;

	//enable systick e clock interno
	SysTick->CTRL = SYSTICK_EN | SYS_CLOCK_SRC ;

	for (int i=0;i<delay; i++)
	{

		while ((SysTick->CTRL & SYS_CLK_COUNT) == 0)
		{}

	}
	SysTick->CTRL =0;
}

