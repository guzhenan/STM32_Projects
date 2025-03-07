#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{

/****************************时钟初始化****************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);   //TIM2时钟外设使能	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
/****************************时钟初始化****************************/
	
/****************************地址重映射****************************/
//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
//GPIO_PinRemapConfig( GPIO_Remap_SWJ_JTAGDisable,ENABLE);
/****************************地址重映射****************************/	
	
/****************************GPIO初始化****************************/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽输出 这样才能将引脚的控制权交给片上外设
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
/****************************GPIO初始化****************************/
	
	
	
/****************************时基单元初始化****************************/		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;			 //ARR 重装器
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36-1;			//PSC 预分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
/****************************时基单元初始化****************************/	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update); 
	
	
/****************************输出比较器初始化****************************/	
	TIM_OCInitTypeDef 	TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);     							//初始化结构体 默认值为0
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;				//输出比较的极性
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; 			//输出使能
	TIM_OCInitStruct.TIM_Pulse =  0;									//设置CCR
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);                               //设置通道CH
/****************************输出比较器初始化****************************/	
	TIM_Cmd(TIM2, ENABLE);									 //时钟生效 PWM的波形就能通过PA输出了
}

void PWM_SetCompare3(uint16_t compare)  //在运行过程中设置CCR
{
	TIM_SetCompare3(TIM2, compare);
}
