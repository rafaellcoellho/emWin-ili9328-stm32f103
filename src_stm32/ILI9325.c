#include "stm32f1xx_hal.h"
#include "ILI9325.h"

/*
 * Anotação:
 * DB0...DB7 -> PIN0...PIN7
 * RESET -> PIN12
 * CS -> PIN11
 * RS -> PIN10
 * WR -> PIN9
 * RD -> PIN8
 */

static GPIO_InitTypeDef GPIO_InitStructOutput;
static GPIO_InitTypeDef GPIO_InitStructInput;

static void ILI9325_InitIO(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

__HAL_RCC_GPIOA_CLK_ENABLE();

HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
	|GPIO_PIN_12, GPIO_PIN_RESET);

GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
	|GPIO_PIN_12;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
	|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

GPIO_InitStructOutput.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
	|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
GPIO_InitStructOutput.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStructOutput.Speed = GPIO_SPEED_FREQ_LOW;

GPIO_InitStructInput.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
	|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
GPIO_InitStructOutput.Mode = GPIO_MODE_INPUT;
GPIO_InitStructOutput.Speed = GPIO_SPEED_FREQ_LOW;

HAL_GPIO_Init(GPIOA, &GPIO_InitStructOutput);
}

static void ILI9325_Reset(void)
{
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); //RESET
HAL_Delay(3);
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET); //RESET
HAL_Delay(70);
}

void ILI9325_Init(void)
{
ILI9325_InitIO();
ILI9325_Reset();
}

void ILI9325_WriteA0(uint8_t data)
{
HAL_GPIO_Init(GPIOA, &GPIO_InitStructOutput);

HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET); // RD
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // WR
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); // RS - A0

HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, (data & 0x01));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, ((data & 0x02) >> 1));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, ((data & 0x04) >> 2));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, ((data & 0x08) >> 3));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ((data & 0x10) >> 4));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ((data & 0x20) >> 5));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ((data & 0x40) >> 6));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, ((data & 0x80) >> 7));

HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); // WR
HAL_Delay(1);
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // WR
HAL_Delay(1);
}

void ILI9325_WriteA1(uint8_t data)
{
HAL_GPIO_Init(GPIOA, &GPIO_InitStructOutput);

HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET); // RD
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // WR
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); // RS - A0

HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, (data & 0x01));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, ((data & 0x02) >> 1));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, ((data & 0x04) >> 2));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, ((data & 0x08) >> 3));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ((data & 0x10) >> 4));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ((data & 0x20) >> 5));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ((data & 0x40) >> 6));
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, ((data & 0x80) >> 7));

HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); // WR
HAL_Delay(1);
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // WR
HAL_Delay(1);
}

uint8_t ILI9325_ReadA1(void)
{
uint8_t data;
HAL_GPIO_Init(GPIOA, &GPIO_InitStructInput);

HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); // RD
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // WR
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); // RS - A0

HAL_Delay(1);
data = (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) << 7)|
	(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) << 6)|
	(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) << 5)|
	(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) << 4)|
	(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) << 3)|
	(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) << 2)|
	(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) << 1)|
	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

return data;
}
