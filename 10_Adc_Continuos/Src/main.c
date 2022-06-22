//virtual com port su PA9Tx e PA10Rx con USART1 su bus APB2



#include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
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
   //attivando la conversione continua non è necessario attivare la conversione ogni volta ma solo una volta
   start_conv();

   while(1)
   {

	   read_value=read_conv();
	   printf("Valore letto: %d \n \r", (int)read_value);

	   for (int i=0;i<500000; i++) {};
   }
}


