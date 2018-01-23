#ifndef __ILI9328_H
#define __ILI9328_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define RESET_MODE_GLCD	GPIO_CRH_MODE12_0
#define RESET_GLCD	GPIO_ODR_ODR12
#define CS_MODE_GLCD	GPIO_CRH_MODE11_0
#define CS_GLCD		GPIO_ODR_ODR11
#define RS_MODE_GLCD	GPIO_CRH_MODE10_0
#define RS_GLCD		GPIO_ODR_ODR10
#define WR_MODE_GLCD	GPIO_CRH_MODE9_0
#define WR_GLCD		GPIO_ODR_ODR9
#define RD_MODE_GLCD	GPIO_CRH_MODE8_0
#define RD_GLCD		GPIO_ODR_ODR8

#define DISPLAY_CONTROL_1		0x07
#define POWER_CONTROL_1			0x10
#define POWER_CONTROL_2			0x11
#define POWER_CONTROL_3			0x12
#define POWER_CONTROL_4			0x13
#define POWER_CONTROL_7			0x29
#define FRAME_RATE_AND_COLOR_CONTROL	0x2B
#define DRIVER_OUTPUT_CONTROL_2		0x60
#define BASE_IMAGEDISPLAY_CONTROL	0x61
#define VERTICAL_SCHOLL_CONTROL		0x6A
#define PANEL_INTERFACE_CONTROL_1	0x90
#define PANEL_INTERFACE_CONTROL_2	0x92

void ILI9328_Init(void);
void ILI9328_WriteRS0(uint8_t data);
void ILI9328_WriteRS1(uint8_t data);
void ILI9328_MultiWriteRS1(uint8_t *p_data, int numItems);
uint8_t ILI9328_ReadRS1(void);
void ILI9328_MultiReadRS1(uint8_t *p_data, int numItems);

#ifdef __cplusplus
}
#endif

#endif
