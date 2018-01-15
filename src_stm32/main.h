#ifndef __MAIN_H
#define __MAIN_H

/* Includes -----------------------------------------------------------------*/

/* Private define -----------------------------------------------------------*/

/* ######################### Assert Selection ############################## */

/*
 * @brief Uncomment the line below to expanse the "assert_param" macro in the
 *        HAL drivers code
 */
/* #define USE_FULL_ASSERT    1U */

#ifdef __cplusplus
extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif
