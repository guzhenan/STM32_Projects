#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
/********************时钟********************/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  	//APB2 , 6分频   则ADC_CLK = 72M HZ / 6 = 12M HZ 
/********************时钟********************/

/********************GPIO********************/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;  		//模拟输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
/********************GPIO********************/


/********************ADC规则组设置********************/
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5); 
	
/********************ADC规则组设置********************/


/********************ADC配置********************/
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent; 					//独立模式;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; 				//数据右对其
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  	//触发源选择软件触发
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;    				//非连续模式
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;							//非扫描模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;								//选择通道数量
	ADC_Init(ADC1,&ADC_InitStruct);
/********************ADC设置********************/

/********************ADC电源开关********************/
	ADC_Cmd(ADC1, ENABLE);
/********************ADC电源开关********************/
	ADC_ResetCalibration(ADC1); 			  							//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);	 
	/*
	返回ADC校准的状态  
	0: 校准寄存器已初始化；
	1：初始化校准寄存器
	*/
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);	


	
}//MODE： 单次转换非扫描模式	



uint16_t AD_GetValue(void)  //读取ADC数据寄存器
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//如果是连续转换模式只需要触发一次可把这个放到初始化的最后，且不需要判断标志位了
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//获取标志位状态 看看转换是否完成 1:代表完成
	return ADC_GetConversionValue(ADC1); 	//AD转换结果 读取DR寄存器 且自动清除EOC标志位After Read
} 
