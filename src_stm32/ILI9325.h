#ifndef __ILI9325_H
#define __ILI9325_H
#ifdef __cplusplus
extern "C" {
#endif

void ILI9325_Init(void);
void ILI9325_WriteRS0(uint8_t data);
void ILI9325_WriteRS1(uint8_t data);
void ILI9325_MultiWriteRS1(uint8_t *p_data, int numItems);
uint8_t ILI9325_ReadRS1(void);
void ILI9325_MultiReadRS1(uint8_t *p_data, int numItems);

#ifdef __cplusplus
}
#endif
#endif
