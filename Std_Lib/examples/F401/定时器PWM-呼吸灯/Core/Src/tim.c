#include "tim.h"

u32 Plow = 10;
u8 direct = 1;    //:1µÝÔö  0£ºµÝ¼õ
u32 Phigh = 990;  //10ms
u32 PeriodValue=0;

void TIM2_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 2;  // x*1ms
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) ((SystemCoreClock / 2) / 1000) - 1; // 1000Mhz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	/* TIM3 enable counter */
	TIM_Cmd(TIM2, ENABLE); 
}



void TIM3_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 10;  // 10ms
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) ((SystemCoreClock / 2) / 100000) - 1; // 0.1Mhz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE); 
}



void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	if(direct)
		Plow++;
	else
		Plow--;
	
	if(Plow == 999)
		direct = 0;
	if(Plow == 50)
		direct = 1;
	
	Phigh = 1000 - Plow;	
  }
  
} 




void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 1)
		PeriodValue = Plow;
	else             
		PeriodValue = Phigh;

	TIM_SetAutoreload(TIM3,PeriodValue);
    GPIO_ToggleBits(GPIOC, GPIO_Pin_13);
  }
  
}


