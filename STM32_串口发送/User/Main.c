#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t Array[] = {0x41,0x42,0x43,0x44};

int main(void)
{


/********************初始化********************/
	OLED_Init();
	Serial_Init();
/********************初始化********************/


	
/********************功能********************/
//	Serial_SendByte(0x42);
//	Serial_SendArray(Array,4);
//	Serial_SendString("HelloWorld!\r\n");
//	Serial_SendNum(1, 1);
//	printf("NUM=%d\r\n",1);
//	Serial_Printf("你好，世界");
	while(1)
	{	
		
	}
/********************功能********************/
		
}
