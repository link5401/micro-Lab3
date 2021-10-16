/*
 * input_processing.c
 *
 *  Created on: Oct 10, 2021
 *      Author: PC
 */
#include "main.h"
#include "input_reading.h"

#define NUMBER_OF_LEDS 2

enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND} ;
enum ButtonState buttonStates[NUMBER_OF_LEDS] = {
		BUTTON_RELEASED,
		BUTTON_RELEASED
};

static GPIO_TypeDef * LEDControlPort[NUMBER_OF_LEDS] = {
		LED1_GPIO_Port,
		LED2_GPIO_Port
};

static uint16_t LEDPin[NUMBER_OF_LEDS] = {
		LED1_Pin,
		LED2_Pin
};

void fsm_for_input_processing(void){
	for(int i = 0; i < NUMBER_OF_LEDS; i++){
		switch(buttonStates[i]){
		case BUTTON_RELEASED:
			if(is_button_pressed(i)){
				buttonStates[i] = BUTTON_PRESSED;
				//INCREASE VALUE OF PORT A BY ONE UNIT
			}
			break;

		case BUTTON_PRESSED:
			if(!is_button_pressed(i)){
				buttonStates[i] = BUTTON_RELEASED;
			} else {
				HAL_GPIO_WritePin(LEDControlPort[i], LEDPin[i], 1);
				if(is_button_press_1s(i)){
					buttonStates[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}

			break;

		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if(!is_button_pressed(i)){
				buttonStates[i] = BUTTON_RELEASED;
			}
			//todo
			HAL_GPIO_WritePin(LEDControlPort[i], LEDPin[i], 1);
			break;
		}
	}
}

