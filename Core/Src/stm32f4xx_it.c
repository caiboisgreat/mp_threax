/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

// Minimal fault output over USART2 (polling, no interrupts).
// Safe to use inside fault handlers as long as clocks/pins are configured.
static void fault_uart2_puts(const char *s) {
  if (s == NULL) {
    return;
  }

  while (*s) {
    while ((USART2->SR & USART_SR_TXE) == 0U) {
      // spin
    }
    USART2->DR = (uint16_t)(uint8_t)(*s++);
  }

  while ((USART2->SR & USART_SR_TC) == 0U) {
    // spin
  }
}

// Send a 32-bit value as 8 hex digits.
static void fault_uart2_hex32(uint32_t v) {
  for (int i = 7; i >= 0; i--) {
    uint8_t nibble = (v >> (i * 4)) & 0xFu;
    char c = (nibble < 10) ? ('0' + nibble) : ('A' + (nibble - 10));
    while ((USART2->SR & USART_SR_TXE) == 0U) {
      // spin
    }
    USART2->DR = (uint16_t)c;
  }
  while ((USART2->SR & USART_SR_TC) == 0U) {
    // spin
  }
}

static void fault_dump_registers(const char *name) {
  fault_uart2_puts("\r\n==== ");
  fault_uart2_puts(name);
  fault_uart2_puts(" ====\r\n");

  fault_uart2_puts("CFSR=");
  fault_uart2_hex32(SCB->CFSR);
  fault_uart2_puts(" HFSR=");
  fault_uart2_hex32(SCB->HFSR);
  fault_uart2_puts("\r\nMMFAR=");
  fault_uart2_hex32(SCB->MMFAR);
  fault_uart2_puts(" BFAR=");
  fault_uart2_hex32(SCB->BFAR);
  fault_uart2_puts("\r\n");
}

static void fault_blink_forever(GPIO_TypeDef *port, uint16_t pin) {
  // interrupts may already be disabled; use a crude busy-wait delay.
  for (;;) {
    HAL_GPIO_TogglePin(port, pin);
    for (volatile uint32_t i = 0; i < 800000U; i++) {
      __NOP();
    }
  }
}
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */
  __disable_irq();
  fault_uart2_puts("HardFault\r\n");
  fault_dump_registers("HardFault");
  /* USER CODE END HardFault_IRQn 0 */
  fault_blink_forever(red_led_GPIO_Port, red_led_Pin);
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  __disable_irq();
  fault_uart2_puts("MemManage\r\n");
  fault_dump_registers("MemManage");

  /* USER CODE END MemoryManagement_IRQn 0 */
  fault_blink_forever(yello_led_GPIO_Port, yello_led_Pin);
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  __disable_irq();
  fault_uart2_puts("BusFault\r\n");
  fault_dump_registers("BusFault");

  /* USER CODE END BusFault_IRQn 0 */
  fault_blink_forever(blue_led_GPIO_Port, blue_led_Pin);
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  __disable_irq();
  fault_uart2_puts("UsageFault\r\n");
  fault_dump_registers("UsageFault");

  /* USER CODE END UsageFault_IRQn 0 */
  fault_blink_forever(green_led_GPIO_Port, green_led_Pin);
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
