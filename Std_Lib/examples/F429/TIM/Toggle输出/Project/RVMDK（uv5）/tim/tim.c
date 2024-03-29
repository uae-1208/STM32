#include "tim.h"
#include "usart.h"

static void TIM5_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
		
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //GPIOA0复用为定时器5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA0	 
}

static void TIM5_IC_Mode_Init(void)
{		 					 
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	 
	TIM_TimeBaseStructure.TIM_Prescaler=90-1;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=65535;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//初始化定时器5
	
	//初始化TIM5 Channel1 	 
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	
	TIM_PWMIConfig(TIM5, &TIM_ICInitStructure);	

	TIM_SelectInputTrigger(TIM5,TIM_TS_TI1FP1);

	TIM_SelectSlaveMode(TIM5, TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM5,TIM_MasterSlaveMode_Enable);

	
	TIM_ITConfig(TIM5,TIM_IT_CC1,ENABLE);
	
	TIM_Cmd(TIM5, ENABLE);  //使能TIM5								  
}  


static void TIM5_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; 	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void TIM5_Init(void)	
{
	TIM5_GPIO_Init();
	TIM5_NVIC_Configuration();
	TIM5_IC_Mode_Init();
}





static void TIM2_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
		
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2); //GPIOA5复用为定时器2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           //GPIOA5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA5	 
}



static void TIM2_OC_Mode_Init(void)
{		 					 
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM2时钟使能    
	 
	TIM_TimeBaseStructure.TIM_Prescaler=90-1;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=65535;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//初始化定时器2
	
	//初始化TIM2 Channel1 翻转模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse=1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:傅偷缙接行�
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);
	
	TIM_ITConfig(TIM2,TIM_IT_CC1,ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);  //使能TIM2										  
}


static void TIM2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void TIM2_Init(void)	
{
	TIM2_GPIO_Init();
	TIM2_NVIC_Configuration();
	TIM2_OC_Mode_Init();
}





void TIM5_IRQHandler(void)
{
	static u16 val1,val2;
	if (TIM_GetITStatus(TIM5,TIM_IT_CC1) != RESET ) 
	{	
		val1 = TIM_GetCapture1(TIM5);
		val2 = TIM_GetCapture2(TIM5);
		printf("%.3fms   %.2f%%  \r\n",(float)(val2+1)/1000,(float)(val2+1)/(val1+1)*100);
		TIM_ClearITPendingBit(TIM5,TIM_IT_CC1);  		 
	}		 	
}

enum Polarity {low,high};
static enum Polarity check = low;   //1表示匹配前为高电平，0为低电平

/*注意让捕获通道的ARR要大些；
最开始OCxREF的极性未知，但好像这样设置刚刚好*/
void TIM2_IRQHandler(void)
{
	u16 capture;
	u16 High = 400,Low = 600;	
	if (TIM_GetITStatus(TIM2,TIM_IT_CC1) != RESET ) 
	{	
		capture = TIM_GetCapture1(TIM2);
		if(check == low)
		{
			TIM_SetCompare1(TIM2,capture+High);
			check=high;
		}
		else 
		{
			TIM_SetCompare1(TIM2,capture+Low);
			check=low;
		}       
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);  		 
	}		 	
}
