#include "tim.h"
#include "usart.h"


static void TIM3_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTA��PORTBʱ��	
		
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOA6����Ϊ��ʱ��3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA5	 
	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOA7
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA7	 
		
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //GPIOB0����Ϊ��ʱ��3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOB0
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PB0	 

		
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOB1����Ϊ��ʱ��3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOB1
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PB1	 

}



static void TIM3_OC_Mode_Init(void)
{		 					 
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ��    
	 
	TIM_TimeBaseStructure.TIM_Prescaler=42-1;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=100-1;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	
	//��ʼ��TIM3 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	

	//��ʼ��TIM3 Channelx PWMģʽ	 
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	
		
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	

	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3										  
}

void TIM3_Init(void)	
{
	TIM3_GPIO_Init();
	TIM3_OC_Mode_Init();
}


static void TIM4_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTAʱ��	
		
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); //GPIOA2����Ϊ��ʱ��9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PA2	 
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); //GPIOA3����Ϊ��ʱ��9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOA3
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PA3 		
}

static void TIM4_IC_Mode_Init(void)
{		 					 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM9ʱ��ʹ��    
	
	TIM_DeInit(TIM4);
	 
	TIM_TimeBaseStructure.TIM_Prescaler = 0;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = 65535;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��9
	
	/*����������*/
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	
	TIM_SetCounter(TIM4,10000);
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM9							  
}  

void TIM4_Init(void)	
{
	TIM4_GPIO_Init();
	TIM4_IC_Mode_Init();
}





