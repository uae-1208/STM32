#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f4xx.h"
	 
#define KEY_READ() 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) //PB2����ȡ�ߵ�ƽʱ����

enum{
	UP,        //δ����
	DOWN       //����
};


void KEY_Init(void);	//IO��ʼ��
u8 Key_Scan(void);


#endif
