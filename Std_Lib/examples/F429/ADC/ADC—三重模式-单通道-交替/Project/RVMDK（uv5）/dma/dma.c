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
	
  // 外设基址为：ADC 数据寄存器地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)0x40012308;	
  // 存储器地址，实际上就是一个内部SRAM的变量	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;  
  // 数据传输方向为外设到存储器	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
  // 缓冲区大小为，指一次传输的数据量
	DMA_InitStructure.DMA_BufferSize = 3;	
  // 外设寄存器只有一个，地址不用递增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // 存储器地址递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
  // // 外设数据大小为半字，即两个字节 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; 
  //	存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;	
  // 循环传输模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  //DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;

  // DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  // 禁止DMA FIFO	，使用直连模式
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
  // FIFO 大小，FIFO模式禁止时，这个不用配置	
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
  // 选择 DMA 通道，通道存在于流中
	DMA_InitStructure.DMA_Channel = DMA_Channel_0; 
  //初始化DMA流，流相当于一个大的管道，管道里面有很多通道
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	
  //配置中断
	//DMA_NVIC_Config();
    //DMA_ITConfig(DMA2_Stream0,DMA_IT_TC,ENABLE);  
	
  // 使能DMA流
	DMA_Cmd(DMA2_Stream0, ENABLE);	
}



void DMA2_Stream0_IRQHandler(void)
{
	if(DMA_GetITStatus (DMA2_Stream0, DMA_IT_TCIF0) != RESET)
	{			
		DMA_Cmd(DMA2_Stream0,DISABLE);
		DMA_SetCurrDataCounter(DMA2_Stream0,1);
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);	
		//DMA流开启后不可对寄存器进行任何修改，所以打开操作要放到最后
		DMA_Cmd(DMA2_Stream0, ENABLE);
	}
}  

