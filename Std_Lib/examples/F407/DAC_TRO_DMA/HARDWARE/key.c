#include "key.h"
#include "systick.h"
#include "usart.h"


//������ʼ������
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;            //KEY��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;         //��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;         //����
	GPIO_Init(GPIOA, &GPIO_InitStructure);               //��ʼ��PA0
	

} 

u8 Key_Scan(void)
{
	static u8 Key_State = UP;
	if(!KEY_READ() && Key_State)
	{
		Delay_ms(3);
		if(!KEY_READ())
		{
			Key_State = UP;     
			Delay_ms(2);
			return DOWN;
		}
	}
	else if(KEY_READ())
		Key_State = DOWN;
	
	return UP;
}






