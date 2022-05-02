#include "stm32f4xx.h"
#include "ledinit.h"


  
#define Green_on() GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define Orange_on() GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define Red_on() GPIO_SetBits(GPIOD,GPIO_Pin_14)
#define Blue_on() GPIO_SetBits(GPIOD,GPIO_Pin_15)

#define Green_off() GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define Orange_off() GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define Red_off() GPIO_ResetBits(GPIOD,GPIO_Pin_14)
#define Blue_off() GPIO_ResetBits(GPIOD,GPIO_Pin_15)

#define Green_toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_12)
#define Orange_toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_13)
#define Red_toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_14)
#define Blue_toggle() GPIO_ToggleBits(GPIOD,GPIO_Pin_15)
uint8_t ModeCount;

int FirstModeTimer;
uint8_t FirstModeCount;
void UpdateFirstMode()
{
	FirstModeTimer++;
	if(FirstModeTimer > 250)
	{
		FirstModeCount++;
		FirstModeTimer = 0;
	}
	if(FirstModeCount >= 4)
		FirstModeCount = 0;
	
	if(FirstModeCount == 0)
	{
		Red_on();
	}
	else if(FirstModeCount == 1)
	{
		Blue_on();
	}
	else if(FirstModeCount == 2)
	{
		Green_on();
	}
	else if(FirstModeCount == 3)
	{
		Orange_on();
	}
}


int FourModeTimer;
uint8_t FourModeCount;
void UpdateFourMode()
{
	FourModeTimer++;
	if(FourModeTimer > 1000)
	{
		FourModeCount++;
		FourModeTimer = 0;
	}
	if(FourModeCount >= 2)
		FourModeCount = 0;
	
	if(FourModeCount == 0)
	{
		Orange_on();
	}
}


int SevenModeTimer;
uint8_t SevenModeCount;
void UpdateSevenMode()
{
	SevenModeTimer++;
	if(SevenModeTimer > 1000)
	{
		SevenModeCount++;
		SevenModeTimer = 0;
	}
	if(SevenModeCount >= 2)
		SevenModeCount = 0;
	
	if(SevenModeCount == 0)
	{
		Blue_on();
	}
}


int TenModeTimer;
uint8_t TenModeCount;
void UpdateTenMode()
{
	
	TenModeTimer++;
	if(TenModeTimer > 250)
	{
		TenModeCount++;
		TenModeTimer = 0;
	}
	if(TenModeCount >= 4)
		TenModeCount = 0;
	
	
	if(TenModeCount == 0)
	{
		Red_on();
	}
	else if(TenModeCount == 1)
	{
		Green_on();
	}
	else if(TenModeCount == 2)
	{
		Blue_on();
	}
	else if(TenModeCount == 3)
	{
		Orange_on();
	}
}

// =================== button ===================
#define BUTTON_READ() 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
uint16_t button_count = 0;
uint16_t button_doubleClick_count = 0;
uint8_t ButtonState = 0; // 1- pressed, 0 - unpressed
uint8_t button_pressed_count = 0;

void OnDoubleClickButton() {}
void OnPressedButton()
{
	ModeCount++;
	if(ModeCount >=4)
		ModeCount = 0;
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
									button_doubleClick_count = 100;
								
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


void SysTick_Handler(void)
{
	Green_off();
  Orange_off();
  Red_off();
  Blue_off();
	
	if(ModeCount == 0)
	{
		UpdateFirstMode();
	}
	else if(ModeCount == 1)
	{
		UpdateFourMode();
	}
	else if(ModeCount == 2)
	{
		UpdateSevenMode();
	}
	else if(ModeCount == 3)
	{
		UpdateTenMode();
	}
}



int main(void)
{
	SysTick_Config(SystemCoreClock /1000);
	port_ini();
	
	while(1){}
}