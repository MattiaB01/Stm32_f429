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
   //usart_init();
   //adc_conf();
   //tim_1Hz_init();
  /*
   * In output compare mode, a timer module controls an output waveform
   * or indicates when a period of time has elapsed.
   * When a match is detected between the output compare register (OCR) and the counter,
   * the output compare function assigns the corresponding output pin to a programmable value defined by the output
   * compare mode defined by the programmer.

   * The output compare pin can be driven high, low, toggles its sate, or stay unchanged.
   * This is determined by the programmer as per the application requirements.
   * This mode of operation can be extremely advantageous for generating timing signals and output driving in many applications
   */

   timPA5_Output_Compare();
   while(1)
   {
	   //a seconda del timer impostato e a quale output corrisponde e alla modalità (high,low,toggle ecc...)
	   //viene generato un interrupt o un cambiamento di stato sul pin corrispondente al timer selezionato

   }
}


