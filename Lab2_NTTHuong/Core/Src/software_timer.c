/*
 * software_timer.c
 *
 *  Created on: Mar 6, 2024
 *      Author: glmun
 */
#include "software_timer.h"
#include "main.h"

int timer1_count = 100;
int timer2_count = 50;
int status = 1;

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
			timer2_count= 50;
	  		  switch (status){
	  		  	  case 1:
	  		  		status = 2;
	  		  		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
	  		  		HAL_GPIO_WritePin(GPIOA, EN2_Pin| EN3_Pin  | EN1_Pin, GPIO_PIN_SET);
	  		  		display7SEG(1);
	  		  		break;
	  		  	  case 2:
	  		  		HAL_GPIO_WritePin(GPIOA,  EN1_Pin, GPIO_PIN_RESET);
	  		  		HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_SET);
	  		  		status = 3;
	  		  		display7SEG(2);
	  		  		break;
	  		  	  case 3:
	  		  		HAL_GPIO_WritePin(GPIOA,EN2_Pin , GPIO_PIN_RESET);
	  		  		HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN3_Pin, GPIO_PIN_SET);
	  		  		status = 4;
	  		  		display7SEG(3);
	  		  		break;
	  		  	  case 4:
	    		  	HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
	    		  	HAL_GPIO_WritePin(GPIOA, EN2_Pin | EN0_Pin | EN1_Pin, GPIO_PIN_SET);
	  		  		status = 1;
	  		  		display7SEG(0);
	  		  		break;
	  		  	  default:
	  		  		display7SEG(0);
	  		  		break;
	  		  }
		}
	}

}


