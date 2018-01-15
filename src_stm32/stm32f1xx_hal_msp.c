/* Includes -----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

extern void _Error_Handler(char *, int);

/*
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
__HAL_RCC_AFIO_CLK_ENABLE();

HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

/* System interrupt init*/
/* MemoryManagement_IRQn interrupt configuration */
HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
/* BusFault_IRQn interrupt configuration */
HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
/* UsageFault_IRQn interrupt configuration */
HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
/* SVCall_IRQn interrupt configuration */
HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
/* DebugMonitor_IRQn interrupt configuration */
HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
/* PendSV_IRQn interrupt configuration */
HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
/* SysTick_IRQn interrupt configuration */
HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

/* DISABLE: JTAG-DP Disabled and SW-DP Disabled */
__HAL_AFIO_REMAP_SWJ_DISABLE();
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
GPIO_InitTypeDef GPIO_InitStruct;
if (huart->Instance == USART1) {
	/* Peripheral clock enable */
	__HAL_RCC_USART1_CLK_ENABLE();

	/*
	 * USART1 GPIO Configuration
	 * PA9     ------> USART1_TX
	 * PA10    ------> USART1_RX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
if (huart->Instance == USART1) {
	/* Peripheral clock disable */
	__HAL_RCC_USART1_CLK_DISABLE();

	/*
	 * USART1 GPIO Configuration
	 * PA9     ------> USART1_TX
	 * PA10    ------> USART1_RX
	 */
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);
}
}
