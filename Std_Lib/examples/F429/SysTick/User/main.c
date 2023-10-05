#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exit.h"
#include "systick.h"
#include <stdio.h>

int main(void)
{        
	led_config();
	SysTick_Init();
	key_config();
	exit_config();
	while(1);
}





