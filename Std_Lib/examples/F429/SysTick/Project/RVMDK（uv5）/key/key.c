#include "key.h"

void key_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                //ph2,key1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	    		
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  	             //ph3,key0
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;               //pc13,key2
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}
