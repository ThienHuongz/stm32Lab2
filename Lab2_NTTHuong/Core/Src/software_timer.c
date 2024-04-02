/*
 * software_timer.c
 *
 *  Created on: Mar 6, 2024
 *      Author: glmun
 */
#include "software_timer.h"
#include "main.h"

int timer1_count = 100;
int timer2_count = 100;
int status = 1;

const int MAX_LED = 4;
int index_led = 0;
int led_buffer [4] = {1 , 2 , 3 , 4};

void update7SEG (int index){
	if (index >3) {
		index_led = 0;
		index = 0;
	}

	switch (index){
		case 0:
		  	HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
		  	HAL_GPIO_WritePin(GPIOA, EN2_Pin| EN3_Pin  | EN1_Pin, GPIO_PIN_SET);
		  	display7SEG(led_buffer[0]);
			break;
		case 1:
		  	HAL_GPIO_WritePin(GPIOA,  EN1_Pin, GPIO_PIN_RESET);
		  	HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_SET);
		  	display7SEG(led_buffer[1]);
			break;
		case 2:
		  	HAL_GPIO_WritePin(GPIOA,EN2_Pin , GPIO_PIN_RESET);
		  	HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN3_Pin, GPIO_PIN_SET);
		  	display7SEG(led_buffer[2]);
			break;
		case 3:
		  	HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
		  	HAL_GPIO_WritePin(GPIOA, EN2_Pin | EN0_Pin | EN1_Pin, GPIO_PIN_SET);
		  	display7SEG(led_buffer[3]);
			break;
		default:
			display7SEG(0);
			break;
	}
}

void timerRun(){

	if (timer1_count > 0){
		timer1_count--;
		if (timer1_count <= 0 ){
	  		  HAL_GPIO_TogglePin(GPIOA,LED_RED_Pin);
	  		  HAL_GPIO_TogglePin(GPIOA,DOT_Pin);
	  		  timer1_count = 100;
		}
	}
	if (timer2_count > 0){
		timer2_count--;
		if (timer2_count <= 0){
			timer2_count= 100;
			update7SEG(index_led++);
		}
	}

}


