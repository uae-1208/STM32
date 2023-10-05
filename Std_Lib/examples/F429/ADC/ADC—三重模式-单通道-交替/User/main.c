#include "stm32f4xx.h"
#include "usart.h"
#include "adc.h"
#include "systick.h"
#include "dma.h"

__IO uint32_t ADC_ConvertedValue[3];


int main(void)
{
	USART_Config();
	SysTick_Init();
	DMA_Config();
	ADC1_Init();
  	while(1)
	{
		printf("The current AD1 value = %fV \r\n", 3.3 / 4096 * (u16)ADC_ConvertedValue[0]);
		printf("The current AD2 value = %fV \r\n", 3.3 / 4096 * (u16)(ADC_ConvertedValue[0]>>16)); 
		printf("The current AD3 value = %fV \r\n", 3.3 / 4096 * (u16)ADC_ConvertedValue[1]);
		printf("The current AD1 value = %fV \r\n", 3.3 / 4096 * (u16)(ADC_ConvertedValue[1]>>16)); 
		printf("The current AD2 value = %fV \r\n", 3.3 / 4096 * (u16)ADC_ConvertedValue[2]);
		printf("The current AD3 value = %fV \r\n\r\n", 3.3 / 4096 * (u16)(ADC_ConvertedValue[2]>>16));     
		Delay_ms(2000); 
	}
}

