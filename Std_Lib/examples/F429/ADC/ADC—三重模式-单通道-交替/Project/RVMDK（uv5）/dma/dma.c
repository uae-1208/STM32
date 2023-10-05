#include "dma.h"
#include "stm32f4xx.h"

static void DMA_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
} 

void DMA_Config(void)
{
	extern __IO uint32_t ADC_ConvertedValue[3];
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); 
	
  // �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)0x40012308;	
  // �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;  
  // ���ݴ��䷽��Ϊ���赽�洢��	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
  // ��������СΪ��ָһ�δ����������
	DMA_InitStructure.DMA_BufferSize = 3;	
  // ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // �洢����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
  // // �������ݴ�СΪ���֣��������ֽ� 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; 
  //	�洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;	
  // ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  //DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;

  // DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  // ��ֹDMA FIFO	��ʹ��ֱ��ģʽ
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
  // FIFO ��С��FIFOģʽ��ֹʱ�������������	
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
  // ѡ�� DMA ͨ����ͨ������������
	DMA_InitStructure.DMA_Channel = DMA_Channel_0; 
  //��ʼ��DMA�������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	
  //�����ж�
	//DMA_NVIC_Config();
    //DMA_ITConfig(DMA2_Stream0,DMA_IT_TC,ENABLE);  
	
  // ʹ��DMA��
	DMA_Cmd(DMA2_Stream0, ENABLE);	
}



void DMA2_Stream0_IRQHandler(void)
{
	if(DMA_GetITStatus (DMA2_Stream0, DMA_IT_TCIF0) != RESET)
	{			
		DMA_Cmd(DMA2_Stream0,DISABLE);
		DMA_SetCurrDataCounter(DMA2_Stream0,1);
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);	
		//DMA�������󲻿ɶԼĴ��������κ��޸ģ����Դ򿪲���Ҫ�ŵ����
		DMA_Cmd(DMA2_Stream0, ENABLE);
	}
}  

