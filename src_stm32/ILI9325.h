#ifndef __ILI9325_H
#define __ILI9325_H
#ifdef __cplusplus
extern "C" {
#endif

void ILI9325_Init(void);
void ILI9325_WriteA0(uint8_t data);
void ILI9325_WriteA1(uint8_t data);

#ifdef __cplusplus
}
#endif
#endif
