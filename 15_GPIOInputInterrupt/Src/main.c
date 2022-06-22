//virtual com port su PA9Tx e PA10Rx con USART1 su bus APB2



#include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "exti.h"
/*
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif*/



static void led(void);

int main(void)
{	//per accendere i led su pg13 green e pg14 red
	RCC->AHB1ENR |= (1U<<6);

	GPIOG->MODER |= (1U<<26);
	GPIOG->MODER &=~(1U<<27);

	GPIOG->MODER |= (1U<<28);
	GPIOG->MODER &=~(1U<<29);

	GPIOG->ODR |= (1U<<14);

	pa0_inter_init();

   while(1)
   {
	   /*
	   printf("in attesa del pulsante...\r \n");
	   for (int i=0;i<=100000;i++) {};*/
   }
}





static void led(void)
{
	GPIOG->ODR ^= (1U<<13);
}
/*funzione per la gestione dell'interrupt corrispondente, in questo caso al pin 0.
 * I nomi della funzione sono contenuti nel file startup della cartella startup.
 */
void EXTI0_IRQHandler(void)
{
	//per controllare con esattezza il bit 0, in questo caso, si usa il pending register*/
   if ((EXTI->PR & (1U<<0)) !=0)
   {

	EXTI->PR |= (1U<<0);

	led();
   }
}



