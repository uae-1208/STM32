#include "systick.h"
static __IO u32 TimingDelay;

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
}



/*当在其他外设的中断中使用由systick生成的延时函数时，需要注意systick
和其他外设的中断优先级。
systick的中断优先级可在 SysTick_Config-> NVIC_SetPriority->
__NVIC_PRIO_BITS的宏设置。*/
void Delay_ms(__IO u32 nTime)
{ 
	TimingDelay = nTime;	
	while(TimingDelay);
}


void SysTick_Handler(void)
{
	TimingDelay--;
}
