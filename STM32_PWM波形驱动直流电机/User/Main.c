#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "KEY.h"
#include "TB6612.h"
int speed;
uint8_t keynum;
float degree;  //旋转角度
int main(void)
{


/****************************初始化****************************/
					OLED_Init();
					KEY_Init();
					TB6612_Init();
/****************************初始化****************************/


	
/****************************功能****************************/
	OLED_ShowString(1, 3, "Speed:");
	

	while(1)
	{
		keynum=KEY_GetNum();
		if(keynum)
		{	
			if(speed>100) speed=-100;
			speed+=10;
		}
		TB6612_SetSpeed(speed);                        
		OLED_ShowSignedNum(1,9,speed,3);
		
	}
/****************************功能****************************/
		
}
