/*
 * flash.h
 *
 *  Created on: 8 dic 2021
 *      Author: Mattia
 */

#ifndef FLASH_H_
#define FLASH_H_
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash.h"


void unlock_flash(void);
void erase_flash(void);
void erase2(void);

void write_flash(void);
int read_flash(void);
uint8_t flash_write(volatile uint32_t* address, uint32_t *data, uint16_t size);

#endif /* FLASH_H_ */
