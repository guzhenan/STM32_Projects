#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

uint8_t i;

int main(void)
{


/********************初始化********************/
					OLED_Init();
					PWM_Init();					
/********************初始化********************/


	
/********************功能********************/
	OLED_ShowString(1, 3, "HelloWorld!");
	while(1)
	{
		for(i=0;i<=100;i++)
		{	PWM_SetCompare1(i);Delay_ms(10);}
		
		for(i=0;i<=100;i++)
		{	PWM_SetCompare1(100-i);Delay_ms(10);}
	}
/********************功能********************/
		
}
