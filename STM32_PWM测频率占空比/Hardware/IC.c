#include "stm32f10x.h"                  // Device header

void IC_Init(void)
{
/****************************时钟初始化****************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
/****************************时钟初始化****************************/



/****************************GPIO初始化****************************/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
/****************************GPIO初始化****************************/


/****************************时基单元初始化****************************/		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65536-1;			 //ARR 重装器
	TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;			//PSC 预分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	TIM_InternalClockConfig(TIM3);
/****************************时基单元初始化****************************/
	TIM_ClearFlag(TIM3,TIM_FLAG_Update); 
/***************************输入捕获单元****************************/
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;                 //通道1
	TIM_ICInitStruct.TIM_ICFilter=0xf;							//值越大噪声越小
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;		//上升触发
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;			//不分频
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI; 	//直连
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	
	TIM_PWMIConfig(TIM3, &TIM_ICInitStruct);
/***************************输入捕获单元****************************/


/***************************触发源从模式选择****************************/
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);    
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
/***************************触发源从模式选择****************************/
	TIM_Cmd(TIM3, ENABLE);
}

uint32_t IC_GetFreq(void)   
{
	//Fc = 72M / (PSC+1)
	return 1000000 / TIM_GetCapture1(TIM3) + 1; 	//测周法
}


uint32_t IC_GetDuty(void)
{
	return  (TIM_GetCapture2(TIM3) * 100) / TIM_GetCapture1(TIM3)+1 ;   
	//整个脉冲周期的计数值存在CCR1里 ; 高电平计数值数存在CCR2里
}

