/*
 * i2c.c
 *
 *  Created on: 13 nov 2021
 *      Author: Mattia
 */

#include "stm32f4xx.h"

void i2c_init(void)
{

	/*Enable clock bus portB */
	RCC->AHB1ENR |= (1U<<1);

	/*Enable clock bus I2C */
	RCC->APB1ENR |=  (1U<<21);
	/*PB6=SCL PB7=SDA */
	/*Alternate function*/
	GPIOB->MODER |= (1U<<15);
	GPIOB->MODER &=~(1U<<14);

	GPIOB->MODER |= (1U<<13);
	GPIOB->MODER &=~(1U<<12);

	/*nel registro di  output OTYPER bisogna settare open drain */
	GPIOB->OTYPER |= (1U<<7);
	GPIOB->OTYPER |= (1U<<6);

	/*nel registro pull-up pull-down bisogna settare pull-up 01*/
	GPIOB->PUPDR &=~(1U<<15);
	GPIOB->PUPDR |= (1U<<14);

	GPIOB->PUPDR &=~ (1U<<13);
	GPIOB->PUPDR |=~(1U<<12);

	/*Set reset*/
	I2C1->CR1 |= (1<<15);

	/*Restore from reset*/
	I2C1->CR1 &=~(1<<15);

	/*Set clk peripheral */
	I2C1->CR2 = (1U<<4);

	/*Set I2C standard mode 100khz*/
	I2C1->CCR = 80;

	/*set rise time*/
	I2C1->TRISE = 17;

	/*Enable I2C */
	I2C1->CR1 |= (1U<<0);




}


void I2C1_readByte (char slaveAddress, char memAddress, char *data)
{
		//wait until bus not busy
		while(I2C1->SR2 & (1U<<1)){}

		//generate start condition
		I2C1->CR1 |= (1U<<8);

		//wait until start flag is set in the register
		while(! (I2C1->SR1 & (1<<0))) {}


}
