#include "stm32f4xx.h"
#include "tim.h"
#include "usart.h"


int main(void)
{
	USART_Config();	
	TIM2_Init();
	TIM5_Init();
  	while(1);
}

