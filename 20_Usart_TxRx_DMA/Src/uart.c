/*
 * uart.c
 *
 *  Created on: 31 ott 2021
 *      Author: Mattia
 */


#include "uart.h"
#include <stdint.h>
#include "stm32f4xx.h"

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


int __io_putchar (int ch)
{
	write_usart (ch);
	return (ch);
}

void uart2(void)
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

	// per settare PA10 come AF
	GPIOA->MODER &= ~(1U<<20);
	GPIOA->MODER |=  (1U<<21);

	//per pin 10
	GPIOA->AFR[1] |= (1U<<8);
	GPIOA->AFR[1] |= (1U<<9);
	GPIOA->AFR[1] |= (1U<<10);
	GPIOA->AFR[1] &= ~(1U<<11);




	//per pin 9
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
	//USART1->CR1 = (1U<<3);

	//per attivare TE e RE
	USART1->CR1 = ((1U<<3)|(1U<<2));
	//usart enable UE
	USART1->CR1 |= (1U<<13);


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
	//USART1->CR1 = (1U<<3);
	//usart enable UE
	//USART1->CR1 |= (1U<<13);



}

void uart_rx_init(void)
{
	//pa10 alternate function
	GPIOA->MODER |= (1U<<21);
	GPIOA->MODER &=~ (1U<<20);

	//pa10 AF7
	GPIOA->AFR[1] &= ~(1U<<11);
	GPIOA->AFR[1] |= (1U<<10);
	GPIOA->AFR[1] |= (1U<<9);
	GPIOA->AFR[1] |= (1U<<8);

	//rx enable
	USART1->CR1 = ((1U<<2) | (1U<<3));
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


char read_usart(void)
{
	//in attesa controllo RXE data register empty
	while (!(USART1->SR & (1U<<5))) {}

	return USART1->DR;
}


static void uart_set_baudrate (USART_TypeDef *UsartTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    //brr è il registro baudrate register
	UsartTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}



//dal reference manual l'usart1 si trova sul DMA2 (DMA2 request mapping)
//dma per la trasmissione usart1 che si trova su stream 7
void dma2_stream7_init(uint32_t src, uint32_t dest,  uint32_t len) //come parametri ci sono src source, dest destination, len length

{

	/*Enable clock access to DMA*/
	RCC->AHB1ENR |= (1U<<22); //dma2 è collegato al bus ahb1

	/*Disable DMA2 Stream7 access*/
	DMA2_Stream7->CR &= ~(1U<<0);  //registro DMA_SxCR

	while (DMA2_Stream7->CR & (1U<<0) ) {};

	/*clear all interrupt flags stream7*/ //bisogna mettere a 1 tutti gli interrupt relativi allo stram7 contenuti nel
	//registro HIFCR


	DMA2->HIFCR |= (1U<<22);
	DMA2->HIFCR |= (1U<<24);
	DMA2->HIFCR |= (1U<<25);
	DMA2->HIFCR |= (1U<<26);
	DMA2->HIFCR |= (1U<<27);


	/*Set destination buffer*/   //nel PAR register peripheral address register
	DMA2_Stream7->PAR = dest;

	/*Set source buffer*/
	DMA2_Stream7->M0AR = src;

	/*Set length buffer*/
	DMA2_Stream7->NDTR = len;

	/*Select dma2 stream7 channel 4*/ //dal dma mappings
	DMA2_Stream7->CR |= (1U<<27);
	DMA2_Stream7->CR &= ~(1U<<26);
	DMA2_Stream7->CR &= ~(1U<<25);



	/*Enable memory increment*/
	DMA2_Stream7->CR |= (1U<<10);

	/*Configure data transfer direction*/ //in questo caso dalla memoria alla periferica è 01
	DMA2_Stream7->CR &= ~(1U<<7);
	DMA2_Stream7->CR |= (1U<<6);


	/*Enable complete transfer interrupt*/
	DMA2_Stream7->CR |= (1U<<4);  //transfer complete interrupt enable TCIE

	/*Enable direct mode and disable Fifo*/
	DMA2_Stream7->FCR = 0;  //nel fifo state register

	/*Enable dma2 stream7*/
	DMA2_Stream7->CR |= (1U<<0);

	/*Enable USART1 transmit DMA*/
	USART1->CR3 |= (1U<<7);

	/*DMA interrupt enable in NVIC*/
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);



}



