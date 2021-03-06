//virtual com port su PA9Tx e PA10Rx con USART1 su bus APB2



#include <stdint.h>
#include "stm32f4xx.h"
//bisogna aggiungere
#include <stdio.h>


/*
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif*/

#define GPIOG_EN (1U<<6)
#define PIN13 (1U<<13)
#define LED_PIN PIN13
#define USART1EN  (1U<<4)


//frequenza di sistema tipica
#define SYS_FREQ  		16000000
#define APB2_CLK 		SYS_FREQ
#define UART_BAUDRATE 	115200


static void uart_set_baudrate (USART_TypeDef *UsartTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void write_usart (int ch);
void usart_init (void);

//aggiunta funzione
int __io_putchar (int ch)
{
	write_usart(ch);
	return ch;
}



int main(void)
{
   usart_init();
   printf("Start...\n\r");


   while(1)
   {
	   //printf("Prova printf stm32 \n\r");
	   //for (int i=0; i<=1000000;i++) {}
   }
}




void usart_init (void)
{

	//per abilitare clock su APB2 dal datasheet
	RCC->APB2ENR |= USART1EN;

	RCC->AHB1ENR |= GPIOG_EN;

	RCC->AHB1ENR |= (1U<<0);

	//i pin 9 e 10 devono essere settati per le funzioni alternative AF
	//in questo caso i pin sono mappati sul registro alto AFRH con AF7 0111


	//per settare il pin 9 nel registro mode con Alternate Function

	GPIOA->MODER &= ~(1U<<18);
	GPIOA->MODER |= (1U<<19);

	GPIOA->AFR[1] |= (1U<<4);
	GPIOA->AFR[1] |= (1U<<5);
	GPIOA->AFR[1] |= (1U<<6);
	GPIOA->AFR[1] &= ~(1U<<7);

	GPIOG->MODER |= (1U<<26);
	GPIOG->MODER &=~(1U<<27);

	//config uart baudrate
	uart_set_baudrate(USART1, APB2_CLK, UART_BAUDRATE);

	//config transfer direction
	//per fare questo bisogna settare USART CR control register
	//e in particolare il bit TE (trasmit enable)
	USART1->CR1 = (1U<<3);
	//usart enable UE
	USART1->CR1 |= (1U<<13);



}




void write_usart (int ch)
{
	//sr status register contiene il bit TXE trasmit data register empty
	while (!(USART1->SR & (1U<<7)))
	{

	}
	USART1->DR = (ch & 0xFF);

}

static void uart_set_baudrate (USART_TypeDef *UsartTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    //brr ?? il registro baudrate register
	UsartTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

