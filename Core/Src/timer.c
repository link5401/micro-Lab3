/*
 * timer.c
 *
 *  Created on: Oct 10, 2021
 *      Author: PC
 */
#include "main.h"
#include "input_reading.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		button_reading();
	}
}

