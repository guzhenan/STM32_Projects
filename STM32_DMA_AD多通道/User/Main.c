#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"



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
		AD_GetValue(); 
//		AD_0=(float)AD_Value[0] / 4095 * 3.3;  //保存0-3.3 之间的浮点数
//		AD_1=(float)AD_Value[1] / 4095 * 3.3;
//		AD_2=(float)AD_Value[2] / 4095 * 3.3;
//		AD_3=(float)AD_Value[3] / 4095 * 3.3;
//		
//		
//		OLED_ShowNum(1, 7, (float)AD_Value[0] / 4095 * 3.3, 1);  	//整数部分
//		OLED_ShowNum(1, 9, (uint16_t)(AD_0* 100) % 100, 2);  //小数部分、
//		
//		OLED_ShowNum(2, 7, (float)AD_Value[1] / 4095 * 3.3, 1);  //整数部分
//		OLED_ShowNum(2, 9, (uint16_t)(AD_1 * 100) % 100, 2);  //小数部分
//		
//		OLED_ShowNum(3, 7, (float)AD_Value[2] / 4095 * 3.3, 1);  //整数部分
//		OLED_ShowNum(3,9, (uint16_t)(AD_2 * 100) % 100, 2);  //小数部分
//		
//		OLED_ShowNum(4, 7, (float)AD_Value[3] / 4095 * 3.3, 1);  //整数部分
//		OLED_ShowNum(3, 9, (uint16_t)(AD_3 * 100) % 100, 2);  //小数部分


		OLED_ShowNum(1,7,AD_Value[0],4);
		OLED_ShowNum(2,7,AD_Value[1],4);
		OLED_ShowNum(3,7,AD_Value[2],4);
		OLED_ShowNum(4,7,AD_Value[3],4);
		Delay_ms(100);
	}
	
/********************功能********************/
		
}
