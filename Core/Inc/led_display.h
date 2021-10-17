/*
 * led_display.h
 *
 *  Created on: Oct 17, 2021
 *      Author: PC
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_



void clearAllLEDs(void );
void setRedDuration(uint16_t red_duration);
void setYellowDuration(uint16_t yellow_duration);
void setGreenDuration(uint16_t green_duration);


void blinkLED(uint16_t DelayTimerForBlink);
void displayLEDsys(uint16_t timerLED);

#endif /* INC_LED_DISPLAY_H_ */
