/*
 * timer.c
 *
 *  Created on: 7 nov 2021
 *      Author: Mattia
 */

#include "stm32f4xx.h"

#define TIM2_EN 	(1U<<0)
#define CR1_EN   	(1U<<0)


void  tim_1Hz_init(void)
{
	/*Enable clock access to tim2*/
	RCC->APB1ENR |= TIM2_EN;

	/*Set prescaler value */
	TIM2->PSC = 1600 - 1;
	/*Il prescaler è il divisore. Partendo da una freq.base di 16Mhz si divide per 1600 ottenendo 10000.
	 * 1600 - 1 perchè anche lo 0 viene considerato. La freq del timer2 è abbassata a 10000.
	 */

	/*Set auto-reload value */
	TIM2->ARR = 10000 - 1;
    /* E' il contenuto del registro contatore. In questo modo viene incrementato o decrementato di 1 fino a 10000.
     * con una frequenza di 10000Hz. Quindi andrà a 0 con una frequenza di 1 Hz.
     */



	/*Clear counter*/
	TIM2->CNT = 0; // viene resettato mettendo tutto a zero.

	/*Enable timer*/
	TIM2->CR1 = CR1_EN;

}


void  tim_1Hz_init_interrupt(void)
{
	/*Enable clock access to tim2*/
	RCC->APB1ENR |= TIM2_EN;

	/*Set prescaler value */
	TIM2->PSC = 1600 - 1;
	/*Il prescaler è il divisore. Partendo da una freq.base di 16Mhz si divide per 1600 ottenendo 10000.
	 * 1600 - 1 perchè anche lo 0 viene considerato. La freq del timer2 è abbassata a 10000.
	 */

	/*Set auto-reload value */
	TIM2->ARR = 10000 - 1;
    /* E' il contenuto del registro contatore. In questo modo viene incrementato o decrementato di 1 fino a 10000.
     * con una frequenza di 10000Hz. Quindi andrà a 0 con una frequenza di 1 Hz.
     */



	/*Clear counter*/
	TIM2->CNT = 0; // viene resettato mettendo tutto a zero.

	/*Enable timer*/
	TIM2->CR1 = CR1_EN;


	/*per abilitare l'interrupt per i timer DMA/interrupt enable register */
	TIM2->DIER |= (1U<<0);


	/*abilitare interrupt nel NVIC*/
	NVIC_EnableIRQ(TIM2_IRQn);


}


