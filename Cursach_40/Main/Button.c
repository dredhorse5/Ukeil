#include "stm32f4xx.h"

// =================== button ===================
#define BUTTON_READ() 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
uint16_t button_count = 0;
uint16_t button_doubleClick_count = 0;
uint8_t ButtonState = 0; // 1- pressed, 0 - unpressed
uint8_t button_pressed_count = 0;


// =================== Leds ===================
#define Blue_on() GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define Green_on() GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define Orange_on() GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define Red_on() GPIO_SetBits(GPIOD,GPIO_Pin_14)

#define Blue_off() GPIO_ResetBits(GPIOD,GPIO_Pin_15)
#define Green_off() GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define Orange_off() GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define Red_off() GPIO_ResetBits(GPIOD,GPIO_Pin_14)


#define Blue_Toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_15)
#define Green_Toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_12)
#define Orange_Toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_13)
#define Red_Toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_14)


// =================== Some ===================
uint8_t LedMode = 0;


void UpdateLeds()
{
		// update Leds
		if (LedMode == 0)
		{
			Green_on();
		}
		else if (LedMode == 1)
		{
			Orange_on();
		}
		else if (LedMode == 2)
		{
			Red_on();
		}
		else if (LedMode == 3)
		{
			Blue_on();
		}
}

void OnDoubleClickButton()
{
	LedMode = 0;
	Red_off();
	Blue_off();
	Green_off();
	Orange_off();
}
void OnPressedButton()
{
	UpdateLeds();
	LedMode++;
}

// call in interruption
void UpdateButton(void)
{
	  if(button_doubleClick_count > 0)
			button_doubleClick_count--;
		
    if (BUTTON_READ() == 1)
    {
        if (button_count < 10)
        {
            button_count++;
        }
        else
        {
            if (ButtonState == 0) 
            {							
							  if(button_doubleClick_count <= 0)
									button_doubleClick_count = 300;
								
							  button_pressed_count++;
								ButtonState = 1;
            }
        }
    }
    else
    {
        if (button_count > 0)
        {
            button_count--;
        }
        else
        {
            if (ButtonState == 1) 
            {
                ButtonState = 0;
            }
        }
    }
		if(button_doubleClick_count <= 0 && button_pressed_count > 0)
		{
				if(button_pressed_count > 1)
					OnDoubleClickButton();
				else
					OnPressedButton();
			  button_pressed_count = 0;
		}
}

