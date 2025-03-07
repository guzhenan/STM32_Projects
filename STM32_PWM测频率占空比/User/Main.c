#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "KEY.h"
#include "PWM.h"
#include "IC.h"
uint16_t p=72,c=1;
uint8_t keynum;
int main(void)
{


/****************************初始化****************************/
					OLED_Init();
					KEY_Init();
					PWM_Init();
					IC_Init();
/****************************初始化****************************/


	
/****************************功能****************************/
	OLED_ShowString(1, 3, "Freq:00000 HZ");
	OLED_ShowString(2, 3, "Duty:00%");
	PWM_SetPrescaler(14400);   			//Freq = 72M / (PSC+1) / 100 = 1KHZ
	PWM_SetCompare1(10);      	 		//Duty = CCR / 100 
	while(1)
	{	
		OLED_ShowNum(1,8,IC_GetFreq(),5);
		OLED_ShowNum(2,8,IC_GetDuty(),2);
		
	}
/****************************功能****************************/
		
}
