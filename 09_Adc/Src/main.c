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



//double read_value;
char key;

int conv = 8;
double read;

uint32_t read_value;

int main(void)
{
   usart_init();
   adc_conf();


   while(1)
   {
	   start_conv();
	   read_value=read_conv();
	  // read = (double) read_value;
	   read = (read_value * conv) / 100 ;


	   printf("Valore letto: %d \n \r", read_value);

	   for (int i=0;i<500000; i++) {};
   }
}


