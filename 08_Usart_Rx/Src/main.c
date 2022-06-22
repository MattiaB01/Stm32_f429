//virtual com port su PA9Tx e PA10Rx con USART1 su bus APB2



#include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"
/*
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif*/




char key;

int main(void)
{
   usart_init();
   while(1)
   {

	   key= read_usart();


	   printf("Prova printf stm32 modulare\n\r");
	   for (int i=0; i<=1000000;i++) {}
   }
}


