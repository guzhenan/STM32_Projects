#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;    							//GPIO初始化结构体定义
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 	//GPIO外设时钟开启
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;						//选择引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //CPU每秒时钟
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	int count=10;
	while(count)
	{	
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);
		Delay_ms(100);
		GPIO_SetBits(GPIOA,GPIO_Pin_10);
		Delay_ms(700);
		count--;
	}
	count=10;
		while(count)
	{	
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);
		Delay_ms(100);
		GPIO_SetBits(GPIOA,GPIO_Pin_10);
		Delay_ms(300);
		count--;
	}
	
		while(1)
	{	
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);
		Delay_ms(100);
		GPIO_SetBits(GPIOA,GPIO_Pin_10);
		Delay_ms(100);
	}
}
