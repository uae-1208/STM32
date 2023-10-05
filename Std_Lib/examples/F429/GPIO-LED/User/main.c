#include "stm32f4xx.h"
void delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
void led_config(void)
{
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;													   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	GPIO_WriteBit(GPIOB, GPIO_Pin_0 | GPIO_Pin_1, Bit_RESET);
}

int main(void)
{
    led_config();
	while(1)
	{
		delay(0x9fffff);
		GPIO_ToggleBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
	}
}



