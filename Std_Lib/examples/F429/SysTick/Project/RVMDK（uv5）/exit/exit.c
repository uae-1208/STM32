#include "exit.h"
#include "systick.h"

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




void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET) 
	{	
		Delay_ms(30);
		GPIO_ToggleBits(GPIOB,GPIO_Pin_0);
		EXTI_ClearITPendingBit(EXTI_Line3);     
	}  
} 


void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET) 
	{	
		Delay_ms(30);
		GPIO_ToggleBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);
		EXTI_ClearITPendingBit(EXTI_Line2);     
	}  
} 


void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line13) != RESET) 
	{	
		Delay_ms(30);
		GPIO_ToggleBits(GPIOB,GPIO_Pin_1);
		EXTI_ClearITPendingBit(EXTI_Line13);     
	}  
}

