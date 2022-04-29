#include "stm32f4xx.h"
#include "ledinit.h"
#include "Usart.h"

char ID[4]  = {'A','B','C','D'};


int main(void)
{
	uint8_t var1 = 0;
	uint8_t var2 = 0;
	uint8_t var3 = 0;
	SysTick_Config(SystemCoreClock /1000);
	port_ini();
	UartInit();
	
	SendString_to_USART(ID);
	var1 = IsIncludeString("s_hello", "hello", sizeof("s_hello")/sizeof(char), sizeof("hello")/sizeof(char));
	var2 = IsIncludeString("hello_s", "hello", sizeof("hello_s")/sizeof(char), sizeof("hello")/sizeof(char));
	var3 = IsIncludeString("hello", "hello", sizeof("hello")/sizeof(char), sizeof("hello")/sizeof(char));
	var3 = IsIncludeString("hell", "hello", sizeof("hell")/sizeof(char), sizeof("hello")/sizeof(char));
	var3 = IsIncludeString("h_ell", "hello", sizeof("h_ell")/sizeof(char), sizeof("hello")/sizeof(char));
	while(1){}
}