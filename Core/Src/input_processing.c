/*
 * input_processing.c
 *
 *  Created on: Oct 10, 2021
 *      Author: PC
 */
#include "main.h"
#include "input_reading.h"
#include "segment_display.h"
#include "timer.h"
#include "led_display.h"

#define NUMBER_OF_EN 4
#define BUTTON1		0
#define BUTTON2		1
#define BUTTON3		2
#define	BUTTON4		3
#define S_TO_MS			1000


enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND} ;
enum ButtonState buttonStates[NUMBER_OF_EN] = {
		BUTTON_RELEASED,
		BUTTON_RELEASED,
		BUTTON_RELEASED,
		BUTTON_RELEASED
};


void buttonStatesInit(void ){
	 HAL_GPIO_WritePin(BUTTON1_GPIO_Port, BUTTON1_Pin ,1);
	 HAL_GPIO_WritePin(BUTTON2_GPIO_Port, BUTTON2_Pin ,1);
	 HAL_GPIO_WritePin(BUTTON3_GPIO_Port, BUTTON3_Pin ,1);
	 HAL_GPIO_WritePin(BUTTON4_GPIO_Port, BUTTON4_Pin ,1);

}
uint8_t mode = 1;
uint16_t DURATION = 1;
void fsm_for_BUTTON1(void){

	switch(buttonStates[BUTTON1]){
		case BUTTON_RELEASED:
			if(is_button_pressed(BUTTON1)){
				mode++;
				DURATION = 1;
				if(mode > 4) {mode = 1;clearAllLEDs();}
				updateClockBuffer(mode,DURATION);
				buttonStates[BUTTON1] = BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:

			if(!is_button_pressed(BUTTON1)) buttonStates[BUTTON1] = BUTTON_RELEASED;
			else {
				if(is_button_press_1s(BUTTON1)){
					buttonStates[BUTTON1] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			mode++;
			DURATION = 1;
			if(mode > 4) {mode = 1;clearAllLEDs();}
			updateClockBuffer(mode,DURATION);
			if(!is_button_pressed(BUTTON1)){
				buttonStates[BUTTON1] = BUTTON_RELEASED;
			}
			break;
	}

}
//increase

void fsm_for_BUTTON2(void){

	switch(buttonStates[BUTTON2]){
			case BUTTON_RELEASED:
				if(is_button_pressed(BUTTON2)){
					DURATION++;
					if(DURATION > 99) DURATION = 1;
					if(DURATION < 1) DURATION = 99;
					updateClockBuffer(mode,DURATION);
					buttonStates[BUTTON2] = BUTTON_PRESSED;
				}
				break;
			case BUTTON_PRESSED:

				if(!is_button_pressed(BUTTON2)) buttonStates[BUTTON2] = BUTTON_RELEASED;
				else {
					if(is_button_press_1s(BUTTON2)){
						buttonStates[BUTTON2] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
					}
				}
				break;
			case BUTTON_PRESSED_MORE_THAN_1_SECOND:
				DURATION++;
				if(DURATION > 99) DURATION = 1;
				if(DURATION < 1) DURATION = 99;
				updateClockBuffer(mode,DURATION);
				if(!is_button_pressed(BUTTON2)){
					buttonStates[BUTTON2] = BUTTON_RELEASED;
				}
				break;
		}

}
void fsm_for_BUTTON3(void){

	switch(buttonStates[BUTTON3]){
			case BUTTON_RELEASED:
				if(is_button_pressed(BUTTON3)){
					DURATION--;
					if(DURATION > 99) DURATION = 1;
					if(DURATION < 1) DURATION = 99;
					updateClockBuffer(mode,DURATION);
					buttonStates[BUTTON3] = BUTTON_PRESSED;
				}
				break;
			case BUTTON_PRESSED:

				if(!is_button_pressed(BUTTON3)) buttonStates[BUTTON3] = BUTTON_RELEASED;
				else {
					if(is_button_press_1s(BUTTON3)){
						buttonStates[BUTTON3] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
					}
				}
				break;
			case BUTTON_PRESSED_MORE_THAN_1_SECOND:
				DURATION--;
				if(DURATION > 99) DURATION = 1;
				if(DURATION < 1) DURATION = 99;
				updateClockBuffer(mode,DURATION);
				if(!is_button_pressed(BUTTON3)){
					buttonStates[BUTTON3] = BUTTON_RELEASED;
				}
				break;
		}

}

void fsm_for_BUTTON4(void){

	switch(buttonStates[BUTTON4]){
			case BUTTON_RELEASED:
				if(is_button_pressed(BUTTON4)){

					if (mode == 2) setRedDuration((DURATION*S_TO_MS)/TIMER_CYCLE);
					if (mode == 3) setYellowDuration((DURATION*S_TO_MS)/TIMER_CYCLE);
					if (mode == 4) setGreenDuration(((DURATION*S_TO_MS)/TIMER_CYCLE));
					DURATION = 1;
					updateClockBuffer(mode,DURATION);
					buttonStates[BUTTON4] = BUTTON_PRESSED;
				}
				break;
			case BUTTON_PRESSED:

				if(!is_button_pressed(BUTTON4)) buttonStates[BUTTON4] = BUTTON_RELEASED;
				else {
					if(is_button_press_1s(BUTTON4)){
						buttonStates[BUTTON4] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
					}
				}
				break;
			case BUTTON_PRESSED_MORE_THAN_1_SECOND:

				if(!is_button_pressed(BUTTON4)){
					buttonStates[BUTTON4] = BUTTON_RELEASED;
				}
				break;
		}

}
uint8_t current_mode(void ){
	return mode;
}


