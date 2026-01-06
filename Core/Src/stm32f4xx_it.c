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
static uint32_t fault_get_pclk1_hz(void) {
  // Derive PCLK1 from HCLK (SystemCoreClock) and APB1 prescaler.
  // This is good enough for fault reporting; it avoids calling HAL.
  uint32_t hclk = SystemCoreClock;
  uint32_t ppre1 = (RCC->CFGR >> 10U) & 0x7U;
  uint32_t div;
  if (ppre1 < 4U) {
    div = 1U;
  } else {
    static const uint8_t apb_div_table[8] = {1, 1, 1, 1, 2, 4, 8, 16};
    div = apb_div_table[ppre1];
  }
  return hclk / div;
}

static void fault_uart2_try_init(void) {
  static uint8_t attempted = 0;
  if (attempted) {
    return;
  }
  attempted = 1;

  // Enable clocks for GPIOA and USART2.
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  __DSB();
  __ISB();

  // Reset USART2 to a known state.
  RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
  __DSB();
  RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
  __DSB();

  // Configure PA2 (TX) and PA3 (RX) as AF7.
  // MODER: 10b = alternate function.
  GPIOA->MODER = (GPIOA->MODER & ~((3U << (2U * 2U)) | (3U << (3U * 2U)))) |
                 ((2U << (2U * 2U)) | (2U << (3U * 2U)));
  // AFRL bits for pins 2 and 3.
  GPIOA->AFR[0] = (GPIOA->AFR[0] & ~((0xFU << (2U * 4U)) | (0xFU << (3U * 4U)))) |
                  ((7U << (2U * 4U)) | (7U << (3U * 4U)));
  // High speed on TX/RX.
  GPIOA->OSPEEDR |= (3U << (2U * 2U)) | (3U << (3U * 2U));
  // No pull-ups.
  GPIOA->PUPDR &= ~((3U << (2U * 2U)) | (3U << (3U * 2U)));

  // Configure USART2: 115200 8N1, oversampling by 16.
  USART2->CR1 = 0;
  USART2->CR2 = 0;
  USART2->CR3 = 0;
  uint32_t pclk1 = fault_get_pclk1_hz();
  if (pclk1 == 0U) {
    pclk1 = 16000000U;
  }
  const uint32_t baud = 115200U;
  // For OVER8=0, BRR is approximately round(PCLK/baud).
  USART2->BRR = (pclk1 + (baud / 2U)) / baud;
  USART2->CR1 = USART_CR1_TE | USART_CR1_RE;
  USART2->CR1 |= USART_CR1_UE;
  __DSB();
  __ISB();
}

