#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exit.h"

int main(void)
{        
	led_config();
	key_config();
	exit_config();  
	while(1);
}








