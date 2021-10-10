/*
 * input_processing.c
 *
 *  Created on: Oct 10, 2021
 *      Author: PC
 */
#include "main.h"
#include "input_reading.h"

enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND} ;
enum ButtonState buttonState = BUTTON_RELEASED;
void fsm_for_input_processing(void){
	switch(buttonState){
	case BUTTON_RELEASED:
		if(is_button_pressed(0)){
			buttonState = BUTTON_PRESSED;
			//INCREASE VALUE OF PORT A BY ONE UNIT
			HAL_GPIO_WritePin(BUTTON_1_GPIO_Port, BUTTON_1_Pin, 0);
		}
		break;

	case BUTTON_PRESSED:
		if(!is_button_pressed(0)){
			buttonState = BUTTON_RELEASED;
		} else {
			HAL_GPIO_WritePin(BUTTON_1_GPIO_Port, BUTTON_1_Pin, 1);
			if(is_button_press_1s(0)){
				buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}

		break;

	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if(!is_button_pressed(0)){
			buttonState = BUTTON_RELEASED;
		}
		//todo
		HAL_GPIO_WritePin(BUTTON_1_GPIO_Port, BUTTON_1_Pin, 1);
		break;
	}
}

