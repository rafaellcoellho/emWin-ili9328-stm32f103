#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "ILI9328.h"

static inline void setIoOutput(void){
	GPIOA->CRL = GPIO_CRL_MODE0_0|GPIO_CRL_MODE1_0|GPIO_CRL_MODE2_0
		|GPIO_CRL_MODE3_0|GPIO_CRL_MODE4_0|GPIO_CRL_MODE5_0
		|GPIO_CRL_MODE6_0|GPIO_CRL_MODE7_0;
}

static inline void setIoInput(void){
	GPIOA->CRL = GPIO_CRL_CNF7_0|GPIO_CRL_CNF6_0|GPIO_CRL_CNF5_0|
		GPIO_CRL_CNF4_0|GPIO_CRL_CNF3_0|GPIO_CRL_CNF2_0|
		GPIO_CRL_CNF1_0|GPIO_CRL_CNF0_0;
}

static void initIo(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	setIoOutput();
	GPIOA->CRH = RD_MODE_GLCD|WR_MODE_GLCD|RS_MODE_GLCD
		|CS_MODE_GLCD|RESET_MODE_GLCD;
	GPIOA->ODR &= 0xE000;
}

static void reset(void)
{
	GPIOA->ODR |= RESET_GLCD;
	HAL_Delay(100);
	GPIOA->ODR &= ~RESET_GLCD;
	HAL_Delay(500);
	GPIOA->ODR |= RESET_GLCD;
	HAL_Delay(500);
}

static void writeIndexRegister(uint8_t adressRegister)
{
	ILI9328_WriteRS0(0x00);
	ILI9328_WriteRS0(adressRegister);
}

static void writeValueInRegister(uint16_t value)
{
	ILI9328_WriteRS1(value >> 8);
	ILI9328_WriteRS1(value);
}

static void writeRegister(uint8_t adressRegister, uint16_t value)
{
	writeIndexRegister(adressRegister);
	writeValueInRegister(value);
}

void ILI9328_Init(void)
{
	initIo();
	reset();
	writeRegister(0xE5, 0x78F0);
	writeRegister(0x01, 0x0000);
	writeRegister(0x02, 0x0400);
	writeRegister(0x03, 0x1090);
	writeRegister(0x04, 0x0000);
	writeRegister(0x08, 0x0202);
	writeRegister(0x09, 0x0000);
	writeRegister(0x0A, 0x0000);
	writeRegister(0x0C, 0x0000);
	writeRegister(0x0D, 0x0000);
	writeRegister(0x0F, 0x0000);
	writeRegister(0x10, 0x0000);
	writeRegister(0x11, 0x0007);
	writeRegister(0x12, 0x0000);
	writeRegister(0x13, 0x0000);
	writeRegister(0x07, 0x0001);
	HAL_Delay(200);
	writeRegister(0x10, 0x1690);
	writeRegister(0x11, 0x0227);
	HAL_Delay(50);
	writeRegister(0x12, 0x008C);
	HAL_Delay(50);
	writeRegister(0x13, 0x1500);
	writeRegister(0x29, 0x0004);
	writeRegister(0x2B, 0x000D);
	HAL_Delay(50);
	writeRegister(0x20, 0x0000);
	writeRegister(0x21, 0x0000);
	writeRegister(0x30, 0x0000);
	writeRegister(0x31, 0x0607);
	writeRegister(0x32, 0x0305);
	writeRegister(0x35, 0x0000);
	writeRegister(0x36, 0x1604);
	writeRegister(0x37, 0x0204);
	writeRegister(0x38, 0x0001);
	writeRegister(0x39, 0x0707);
	writeRegister(0x3C, 0x0000);
	writeRegister(0x3D, 0x000F);
	writeRegister(0x50, 0x0000);
	writeRegister(0x51, 0x00EF);
	writeRegister(0x52, 0x0000);
	writeRegister(0x53, 0x013F);
	writeRegister(0x60, 0xA700);
	writeRegister(0x61, 0x0001);
	writeRegister(0x6A, 0x0000);
	writeRegister(0x80, 0x0000);
	writeRegister(0x81, 0x0000);
	writeRegister(0x82, 0x0000);
	writeRegister(0x83, 0x0000);
	writeRegister(0x84, 0x0000);
	writeRegister(0x85, 0x0000);
	writeRegister(0x90, 0x0010);
	writeRegister(0x92, 0x0600);
	writeRegister(0x07, 0x0133);
}

void ILI9328_WriteRS0(uint8_t data)
{
	setIoOutput();
	GPIOA->ODR |= RD_GLCD;
	GPIOA->ODR |= WR_GLCD;
	GPIOA->ODR &= ~RS_GLCD;

	GPIOA->ODR &= 0xFF00;
	GPIOA->ODR |= ((uint16_t)data & 0x00FF);

	GPIOA->ODR &= ~WR_GLCD;
	HAL_Delay(1);
	GPIOA->ODR |= WR_GLCD;
	HAL_Delay(1);

	GPIOA->ODR |= RS_GLCD;
}

void ILI9328_WriteRS1(uint8_t data)
{
	setIoOutput();

	GPIOA->ODR |= RD_GLCD;
	GPIOA->ODR |= WR_GLCD;
	GPIOA->ODR |= RS_GLCD;

	GPIOA->ODR &= 0xFF00;
	GPIOA->ODR |= ((uint16_t)data & 0x00FF);

	GPIOA->ODR &= ~WR_GLCD;
	HAL_Delay(1);
	GPIOA->ODR |= WR_GLCD;
	HAL_Delay(1);
}

void ILI9328_MultiWriteRS1(uint8_t *p_data, int numItems)
{
	for (int i = 0; i < numItems; i++)
		ILI9328_WriteRS1(p_data[i]);
}

uint8_t ILI9328_ReadRS1(void)
{
	setIoInput();

	uint8_t data = 0x00;

	GPIOA->ODR &= ~RD_GLCD;
	GPIOA->ODR |= WR_GLCD;
	GPIOA->ODR |= RS_GLCD;

	HAL_Delay(1);
	data = (uint8_t)GPIOA->IDR & 0xFF;
	GPIOA->ODR |= RD_GLCD;

	return data;
}

void ILI9328_MultiReadRS1(uint8_t *p_data, int numItems)
{
	for (int i = 0; i < numItems; i++)
		p_data[i] = ILI9328_ReadRS1();
}
