#include "stm32f10x.h"                  // Device header

void LightSensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;    					//GPIO初始化结构体定义
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 		//GPIO外设时钟开启
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;					//选择引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     		//CPU每秒时钟
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//初始化
}

uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12); //无输入是1

}