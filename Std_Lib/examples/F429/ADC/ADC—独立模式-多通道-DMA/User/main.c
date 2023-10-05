#include "stm32f4xx.h"
#include "usart.h"
#include "adc.h"
#include "systick.h"
#include "dma.h"

__IO uint16_t ADC_ConvertedValue[2];

int main(void)
{
	USART_Config();
	SysTick_Init();
	DMA_Config();
	ADC1_Init();
  	while(1)
	{
		printf("PA5£ºThe current AD value = %fV \r\n", 3.3 / 4096 * ADC_ConvertedValue[0]); 
		printf("PA0:The current AD value = %fV \r\n\r\n",3.3 / 4096 * ADC_ConvertedValue[1]);     
		Delay_ms(1000); 
	}
}

