/*
 * timer.c
 *
 *  Created on: Oct 10, 2021
 *      Author: PC
 */
#include "main.h"
#include "input_reading.h"
#include "segment_display.h"
#include "led_display.h"

//timer 0 is for displaying segments

uint16_t timer0_counter = 0;
uint8_t timer0_flag = 0;

void setTimer0(uint16_t duration){
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
}
void timer0_run(){
	if(timer0_counter > 0){
		timer0_counter--;
		if(timer0_counter == 0) timer0_flag = 1;
	}
}

uint8_t isTimer0(void ){
	return timer0_flag;
}

void displaySegment(uint16_t DelayTimerForSegment){
	displayClock(timer0_counter,DelayTimerForSegment);
}
//*******************************************************************
//timer for LED system


uint16_t timerLED_counter = 0;
uint8_t timerLED_flag = 0;

void setTimerLED(uint16_t duration){
	timerLED_counter = duration/TIMER_CYCLE;
	 timerLED_flag = 0;
}

void timerLED_run(){
	if(timerLED_counter > 0){
		timerLED_counter--;
		if(timerLED_counter == 0){ timerLED_flag = 1;}
	}
}

uint8_t isTimerLED(void){
	return timerLED_flag;
}

void displayLED(){
	displayLEDsys(timerLED_counter);
}


//************************************************************************
//timer for lED blinking
uint16_t timer1_counter = 0;
uint8_t timer1_flag = 0;

void setTimer1(uint16_t duration){
	timer1_counter = duration / TIMER_CYCLE;
	timer1_flag = 0;
}
void timer1_run(){
	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter == 0) timer1_flag = 1;
	}
}

uint8_t isTimer1(void ){
	return timer1_flag;
}



//***********************************************************************************
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		button_reading();
		timer0_run();
		timerLED_run();
		timer1_run();
	}

}
