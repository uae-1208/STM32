#include "systick.h"
static __IO u32 TimingDelay;

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
}



/*��������������ж���ʹ����systick���ɵ���ʱ����ʱ����Ҫע��systick
������������ж����ȼ���
systick���ж����ȼ����� SysTick_Config-> NVIC_SetPriority->
__NVIC_PRIO_BITS�ĺ����á�*/
void Delay_ms(__IO u32 nTime)
{ 
	TimingDelay = nTime;	
	while(TimingDelay);
}


void SysTick_Handler(void)
{
	TimingDelay--;
}
