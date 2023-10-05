#include "exit.h"

void delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}


void EXIT_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;           //通道2,key1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;          //通道3,key0
	NVIC_Init(&NVIC_InitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	  //通道13,key2
	NVIC_Init(&NVIC_InitStructure);
}

void exit_config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
	EXIT_NVIC_Configuration();
  
	
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOH,EXTI_PinSource2);        //ph2,key1

	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
  

	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOH,EXTI_PinSource3);        //ph3,key0

	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);
	   
	   

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);        //pc13,key2

	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure);
}
