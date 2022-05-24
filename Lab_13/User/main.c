#include "ini.h"
#include "main.h"

uint32_t temp1 = 0; 
uint32_t count_size = 0; 
uint32_t randi = 0;
uint32_t count = 0; 
uint32_t max_num = 0xFFFFFFFF;
uint16_t i = 0;
uint16_t j = 0;
uint16_t hist[10];
uint8_t TX_buffer[1000];
uint8_t TX_flag = 0;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_TXE) == 1)
	{
		USART_ClearITPendingBit(USART2, USART_IT_TXE);
	
		if (count != count_size)
		{
			USART_SendData(USART2, TX_buffer[count]);
			count++;
		}
		else
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
			count = 0;
			TX_flag = 1;
			
		}
	}	
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------	
void TX_Buffer_init(uint32_t data_size)
{
	count_size = data_size;
	
	USART_SendData(USART2, TX_buffer[0]);
	count++;
	
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
int main(void)
{

	Init_usart();
	
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	RNG_Cmd(ENABLE);
	
	// part 1
	while (i <= 796)
	{
		temp1 = RNG_GetRandomNumber();
		TX_buffer[i] = temp1 >> 24;
		TX_buffer[i+1] = temp1 >> 16;
		TX_buffer[i+2] = temp1 >> 8;
		TX_buffer[i+3] = temp1;
		i = i + 4;
	}
	TX_Buffer_init(800);
	while(TX_flag != 1) {}
	TX_flag = 0;
		
	// razdelenie
	for(i = 0; i <= 9; i++)
	{
		TX_buffer[i] = 0xFF;
	} 
	TX_Buffer_init(10);
	while(TX_flag != 1) {}
	TX_flag = 0;
	
	// part 2
	for(i = 0; i <= 9; i++)
	{
		hist[i] = 0;
	}
	for(j = 0; j <= 9999; j++)
	{
		randi = RNG_GetRandomNumber();
		if (randi <= max_num/10)
		{
			hist[0]++;
		} else if (randi <= max_num/10*2)
		{
			hist[1]++;
		} else if (randi <= max_num/10*3)
		{
			hist[2]++;
		} else if (randi <= max_num/10*4)
		{
			hist[3]++;
		} else if (randi <= max_num/10*5)
		{
			hist[4]++;
		} else if (randi <= max_num/10*6)
		{
			hist[5]++;
		} else if (randi <= max_num/10*7)
		{
			hist[6]++;
		} else if (randi <= max_num/10*8)
		{
			hist[7]++;
		} else if (randi <= max_num/10*9)
		{
			hist[8]++;
		} else if (randi <= max_num)
		{
			hist[9]++;
		}
	}
	i = 0;
	j = 0;
	while (i <= 18)
	{
		TX_buffer[i] = hist[j] >> 8;
		TX_buffer[i+1] = hist[j];
		i = i + 2;
		j = j + 1;
	}
	TX_Buffer_init(20);
	while(TX_flag != 1) {}
	TX_flag = 0;
	
}
