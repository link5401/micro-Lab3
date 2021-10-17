/*
 * timer.h
 *
 *  Created on: Oct 17, 2021
 *      Author: PC
 */
#include "main.h"
#ifndef INC_TIMER_H_
#define INC_TIMER_H_


uint8_t isTimer1(void );
void setTimer1(uint16_t duration);
uint8_t isTimer0(void );
void setTimer0(uint16_t duration);
void displaySegment(uint16_t DelayTimerForSegment);



uint8_t isTimerLED(void);
void setTimerLED(uint16_t duration);
void displayLED();



#endif /* INC_TIMER_H_ */
