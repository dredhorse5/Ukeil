#include "stm32f4xx.h"
#include "ledinit.h"
#include "Usart.h"

char ID[4]  = {'A','B','C','D'};


int main(void)
{
	SysTick_Config(SystemCoreClock /1000);
	port_ini();
	UartInit();
	
	SendString_to_USART(ID);
	while(1){}
}