#include "stm32f4xx.h"
#include "usart.h"
#include "adc.h"
#include "systick.h"

__IO uint16_t ADC_ConvertedValue;
float ADC_Vol;

int main(void)
{
	USART_Config();
	SysTick_Init();
	ADC1_Init();	
	while(1)
	{
		ADC_Vol = 3.3 / 4096 * ADC_ConvertedValue;
		printf("The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
		printf("The current AD value = %fV \r\n\r\n", ADC_Vol);
		Delay_ms(1000);
	}
}

