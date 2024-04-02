/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "linkedList.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
const int MAX_LED = 4;
int index_led = 0;
int led_buffer [4] = {1 , 2 , 3 , 4};
int hour = 15 , minute = 8 , second = 50;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
void update7SEG (int index);
void display7SEG(int k);
void updateClockBuffer();
void controlColumns (int value);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
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
void updateClockBuffer(){
	  second ++;
	  	if ( second >= 60) {
	  		second = 0;
	  		minute++;
	  	}
	  	if (minute >= 60){
	  		minute =0;
	  		hour++;
	  	}
	  	if (hour >= 24){
	  		hour=0;
	  	}

	led_buffer[0] = hour / 10;
	led_buffer[1] =	hour %10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}
void display7SEG(int k){
	switch (k){
	case 0:
		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_B_Pin|LED_C_Pin|LED_D_Pin
		                          |LED_E_Pin|LED_F_Pin|LED_G_Pin, GPIO_PIN_RESET);

		  HAL_GPIO_WritePin(GPIOB, LED_G_Pin, GPIO_PIN_SET);
		break;
	case 1:
		  HAL_GPIO_WritePin(GPIOB, LED_B_Pin|LED_C_Pin, GPIO_PIN_RESET);

		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_D_Pin
		                          |LED_E_Pin|LED_F_Pin|LED_G_Pin, GPIO_PIN_SET);
		break;
	case 2:
		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_B_Pin | LED_D_Pin
		                          |LED_E_Pin|LED_G_Pin, GPIO_PIN_RESET);

		  HAL_GPIO_WritePin(GPIOB,LED_C_Pin|LED_F_Pin, GPIO_PIN_SET);
		break;
	case 3:
		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_B_Pin|LED_C_Pin|LED_D_Pin
		                          |LED_G_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, LED_E_Pin|LED_F_Pin, GPIO_PIN_SET);
		break;
	case 4:
		  HAL_GPIO_WritePin(GPIOB, LED_B_Pin|LED_C_Pin |LED_F_Pin|LED_G_Pin, GPIO_PIN_RESET);

		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_D_Pin|LED_E_Pin, GPIO_PIN_SET);
		break;
	case 5:
		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_C_Pin|LED_D_Pin
		                          |LED_F_Pin|LED_G_Pin, GPIO_PIN_RESET);

		  HAL_GPIO_WritePin(GPIOB,LED_B_Pin|LED_E_Pin, GPIO_PIN_SET);
		break;
	case 6:
		  HAL_GPIO_WritePin(GPIOB,LED_B_Pin, GPIO_PIN_SET);

		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_C_Pin|LED_D_Pin
		                          |LED_E_Pin|LED_F_Pin|LED_G_Pin, GPIO_PIN_RESET);

		break;
	case 7:
		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_B_Pin|LED_C_Pin , GPIO_PIN_RESET);

		  HAL_GPIO_WritePin(GPIOB, LED_D_Pin |LED_E_Pin|LED_F_Pin|LED_G_Pin, GPIO_PIN_SET);
		break;
	case 8:
		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_B_Pin|LED_C_Pin|LED_D_Pin
		                          |LED_E_Pin|LED_F_Pin|LED_G_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_B_Pin|LED_C_Pin|LED_D_Pin
		                          |LED_E_Pin|LED_F_Pin|LED_G_Pin, GPIO_PIN_RESET);

		  HAL_GPIO_WritePin(GPIOB, LED_E_Pin, GPIO_PIN_SET);
		break;
	default:
		  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_B_Pin|LED_C_Pin|LED_D_Pin
		                          |LED_E_Pin|LED_F_Pin|LED_G_Pin, GPIO_PIN_RESET);
	}
}
void controlColumns (int value){
	switch (value){
		case 0:
			HAL_GPIO_WritePin(GPIOA, ENM0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
			  	                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, ENM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
			  	                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, ENM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
			  	                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, ENM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM4_Pin|ENM5_Pin
			  	                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOA, ENM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM5_Pin
			  	                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOA, ENM5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin
			  	                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOA, ENM6_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
			  	                          |ENM7_Pin, GPIO_PIN_RESET);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOA, ENM7_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
			  	                          |ENM6_Pin, GPIO_PIN_RESET);
			break;
		default:
			HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
			  	                          |ENM6_Pin |ENM7_Pin, GPIO_PIN_RESET);
			break;
	}
}
void controlRows (int value){
	switch (value){
		case 0:
	  		  HAL_GPIO_WritePin(GPIOB, ROW0_Pin , SET);
			break;
		case 1:
	  		  HAL_GPIO_WritePin(GPIOB, ROW1_Pin , SET);

			break;
		case 2:
	  		  HAL_GPIO_WritePin(GPIOB, ROW2_Pin , SET);

			break;
		case 3:
	  		  HAL_GPIO_WritePin(GPIOB, ROW3_Pin , SET);

			break;
		case 4:
	  		  HAL_GPIO_WritePin(GPIOB, ROW4_Pin , SET);

			break;
		case 5:
	  		  HAL_GPIO_WritePin(GPIOB, ROW5_Pin , SET);

			break;
		case 6:
	  		  HAL_GPIO_WritePin(GPIOB, ROW6_Pin , SET);

			break;
		case 7:
	  		  HAL_GPIO_WritePin(GPIOB, ROW7_Pin , SET);
			break;
		default:
	  		  HAL_GPIO_WritePin(GPIOB, ROW0_Pin |ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin |
	  				  ROW5_Pin| ROW6_Pin |ROW7_Pin , RESET);
			break;
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  int i=7;
  int character_A[8][8] = {{0,0,0,1,1,0,0,0},{0,0,1,1,1,1,0,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},
    		  {0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0}};
//    int character_A[8][8] = {{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,0},
//    		{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,0},{0,0,1,1,1,1,0,0},{0,0,0,1,1,0,0,0}};


  Node* head[8] = { NULL };

  for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
          insertAtEnd(&head[i], character_A[i][j]);
      }
      connectEndToFirst(&head[i]);
  }

  Node* temp = head[i];
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setTimer0(100);
  setTimer1(1000);
  setTimer2(500);
  setTimer3(10);

  // ngat timer goi 10ms moi lan => 10x100 = 1000ms = 1s
  while (1)
      {
  	  /* USER CODE END WHILE */
	  	  // update hour minute and second
		  if (timer0_flag == 1 ){
				updateClockBuffer();
				setTimer0(100);
		  }
		  // LED PA5 and DOT
    	  if (timer1_flag == 1){

    		  HAL_GPIO_TogglePin(GPIOA,LED_RED_Pin);
    		  HAL_GPIO_TogglePin(GPIOA,DOT_Pin);
    		  setTimer1(1000);
    	  }
    	  // update buffer to 7seg
    	  if (timer2_flag == 1){
    		  update7SEG(index_led++);
    		  setTimer2(500);
    	  }
    	  // led matrix
    	  if (timer3_flag == 1){
    		  	 // turn of all led row
				controlRows(-1);
				// turn on i column
    	 		controlColumns(i);


    	 		 for (int j = 0; j < 8; j++) {
    	 	    	if (temp->data == 1){
    	 	    			controlRows(j);
    	 	    	}
    	 	    	temp = temp->next;
    	 		  }

    	 		 // update led matrix
    	 		 head[i] = head[i]->next;

    	 	     i--;
    	 	     if (i == -1) {
    	 	    	 i = 7;
    	 	     }
    	 	     temp = head[i];

    	  	setTimer3(10);
    	  }


// 	    HAL_Delay(1);
      }
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_B_Pin|LED_C_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|LED_D_Pin|LED_E_Pin|LED_F_Pin
                          |LED_G_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_A_Pin LED_B_Pin LED_C_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin LED_D_Pin LED_E_Pin LED_F_Pin
                           LED_G_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = LED_A_Pin|LED_B_Pin|LED_C_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|LED_D_Pin|LED_E_Pin|LED_F_Pin
                          |LED_G_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timerRun();

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
