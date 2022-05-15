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

// constants
uint8_t LedBurnTime = 100; // in ms
uint8_t Random_Time = 10000000; // in ms



uint8_t LedMode = 1;
uint8_t LedMode_Breaked = 0;

uint16_t ModeTimer = 0;
uint16_t RandomTimer = 0;
int16_t Direction = 0;

//-----------------------------------------
uint16_t button_count = 0;
uint8_t button_state = 0;

void SysTick_Handler(void)
{
	
    if (ModeTimer > 0)
    {
        ModeTimer--;
    }
		
		
		if(RandomTimer > 0)
		{
				RandomTimer--;
		}
			
}

//-----------------------------------------

void UpdateLeds()
{
	// switch mode if timer is over
	if(ModeTimer <= 0)
	{
		ModeTimer = LedBurnTime;
		if(Direction == 0)
			LedMode = LedMode + 1;
		else
			LedMode = LedMode - 1;
		
		if(LedMode >= 5)
			LedMode = 1;
		else if(LedMode < 1)
			LedMode = 4;
	}
	
	// switch randomly direction
	if(RandomTimer <= 0)
	{
			 Direction = RNG_GetRandomNumber() % 2;
			 RandomTimer = 2000;
	}
		
	
	
	
		// update Leds
		if (LedMode == 1)
		{
			Red_on();
		
			Blue_off();
			Green_off();
			Orange_off();
		}
		else if (LedMode == 2)
		{
			Blue_on();
		
			Green_off();
			Orange_off();
			Red_off();
		}
		else if (LedMode == 3)
		{
			Green_on();
		
			Blue_off();
			Orange_off();
			Red_off();
		}
		else if (LedMode == 4)
		{
			Orange_on();
		
			Blue_off();
			Green_off();
			Red_off();
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
