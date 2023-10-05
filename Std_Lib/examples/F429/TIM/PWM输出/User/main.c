#include "stm32f4xx.h"
#include "led.h"
#include "tim.h"

void Delay(__IO uint32_t nCount)	
{
	for(; nCount != 0; nCount--);
}

int main(void)
{
	LED_Init();
	TIM3_Init();
	TIM7_Init();	
	while(1)
	{
	}
}

