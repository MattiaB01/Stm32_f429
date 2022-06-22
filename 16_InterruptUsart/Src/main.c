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


char key;


int main(void)
{
	usart_init ();
	//pa0_inter_init();
	//usart_interrupt_init();
	printf("in attesa");
	printf("in attesa");
	   for (int i=0; i<=1000000;i++) {}
	   printf("in attesa");
	   	printf("in attesa");

	   while(1)
   {
	   /*printf("Prova printf stm32 modulare\n\r");
	   for (int i=0; i<=1000000;i++) {}*/
   }
}
/*funzione per la gestione dell'interrupt corrispondente, in questo caso al pin 0.
 * I nomi della funzione sono contenuti nel file startup della cartella startup.
 */
/*
void EXTI0_IRQHandler()
{*/
	//per controllare con esattezza il bit 0, in questo caso, si usa il pending register*/
	/*printf("Pulsante premuto...");

	EXTI->PR |= (1<<0);


}*/

//funzione eseguita in caso di interrupt su usart1
/*void USART1_IRQHandler()
{*/

	/*per controllare che il data register non è vuoto*/
/*	if (USART1->SR & (1<<5))
	{
		key = USART1->DR;
		printf("premuto il tasto %c", key);
	}

}*/
