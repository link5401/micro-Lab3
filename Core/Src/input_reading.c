/*
 * input_reading.c
 *
 *  Created on: Oct 10, 2021
 *      Author: PC
 */
#include "main.h"

#define NUMBER_OF_BUTTON				4
#define DURATION_FOR_AUTO_INCREASING	100

#define BUTTON_IS_PRESSED                  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED                 GPIO_PIN_SET

//the buffer that the final result is stored after deboucing
static GPIO_PinState buttonBuffer[NUMBER_OF_BUTTON] = {
		BUTTON_IS_RELEASED,
		BUTTON_IS_RELEASED,
		BUTTON_IS_RELEASED,
		BUTTON_IS_RELEASED
};


//we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[NUMBER_OF_BUTTON] = {
		BUTTON_IS_RELEASED,
		BUTTON_IS_RELEASED,
		BUTTON_IS_RELEASED,
		BUTTON_IS_RELEASED
};
static GPIO_PinState debounceButtonBuffer2[NUMBER_OF_BUTTON]= {
		BUTTON_IS_RELEASED,
		BUTTON_IS_RELEASED,
		BUTTON_IS_RELEASED,
		BUTTON_IS_RELEASED
};

static uint16_t counterForButtonPress1s[NUMBER_OF_BUTTON]= {
		0,
		0,
		0,
		0
};
static uint8_t flagForButtonPress1s[NUMBER_OF_BUTTON] = {
		0,
		0,
		0,
		0
};


static GPIO_TypeDef * ButtonPort[NUMBER_OF_BUTTON] = {
		BUTTON1_GPIO_Port,
		BUTTON2_GPIO_Port,
		BUTTON3_GPIO_Port,
		BUTTON4_GPIO_Port
};

static uint16_t ButtonPin[NUMBER_OF_BUTTON] = {
		BUTTON1_Pin,
		BUTTON2_Pin,
		BUTTON3_Pin,
		BUTTON4_Pin
};

unsigned char is_button_pressed(uint8_t index){
	if(index >= NUMBER_OF_BUTTON) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}
unsigned char is_button_press_1s(unsigned char index){
	if(index >= NUMBER_OF_BUTTON) return 0xff;
	return (flagForButtonPress1s[index] == 1);
}
//read all buttons available and debouncing. the program reads all buttons
//two consecutive times and compare the values.
//If the values are the same, update the value to buttonBuffer.
void button_reading(void){
	for(uint8_t i = 0; i < NUMBER_OF_BUTTON; i++){
		//read pin, check for bounce
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(ButtonPort[i], ButtonPin[i]);

		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
			buttonBuffer[i] = debounceButtonBuffer1[i];
			if(buttonBuffer[i] == BUTTON_IS_PRESSED){
				if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
					counterForButtonPress1s[i]++;
				} else {
					flagForButtonPress1s[i] = 1;

				}

			} else {
				counterForButtonPress1s[i] = 0;
				flagForButtonPress1s[i] = 0;
			}
		}
	}
}

