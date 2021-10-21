/*
 * led_display.c
 *
 *  Created on: Oct 17, 2021
 *      Author: PC
 */
#include "timer.h"
#include "main.h"
#include "input_processing.h"
#include "segment_display.h"
uint16_t redDuration = 		10;
uint16_t yellowDuration = 	10;
uint16_t greenDuration = 	10;

void clearAllLEDs(void ){
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin , 1);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin , 1);

	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin , 1);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin , 1);

	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin , 1);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin , 1);
}
void setRedDuration(uint16_t red_duration){
	redDuration = red_duration;
}
void setYellowDuration(uint16_t yellow_duration){
	yellowDuration = yellow_duration;
}
void setGreenDuration(uint16_t green_duration){
	greenDuration = green_duration;

}

//GREEN+YELLOW == RED
//RED > GREEN > YELLOW
void displayLEDsys(uint16_t timerLED){
	//reached TimerLED, reset timer based on the lastest inputs
	 if(isTimerLED() == 1){
		 		setTimerLED((redDuration*TIMER_CYCLE)+(yellowDuration*TIMER_CYCLE)+(greenDuration*TIMER_CYCLE));
	}
	 //display LED, if Duration is different from initial values, do the job
	if(current_mode() == 1 && redDuration !=10 && yellowDuration != 10 && greenDuration != 10){
		//first green burns out
		if(timerLED >= redDuration + yellowDuration){
			clearAllLEDs();
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 0);
		//first yellow burns out
		} else if (timerLED >= redDuration){
			clearAllLEDs();
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
			HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 0);
			//first red burns out
		} else if (timerLED >= yellowDuration){
			clearAllLEDs();
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
			HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 0);
			//repeat.
		}else if (timerLED >=0){
			clearAllLEDs();
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 0);
		}
	}

}
void blinkLED(uint16_t DelayTimerForBlink){

	 if(isTimer1() == 1){

			  if(current_mode() == 2){
				  clearAllLEDs();
				  HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
				  HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);
			  }
			  if(current_mode() ==3){
				  clearAllLEDs();
				  HAL_GPIO_TogglePin(YELLOW1_GPIO_Port, YELLOW1_Pin);
				  HAL_GPIO_TogglePin(YELLOW2_GPIO_Port, YELLOW2_Pin);
			  }
			  if(current_mode() == 4){
				  clearAllLEDs();
				  HAL_GPIO_TogglePin(GREEN1_GPIO_Port, GREEN1_Pin);
				  HAL_GPIO_TogglePin(GREEN2_GPIO_Port, GREEN2_Pin);
			  }

			  setTimer1(DelayTimerForBlink);
		  }
}
