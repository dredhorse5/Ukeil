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

uint8_t LedBurnTime = 100; // in ms

uint8_t LedMode = 0;
uint8_t LedMode_Breaked = 0;

uint8_t IsPressedButton = 0; // 1 - pressed, 0 - unpressed
uint8_t wasPresseButton = 0;
uint16_t ModeTimer = 0;

//-----------------------------------------
uint16_t button_count = 0;
uint8_t button_state = 0;

void SysTick_Handler(void)
{
    if (ModeTimer > 0)
    {
        ModeTimer--;
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
                IsPressedButton = 1;
            }
        }
    }
    else
    {
        IsPressedButton = 0;
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

void UpdateLeds()
{
	// switch mode if timer is over
	if(ModeTimer <= 0)
	{
		ModeTimer = LedBurnTime;
		LedMode = LedMode + 1;
		LedMode_Breaked = 0;
		if(LedMode >= 4)
			LedMode = 0;
	}
	
	if(LedMode_Breaked == 0)
	{
		// update Leds
		if (LedMode == 0)
		{
			Red_on();
		
			Blue_off();
			Green_off();
			Orange_off();
		}
		else if (LedMode == 1)
		{
			Blue_on();
		
			Green_off();
			Orange_off();
			Red_off();
		}
		else if (LedMode == 2)
		{
			Green_on();
		
			Blue_off();
			Orange_off();
			Red_off();
		}
		else if (LedMode == 3)
		{
			Orange_on();
		
			Blue_off();
			Green_off();
			Red_off();
		}
	}
}

void UpdateButton()
{
	if(IsPressedButton == 1)
	{
		if(wasPresseButton == 0)
		{
			wasPresseButton = 1;
			
			LedMode_Breaked = 1;
			ModeTimer = 1000;
		}
	}
	else
	{
		wasPresseButton = 0;
	}
		
}

int main(void)
{
	init();

	SysTick_Config(SystemCoreClock/1000);

	while (1)
	{
		UpdateLeds();
		UpdateButton();
	}
}
