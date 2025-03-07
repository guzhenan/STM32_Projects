#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "SG90.h"
#include "KEY.h"
uint8_t keynum;
float degree;  //旋转角度
int main(void)
{


/****************************初始化****************************/
					OLED_Init();
					SG90_Init();
					KEY_Init();
/****************************初始化****************************/


	
/****************************功能****************************/
	OLED_ShowString(1, 3, "Degree:");
	
	while(1)
	{
		keynum=KEY_GetNum();
		if(keynum) 
		{
			degree+=30;
			if(degree>180) degree = 0;  //大于180度转到0度
		}
		SG90_SetAngle(degree); //设置转动的角度
		OLED_ShowSignedNum(1,10,degree,3);
	}
/****************************功能****************************/
		
}
