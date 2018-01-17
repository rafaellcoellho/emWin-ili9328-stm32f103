#ifndef __ILI9325_H
#define __ILI9325_H
#ifdef __cplusplus
extern "C" {
#endif

void ILI9325_Init(void);
void ILI9325_WriteRS0(uint8_t data);
void ILI9325_WriteRS1(uint8_t data);
uint8_t ILI9325_ReadRS1(void);

#ifdef __cplusplus
}
#endif
#endif
