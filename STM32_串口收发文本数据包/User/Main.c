#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "LED.h"
#include <string.h>
uint8_t Rx_DATA;

int main(void)
{


/********************初始化********************/
	OLED_Init();
	Serial_Init();
	LED_Init();  
/********************初始化********************/


	
/********************功能********************/
//strcmp(s1,s2)的功能
//如果返回值 < 0：表示第一个不匹配的字符在第一个字符串中的ASCII值小于第二个字符串中的对应字符。
//如果返回值为 0：表示两个字符串相等。
//如果返回值 > 0：表示第一个不匹配的字符在第一个字符串中的ASCII值大于第二个字符串中的对应字符
	OLED_ShowString(1,1,"RxData");
	OLED_ShowString(3,1,"TxData");
	while(1)
	{	
		if(Serial_GetRxFlag()==1)
		{
			if(strcmp(Serial_RxPakage,"LED_ON")==0)
			{
				LED1_ON();
				OLED_ShowString(2,1,"                ");
				OLED_ShowString(4,1,"                ");
				OLED_ShowString(2,1,Serial_RxPakage);
				OLED_ShowString(4,1,"LED_ON_OK");
			}
			else if(strcmp(Serial_RxPakage,"LED_OFF")==0)
			{
				OLED_ShowString(2,1,"                ");
				OLED_ShowString(4,1,"                ");
				LED1_OFF();
				OLED_ShowString(2,1,Serial_RxPakage);
				OLED_ShowString(4,1,"LED_OFF_OK");
			}
			else
			{
				OLED_ShowString(2,1,"                ");
				OLED_ShowString(4,1,"                ");			
				OLED_ShowString(2,1,Serial_RxPakage);
				OLED_ShowString(4,1,"Error_Value");
			}
		}
		
	}
/********************功能********************/
		
}
