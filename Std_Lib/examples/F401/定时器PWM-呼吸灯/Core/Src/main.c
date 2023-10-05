#include "main.h"
#include "tim.h"
#include "gpio.h"
#include <stdio.h>


int main(void)
{ 
	GPIO_Config();

	
	TIM2_Config();  
	TIM3_Config(); 

	
	while (1)
	{

	}
}
