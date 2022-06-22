//virtual com port su PA9Tx e PA10Rx con USART1 su bus APB2



#include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"


/*
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif*/




int main(void)
{
   usart_init();

   while(1)
   {
   }

}


void print_text (void)
{
	printf("E' passato un secondo");
}



void SysTick_Handler(void)
{

	print_text();

}
