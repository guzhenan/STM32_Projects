#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{

/****************************时钟初始化****************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);   //TIM2时钟外设使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);   //TIM2时钟外设使能		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
/****************************时钟初始化****************************/
	
/****************************地址重映射****************************/
//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
//GPIO_PinRemapConfig( GPIO_Remap_SWJ_JTAGDisable,ENABLE);
/****************************地址重映射****************************/	
	
/****************************GPIO初始化****************************/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽输出 这样才能将引脚的控制权交给片上外设
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
/****************************GPIO初始化****************************/
	
	
	
/****************************时基单元初始化****************************/		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=20000-1;			 //ARR 重装器
	TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;			//PSC 预分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
/****************************时基单元初始化****************************/	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update); 
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	
/****************************输出比较器初始化****************************/	
	TIM_OCInitTypeDef 	TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);     							//初始化结构体 默认值为0
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;				//输出比较的极性
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; 			//输出使能
	TIM_OCInitStruct.TIM_Pulse =  0;									//设置CCR
	
	 //设置通道CH
	TIM_OC1Init(TIM2, &TIM_OCInitStruct); 
	TIM_OC2Init(TIM2, &TIM_OCInitStruct); 
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);                             
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);
	
	TIM_OC1Init(TIM4, &TIM_OCInitStruct); 
	TIM_OC2Init(TIM4, &TIM_OCInitStruct); 
	TIM_OC3Init(TIM4, &TIM_OCInitStruct);                             
	TIM_OC4Init(TIM4, &TIM_OCInitStruct);
	//设置通道CH
/****************************输出比较器初始化****************************/	
	TIM_Cmd(TIM2, ENABLE);									 //时钟生效 PWM的波形就能通过PAx输出了
	TIM_Cmd(TIM4, ENABLE);
}


void PWM1_SetCompare1(uint16_t compare)  //在运行过程中设置CCR
{
	TIM_SetCompare1(TIM2, compare);
}
void PWM1_SetCompare2(uint16_t compare)  //在运行过程中设置CCR
{
	TIM_SetCompare2(TIM2, compare);
}
void PWM1_SetCompare3(uint16_t compare)  //在运行过程中设置CCR
{
	TIM_SetCompare3(TIM2, compare);
}
void PWM1_SetCompare4(uint16_t compare)  //在运行过程中设置CCR
{
	TIM_SetCompare4(TIM2, compare);
}
/**********************************************************************/
void PWM2_SetCompare1(uint16_t compare)  //在运行过程中设置CCR
{
	TIM_SetCompare1(TIM4, compare);
}
void PWM2_SetCompare2(uint16_t compare)  //在运行过程中设置CCR
{
	TIM_SetCompare2(TIM4, compare);
}
void PWM2_SetCompare3(uint16_t compare)  //在运行过程中设置CCR
{
	TIM_SetCompare3(TIM4, compare);
}
void PWM2_SetCompare4(uint16_t compare)  //在运行过程中设置CCR
{
	TIM_SetCompare4(TIM4, compare);
}
