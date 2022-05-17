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
	UartInit();
}

void UartInit()
{
	GPIO_InitTypeDef USART_ini;
	USART_InitTypeDef set_usart;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	USART_ini.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;
	USART_ini.GPIO_Mode  = GPIO_Mode_AF;
	USART_ini.GPIO_OType = GPIO_OType_PP;
	USART_ini.GPIO_PuPd  = GPIO_PuPd_UP;
	USART_ini.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &USART_ini);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	set_usart.USART_BaudRate = 38400;
	set_usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	set_usart.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	set_usart.USART_Parity = USART_Parity_No;
	set_usart.USART_StopBits = USART_StopBits_1;
	set_usart.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART2, &set_usart);
	USART_Cmd(USART2, ENABLE);
	
	NVIC_EnableIRQ(USART2_IRQn);	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);


}