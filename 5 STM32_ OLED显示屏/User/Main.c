#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"



int main(void)
{


/********************初始化********************/
OLED_Init();
/********************初始化********************/


	
/********************功能********************/
OLED_ShowString(1, 3, "HelloWorld!");
OLED_ShowSignedNum(2,3,100,3);
OLED_ShowBinNum(3,3,0xFFFF,16);
/********************功能********************/
		
}
