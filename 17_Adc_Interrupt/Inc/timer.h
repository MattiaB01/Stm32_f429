/*
 * timer.h
 *
 *  Created on: 7 nov 2021
 *      Author: Mattia
 */

#ifndef TIMER_H_
#define TIMER_H_


void  tim_1Hz_init(void);
void  timPA5_Output_Compare(void);
void  tim3_pa6_input_capture(void);

#define SR_UIF 	 (1U<<0)
#define SR_CC1IF (1U<<1)  // il pin è settato a 1 dall'hardware quando l'input è catturato leggendo il registro CCR1
#endif /* TIMER_H_ */
