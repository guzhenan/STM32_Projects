#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t Rx_DATA;

int main(void)
{


/********************初始化********************/
	OLED_Init();
	Serial_Init();
/********************初始化********************/


	
/********************功能********************/

	while(1)
	{	
		if(Serial_GetRxFlag()==1)
		{
			Rx_DATA=Serial_GetRxData();
			Serial_SendByte(Rx_DATA);
			OLED_ShowHexNum(1,1,Rx_DATA,2);
		}
		
	}
/********************功能********************/
		
}
