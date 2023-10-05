#include "adc.h"

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);       //ͨ��PA5
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	           //����Ϊģ�⹦��ʱ������ʧЧ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; //������������
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
}

static void ADC_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

  // ����ADCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 , ENABLE);

// -------------------ADC Common �ṹ�� ���� ��ʼ��------------------------
  // ����ADCģʽ
	ADC_CommonInitStructure.ADC_Mode = ADC_DualMode_RegSimult;
  // ʱ��Ϊfpclk x��Ƶ	
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
  // ��ֹDMAֱ�ӷ���ģʽ	
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
  // ����ʱ����	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;  
	ADC_CommonInit(&ADC_CommonInitStructure);
	
// -------------------ADC Init �ṹ�� ���� ��ʼ��--------------------------
	ADC_StructInit(&ADC_InitStructure);
  // ADC �ֱ���
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  // ɨ��ģʽ����ͨ���ɼ���Ҫ	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; 
  // ����ת��	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  //��ֹ�ⲿ���ش���
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  //�ⲿ����ͨ����������ʹ�������������ֵ��㸳ֵ����
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  //�����Ҷ���	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  //ת��ͨ��2��
	ADC_InitStructure.ADC_NbrOfConversion = 1;                                    
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Init(ADC2, &ADC_InitStructure);

	
  // ���� ADC ͨ��ת��˳��Ͳ���ʱ������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);	

  //ʹÿ��ת����ɶ���������   
	ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
  // ʹ��ADC DMA
  	ADC_DMACmd(ADC1, ENABLE);     

  // ʹ��ADC
	ADC_Cmd(ADC1, ENABLE); 
	ADC_Cmd(ADC2, ENABLE);  

	
  //��ʼadcת�����������
	ADC_SoftwareStartConv(ADC1);	
}

// �����ж����ȼ�
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

