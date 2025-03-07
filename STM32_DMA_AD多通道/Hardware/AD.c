#include "stm32f10x.h"                  // Device header
uint16_t AD_Value[4];               

void AD_Init(void)
{
/********************时钟********************/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  	//APB2 , 6分频   则ADC_CLK = 72M HZ / 6 = 12M HZ 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);			//开启AHB时钟
/********************时钟********************/

/********************GPIO********************/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;  		//模拟输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3; //选中4个GPIO输入
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
/********************GPIO********************/


/********************ADC规则组设置********************/
	 //点四个规则组菜单
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	//点四个规则组菜单
/********************ADC规则组设置********************/


/********************ADC配置********************/
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent; 					//独立模式;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; 				//数据右对其
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  	//触发源选择软件触发
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;    				//非连续模式
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;							//非扫描模式
	ADC_InitStruct.ADC_NbrOfChannel = 4;								//选择通道数量
	ADC_Init(ADC1,&ADC_InitStruct);
	

/********************ADC设置********************/


	
	
/********************DMA设置********************/
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)AD_Value;		 //存储器地址
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //每次传输数据大小
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;			 //是否自增
	
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;	//外设地址
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;//每次接收数据大小
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//是否自增
	
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_BufferSize = 4;       						//DMA要传送的数据个数
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;				   //外设是源地址还是目的
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;					   //硬件触发还是软件触发
	 
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	
/********************DMA设置********************/


/********************ADC&DMA电源开关********************/
	DMA_Cmd(DMA1_Channel1 ,ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
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



void AD_GetValue(void)  //读取ADC数据寄存器
{


	DMA_Cmd(DMA1_Channel1 ,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, 4);     	 //传输计数值 一次传输多少个数据 必须在DMA关闭下设置
	DMA_Cmd(DMA1_Channel1 ,ENABLE);					 //开启DMA传送
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//如果是连续转换模式只需要触发一次可把这个放到初始化的最后，且不需要判断标志位了
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);  //等待完成传输
	DMA_ClearFlag(DMA1_FLAG_TC1);//清除标志位
	
	
	
} 

