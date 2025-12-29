/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "py_init.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define THREAD_LED_STACK_SIZE         1024
#define MICROPY_BYTE_POOL_SIZE        1024
#define MICROPY_STACK_SIZE            (32*1024)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
TX_THREAD     thread_led;
TX_THREAD     thread_mp;
TX_BYTE_POOL  byte_pool_mp;
__attribute__((aligned(8))) ULONG thread_led_stack[THREAD_LED_STACK_SIZE / sizeof(ULONG)];
UCHAR         memory_area[MICROPY_BYTE_POOL_SIZE];
__attribute__((aligned(8))) static ULONG micropy_stack[MICROPY_STACK_SIZE / sizeof(ULONG)];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void    thread_led_entry(ULONG thread_input);
void    thread_micropy_entry(ULONG thread_input);
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_ThreadX_Init */
  UNUSED(byte_pool);
  ret = tx_thread_create(&thread_led, "thread led", thread_led_entry, 0,  
            thread_led_stack, (ULONG)sizeof(thread_led_stack), 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
  if(ret != TX_SUCCESS){
    char TxBuf[] = "error:threadx create thread_led failed";
    HAL_UART_Transmit(&huart2,(uint8_t*)TxBuf,strlen(TxBuf),100);
  }
  
  ret = tx_byte_pool_create(&byte_pool_mp, "byte pool 0", memory_area, MICROPY_BYTE_POOL_SIZE);
  ret = tx_thread_create(&thread_mp, "thread mp", thread_micropy_entry, 0,  
      micropy_stack, (ULONG)sizeof(micropy_stack), 
      2, 2, TX_NO_TIME_SLICE, TX_AUTO_START);
   if(ret != TX_SUCCESS){
	   char TxBuf[] = "error:threadx create thread microPython failed";
	   HAL_UART_Transmit(&huart2,(uint8_t*)TxBuf,strlen(TxBuf),100);
   }
  /* USER CODE END App_ThreadX_Init */

    char msg[]="thread created....\r\n";
    HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),200);
  
  return ret;
}

/**
  * @brief  MX_ThreadX_Init
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */
void thread_led_entry(ULONG thread_input)
{
  UNUSED(thread_input);
	while(1)
	{	
		HAL_GPIO_WritePin(red_led_GPIO_Port,red_led_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(green_led_GPIO_Port,green_led_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(yello_led_GPIO_Port,yello_led_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(blue_led_GPIO_Port,blue_led_Pin,GPIO_PIN_RESET);
        
		tx_thread_sleep(500);
        
		HAL_GPIO_WritePin(red_led_GPIO_Port,red_led_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(green_led_GPIO_Port,green_led_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(yello_led_GPIO_Port,yello_led_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(blue_led_GPIO_Port,blue_led_Pin,GPIO_PIN_RESET);
        
		tx_thread_sleep(500);
        
		HAL_GPIO_WritePin(red_led_GPIO_Port,red_led_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(green_led_GPIO_Port,green_led_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(yello_led_GPIO_Port,yello_led_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(blue_led_GPIO_Port,blue_led_Pin,GPIO_PIN_RESET);	
        
    tx_thread_sleep(500);
        
		HAL_GPIO_WritePin(red_led_GPIO_Port,red_led_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(green_led_GPIO_Port,green_led_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(yello_led_GPIO_Port,yello_led_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(blue_led_GPIO_Port,blue_led_Pin,GPIO_PIN_SET); 
    tx_thread_sleep(500);   
	}
}

void thread_micropy_entry(ULONG thread_input)
{
    UNUSED(thread_input);
    micro_python_init();
      for (;;) {
        tx_thread_sleep(1000);
    }
}
/* USER CODE END 1 */
