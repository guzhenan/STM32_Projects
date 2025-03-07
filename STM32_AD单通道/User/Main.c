#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
uint16_t AD_Value;
float valtage;
int main(void)
{


/********************初始化********************/
	OLED_Init();
	AD_Init();
/********************初始化********************/


	
/********************功能********************/
	OLED_ShowString(1, 3, "ADValue:");
	OLED_ShowString(2, 3, "Voltage:0.00V");
	while(1)
	{
		AD_Value=AD_GetValue();
		valtage = (float)AD_Value/4095 * 3.3;
		OLED_ShowNum(1,11,AD_Value,5);
		OLED_ShowNum(2,11,AD_Value,1);  					//显示整数
		OLED_ShowNum(2,13,(uint16_t)(valtage*100)%100,2);	//取余显示小数部分 浮点数能取余
		Delay_ms(100);
	}
	
/********************功能********************/
		
}
