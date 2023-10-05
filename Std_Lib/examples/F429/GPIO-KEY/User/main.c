#include "stm32f4xx.h"
#define KEY0 0
#define KEY1 1
#define KEY2 2
#define WK_UP 3
#define NONKEY 4

void delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

unsigned char keyscan(void)
{
	static unsigned char key = 1;         //static很关键
	unsigned char key0 = GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_3);
	unsigned char key1 = GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_2);
	unsigned char key2 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
	unsigned char wk_up = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	if(key && (key0 == 0 || key1 == 0 || key2 == 0 || wk_up))
		{
			delay(0xffff);       //松手检测必须有
			key = 0;
			if(!key0)
				return	KEY0;
			else if(!key1)
				return KEY1;
			else if(!key2)
				return KEY2;
			else 
				return WK_UP;
		}
		else if (key0 && key1 && key2 && wk_up == 0 && key == 0)
		{
			key = 1;
			delay(0xffff);      //松手检测必须有
		}
		return NONKEY;
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

void key_config(void)
{
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA |RCC_AHB1Periph_GPIOC 
							| RCC_AHB1Periph_GPIOH, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;													   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GPIOH, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main(void)
{
	unsigned char state = NONKEY;
	unsigned char SWITCH;          
	key_config();
	led_config();
	while(1)
	{
		state = keyscan();
		switch(state)
		{
			case KEY0:	if(SWITCH)
							GPIO_ToggleBits(GPIOB,GPIO_Pin_0);	
					break;
			case KEY1:	if(SWITCH)
							GPIO_ToggleBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);
					break;
			case KEY2:	if(SWITCH)
							GPIO_ToggleBits(GPIOB,GPIO_Pin_1);
					break;
			case WK_UP:	SWITCH = (~SWITCH) & 0x01; 
					break;
			case NONKEY:break;
		}  
	}
}


