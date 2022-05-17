#include "stm32f4xx.h"
#include "init.h"
#define Blue_on() GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define Green_on() GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define Orange_on() GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define Red_on() GPIO_SetBits(GPIOD,GPIO_Pin_14)

#define Blue_off() GPIO_ResetBits(GPIOD,GPIO_Pin_15)
#define Green_off() GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define Orange_off() GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define Red_off() GPIO_ResetBits(GPIOD,GPIO_Pin_14)    

#define Green_toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_12)
#define Orange_toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_13)
#define Red_toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_14)
#define Blue_toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_15)

// constants
uint8_t LedMode = 1;// 1 -  random led is blinking, 2- random led burning, 3 - burning all leds, 4- all leds shut down
uint8_t RandomLed = 1; // needs for modes 1 and 2
int BlinkTimer = 0; // for mode 1


void SysTick_Handler(void)
{
	if(BlinkTimer > 0)
		BlinkTimer--;
}

void ToggleLed(uint8_t num)
{
	switch(num)
	{
		case 1:Green_toggle(); break;
		case 2:Orange_toggle();break;
		case 3:Red_toggle();   break;
		case 4:Blue_toggle();  break;
	}
}
void SwitchLed(uint8_t num, uint8_t state)
{
	switch(num)
	{
			
		case 1:
			if(state)
				Green_on(); 
			else 
				Green_off();
				break;
			
			
		case 2:
			if(state)
				Orange_on(); 
			else 
				Orange_off();
				break;
			
			
		case 3:
			if(state)
				Red_on(); 
			else 
				Red_off();
				break;
			
		case 4:
			if(state)
				Blue_on(); 
			else 
				Blue_off();
				break;
			
	}
}

void UpdateLeds()
{
	Blue_off();
	Green_off();
	Orange_off();
	Red_off();
	
	switch(LedMode)
	{
		case 1:
			if(BlinkTimer <= 0)
				ToggleLed(RandomLed);
			break;
		
		
		case 2:
			SwitchLed(RandomLed, 1);
			break;
		
		
		case 3:
			SwitchLed(1, 1);
			SwitchLed(2, 1);
			SwitchLed(3, 1);
			SwitchLed(4, 1);
			break;
		
		
		case 4:
			// shut down #_#
			break;
	}
}

void WriteUSART()
{
	char uart_data;
	USART2->DR = USART2->DR;
	uart_data=USART2->DR; 
	
	RandomLed = (RNG_GetRandomNumber() % 4) + 1; // from 1 to 4
	// set modes
	switch(uart_data)
	{
		case '1':LedMode = 1;break;
		case '2':LedMode = 2;break;
		case '3':LedMode = 3;break;
		case '4':LedMode = 4;break;
	}
}




void USART2_IRQHandler(void)
{
	if (USART2->SR & USART_SR_RXNE)
	{
		WriteUSART();
	}
}


int main(void)
{
	init();

	SysTick_Config(SystemCoreClock/1000);

	while (1)
	{
		UpdateLeds();
	}
}
