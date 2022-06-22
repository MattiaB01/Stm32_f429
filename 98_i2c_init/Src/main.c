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



/*SET-UP : connect a jump from PA5 to PA6 */

int timestamp=0;


int main(void)
{
	timPA5_Output_Compare();
	tim3_pa6_input_capture();


   while(1)
   {
	   /*Wait until edge is captured*/
	   while (! (TIM3->SR & SR_CC1IF)) {}

	   /*Read value*/
	   timestamp = TIM3->CCR1;
   }
}


