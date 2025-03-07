#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t num;

int main(void)
{


/********************初始化********************/
		OLED_Init();
		Timer_Init();
/********************初始化********************/

		OLED_ShowString(1,3,"Num: ");
		OLED_ShowString(2,3,"Cnt: ");
	
/********************功能********************/
	while(1)
	{
		OLED_ShowNum(1,8,num,4);
		OLED_ShowNum(2,8,TimerCounter(),4);
	}	
/********************功能********************/
		
}


/********************定时器********************/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
/********************定时器********************/
