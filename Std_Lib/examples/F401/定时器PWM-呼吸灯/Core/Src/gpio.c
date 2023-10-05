#include "gpio.h"
  
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* LED on C13 pin(PC13) ***********************************/ 
	/* Enable the GPIOCperipheral */ 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Configure C13 pin(PC13) in output function */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

