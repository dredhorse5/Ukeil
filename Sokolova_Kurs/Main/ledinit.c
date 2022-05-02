#include "stm32f4xx.h"
#include "stdio.h"
#include "stm32f4xx_conf.h"

    void port_ini(void)
    {
        GPIO_InitTypeDef GPIO_Struct_LED;
        GPIO_InitTypeDef GPIO_Struct_Button;

        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 

        GPIO_Struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
        GPIO_Struct_LED.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_Struct_LED.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_Struct_LED.GPIO_OType = GPIO_OType_PP;
        GPIO_Struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;

        GPIO_Init(GPIOD, &GPIO_Struct_LED);


        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

        GPIO_Struct_Button.GPIO_Pin = GPIO_Pin_0;
        GPIO_Struct_Button.GPIO_Mode = GPIO_Mode_IN;
        GPIO_Struct_Button.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_Struct_Button.GPIO_OType = GPIO_OType_PP;
        GPIO_Struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;

        GPIO_Init(GPIOA, &GPIO_Struct_Button);
			}