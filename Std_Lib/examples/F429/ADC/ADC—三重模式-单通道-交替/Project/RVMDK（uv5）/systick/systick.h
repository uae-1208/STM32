#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stm32f4xx.h"
void SysTick_Init(void);
void Delay_ms(__IO u32 nTime);

#endif
