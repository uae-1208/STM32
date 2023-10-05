#include "tim.h"
#include "gpio.h"

static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/* TIM_Prescaler         ����
 * TIM_CounterMode		 TIMx,x[6,7]û�У��������У�������ʱ����
 * TIM_Period            ����
 * TIM_ClockDivision     TIMx,x[6,7]û�У���������(������ʱ��)
 * TIM_RepetitionCounter TIMx,x[1,8]����(�߼���ʱ��)*/


static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 
	TIM_TimeBaseStructure.TIM_Period = 500-1;       
	
	//��ʱ��ʱ��ԴTIMxCLK = 2 * PCLK1  
	//				PCLK1 = HCLK / 4 
	//				=> TIMxCLK=HCLK/2=SystemCoreClock/2=90MHz
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=10000Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 9000-1;	

	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	
	// ������ʱ�������ж�
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	// ʹ�ܶ�ʱ��
	TIM_Cmd(TIM7, ENABLE);	
}

void TIMx_Configuration(void)
{
	TIMx_NVIC_Configuration();	
	TIM_Mode_Config();
}


void  TIM7_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET ) 
	{	
		GPIO_ToggleBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  		 
	}		 	
}

