/* Includes -----------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "helloWorld.h"

/* Macros -------------------------------------------------------------------*/
#define CALMDOWN_COMPILER

/* Private variables --------------------------------------------------------*/

/* Private function prototypes ----------------------------------------------*/
static void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
/* MCU Configuration---------------------------------------------------------*/

HAL_Init();
SystemClock_Config();
MX_GPIO_Init();
helloWorld();

/* Infinite loop-------------------------------------------------------------*/
while (1) {
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	HAL_Delay(1000);
}
}

static void SystemClock_Config(void)
{
RCC_OscInitTypeDef RCC_OscInitStruct;
RCC_ClkInitTypeDef RCC_ClkInitStruct;

/*Initializes the CPU, AHB and APB busses clocks*/
RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
RCC_OscInitStruct.HSIState = RCC_HSI_ON;
RCC_OscInitStruct.HSICalibrationValue = 16;
RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	_Error_Handler(__FILE__, __LINE__);

/*Initializes the CPU, AHB and APB busses clocks*/
RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	_Error_Handler(__FILE__, __LINE__);

/*Configure the Systick interrupt time*/
HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

/*Configure the Systick*/
HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

/*SysTick_IRQn interrupt configuration*/
HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

static void MX_GPIO_Init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

/* GPIO Ports Clock Enable */
__HAL_RCC_GPIOC_CLK_ENABLE();
__HAL_RCC_GPIOA_CLK_ENABLE();

/*Configure GPIO pin Output Level */
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

/*Configure GPIO pin : PC13 */
GPIO_InitStruct.Pin = GPIO_PIN_13;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/*
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void _Error_Handler(char *file, int line)
{
/* User can add his own implementation to report the HAL error return state */
while (1)
	CALMDOWN_COMPILER;
}

#ifdef USE_FULL_ASSERT

/*
 * @brief Reports the name of the source file and the source line number
 * where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
/*
 * User can add his own implementation to report the file name and line
 * number, ex: printf("Wrong parameters value: file %s on line
 * %d\r\n", file, line)
 */
}

#endif
