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

	OLED_ShowString(1,1,"RxData");
	while(1)
	{	
		if(Serial_GetRxFlag()==1)
		{
			OLED_ShowHexNum(2,1,Serial_RxPakage[0],2);
			OLED_ShowHexNum(2,4,Serial_RxPakage[1],2);
			OLED_ShowHexNum(2,7,Serial_RxPakage[2],2);
			OLED_ShowHexNum(2,10,Serial_RxPakage[3],2);
		}
		
	}
/********************功能********************/
		
}
