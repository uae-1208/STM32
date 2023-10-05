#include "stm32f4xx.h"
#include "dac.h"
#include "usart.h"



int main(void)
{
	USART_Config();
	DAC_INIT();
	
  	while(1)
	{
		


	}
}

