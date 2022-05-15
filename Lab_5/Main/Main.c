#include "stm32f4xx.h"
#include "ledinit.h"
#include "Usart.h"



int main(void)
{
	SysTick_Config(SystemCoreClock /1000);
	port_ini();
	UartInit();
	
	while(1){}
}