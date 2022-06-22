//virtual com port su PA9Tx e PA10Rx con USART1 su bus APB2



#include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "timer.h"
/*
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif*/



uint32_t read_value;
char key;

int main(void)
{
   usart_init();
   adc_conf();
   tim_1Hz_init();


   while(1)
   {
	   while (!(TIM2->SR & SR_UIF)) {}; // il bit nello status register UIF è l'update interrupt flag
	   /* viene settato se il contatore timer raggiunge il valore fissato nel ARR register*/

	   //viene resettato l'interrupt mettendolo a zero
	   TIM2->SR &= ~SR_UIF;

	   printf("E' passato un secondo \n \r");


   }
}


