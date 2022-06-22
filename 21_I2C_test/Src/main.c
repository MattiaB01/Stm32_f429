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
   //usart_init();
   //uart_rx_init();
	uart2();
	printf("inizio\n\r");
	char src[20]="text from dma\n\r";

	dma2_stream7_init( (uint32_t) src, (uint32_t)&USART1->DR,  20);

   while(1)
   {
	   /*
	   printf("Prova printf stm32 modulare\n\r");
	   for (int i=0; i<=1000000;i++) {}*/
	  /* key= read_usart();
	   printf("tasto");
	   for (int i=0; i<=1000000;i++) {}*/
/*
	   key= read_usart();


	   printf("Hai premuto il tasto %c \n\r",key);
	   for (int i=0; i<=1000000;i++) {}
*/

   }
}

static void dma_callback()
{
	printf("Stampa contenuto dalla memoria\n\r");
	printf(read_usart());

}


void DMA2_Stream7_IRQHandler  ()
{

//DMA2->HISR
	/*Check for transfer complete interrupt*/
		if(DMA2->HISR & (1U<<27) )   //TCIF7 transfer complete interrupt stream7
		{
			/*Clear flag*/
			DMA2->HIFCR |= (1U<<27);  //Flag Clear Register / Clear interrupt complete transfer

			/*Do something*/
			dma_callback();
		}



}

