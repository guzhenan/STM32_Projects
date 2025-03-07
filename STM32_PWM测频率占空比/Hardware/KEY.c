#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"

void KEY_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;  //上拉输入
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);		
}

uint8_t KEY_GetNum(void)  //返回值是8位Char 0-255
{
	uint8_t KeyNum=0;
	/*判断按键1*/
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0)  //读取外部引脚的按下值 0代表按下
	{
			Delay_ms(20);	 //消按键按下的抖动
			while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0); //如果按键一直没有松开则卡在这
			Delay_ms(20);	 //消按下松开的抖动
			KeyNum = 1; 	//按键按下

	}	
	/*按键1*/
		
	
	return KeyNum; 	//返回值代表哪个按键生效 等于0无按键按下
}
