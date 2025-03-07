#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t AD0;
uint16_t AD1;
uint16_t AD2;
uint16_t AD3;

float AD_0;
float AD_1;
float AD_2;
float AD_3;

int main(void)
{


/********************初始化********************/
	OLED_Init();
	AD_Init();
/********************初始化********************/


	
/********************功能********************/
	OLED_ShowString(1, 3, "AD0:0.00V");
	OLED_ShowString(2, 3, "AD1:0.00V");
	OLED_ShowString(3, 3, "AD2:0.00V");
	OLED_ShowString(4, 3, "AD3:0.00V");
	while(1)
	{
	
		AD_0 = AD_GetValue(ADC_Channel_0);
		AD_1 = AD_GetValue(ADC_Channel_1);
		AD_2 = AD_GetValue(ADC_Channel_2);
		AD_3 = AD_GetValue(ADC_Channel_3);
		AD_0 = (float)AD_0 / 4095 * 3.3;
		AD_1 = (float)AD_1 / 4095 * 3.3;
		AD_2 = (float)AD_2 / 4095 * 3.3;
		AD_3 = (float)AD_3 / 4095 * 3.3;
		
		OLED_ShowNum(1, 7, AD_0, 1);  	//整数部分
		OLED_ShowNum(1, 9, (uint16_t)AD_0 * 100 % 100, 2);  //小数部分、
		
		OLED_ShowNum(2, 7, AD_1, 1);  //整数部分
		OLED_ShowNum(2, 9, (uint16_t)AD_1 * 100 % 100, 2);  //小数部分
		
		OLED_ShowNum(3, 7, AD_2, 1);  //整数部分
		OLED_ShowNum(3,9, (uint16_t)AD_2 * 100 % 100, 2);  //小数部分
		
		OLED_ShowNum(4, 7, AD_3, 1);  //整数部分
		OLED_ShowNum(3, 9, (uint16_t)AD_3 * 100 % 100, 2);  //小数部分
		
		Delay_ms(100);
	}
	
/********************功能********************/
		
}
