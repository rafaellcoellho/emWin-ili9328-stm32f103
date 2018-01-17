#ifndef __ILI9328_H
#define __ILI9328_H
#ifdef __cplusplus
extern "C" {
#endif

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
