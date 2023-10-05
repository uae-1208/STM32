#include "dac.h" 	
#include "usart.h"

uint32_t Sine12bit[64] = {
	2249,2448,2643,2832,3013,3186,3347,3496,3631,3751,3854,3940,4008,
	4057,4086,4095,4086,4057,4008,3940,3854,3751,3631,3496,3347,3186,
	3013,2832,2643,2448,2249,2048,1847,1648,1453,1264,1083,910,749,
	600,465,345,242,156,88,39,10,0,10,39,88,156,242,345,465,600,749,910,
	1083,1264,1453,1648,1847,2048};
	

//����
//uint32_t DualSine12bit[32] ={4095,4095,4095,4095,4095,4095,4095,4095,4095,
//4095,4095,4095,4095,4095,4095,4095,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


static void DAC_GPIO_Config(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//PA4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO

}


void DAC_Mode_Config(void)
{    	 
	DAC_InitTypeDef  DAC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//ʹ��DACʱ��
 
//	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;				//��ʹ�ô���Դ
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;			//ʹ���������Դ
//	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;			//ʹ��TIM2��Ϊ����Դ
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	//��ʹ�ò��η�����
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;	//��ʹ��DAC�������
	
	//���ǲ��������ʵ��û���õ��������ó�����ֵ�������ṹ���Ա����Ϊ�գ�
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	
	/* ʹ�� DAC��DMA���� */
//	DAC_DMACmd(DAC_Channel_1, ENABLE);

}

static void DAC_TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	/* ʹ��TIM2ʱ�ӣ�TIM2CLK Ϊ180M */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
   NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 	
		// ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ���������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	

	/* TIM2������ʱ������ */
	TIM_TimeBaseStructure.TIM_Period = 19;       			//��ʱ���� 20  
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       		//Ԥ��Ƶ������Ƶ 180M / (0+1) = 180M
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    		//ʱ�ӷ�Ƶϵ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* ����TIM2����Դ */
//	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	/* ʹ��TIM2 */
	TIM_Cmd(TIM2, ENABLE);

}


#define DHR12R1_OFFSET             ((uint32_t)0x00000008)
#define DHR12R2_OFFSET             ((uint32_t)0x00000014)
#define DHR12RD_OFFSET             ((uint32_t)0x00000020)

static void DAC_DMA_Config(void)
{	
	DMA_InitTypeDef  DMA_InitStructure;

	/* DAC1ʹ��DMA1 ͨ��7 ������5ʱ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	/* ����DMA2 */
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;  
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(DAC_BASE+DHR12R1_OFFSET);	//�������ݵ�ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(DAC_BASE+DHR12RD_OFFSET);	//����
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&Sine12bit ;				    //�ڴ����ݵ�ַSine12bit
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;							//���ݴ��䷽���ڴ�������
	DMA_InitStructure.DMA_BufferSize = 64;											//�����СΪ32�ֽ�	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				//�������ݵ�ַ�̶�	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;							//�ڴ����ݵ�ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;			//������������Ϊ��λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;					//�ڴ���������Ϊ��λ	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;									//ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;								//��DMAͨ�����ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA1_Stream5, &DMA_InitStructure);

	/* ʹ�� DMA_Stream */
	DMA_Cmd(DMA1_Stream5, ENABLE);
}

void DAC_INIT(void)
{
	DAC_GPIO_Config();
	DAC_Mode_Config();
	DAC_TIM_Config();
//	DAC_DMA_Config();
}



int i = 0;

void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET ) 
	{	
		DAC_SetChannel1Data(DAC_Align_12b_R,(uint16_t)Sine12bit[i]);
		DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
		i++;
		if(i == 64)
			i = 0;
//		printf("%d\r\n",DAC_GetDataOutputValue(DAC_Channel_1));
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  		 
	}		 	
}






