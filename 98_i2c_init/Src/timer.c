/*
 * timer.c
 *
 *  Created on: 7 nov 2021
 *      Author: Mattia
 */

#include "stm32f4xx.h"

#define TIM2_EN 	(1U<<0)
#define CR1_EN   	(1U<<0)
#define OC_TOGGLE	((1U<<4)|(1U<<5))
#define PORTA_EN    (1U<<0)

void  tim_1Hz_init(void)
{
	/*Enable clock access to tim2*/
	RCC->APB1ENR = TIM2_EN;

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


void  timPA5_Output_Compare(void)
{
	/*Enable portA clk */
	RCC->AHB1ENR |= PORTA_EN;

	/*Set PA5 to alternate mode*/
	GPIOA->MODER |= (1U<<11);
	GPIOA->MODER &=~(1U<<10);

	/*Set alternate function PA5 TIM2ch1 AF1 0001 */
		GPIOA->AFR[0] &= ~(1U<<23);
		GPIOA->AFR[0] &= ~(1U<<22);
		GPIOA->AFR[0] &= ~(1U<<21);
		GPIOA->AFR[0] |=  (1U<<20);


	/*Enable clock access to tim2*/
	RCC->APB1ENR = TIM2_EN;

	/*Set prescaler value */
	TIM2->PSC = 160 - 1;
	/*Il prescaler è il divisore. Partendo da una freq.base di 16Mhz si divide per 1600 ottenendo 10000.
	 * 1600 - 1 perchè anche lo 0 viene considerato. La freq del timer2 è abbassata a 10000.
	 */

	/*Set auto-reload value */
	TIM2->ARR = 10000 - 1;
    /* E' il contenuto del registro contatore. In questo modo viene incrementato o decrementato di 1 fino a 10000.
     * con una frequenza di 10000Hz. Quindi andrà a 0 con una frequenza di 1 Hz.
     */

	/*Set output compare mode to Toggle (attraverso registro CCMR1)*/
	TIM2->CCMR1 = OC_TOGGLE;


	/*Enable Tim2 ch1 in compare mode  (attraverso registo CCER captureCompareEnableRegister)*/
	TIM2->CCER = (1U<<0);


	/*Clear counter*/
	TIM2->CNT = 0; // viene resettato mettendo tutto a zero.

	/*Enable timer*/
	TIM2->CR1 = CR1_EN;

}

void tim3_pa6_input_capture(void)
{	/*In questo esempio viene usato il pin PA6
	  per essere usato come input capture di un timer
	  in questo caso TIM3CH1 */

	/*Enable portA clk */
	RCC->AHB1ENR |= PORTA_EN;

	/*Set PA6 to alternate mode*/
	GPIOA->MODER |= (1U<<13);
	GPIOA->MODER &=~(1U<<12);

	/*Set alternate function PA6 TIM3ch1 AF2 */
	GPIOA->AFR[0] &= ~(1U<<27);
	GPIOA->AFR[0] &= ~(1U<<26);
	GPIOA->AFR[0] |=  (1U<<25);
	GPIOA->AFR[0] &= ~(1U<<24);

	/*Enable TIM3 CLK*/
	RCC->APB1ENR |= (1U<<1);

	/*Set prescaler tim3*/
	TIM3->PSC = 160-1; //divide 16000000/16000 (-1 perchè parte da 0)

	/*Set ch1 input capture mode*/
	TIM3->CCMR1 = (1U<<0);

	/*Enable input capture rising edge */
	TIM3->CCER = (1U<<0);

	/*Enable tim3 control register*/
	TIM3->CR1 = CR1_EN;



}
