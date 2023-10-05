#include "adc.h"

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);       //通道PA5
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	           //配置为模拟功能时上下拉失效
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; //不上拉不下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
}

static void ADC_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

  // 开启ADC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 , ENABLE);

// -------------------ADC Common 结构体 参数 初始化------------------------
  // 独立ADC模式
	ADC_CommonInitStructure.ADC_Mode = ADC_DualMode_RegSimult;
  // 时钟为fpclk x分频	
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
  // 禁止DMA直接访问模式	
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
  // 采样时间间隔	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;  
	ADC_CommonInit(&ADC_CommonInitStructure);
	
// -------------------ADC Init 结构体 参数 初始化--------------------------
	ADC_StructInit(&ADC_InitStructure);
  // ADC 分辨率
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  // 扫描模式，多通道采集需要	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; 
  // 连续转换	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  //禁止外部边沿触发
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  //外部触发通道，本例子使用软件触发，此值随便赋值即可
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  //数据右对齐	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  //转换通道2个
	ADC_InitStructure.ADC_NbrOfConversion = 1;                                    
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Init(ADC2, &ADC_InitStructure);

	
  // 配置 ADC 通道转换顺序和采样时间周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);	

  //使每次转换完成都发出请求   
	ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
  // 使能ADC DMA
  	ADC_DMACmd(ADC1, ENABLE);     

  // 使能ADC
	ADC_Cmd(ADC1, ENABLE); 
	ADC_Cmd(ADC2, ENABLE);  

	
  //开始adc转换，软件触发
	ADC_SoftwareStartConv(ADC1);	
}

// 配置中断优先级
/*static void ADC_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
} */


void ADC1_Init(void)
{
	ADC_GPIO_Config();
	ADC_Mode_Config();
	//ADC_NVIC_Config();
}

/*void ADC_IRQHandler(void)
{
	extern __IO uint16_t ADC_ConvertedValue;
	if(ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET)
	{
		ADC_ConvertedValue = ADC_GetConversionValue(ADC1);
	}
	ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
} */   

