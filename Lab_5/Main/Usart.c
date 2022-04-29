#include "stm32f4xx.h"
#include "Main.h"

char uart2_rx_buf[128]; //Буфер для приёма сообщения.
uint8_t uart2_rx_bit; //Номер байта UART принимаемого в буфер.
uint8_t isReadCommand; // true if a symbol "/" was seen from uart. allow to read a commands
uint8_t CommandType = 0; // see below


// ===== commands =====
// 2 - /LedBlink delay  {100-infinity} [1-4,1-4,1-4,...];   // allow to set to leds by numbers n(1-4) blink delay - from 100 to infinity
// 5 - /LedBlink switch		off/on	   [1-4,1-4,1-4,...];   // allow to set to leds by numbers n(1-4) state - on or off
// 8 - /Ten2Six {0-255}; // returns number of decimal system in hexadecimal system
// ===== /commands =====



int LedTimer1 = 0;
uint8_t LedState1 = 0;
int LedTimerDuration1 = 200;
int LedTimer2 = 0;
uint8_t LedState2 = 0;
int LedTimerDuration2 = 200;
int LedTimer3 = 0;
uint8_t LedState3 = 0;
int LedTimerDuration3 = 200;
int LedTimer4 = 0;
uint8_t LedState4 = 0;
int LedTimerDuration4 = 200;

uint8_t IsIncludeString(char * mainString, char * example, uint8_t main_length, uint8_t example_length)
{
	uint8_t isGetIn = 0;
	uint8_t j = 0;
	uint8_t i = 0;
	
	main_length--;
	example_length--;
	
	for(j; j < main_length; j++)
	{
		if(isGetIn)
		{
			i++;
			if( i >= example_length)
				break;
			if(mainString[j] != example[i])
				return 0;
		}
		
		if(mainString[j] == example[0])
		{
			isGetIn = 1;
		}
	}
	if(isGetIn == 1)
		return 1;
}

void SysTick_Handler(void)
{
	if(LedTimer1 > 0 && LedState1 >= 0)
	{
		LedTimer1--;
	}
	else
	{
		if(LedState1 == 0)
		{
			LedState1 = 1;
			LedTimer1 = LedTimerDuration1;
			Green_on();
		}
		else
		{
			LedState1 = 0;
			LedTimer1 = 500;
			Green_off();
		}
	}

	
	if(LedTimer2 > 0 && LedState2 >= 0)
	{
		LedTimer2--;
	}
	else
	{
		if(LedState2 == 0)
		{
			LedState2 = 1;
			LedTimer2 = LedTimerDuration2;
			Orange_on();
		}
		else
		{
			LedState2 = 0;
			LedTimer2 = 500;
			Orange_off();
		}
	}

	
	if(LedTimer3 > 0 && LedState3 >= 0)
	{
		LedTimer3--;
	}
	else
	{
		if(LedState3 == 0)
		{
			LedState3 = 1;
			LedTimer3 = LedTimerDuration3;
			Red_on();
		}
		else
		{
			LedState3 = 0;
			LedTimer3 = 500;
			Red_off();
		}
	}

	
	if(LedTimer4 > 0 && LedState4 >= 0)
	{
		LedTimer4--;
	}
	else
	{
		if(LedState4 == 0)
		{
			LedState4 = 1;
			LedTimer4 = LedTimerDuration4;
			Blue_on();
		}
		else
		{
			LedState4 = 0;
			LedTimer4 = 500;
			Blue_off();
		}
	}
}




