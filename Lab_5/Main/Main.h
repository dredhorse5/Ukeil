
  
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

    #define PORTD12 12
    #define PORTD13 13
    #define PORTD14 14
		