static void fault_uart2_puts(const char *s) {
  if (s == NULL) {
    return;
  }

  // If USART2 isn't enabled yet, try to bring it up so we can print fault info.
  if ((RCC->APB1ENR & RCC_APB1ENR_USART2EN) == 0U || (USART2->CR1 & USART_CR1_UE) == 0U) {
    fault_uart2_try_init();
  }
  if ((RCC->APB1ENR & RCC_APB1ENR_USART2EN) == 0U || (USART2->CR1 & USART_CR1_UE) == 0U) {
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
  if ((RCC->APB1ENR & RCC_APB1ENR_USART2EN) == 0U || (USART2->CR1 & USART_CR1_UE) == 0U) {
    fault_uart2_try_init();
  }
  if ((RCC->APB1ENR & RCC_APB1ENR_USART2EN) == 0U || (USART2->CR1 & USART_CR1_UE) == 0U) {
    return;
  }
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

  uint32_t cfsr = SCB->CFSR;
  uint32_t hfsr = SCB->HFSR;

  fault_uart2_puts("CFSR=");
  fault_uart2_hex32(cfsr);
  fault_uart2_puts(" HFSR=");
  fault_uart2_hex32(hfsr);

  fault_uart2_puts("\r\nSHCSR=");
  fault_uart2_hex32(SCB->SHCSR);
  fault_uart2_puts(" ICSR=");
  fault_uart2_hex32(SCB->ICSR);
  fault_uart2_puts("\r\nDFSR=");
  fault_uart2_hex32(SCB->DFSR);

  // MMFAR/BFAR are only valid if the corresponding VALID bit is set in CFSR.
  // If not valid, printing them is misleading (could appear as a constant).
  fault_uart2_puts("\r\nMMFAR=");
  if ((cfsr & (1U << 7U)) != 0U) {
    fault_uart2_hex32(SCB->MMFAR);
  } else {
    fault_uart2_puts("--------");
  }
  fault_uart2_puts(" BFAR=");
  if ((cfsr & (1U << 15U)) != 0U) {
    fault_uart2_hex32(SCB->BFAR);
  } else {
    fault_uart2_puts("--------");
  }
  fault_uart2_puts("\r\n");
}

// Forward declaration: used by fault handlers defined before the function body.
static void fault_blink_raw_forever(void);

typedef struct {
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t pc;
  uint32_t psr;
} fault_stack_frame_t;

static void fault_dump_stack_frame(const fault_stack_frame_t *f, uint32_t exc_return) {
  if (f == NULL) {
    return;
  }
  fault_uart2_puts("Stack@=");
  fault_uart2_hex32((uint32_t)(uintptr_t)f);
  fault_uart2_puts(" EXC_RETURN=");
  fault_uart2_hex32(exc_return);
  fault_uart2_puts("\r\nR0 =");
  fault_uart2_hex32(f->r0);
  fault_uart2_puts(" R1 =");
  fault_uart2_hex32(f->r1);
  fault_uart2_puts("\r\nR2 =");
  fault_uart2_hex32(f->r2);
  fault_uart2_puts(" R3 =");
  fault_uart2_hex32(f->r3);
  fault_uart2_puts("\r\nR12=");
  fault_uart2_hex32(f->r12);
  fault_uart2_puts(" LR =");
  fault_uart2_hex32(f->lr);
  fault_uart2_puts("\r\nPC =");
  fault_uart2_hex32(f->pc);
  fault_uart2_puts(" PSR=");
  fault_uart2_hex32(f->psr);
  fault_uart2_puts("\r\n");
}

static int fault_debugger_attached(void) {
  // When a debugger is connected, C_DEBUGEN is set.
  return (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) != 0U;
}

static int fault_try_handle_semihosting_bkpt(fault_stack_frame_t *f) {
  if (f == NULL) {
    return 0;
  }

  // Semihosting uses a BKPT with immediate 0xAB (Thumb halfword 0xBEAB).
  // Under a debugger it is handled; without a debugger it typically HardFaults.
  // If this is the case, skip the BKPT and continue.
  uint32_t pc = f->pc;
  if (pc < 0x08000002U || pc > 0x08100000U) {
    return 0;
  }

  volatile uint16_t *insn_pc = (volatile uint16_t *)(uintptr_t)pc;
  volatile uint16_t *insn_pc_m2 = (volatile uint16_t *)(uintptr_t)(pc - 2U);
  uint16_t i0 = *insn_pc;
  uint16_t i1 = *insn_pc_m2;
  if (i0 == 0xBEABU) {
    f->pc = pc + 2U;
    return 1;
  }
  if (i1 == 0xBEABU) {
    // PC is already the next instruction after BKPT.
    return 1;
  }
  return 0;
}

__attribute__((used)) int HardFault_C_Handler(uint32_t *stack_ptr, uint32_t exc_return) {
  fault_stack_frame_t *f = (fault_stack_frame_t *)stack_ptr;

  // Common root-cause for: "Debug(F5) OK, standalone HardFault".
  // When semihosting is enabled, the C library may execute BKPT 0xAB.
  // A debugger catches it; without a debugger it becomes a HardFault.
  if (!fault_debugger_attached()) {
    if (fault_try_handle_semihosting_bkpt(f)) {
      return 1; // handled, resume execution
    }
  }

  __disable_irq();
  fault_uart2_puts("HardFault\r\n");
  fault_dump_registers("HardFault");
  fault_dump_stack_frame((const fault_stack_frame_t *)stack_ptr, exc_return);
  // Always provide a visible indication even if UART isn't available.
  fault_blink_raw_forever();
  return 0;
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

// GPIO-only blink that doesn't rely on HAL init.
static void fault_blink_raw_forever(void) {
  // Enable GPIOA/GPIOB clocks.
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
  __DSB();
  __ISB();

  // Configure PA15 and PB4 as outputs.
  GPIOA->MODER = (GPIOA->MODER & ~(3U << (15U * 2U))) | (1U << (15U * 2U));
  GPIOB->MODER = (GPIOB->MODER & ~(3U << (4U * 2U))) | (1U << (4U * 2U));

  for (;;) {
    GPIOA->ODR ^= (1U << 15U);
    GPIOB->ODR ^= (1U << 4U);
    for (volatile uint32_t i = 0; i < 1200000U; i++) {
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
  // Dispatch to C handler with the correct stack pointer.
  // Bit[2] of EXC_RETURN indicates which stack pointer was in use.
  __asm volatile(
      "tst lr, #4\n"
      "ite eq\n"
      "mrseq r0, msp\n"
      "mrsne r0, psp\n"
  "mov r1, lr\n"
  "mov r2, lr\n"
  "bl HardFault_C_Handler\n"
  "mov lr, r2\n"
  "bx lr\n");
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
  fault_blink_raw_forever();

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
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
  fault_blink_raw_forever();

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
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
  fault_blink_raw_forever();

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
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

/**
  * @brief This function handles USB OTG FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
  // TinyUSB device controller driver (DCD) interrupt handler.
  // rhport=0 for the single FS port.
  extern void dcd_int_handler(uint8_t rhport);
  dcd_int_handler(0);
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
