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
uint32_t sensor_value;

int main(void)
{
	usart_init ();
	adc_conf ();
	start_conv ();

	while(1)
   {


   }
}

static void adc_read(void)
{
	sensor_value = ADC1->DR;
	printf("Sensor value : %d \n\r",(int)sensor_value);

}



void ADC_IRQHandler(void)
{
	//check bit EOC
	if ( (ADC1->SR & (1U<<1)) !=0)
	{
		//clear bit ECO
		ADC1->SR = (1U<<0);

		adc_read();
	}

}