void send_to_uart(uint8_t data)
{
	while(!(USART2->SR & USART_SR_TC));
	USART2->DR=data;
}
void send_str(char * string)
{
	uint8_t i=0;
	while(string[i])
	{
		send_to_uart(string[i]);
		i++;
	}
}
void SetBlinkDelay(char led, int delay)
{
	switch(led)
	{
		case '1':
		LedTimerDuration1 = delay;
		break;


		case '2':
		LedTimerDuration2 = delay;
		break;


		case '3':
		LedTimerDuration3 = delay;
		break;


		case '4':
		LedTimerDuration4 = delay;
		break;
	}
}
void SwitchBlink(char led, uint8_t state)
{
	switch(led)
	{
		case '1':
		LedState1 = state - 1;
		break;


		case '2':
		LedState2 = state - 1;
		break;


		case '3':
		LedState3 = state - 1;
		break;


		case '4':
		LedState4 = state - 1;
		break;
	}
}
char DigitToHex(int N)
{
  switch (N)
  {
    case 0  : return('0'); break;
    case 1  : return('1'); break;
    case 2  : return('2'); break;
    case 3  : return('3'); break;
    case 4  : return('4'); break;
    case 5  : return('5'); break;
    case 6  : return('6'); break;
    case 7  : return('7'); break;
    case 8  : return('8'); break;
    case 9  : return('9'); break;
    case 10 : return('A'); break;
    case 11 : return('B'); break;
    case 12 : return('C'); break;
    case 13 : return('D'); break;
    case 14 : return('E'); break;
    case 15 : return('F'); break;
    default : return('?');
  }
}
void MyIntToHex(int Num)
{
  char Res[5] = "?";
  int N = Num;
  int i = 1;
  int X;
  while (N > 0)
  {
    i++;
    X = N % 16;
    N = N / 16;
    if (X < 16) 
			Res[i] = DigitToHex(X);
  }

  send_str(Res);
  //for (int j = i; j <= 4; j++) Res[j] = '0'; ??
}  

// call when the command has completed
uint8_t CheckCommand()
{
	
	if(strcmp(uart2_rx_buf, "LedBlink delay") == 0)
	{
		if(uart2_rx_buf[15] == '{')
		{
			char delay_char[16];
			int delay = 0;
			uint8_t i = 16;
			
			for(i = 0 ; i < 16; i++)
				delay_char[i] = 0x00;
			
			for(i = 16 ; i < 38; i++)
			{
				if(uart2_rx_buf[i] == '}')
					break;
				delay_char[i - 16] = uart2_rx_buf[i];
			}
			delay = atoi(delay_char);

			if(uart2_rx_buf[i + 2] == '[')
			{
				int j = i + 2 + 1;
				for(j; j < i + 2 + 32; j++)
				{
					SetBlinkDelay(uart2_rx_buf[j], delay);
				}
				return 1; // successful
			}
		}
	}
	else if(strcmp(uart2_rx_buf, "LedBlink switch") == 1)
	{
		if(strcmp(uart2_rx_buf, "LedBlink switch on") == 1)
		{
			if(uart2_rx_buf[19] == '[')
			{
				int j = 19 + 1;
				for(j; j < 19 + 16; j++)
				{
					SwitchBlink(uart2_rx_buf[j], 1);
				}
				return 1; // successful
			}
		}
		else if(strcmp(uart2_rx_buf, "LedBlink switch off") == 1)
		{
			if(uart2_rx_buf[20] == '[')
			{
				int j = 20 + 1;
				for(j; j < 20 + 16; j++)
				{
					SwitchBlink(uart2_rx_buf[j], 0);
				}
				return 1; // successful
			}
		}
	}
	else if(strcmp(uart2_rx_buf, "Ten2Six") == 1)
	{
		if(uart2_rx_buf[8] == '{')
		{
			char num_char[3];
			uint8_t num = 0;
			int j = 8 + 1;
			for(j; j < 8 + 3; j++)
			{
				num_char[j - 9] = uart2_rx_buf[j];
			}
			num = atoi(num_char);

			MyIntToHex(num);

			return 1; // successful
		}
	}

	return 0; // fail 

}

void ClearBuffet()
{
	memset(uart2_rx_buf, 0, sizeof(uart2_rx_buf)); //Очищаем буфер
	uart2_rx_bit=0; //Сбрасываем счетчик
}

void WriteBuffer()
{
	char uart_data;
	USART2->DR = USART2->DR; //Echo по приему, символ отправленный в консоль вернется
	uart_data=USART2->DR; //Считываем то что пришло в переменную..
	if(uart_data == '/')
	{
		isReadCommand = 1;
	}
	else if(isReadCommand == 1)
	{
		uart2_rx_buf[uart2_rx_bit]=USART2->DR; 
		uart2_rx_bit++;
		if(uart_data == ';')
		{
			isReadCommand = 0;
			CheckCommand();
			ClearBuffet();
		}
	}
}




void USART2_IRQHandler(void)
{
	if (USART2->SR & USART_SR_RXNE) //Проверяем, прило ли чтонибудь в UART
	{
		WriteBuffer();
	}
}

void SendString_to_USART (const char *str)
{
	while(*str != '\0')
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        USART_SendData(USART2, *str++);
	}
}

