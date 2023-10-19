/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Blink */
osThreadId_t BlinkHandle;
const osThreadAttr_t Blink_attributes = {
  .name = "Blink",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for button */
osThreadId_t buttonHandle;
const osThreadAttr_t button_attributes = {
  .name = "button",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for Potenciometer */
osThreadId_t PotenciometerHandle;
const osThreadAttr_t Potenciometer_attributes = {
  .name = "Potenciometer",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartBlink(void *argument);
void StartButton(void *argument);
void StartPot(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Blink */
  BlinkHandle = osThreadNew(StartBlink, NULL, &Blink_attributes);

  /* creation of button */
  buttonHandle = osThreadNew(StartButton, NULL, &button_attributes);

  /* creation of Potenciometer */
  PotenciometerHandle = osThreadNew(StartPot, NULL, &Potenciometer_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  char val;
  char val2;
  /* Infinite loop */
  for(;;)
  {
		HAL_UART_Transmit(&huart1,&val,1,100);
		HAL_UART_Transmit(&huart1,&val2,1,100);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartBlink */
/**
* @brief Function implementing the Blink thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBlink */
void StartBlink(void *argument)
{
  /* USER CODE BEGIN StartBlink */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, 0);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, 1);
    HAL_Delay(1000);
  }
  /* USER CODE END StartBlink */
}

/* USER CODE BEGIN Header_StartButton */
/**
* @brief Function implementing the button thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartButton */
void StartButton(void *argument)
{
  /* USER CODE BEGIN StartButton */
  int buttonState = 0;           // Estado actual del botón (0 = no presionado, 1 = presionado)
  int buttonState2 = 0;
  /* Infinite loop */
  for(;;)
  {

	int buttonStateCurrent = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
	int buttonStateCurrent2 = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
	  // Si el botón ha sido presionado y no estaba presionado previamente
	if ((buttonStateCurrent == 1 && buttonState == 0) || (buttonStateCurrent2 == 1 && buttonState2 == 0)) {
	    // Cambiar el estado del botón a 1
	    buttonState = 1;
	    buttonState2 = 1;
	    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, 1);
	}
	    // Si el botón está siendo liberado y estaba presionado previamente
	else if ((buttonStateCurrent == 0 && buttonState == 1) || ((buttonStateCurrent2 == 0 && buttonState2 == 1))) {
	    // Cambiar el estado del botón a 0
	    buttonState = 0;
	    buttonState2 = 0;
	    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8, 0);
	}
  }
  /* USER CODE END StartButton */
}

/* USER CODE BEGIN Header_StartPot */
/**
* @brief Function implementing the Potenciometer thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPot */
void StartPot(void *argument)
{
  /* USER CODE BEGIN StartPot */
  int readValue = 0;
  /* Infinite loop */
  for(;;)
  {
		HAL_ADC_PollForConversion(&hadc1,1000);
		readValue = HAL_ADC_GetValue(&hadc1);
  }
  /* USER CODE END StartPot */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

