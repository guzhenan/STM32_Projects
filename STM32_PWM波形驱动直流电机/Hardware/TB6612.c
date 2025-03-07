#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void TB6612_Init(void)
{
/****************************GPIO初始化****************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4 | GPIO_Pin_5;  //初始化方向控制的引脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
/****************************GPIO初始化****************************/	
	PWM_Init();
}

void TB6612_SetSpeed(uint8_t speed)         //正反转速度方向
{
	if(speed>=0) //正转
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);  	//H
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);	//L
		PWM_SetCompare3(speed);
		
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);	//H
		GPIO_SetBits(GPIOA,GPIO_Pin_5);  	//L     
		PWM_SetCompare3(-speed);
		
	}
}

