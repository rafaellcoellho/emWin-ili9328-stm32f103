#ifndef __ILI9328_H
#define __ILI9328_H
#ifdef __cplusplus
extern "C" {
#endif

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
