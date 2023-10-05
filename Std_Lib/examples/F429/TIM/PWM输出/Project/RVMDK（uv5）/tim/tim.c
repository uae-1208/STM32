#include "tim.h"

static void TIM_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//Ê¹ÄÜPORTBÊ±ÖÓ	
		
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOB1¸´ÓÃÎª¶¨Ê±Æ÷3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //GPIOB1¸´ÓÃÎª¶¨Ê±Æ÷3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;           //GPIOF1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //³õÊ¼»¯PB1	 
}

static void TIM3_Mode_Init(void)
{		 					 
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3Ê±ÖÓÊ¹ÄÜ    
	 
	TIM_TimeBaseStructure.TIM_Prescaler=180-1;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseStructure.TIM_Period=500-1;   //×Ô¶¯ÖØ×°ÔØÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷3
	
	//³õÊ¼»¯TIM3 Channel4 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_Pulse=10;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ÐÔ:¸µÍµçÆ½ÓÐÐ§
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	

	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR4ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEÊ¹ÄÜ 
	
	TIM_Cmd(TIM3, ENABLE);  //Ê¹ÄÜTIM3									  
}  

void TIM3_Init(void)	
{
	TIM_GPIO_Init();
	TIM3_Mode_Init();
}



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

static void TIM7_Mode_Init(void)
{		 					 
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  	//TIM7Ê±ÖÓÊ¹ÄÜ    
	 
	TIM_TimeBaseStructure.TIM_Prescaler=9000-1;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseStructure.TIM_Period=30-1;   //×Ô¶¯ÖØ×°ÔØÖµ,3msÖÐ¶ÏÒ»´Î
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷7

	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM7, ENABLE);  //Ê¹ÄÜTIM3									  
}

void TIM7_Init(void)	
{
	TIMx_NVIC_Configuration();
	TIM7_Mode_Init();
}


void TIM7_IRQHandler(void)
{
	static u16 arr = 0;
	static u8 dir = 1;         //·½Ïò
	if ( TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET ) 
	{	
		if(dir)
			arr++;
		else 
			arr--;
		if(arr == 500)            //×î¸ßÁÁ¶È
			dir = 0;
		if(arr == 40)             //×îµÍÁÁ¶È
			dir = 1;
        TIM_SetCompare4(TIM3,arr);
        TIM_SetCompare3(TIM3,arr);
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  		 
	}		 	
	//±ä»¯ËÙ¶ÈÓÉÖÐ¶ÏÆµÂÊÈ·¶¨
}
