#include "systick.h"

static __IO u32 TimingDelay;
static __IO uint32_t g_ul_ms_ticks=0;
 
/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
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

/**
  * @brief   us延时程序,1ms为一个单位
  * @param   
  *		@arg nTime: Delay_ms( 1 ) 则实现的延时为 1 ms
  * @retval  无
  */
void Delay_ms(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	while(TimingDelay != 0);
}

/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

/**
  * @brief  获取当前毫秒值
  * @param  存储最新毫秒值的变量
  * @retval 无
  */
int get_tick_count(unsigned long *count)
{
   count[0] = g_ul_ms_ticks;
	return 0;
}

/**
  * @brief  毫秒累加器，在中断里每毫秒加1
  * @param  无
  * @retval 无
  */
void TimeStamp_Increment(void)
{
	g_ul_ms_ticks++;
}
/*********************************************END OF FILE**********************/
