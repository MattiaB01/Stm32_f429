/*
 * flash.c
 *
 *  Created on: 8 dic 2021
 *      Author: Mattia
 */

#include <stdint.h>
#include "stm32f4xx.h"
#include "flash.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash.h"

//keys as described in the data-sheets
#define FLASH_FKEY1 0x45670123UL
#define FLASH_FKEY2 0xCDEF89ABUL
/*
IAPCode program_flash(int address, char *data, unsigned int length) {
    unlock_flash(true);

    FLASH->CR = FLASH_CR_PG;

    uint8_t* write_addr = (uint8_t*)address;
    for (int i = 0; i<length; i++) {
        while (FLASH->SR & FLASH_SR_BSY);
        write_addr[i] = data[i];
    }


    IAPCode retval = check_error();
    FLASH->CR = 0;

    unlock_flash(false);

    return retval;
}
*/

void unlock_flash(void)
{
// Wait for the flash memory not to be busy
	while ((FLASH->SR & FLASH_SR_BSY) != 0 ) {};  // (1U<<16)

// Check if the controller is unlocked already

		if ((FLASH->CR & FLASH_CR_LOCK) != 0 ){ // (1U<<31)
			// Write the first key
			FLASH->KEYR = FLASH_FKEY1;
			// Write the second key
			FLASH->KEYR = FLASH_FKEY2;
		}

}

void lock_flash(void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}

void erase2(void)
{

	while ( (FLASH->SR & FLASH_SR_BSY) !=0 ) { };

		FLASH->CR |= (1U<<1); //Sector erase selection

		// indicates the sector 6
		FLASH->CR &=~ (1U<<3);
		FLASH->CR |=  (1U<<4);
		FLASH->CR |=  (1U<<5);
		FLASH->CR &=~ (1U<<6);
		FLASH->CR &=~ (1U<<7);

	    FLASH->CR |= (1U<<16); //start erase

	    // Wait until page erase is done
	    while ( (FLASH->SR & (1U<<16)) != 0 ) {};  //(1U<<16)
	    // If the end of operation bit is set...

	    if ((FLASH->SR & (1U<<0)) != 0){ 	// (1U<<0)
	        // Clear it, the operation was successful
	        FLASH->SR |= (1U<<0);
	    }
	    //Otherwise there was an error
	    else{
	        // Manage the error cases
	    }
	    // Get out of sector erase mode
	    FLASH->CR &= ~(1U<<1);


}



void erase_flash(void)
{

	while ( (FLASH->SR & FLASH_SR_BSY) !=0 ) { };

	FLASH->CR |= (1U<<1); //Sector erase selection

	/// 0000 indicates the sector 0
	FLASH->CR &=~ (1U<<3);
	FLASH->CR &=~  (1U<<4);
	FLASH->CR |= (1U<<5);
	FLASH->CR |= (1U<<6);
	FLASH->CR &=~ (1U<<7);


	FLASH->CR |= (1U<<16); //start erase




	/*FLASH->CR |= FLASH_CR_PER; // Page erase operation
	//	FLASH->AR = page_addr;     // Set the address to the page to be written
	FLASH->CR |= FLASH_CR_STRT;// Start the page erase*/

// Wait until page erase is done
while ( (FLASH->SR & (1U<<16)) != 0 ) {};  //(1U<<16)
// If the end of operation bit is set...

if ((FLASH->SR & (1U<<0)) != 0){ 	// (1U<<0)
    // Clear it, the operation was successful
    FLASH->SR |= (1U<<0);
}
//Otherwise there was an error
else{
    // Manage the error cases
}
// Get out of sector erase mode
FLASH->CR &= ~(1U<<1);

}



void write_flash(void)
{
	//word 32 bit
	/*FLASH->CR &=~ (1U<<8);
	FLASH->CR |= (1U<<9);*/

	//byte 8bit
	FLASH->CR &=~ (1U<<8);
	FLASH->CR &=~ (1U<<9);


	FLASH->CR |= (1U<<24); //interrupt EOP enable
	char mex[4]= "ciao";

	FLASH->CR |= (1U<<0);                   // Programing mode

	//*(__IO uint16_t*)(0x08080000UL) = *mex;       // Write data
    //*(__IO uint32_t*)(0x080400090UL) = *(uint32_t*)"Y";

	uint8_t* write_addr = 0x08040020UL;
	char *data="1234";

	write_addr[0] = data[0];
	write_addr[1] = data[1];
	write_addr[2] = data[2];
	write_addr[3] = data[3];

	// Wait until the end of the operation
	while ( (FLASH->SR & (1U<<16) ) != 0) {};
	// If the end of operation bit is set...
	if ((FLASH->SR & (1U<<0)) != 0){
	    // Clear it, the operation was successful
	     FLASH->SR |= (1U<<0);
	}
	//Otherwise there was an error
	else{
	    // Manage the error cases
		printf("error!\n\r");
		if (FLASH_SR_WRPERR & (1U<<4))
		{
			printf("error pgserr\n\r");
		}
	}
	FLASH->CR &= ~(1U<<0);


}

int read_flash(void)
{
	int a = *(__IO uint16_t*)(0x08080000) ;

	int b= *(volatile unsigned int* ) (0x08080000UL);
    //int a = *(volatile unsigned int *)(0x08000000UL) ;

	return a;
}



