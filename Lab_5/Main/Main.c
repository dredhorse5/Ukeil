#include "stm32f4xx.h"
#include "ledinit.h"
#include "Usart.h"



int main(void)
{
	SysTick_Config(SystemCoreClock /1000);
	port_ini();
	UartInit();
	
	//var1 = IsIncludeString("s_hello", "hello", sizeof("s_hello")/sizeof(char), sizeof("hello")/sizeof(char));
	//var2 = IsIncludeString("hello_s", "hello", sizeof("hello_s")/sizeof(char), sizeof("hello")/sizeof(char));
	//var3 = IsIncludeString("hello", "hello", sizeof("hello")/sizeof(char), sizeof("hello")/sizeof(char));
	//var3 = IsIncludeString("hell", "hello", sizeof("hell")/sizeof(char), sizeof("hello")/sizeof(char));
	//var3 = IsIncludeString("h_ell", "hello", sizeof("h_ell")/sizeof(char), sizeof("hello")/sizeof(char));
	while(1){}
}