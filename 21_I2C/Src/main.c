//virtual com port su PA9Tx e PA10Rx con USART1 su bus APB2



#include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>
#include "uart.h"
#include "i2c.h"
#include "oled.h"
#include "fonts.h"
#include "rccconfig.h"
/*
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif*/

int numero;
int res;

void SysClockConfig__(void) //set the core frequency to 100MHz
{
//#define PLL_M      4
//#define PLL_N      200
//#define PLL_P      4
//#define PLL_Q      2

#define	PLL_M  8


#define	PLL_N  360


#define	PLL_P  4


#define	PLL_Q  15

__IO uint32_t StartUpCounter = 0, HSEStatus = 0;


  RCC->CR |= ((uint32_t)RCC_CR_HSEON);


  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != 3000));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR &= (uint32_t)~(PWR_CR_VOS);


    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;


    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;


    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;


    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);


    RCC->CR |= RCC_CR_PLLON;


    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
    FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_3WS;

    /* Select the main PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    /* Wait till the main PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL)
    {;}
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }

}

int main(void)
{
SysClockConfig();
i2c_init();
res= i2c_bus_scan();
SSD1306_Init();
SSD1306_GotoXY (0,0);

SSD1306_Puts ("0", &Font_7x10, 1);
while(1)
   {
		numero++;
		for (int k=0;k<1000;k++){};

   }
}
