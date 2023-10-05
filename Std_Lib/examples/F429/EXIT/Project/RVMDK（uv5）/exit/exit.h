#ifndef __EXIT_H__
#define __EXIT_H__

#include "stm32f4xx.h"
void exit_config(void);
void delay(__IO uint32_t nCount);
void EXIT_NVIC_Configuration(void);

#endif
