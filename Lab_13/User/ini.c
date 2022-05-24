#include "ini.h"

void Init_usart(void)
{
	GPIO_InitTypeDef USART_ini;
	USART_InitTypeDef set_usart;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	USART_ini.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	USART_ini.GPIO_Mode = GPIO_Mode_AF;
	USART_ini.GPIO_OType = GPIO_OType_PP;
	USART_ini.GPIO_PuPd = GPIO_PuPd_UP;
	USART_ini.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &USART_ini);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	set_usart.USART_BaudRate = 9600;
	set_usart.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	set_usart.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	set_usart.USART_Parity = USART_Parity_No;
	set_usart.USART_StopBits = USART_StopBits_1;
	set_usart.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART2, &set_usart);
	NVIC_EnableIRQ(USART2_IRQn);
	USART_Cmd(USART2, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}
