/*
 * timer.h
 *
 *  Created on: 7 nov 2021
 *      Author: Mattia
 */

#ifndef TIMER_H_
#define TIMER_H_


void  tim_1Hz_init(void);

void  tim_1Hz_init_interrupt(void);

#define SR_UIF 	(1U<<0)
#endif /* TIMER_H_ */
