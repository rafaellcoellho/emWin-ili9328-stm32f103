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
	HAL_Delay(50);
	GPIOA->ODR &= ~RESET_GLCD;
	HAL_Delay(50);
	GPIOA->ODR |= RESET_GLCD;
	HAL_Delay(10);
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

static void configPowerControl(void)
{
	writeRegister(POWER_CONTROL_1, 0x0000);
	writeRegister(POWER_CONTROL_2, 0x0007);
	writeRegister(POWER_CONTROL_3, 0x0000);
	writeRegister(POWER_CONTROL_4, 0x0000);
	writeRegister(DISPLAY_CONTROL_1, 0x0001);
	HAL_Delay(200);
	writeRegister(POWER_CONTROL_1, 0x1690);
	writeRegister(POWER_CONTROL_2, 0x0227);
	HAL_Delay(50);
	writeRegister(POWER_CONTROL_3, 0x008C);
	HAL_Delay(50);
	writeRegister(POWER_CONTROL_4, 0x1500);
	writeRegister(POWER_CONTROL_7, 0x0004);
}

static void configFrameRateAndColorControl(void)
{
	writeRegister(FRAME_RATE_AND_COLOR_CONTROL, 0x000D);
	HAL_Delay(50);
}

static void configGateScanControl(void)
{
	writeRegister(DRIVER_OUTPUT_CONTROL_2, 0xA700);
	writeRegister(BASE_IMAGEDISPLAY_CONTROL, 0x0001);
	writeRegister(VERTICAL_SCHOLL_CONTROL, 0x0000);
}

static void configPanelInterfaceControl(void)
{
	writeRegister(PANEL_INTERFACE_CONTROL_1, 0x0010);
	writeRegister(PANEL_INTERFACE_CONTROL_2, 0x0600);
}

void ILI9328_Init(void)
{
	initIo();
	reset();
	configPowerControl();
	configFrameRateAndColorControl();
	configGateScanControl();
	configPanelInterfaceControl();
	writeRegister(DISPLAY_CONTROL_1, 0x0133);
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
	GPIOA->ODR |= WR_GLCD;

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
	GPIOA->ODR |= WR_GLCD;
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
