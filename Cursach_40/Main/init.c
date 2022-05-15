#include "stm32f4xx.h"
#include "Main.h"

void init(void)
{
	GPIO_InitTypeDef GPIO_struct_LED;
	GPIO_InitTypeDef GPIO_struct_Button;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_struct_LED.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12;
	GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_struct_LED.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_struct_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_struct_LED);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_struct_Button.GPIO_Pin = GPIO_Pin_0;
	GPIO_struct_Button.GPIO_Mode = GPIO_Mode_IN;
	GPIO_struct_Button.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_struct_Button.GPIO_OType = GPIO_OType_PP;
	GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &GPIO_struct_Button);
	
	// random
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	RNG_Cmd(ENABLE);



}