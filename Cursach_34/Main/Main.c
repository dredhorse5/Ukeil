#include "stm32f4xx.h"
#include "init.h"

#include "stm32f4xx.h"
//#include "LED_ini.h"
//#include "Button_ini.h"
//#include "ports.h"

#define BUTTON_READ() 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

#define Blue_on() GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define Green_on() GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define Orange_on() GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define Red_on() GPIO_SetBits(GPIOD,GPIO_Pin_14)

#define Blue_off() GPIO_ResetBits(GPIOD,GPIO_Pin_15)
#define Green_off() GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define Orange_off() GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define Red_off() GPIO_ResetBits(GPIOD,GPIO_Pin_14)


uint16_t button_count = 0;
uint8_t button_state = 0;

uint8_t Mode = 0;
uint8_t Mode0 = 0;
uint8_t Start_Mode = 0;

uint16_t delay_count = 0;

//-----------------------------------------

void SysTick_Handler(void)
{
	if (delay_count > 0)

			{

			delay_count--;

			}
	if (BUTTON_READ() == 1)
	{
		if (button_count < 10)
		{
			button_count++;
			
		}
		else
		{
			if (button_state == 0) 
			{
  				  Mode0 = 0;
			}
		}
	}
	else
	{
		 Mode0 = 1;
		if (button_count > 0)
		{
			button_count--;
		}
		else
		{
			if (button_state == 1) 
			{
				button_state = 0;
			}
		}
	}
}

//-----------------------------------------

int main(void)
{
	init();
	//LED_ini();
	//Button_ini();
	
	SystemCoreClockUpdate();
	SysTick_Config(168000000 /1000);
	
	while(1)
		{
			if (Mode0 == 0){
				if (Mode == 0)
					{
						if (Start_Mode == 0)
							{
								Red_on();
								Start_Mode = 1;
								delay_count = 100;
							}
						if (delay_count == 0)
							{
								Red_off();
								Start_Mode = 0;
								Mode = 1;
							}
				} else if (Mode == 1)
					{
						if (Start_Mode == 0)
							{
								Blue_on();
								Start_Mode = 1;
								delay_count = 100;
							}
						if (delay_count == 0)
							{
								Blue_off();
								Start_Mode = 0;
								Mode = 2;
							}
				} else if (Mode == 2)
					{
						if (Start_Mode == 0)
							{
								Green_on();
								Start_Mode = 1;
								delay_count = 100;
							}
						if (delay_count == 0)
							{
								Green_off();
								Start_Mode = 0;
								delay_count = 100;
								Mode = 3;
							}
							
				} else if (Mode == 3)
					{
						if (Start_Mode == 0)
							{
								Orange_on();
								Start_Mode = 1;
								delay_count = 100;
							}
						if (delay_count == 0)
							{
								Orange_off();
								Start_Mode = 0;
								delay_count = 100;
								Mode = 0;
					}
		}
	} else if (Mode == 0)
					{
						Red_on();
					
				} else if (Mode == 1)
					{
						Blue_on();
				} else if (Mode == 2)
					{
						Green_on();
							
				} else if (Mode == 3)
					{
						Orange_on();
					}
		}
}
